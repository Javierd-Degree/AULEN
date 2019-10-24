#include "transforma.h"
/*
- TAD Estado: Almacenamos la lista de estados que corresponde al nuevo estado.

- Lista de nuevos estados: Lista de TAD Estado creados

- Matriz del nuevo automata, indexada por el simbolo, y el indice de un nuevo estado en la
lista de estados. Dado un simbolo con indice i, y un estado con indice j matriz[i][j]
contiene un entero k que indica el indice del nuevo estado destino en la lista de nuevos estados.

*/




/* Devuelve el cierre transitivo del estado dado */
int *AFNDCierreLEstado(AFND * afnd, int q){
  int numEstados, i;
  int *cierreTransitivo;

  numEstados = AFNDNumEstados(afnd);
  cierreTransitivo = (int *)malloc(sizeof(int)*numEstados);
  if (cierreTransitivo == NULL){
    return NULL;
  }

  for (i = 0; i < numEstados; i++){
    cierreTransitivo[i] =  AFNDCierreLTransicionIJ(afnd, q, i);
  }
}

/* Devuelve las conexiones desde q al resto de estados usando el simbolo s */
int *AFNDConexionesEstadoSimbolo(AFND * afnd, int q, int s){
  int numEstados, i;
  int *conexiones;

  numEstados = AFNDNumEstados(afnd);
  conexiones = (int *)malloc(sizeof(int)*numEstados);
  if (conexiones == NULL){
    return NULL;
  }

  for (i = 0; i < numEstados; i++){
    conexiones[i] =  AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, q, s, i);
  }
}

int *IndicesListaEstados(int *list, int len){
  int i, j, sum;
  int *result;

  for (i = 0, sum = 0; i < len; i++, sum+=list[i]);
  result = (int *)malloc(sizeof(int)*sum);
  if (result == NULL){
    return NULL;
  }

  for (i = 0, j = 0 ; i < len, j < sum ; i++){

    result[j] =

  }

  return result;
}

AFND * AFNDTransforma(AFND * afnd){
  AFND *c_afnd;
  int numEstados;
  if (afnd == NULL){
    return NULL;
  }

  numEstados = AFNDNumEstados(afnd);
  /* Hacemos el cierre transitivo por lambdas para usarlo siempre que lo necesitemos */
  c_afnd = AFNDCierraLTransicion(afnd);
}
