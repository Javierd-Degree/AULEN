#include "lista_estados.h"
#include "afnd.h"
#include <stdlib.h>

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

void *estadosDistinguibles(AFND* afd, int* estadosAccesibles, int numAccesibles){
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
