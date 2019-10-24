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
  char **tabla;
  int i;

  int estadoActual;
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

  fscanf(f, "%d %d %d %d\n", &lenAlfabeto, &numEstados, &estadoActual, &estadoFinal);
  alfabeto = (char*)malloc(sizeof(char)*(lenAlfabeto+1));
  if(alfabeto == NULL){
    printf("Error al reservar memoria para alfabeto\n");
    fclose(f);
    exit(-1);
  }
  fscanf(f, "%s\n", alfabeto);


  /* Reservamos memoria para la tabla */
  tabla = (char **)malloc(sizeof(char*)*numEstados);
  if (tabla == NULL){
    printf("Error al reservar memoria para tabla\n");
    free(alfabeto);
    fclose(f);
    exit(-1);
  }

  for(i = 0; i < numEstados; i++){
    tabla[i] = (char *)malloc(sizeof(char)*lenAlfabeto);
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
  int orgTemp, dstTemp, indexTemp;
  for(i = 0; i < numEstados*lenAlfabeto; i++){
    fscanf(f, "%d %c %d\n", &orgTemp, &temp, &dstTemp);
    indexTemp = index_alf(alfabeto, lenAlfabeto, temp);
    if (indexTemp == -1){
      printf("La línea %d: %d %c %d es incorrecta, pues el caracter %c no pertenece al alfabeto.\n", i+3, orgTemp, temp, dstTemp, temp);
      for(i = 0; i < numEstados; i++){
        free(tabla[i]);
      }
      free(tabla);
      free(alfabeto);
      fclose(f);
    }
    tabla[orgTemp][indexTemp] = dstTemp;
  }

  fclose(f);

  for(i=0; i < strlen(argv[2]); i++){
    int c = index_alf(alfabeto, lenAlfabeto, argv[2][i]);
    if (c == -1){
      printf("Error: simbolo %c no perteneciente al alfabeto.\n", argv[2][i]);
    }

    estadoActual = tabla[estadoActual][c];
    printf("Leemos %c, pasamos al estado %d\n", argv[2][i], estadoActual);
    if (estadoActual == -1){
      printf("Palabra no reconocida\n");
    }
  }

  if (estadoActual != estadoFinal){
    printf("Palabra no reconocida: El estado actual es %d. El final es %d\n", estadoActual, estadoFinal);
  }else{
    printf("Palabra reconocida\n");
  }



  /* Liberamos la memoria */
  for(i = 0; i < numEstados; i++){
    free(tabla[i]);
  }
  free(tabla);
  free(alfabeto);
}
