#include <stdlib.h>
#include <string.h>
#include "minimize.h"
#include "diccionario_pares.h"

/* Devuelve las conexiones desde q al resto de estados usando el simbolo s
Parámetros
    afnd -> autómata inicial.
    numEstados -> número de estados del afnd.
    q -> estado actual.
    s -> símbolo procesado.
Return
    int* con las conexiones que hay desde q con el símbolo s (formato de 1s y 0s). */

int *AFNDConexionesEstadoSimbolo(AFND * afnd, int numEstados, int q, int s){
  int i;
  int *conexiones;

  /* Reservamos un array que contendrá las conexiones del estado con el símbolo dado. */
  conexiones = (int *)malloc(sizeof(int)*numEstados);
  if (conexiones == NULL){
    return NULL;
  }

  /* Para cada estado del AFND comprobamos si hay conexión con el símbolo dado desde el
  estado actual hasta este y lo añadimos a la posición correspondiente del array. */
  for (i = 0; i < numEstados; i++){
    conexiones[i] =  AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, q, s, i);
  }

  /* Devolvemos el array de conexiones. */
  return conexiones;
}

/* Devuelve el estado al que se llega desde q usando el simbolo s
Parámetros
    afd -> autómata determinista inicial.
    q -> estado actual.
    s -> símbolo procesado.
Return
    int con el indice del estado destino en el automata, o -1 si no lo hay.
*/
int AFDConexionEstadoSimbolo(AFND *afd, int q, int s){
  int i;
  for (i = 0; i < AFNDNumEstados(afd); i++){
    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, q, s, i)){
      return i;
    }
  }

  return -1;
}


/* Devuelve el indice que tiene un estado en nuestro array de estados accesibles
Parámetros
    p -> estado cuyo indice en el array de accesibles queremos conocer.
    estadosAccesibles -> array de todos los estados accesibles
    numAccesibles -> numero de elementos en el array de accesibles
Return
    int con el indice del estado en el array, o -1 si no está
*/
int indiceEstadoAccesible(int p, int* estadosAccesibles, int numAccesibles){
  int i;
  for (i = 0; i < numAccesibles; i++){
    if(estadosAccesibles[i] == p){
      return i;
    }
  }

  return -1;
}

int* estadosAccesibles(AFND* afd){
  int numEstados, numSimbolos, aux;
  int i, j;
  int *listaAccesibles, *conexiones;
  LList *descubiertos;


  numEstados = AFNDNumEstados(afd);
  numSimbolos = AFNDNumSimbolos(afd);

  listaAccesibles = (int *)calloc(numEstados, sizeof(int));
  if (listaAccesibles == NULL){
    printf("Error al reservar memoria para el array de accesibles\n");
    return NULL;
  }

  aux = AFNDIndiceEstadoInicial(afd);
  descubiertos = createLList();
  if (descubiertos == NULL){
    printf("Error al reservar memoria para la lista de descubiertos\n");
    free(listaAccesibles);
    return NULL;
  }

  addToLList(descubiertos, aux);

  while (!isLListVoid(descubiertos)){
    aux = getLListValue(descubiertos, 0);
    removeLListFirstElem(descubiertos);

    /* Marcamos el estado como accesible */
    listaAccesibles[aux] = 1;

    for (i = 0; i < numSimbolos; i++){
      /* Cogemos todas las conexiones del estado que estamos explorando a partir de un simbolo*/
      conexiones = AFNDConexionesEstadoSimbolo(afd, numEstados, aux, i);
      for (j = 0; j < numEstados; j++){
        /* Añadimos todos los estados no explorados a la lista */
        if(conexiones[j] == 1 && listaAccesibles[j] == 0){
          addToLList(descubiertos, j);
        }
      }
      free(conexiones);
    }
  }

  deleteLList(descubiertos);
  return listaAccesibles;
}


void marcarDistinguiblesRecursivo(int p, int q, int **matriz, TupleDict *dict){
  TupleNode *list, *node;

  if (dict == NULL){
    return;
  }

  list = getTupleDictValue(dict, p, q);
  if (list == NULL){
    return;
  }

  node = list;
  for(node = list; node != NULL; node = getNextTupleNode(node)){
    marcarDistinguiblesRecursivo(node->a, node->b, matriz, dict);
    matriz[node->a][node->b] = 1;
    matriz[node->b][node->a] = 1;
  }
}

void *estadosDistinguibles(AFND* afd, int* estadosAccesibles, int numAccesibles){
  int **matriz, i, j, k, tipo1, tipo2, numSimbolos;
  int dst1, dst2, marcado;
  TupleDict *dict;
  TupleNode *list;

  /* Aunque la matriz sea simétrica, usamos una matriz cuadrada para simplificar*/
  matriz = (int **)malloc(sizeof(int*)*numAccesibles);
  if (matriz == NULL){
    printf("Error al reservar la matriz\n");
    return NULL;
  }

  for (i=0; i<numAccesibles; i++){
    matriz[i] = (int *)calloc(numAccesibles, sizeof(int));
    if (matriz[i] == NULL){
      for (; i>0; i--){
        free(matriz[i-1]);
      }
      printf("Error al reservar la matriz\n");
      return NULL;
    }
  }

  /* En primer lugar, comparamos todos los pares de estados
  y marcamos como distinguibles aquellos pares en los que
  uno es final y el otro no */
  for (i=0; i<numAccesibles; i++){
    tipo1 = AFNDTipoEstadoEn(afd, estadosAccesibles[i]);
    for (j=i+1; j<numAccesibles; j++){
      tipo2 = AFNDTipoEstadoEn(afd, estadosAccesibles[j]);
      /* Si uno es final y el otro no, marcamos como distinguibles */
      if((tipo1 == FINAL || tipo1 == INICIAL_Y_FINAL) != (tipo2 == FINAL || tipo2 == INICIAL_Y_FINAL)){
        matriz[i][j] = 1;
        matriz[j][i] = 1;
      }
    }
  }


  /* Una vez tenemos marcados como distinguibles los finales y no finales, comenzamos */
  dict = NULL;
  list = NULL;
  numSimbolos = AFNDNumSimbolos(afd);
  for (i=0; i<numAccesibles; i++){
    for (j=i+1; j<numAccesibles; j++){
      /* Para cada par de estados (p, q)*/
      for (k=0, marcado=0; k<numSimbolos; k++){
        /* Si para algún símbolo k, delta(p, k), delta(q, k) marcados, marcamos (p, q) */
        dst1 = AFDConexionEstadoSimbolo(afd, estadosAccesibles[i], k);
        dst2 = AFDConexionEstadoSimbolo(afd, estadosAccesibles[j], k);



        /* Estos son los indices en el automata inicial, no en nuestro array de accesibles. Los transformamos */
        dst1 = indiceEstadoAccesible(dst1, estadosAccesibles, numAccesibles);
        dst2 = indiceEstadoAccesible(dst2, estadosAccesibles, numAccesibles);
        if (dst1 == -1 || dst2 == -1){
          printf("Error grave. Hemos encontrado un estado que no estaba en nuestra lista de accesibles.\n");
          exit(-1);
        }

        if (matriz[dst1][dst2] == 1 || matriz[dst2][dst1] == 1){
          matriz[i][j] = 1;
          matriz[j][i] = 1;
          marcado=1;
          /* Cogemos la lista de dependencias y marcamos de forma recursiva */
          marcarDistinguiblesRecursivo(i, j, matriz, dict);
          break;
        }

      }


      if (marcado == 0){
        /* Si estos dos simbolos no son distinguibles (hasta ahora),
        para cada simbolo k, agregamos (p, q) a la lista de dependencias de delta(p, k), delta(q, k)
        siempre que estos dos no sean iguales */

        for (k=0, marcado=0; k<numSimbolos; k++){
          dst1 = AFDConexionEstadoSimbolo(afd, estadosAccesibles[i], k);
          dst2 = AFDConexionEstadoSimbolo(afd, estadosAccesibles[j], k);
          /* Estos son los indices en el automata inicial, no en nuestro array de accesibles. Los transformamos */
          dst1 = indiceEstadoAccesible(dst1, estadosAccesibles, numAccesibles);
          dst2 = indiceEstadoAccesible(dst2, estadosAccesibles, numAccesibles);
          if (dst1 == -1 || dst2 == -1){
            printf("Error grave. Hemos encontrado un estado que no estaba en nuestra lista de accesibles.\n");
            exit(-1);
          }

          if (dst1 == dst2){
            continue;
          }

          /* Agregamos (p,q) a la lista de dependencias de (delta(p, k), delta(q, k)) */
          if (dict == NULL){
            list = initTupleNode(i, j);
            dict = initTupleDict(dst1, dst2, list);
          }else{
            list = getTupleDictValue(dict, dst1, dst2);
            if (list != NULL){
              addTupleNode(list, i, j);
            }else{
              list = initTupleNode(i, j);
              addTupleDict(dict, dst1, dst2, list);
            }
          }
        }
      }
    }
  }


  /* Mostramos cuales son distinguibles y cuales no */
  printf("Estados accesibles:\n");
  for (i=0; i<numAccesibles; i++){
    printf("%s\t", AFNDNombreEstadoEn(afd, estadosAccesibles[i]));
  }
  printf("\n");

  for (i=0; i<numAccesibles; i++){
    for (j=0; j<numAccesibles; j++){
      printf("%d\t", matriz[i][j]);
    }
    printf("|%s\n", AFNDNombreEstadoEn(afd, estadosAccesibles[i]));
  }

  destroyTupleDict(dict);
  for (i=0; i<numAccesibles; i++){
    free(matriz[i]);
  }
  free(matriz);

}

void *estadosDistinguibles2(AFND* afd, int* estadosAccesibles, int numAccesibles){
  LList *finales, *noFinales;
  int i, aux;

  finales = createLList();
  noFinales = createLList();

  for (i=0; i<numAccesibles; i++){
    aux = AFNDTipoEstadoEn(afd, estadosAccesibles[i]);
    if (aux == FINAL || aux == INICIAL_Y_FINAL){
      addToLList(finales, estadosAccesibles[i]);
    }else{
      addToLList(noFinales, estadosAccesibles[i]);
    }
  }

  printLList(finales);
  printLList(noFinales);

  deleteLList(finales);
  deleteLList(noFinales);
}
