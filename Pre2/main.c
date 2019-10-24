#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int index_alf(char* alfabeto, int lenAlfabeto, char c){
  int i;
  for (i = 0; i < lenAlfabeto; i++){
    if (alfabeto[i] == c){
      return i;
    }
  }
  return -1;
}

int* cierre_trans_aux(int*** tabla, int numEstados, int lenAlfabeto, int estado){
  int *estados = tabla[estado][lenAlfabeto-1];
  int *aux, i, j, k;

  for(i=1; i<=estados[0]; i++){
    aux = cierre_trans_aux(tabla, numEstados, lenAlfabeto, estados[i]);

    for(j=1; j<=aux[0]; j++){
      int encontrado = 0;
      for(k=1; k<=estados[0]; k++){
        if(estados[k] == aux[j]){
          encontrado = 1;
          break;
        }
      }
      if(encontrado==0){
        estados[estados[0]] = aux[j];
        estados[0]++;
      }
    }
  }

  return estados;
}

int cierre_trans(int*** tabla, int numEstados, int lenAlfabeto){
  int i, j, k, l ,m;
  int *aux;
  for(i=0; i<numEstados; i++){
    for (j=0; j< lenAlfabeto-1; j++){
      for (k=1; k<=tabla[i][j][0]; k++){
        /* Para cada estado destino añadimos las transiciones lambda */
        aux = cierre_trans_aux(tabla, numEstados, lenAlfabeto, tabla[i][j][k]);
        printf("Desde %d con %d llega a: ", i, j);
        for(l=1; l<=aux[0]; l++){
          printf("%d ", aux[l]);
        }
        printf("\n");
        /* Añadimos solo las no repetidas */
        for(l=1; l<=aux[0]; l++){
          int encontrado = 0;
          for(m=1; m<=tabla[i][j][0]; m++){
            if(tabla[i][j][m] == aux[l]){
              encontrado = 1;
              break;
            }
          }
          if(encontrado==0){
            tabla[i][j][tabla[i][j][0]] = aux[l];
            tabla[i][j][0]++;
          }
        }
      }

    }

  }

}

/*
El fichero consta de:
tamaño del alfabeto, numero de estados, estado inicial y estado final en la primera
línea, separados por espacios.

Alfabeto entero, con las letras seguidas, en la segunda linea.
En las lineas siguientes: estado simbolo recibido y siguiente estado (o -1)
separados con espacios.
*/
void main(int argc, char* argv[]){
  char *alfabeto;
  int lenAlfabeto;
  int numEstados;
  int ***tabla;
  int i, j, k;

  int estadoActual;
  int estadoInicial;
  int *estadosActuales, *estadosActualesAux;
  int estadoFinal;

  if(argc != 3){
    printf("Numero de argumentos incorrecto");
    exit(-1);
  }


  FILE *f;
  f = fopen(argv[1], "r");
  if (f == NULL){
    printf("Error al abrir el archivo");
    exit(-1);
  }

  fscanf(f, "%d %d %d %d\n", &lenAlfabeto, &numEstados, &estadoInicial, &estadoFinal);
  alfabeto = (char*)malloc(sizeof(char)*(lenAlfabeto+1));
  if(alfabeto == NULL){
    printf("Error al reservar memoria para alfabeto\n");
    fclose(f);
    exit(-1);
  }
  fscanf(f, "%s\n", alfabeto);


  /* Reservamos memoria para la tabla de estados actuales */
  estadosActuales = (int*)calloc(numEstados, sizeof(int));
  estadosActuales[estadoInicial] = 1;

  /* Reservamos memoria para la tabla */
  tabla = (int ***)malloc(sizeof(int**)*numEstados);
  if (tabla == NULL){
    printf("Error al reservar memoria para tabla\n");
    free(alfabeto);
    fclose(f);
    exit(-1);
  }

  for(i = 0; i < numEstados; i++){
    tabla[i] = (int **)malloc(sizeof(int*)*lenAlfabeto);
    if (tabla[i] == NULL){
      printf("Error al reservar memoria para tabla\n");
      for(--i; i >= 0; i--){
        free(tabla[i]);
      }
      free(tabla);
      free(alfabeto);
      fclose(f);
      exit(-1);
    }
  }

  /* Escaneamos la tabla entera */
  char temp;
  int *tmpEstados;
  int orgTemp, dstTemp, indexTemp, nEstadosTmp, temp2;
  for(i = 0; i < numEstados*lenAlfabeto; i++){
    fscanf(f, "%d %c %d\n", &orgTemp, &temp, &nEstadosTmp);

    indexTemp = index_alf(alfabeto, lenAlfabeto, temp);
    if (indexTemp == -1){
      printf("La línea %d: %d %c %d es incorrecta, pues el caracter %c no pertenece al alfabeto.\n", i+3, orgTemp, temp, dstTemp, temp);
      for(i = 0; i < numEstados; i++){
        free(tabla[i]);
      }
      free(tabla);
      free(alfabeto);
      fclose(f);
      exit(-1);
    }
    /* Reservamos siempre memoria para todos los estados */
    tmpEstados = (int *)malloc(sizeof(int)*(numEstados+1));
    tmpEstados[0] = nEstadosTmp;
    for(j=1; j<=nEstadosTmp; j++){
      fscanf(f, "%d\n", &temp2);
      tmpEstados[j] = temp2;
    }

    tabla[orgTemp][indexTemp] = tmpEstados;
  }

  fclose(f);

  cierre_trans(tabla, numEstados, lenAlfabeto);

  for(i=0; i < strlen(argv[2]); i++){
    int c = index_alf(alfabeto, lenAlfabeto, argv[2][i]);
    if (c == -1){
      printf("Error: simbolo %c no perteneciente al alfabeto.\n", argv[2][i]);
    }

    int nEstadosActuales = 0;
    estadosActualesAux = (int*)calloc(numEstados, sizeof(int));
    for(j=0; j<numEstados; j++){
      if (estadosActuales[j] == 1){
        tmpEstados = tabla[j][c];
        for(k=1; k<= tmpEstados[0]; k++){
          estadosActualesAux[tmpEstados[k]] = 1;
          nEstadosActuales++;
        }
      }
    }

    free(estadosActuales);
    estadosActuales = estadosActualesAux;

    printf("Leemos %c, la lista de estados actuales es: ", argv[2][i]);
    for(j=0; j<numEstados; j++){
      printf("%d ", estadosActuales[j]);
    }
    printf("\n");
    if (nEstadosActuales == 0){
      printf("Palabra no reconocida\n");
    }
  }

  if (estadosActuales[estadoFinal] != 1){
    printf("Palabra no reconocida: El final es %d\n", estadoFinal);
    printf("La lista de estados actuales es: ");
    for(j=0; j<numEstados; j++){
      printf("%d ", estadosActuales[j]);
    }
  }else{
    printf("Palabra reconocida\n");
    printf("La lista de estados actuales es: ");
    for(j=0; j<numEstados; j++){
      printf("%d ", estadosActuales[j]);
    }
  }



  /* Liberamos la memoria */
  for(i = 0; i < numEstados; i++){
    free(tabla[i]);
  }
  free(tabla);
  free(alfabeto);
}
