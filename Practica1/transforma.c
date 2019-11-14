#include "transforma.h"
#include "state.h"
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 256
/*
- TAD Estado: Almacenamos la lista de estados que corresponde al nuevo estado.

- Lista de nuevos estados: Lista de TAD Estado creados

- Matriz del nuevo automata, indexada por el simbolo, y el indice de un nuevo estado en la
lista de estados. Dado un simbolo con indice i, y un estado con indice j matriz[i][j]
contiene un entero k que indica el indice del nuevo estado destino en la lista de nuevos estados.

*/





/* Estructura para la matriz de transiciones del AFD nuevo.

struct _State{

  Array con los estados del AFND inicial qie componen el estado del AFD nuevo
  (ej, si el estado es q0q1q3, este array será [0, 1, 3]).
  int* elems;

  Entero que indica la longitud del array elems.
  int numElems;

  Array que contiene los índices (en el nuevo AFD) de los estados a los que se puede
  ir desde el estado en el que estamos. Tiene longitud numSimbolos, el primer elemento del
  array es el estado al que se va con el simbolo 0, luego con el 1... etc.
  int* connections;

  Puntero al siguiente estado (siguiente fila de la matriz).
  struct _State *nextState;
};

*/


/* Devuelve el cierre transitivo del estado dado
Parámetros
   afnd -> autómata inicial.
   numEstados -> número de estados del afnd.
   q -> estado actual.
Return
   int* con el cierre transitivo del estado (formato de 1s y 0s). */
int *AFNDCierreLEstado(AFND * afnd, int numEstados, int q){
  int i;
  int *cierreTransitivo;

  /* Reservamos un array que contendrá el cierre transitivo del estado. */
  cierreTransitivo = (int *)malloc(sizeof(int)*numEstados);
  if (cierreTransitivo == NULL){
    return NULL;
  }

  /* Para cada estado del AFND comprobamos si hay conexión lambda desde el
  estado actual hasta este y lo añadimos a la posición correspondiente del array. */
  for (i = 0; i < numEstados; i++){
    cierreTransitivo[i] =  AFNDCierreLTransicionIJ(afnd, q, i);
  }

  /* Devolvemos el array de conexiones lambda. */
  return cierreTransitivo;
}

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

/* A partir de un array de conexiones de long numEstados donde un 0 es que no hay
conexion a ese estado y un 1 es que si la hay, genera un array con los índices de
los estados a los que hay conexión.
IMPORTANTE numelems es la dirección de una variable donde queremos guardar la longitud del array.
Parámetros
    list -> array inicial de conexiones en formato de 1s y 0s.
    numEstados -> número de estados del afnd.
    numElems -> dirección para almacenar el número de elementos que tiene el array que se devuelve.
Return
    int* con los índices de los estados a los que se puede ir según el array de conexiones proporcionado (formato de índices).
*/
int *IndicesListaEstados(int *list, int numEstados, int* numElems){
  int i, j, sum = 0;
  int *result;

  /* Sumamos los elementos del array para obtener el número de conexiones que habrá. */
  for (i = 0, sum = 0; i < numEstados; i++){
    sum+=list[i];
  }

  /* Reservamos un array resultado en el que devolver las conexiones. */
  result = (int *)malloc(sizeof(int)*sum);
  if (result == NULL){
    return NULL;
  }

  /* Para cada elemento del array de conexiones inicial, si hay conexión (es un 1)
  añadimos al array final el índice del elemento del array. */
  for (i = 0, j = 0 ; (i < numEstados) && (j < sum); i++){
    if(list[i] == 1){
      result[j] = i;
      j++;
    }
  }

  /* Almacenamos en la dirección numElems la longitud del array obtenido. */
  *numElems = sum;

  /* Devolvemos el array con los índices de las conexiones. */
  return result;
}

/* Recorre el array de elementos de un estado del AFD y para cada uno de ellos halla las transiciones con el símbolo dado,
es decir, obtiene  finalmente el array de conexiones desde el elemento formado por la union de elementos del AFND (q1q2q4).
Parámetros
    afnd -> autómata inicial.
    elems -> array con los estados del afnd que componen el estado del AFD.
    numElems -> longitud del array elems.
    numEstados -> número de estados del afnd.
    s -> símbolo procesado.
Return
    int* con el array de conexiones (formato de 1s y 0s). */
int *AFNDUnionConexionesEstadoSimbolo(AFND* afnd, int* elems, int numElems, int numEstados, int s){
  int i,j, sumElems;
  int* conexionesAux, *conexiones, *elemsConSimbolo;
  /* Inicializamos el array de conexiones con 0s (long numEstados de AFND). */
  conexiones = (int*)calloc(numEstados, sizeof(int));

  for(i=0; i<numElems; i++){
    /* Para cada elemento que compone el estado, hallamos su array de conexiones a otros nodos del AFND. */
    conexionesAux = AFNDConexionesEstadoSimbolo(afnd, numEstados, elems[i], s);

    for(j=0; j<numEstados; j++){
      /* Unimos el nuevo array con el anterior. */
      if((conexiones[j] + conexionesAux[j]) > 0){
        conexiones[j]=1;
      }else{
        conexiones[j] = 0;
      }
    }
    free(conexionesAux);
  }
  /* A partir del array de conexiones obtenido generamos el array de los índices de las conexiones. */
  elemsConSimbolo = IndicesListaEstados(conexiones, numEstados, &sumElems);
  for(i=0; i<sumElems; i++){
    /*Para cada estado de este array hallamos su cierre lambda */
    conexionesAux = AFNDCierreLEstado(afnd, numEstados, elemsConSimbolo[i]);
    for(j=0; j<numEstados; j++){
      /* Unimos los arrays de conexiones de los cierres lambda al array de conexiones que teníamos. */
      if((conexiones[j] + conexionesAux[j]) > 0){
        conexiones[j]=1;
      }else{
        conexiones[j]=0;
      }
    }
    free(conexionesAux);
  }
  free(elemsConSimbolo);
  /*Devolvemos el array de conexiones.*/
  return conexiones;
}

/* Función que comprueba si el estado del AFD compuesto por los estados elems del AFND es final o no.
Parámetros
    afnd -> autómata inicial.
    elems -> array con los estados del afnd que componen el estado del AFD.
    numElems -> longitud del array elems.
Return
    1 si el estado es final, y 0 si no lo es. */
int esFinal(AFND* afnd, int* elems, int numElems){
  int i;
  for(i=0; i<numElems; i++){
    /*Si alguno de los estados de elems es FINAL o INICIAL_Y_FINAL en el AFND devolvemos true. */
    if(AFNDTipoEstadoEn(afnd, elems[i]) == FINAL || AFNDTipoEstadoEn(afnd, elems[i]) == INICIAL_Y_FINAL){
      return 1;
    }
  }
  /* Si no, devolvemos false. */
  return 0;
}

/* Función que recorre el AFND y genera un nuevo estado del AFD añadiendolo a la matriz.
Parámetros
    afnd -> autómata inicial.
    numSimbolos -> número de sḿbolos en el alfabetod el AFND.
    numEstados -> número de estados del afnd.
    actualState -> puntero a la fila de la matriz de transiciones correspondiente al estado actual.
    states -> puntero al inicio de la matriz de transiciones.
*/
void generarNuevoEstado(AFND* afnd, int numSimbolos, int numEstados, State* actualState, State* states){
  int *conexiones, *conexionesAux, *elemsNewState;
  int i, numElems, res;
  /* Reservamos un array de conexiones que será el que irá en el campo connections de la nueva fila de la matriz que se creará. */
  conexiones = (int*)malloc(sizeof(int)*numSimbolos);
  for(i=0; i<numSimbolos; i++){
    /* Para cada símbolo del alfabeto, hallamos a que estados del AFND se puede ir desde el estado actualState.*/
    conexionesAux = AFNDUnionConexionesEstadoSimbolo(afnd, actualState->elems, actualState->numElems, numEstados, i);
    /* A partir del array de conexiones obtenido, generamos el array de índices correspondiente.*/
    elemsNewState = IndicesListaEstados(conexionesAux, numEstados, &numElems);
    free(conexionesAux);
    if(numElems == 0){
      conexiones[i] = -1;
      free(elemsNewState);
      continue;
    }

    /* Añadimos el nuevo estado a la matriz (si no está ya en ella). */
    res = addState(elemsNewState, numElems, states);
    /*Actualizamos el elemento i del array de conexiones (el correspondiente al símbolo procesado)
    para que sea igual al índice del nuevo elemento del AFD. */
    conexiones[i] = index_main(elemsNewState, numElems, states);
    if(res == 0){
      free(elemsNewState);
    }
  }

  /* Introducimos el array de conexiones en la estructura.*/
  actualState->connections = conexiones;
}

/* Función que genera el AFND a partir de la matriz de transiciones.
Parámetros
    afnd -> autómata inicial.
    numSimbolos -> número de sḿbolos en el alfabetod el AFND.
    states -> puntero al inicio de la matriz de transiciones.
Return
    AFND* con el AFD generado.
*/
AFND* generarAFD(AFND* afnd, State* states, int numSimbolos){
  AFND * afd;
  State* actualState = states;
  int i, j, type;
  /*número de estados del AFD nuevo.*/
  int numEstados = numStates(states);
  char name[MAX_LEN], *temp;

  /* Creamos el nuevo AFND. */
  afd= AFNDNuevo("afd", numEstados, numSimbolos);
  for(i=0; i<numSimbolos; i++){
    /* Insertamos los símbolos del alfabeto. */
    afd = AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
  }

  /*Insertamos los estados.*/
  for(i=0; i<numEstados; i++){
    strcpy(name, "");

    for(j=0; j<actualState->numElems; j++){
      /*Para cada elemento del estado de la fila de la matriz de transiciones,
      generamos su nombre concatenando los nombres que tenían estos estados en el AFND. */
      temp = AFNDNombreEstadoEn(afnd, actualState->elems[j]);
      if ((strlen(temp) + strlen(name)) >= MAX_LEN){
        printf("ERROR: Overflow al crear el nombre del estado\n");
        return NULL;
      }
      strcat(name, temp);
    }

    /* Si es la primera fila de la matriz y el estado es final, el estado es INICIAL_Y_FINAL. */
    if(i == 0 && esFinal(afnd, actualState->elems, actualState->numElems)){
      type = INICIAL_Y_FINAL;
    /* Si es la primera fila de la matriz pero el estado no es final, el estado es INICIAL. */
    }else if(i == 0){
      type = INICIAL;
    /* Si no es la primera fila y el estado es final, el estado es FINAL. */
    }else if(esFinal(afnd, actualState->elems, actualState->numElems)){
      type = FINAL;
    /* Si no, el estado es NORMAL. */
    }else{
      type = NORMAL;
    }

    /* Insertamos el estado correspondiente a la iteración y la fila correspondiente de la matriz. */
    AFNDInsertaEstado(afd, name, type);
    /* Pasamos a la siguiente fila de la matriz. */
    actualState = actualState->nextState;
  }

  /* Colocamos el puntero al inicio de la matriz de nuevo para recorrerla desde el inicio. */
  actualState = states;

  /* Insertamos las transiciones. */
  for(i=0; i<numEstados; i++){
    for(j=0; j<numSimbolos; j++){
      /*Para cada estado del nuevo AFD y cada símbolo del alfabeto, si no existe conexión desde el
      estado con el símbolo dado, pasamos a la iteración del siguiente símbolo. */
      if(actualState->connections[j] == -1){
        continue;
      }
      /* Insertamos la transición. */
      AFNDInsertaTransicion(
        afd,
        /* El origen es el nombre del estado de actualState. */
        AFNDNombreEstadoEn(afd, index_main(actualState->elems, actualState->numElems, states)),
        /*Símbolo j*/
        AFNDSimboloEn(afd, j),
        /* El destino es el nombre del estado en la posición j (correspondiente al símbolo)
        del array de conexiones del estado actualState.*/
        AFNDNombreEstadoEn(afd, actualState->connections[j]));
    }
    /* Pasamos al siguiente estado del AFD (siguiente fila de la matriz). */
    actualState = actualState->nextState;
  }
  /* Devolvemos el AFD generado. */
  return afd;
}


/*Función que transforma un AFND en AFD.
Parámetros
    afnd -> autómata inicial.
Return
    AFND* con el AFD resultado.
*/
AFND * AFNDTransforma(AFND * afnd){
  AFND *afd;
  int numEstados, estadoAux, numElems, numSimbolos;
  int *conexionesAux, *elemsNewState;
  State* states, *actualState;
  if (afnd == NULL){
    return NULL;
  }

  numEstados = AFNDNumEstados(afnd);
  numSimbolos = AFNDNumSimbolos(afnd);
  /*Obtenemos el estado inicial del AFND*/
  estadoAux = AFNDIndiceEstadoInicial(afnd);
  /*Obtenemos su cierre transitivo*/
  conexionesAux = AFNDCierreLEstado(afnd, numEstados, estadoAux);
  /*Lo pasamos a un array de indices de estados*/
  elemsNewState = IndicesListaEstados(conexionesAux, numEstados, &numElems);
  free(conexionesAux);
  /*Creamos la lista de estados y el estado actual del afd como este conjunto de estados*/
  states = createState(elemsNewState, numElems);
  actualState = states;
  /*Genermos la nueva matriz de conexiones para el AFD*/
  while(actualState != NULL){
    generarNuevoEstado(afnd, numSimbolos, numEstados, actualState, states);
    actualState = actualState->nextState;
  }

  /*Generamos el AFD.*/
  afd = generarAFD(afnd, states, numSimbolos);

  /* Liberamos la estructura de la matriz de transiciones. */
  deleteState(states);

  /* Devolvemos el AFD generado. */
  return afd;
}
