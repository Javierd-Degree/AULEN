#include <stdio.h>
#include <stdlib.h>
#include "state.h"


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

/* Creador de la estructura State. */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado del AFD.
/* numElems -> longitud del array elems.
/*** Return ***/
/* State* con la fila de la matriz generada. */
State* createState(int* elems, int numElems){
  State* newState;
  if(elems == NULL){
    return NULL;
  }
  /* Reservamos memoria */
  newState = (State*)malloc(sizeof(State));
  if(newState == NULL){
    return NULL;
  }
  /* Inicializamos los atributos */
  newState->elems = elems;
  newState->numElems = numElems;
  newState->connections = NULL;
  newState->nextState = NULL;
  return newState;
}

/* Destructor de la estructura State. */
/*** Parámetros ***/
/* state -> puntero a la estructura que se quiere borrar.
/*** Return ***/
/* void */
void deleteState(State* state){
  /* Si hay más estados en la matriz, los destruimos */
  if(state->nextState){
    deleteState(state->nextState);
  }
  /* Liberamos el array elems */
  if(state->elems){
    free(state->elems);
  }
  /* Liberamos el array connections si lo hay */
  if(state->connections){
    free(state->connections);
  }
  /* Liberamos la estructura State */
  free(state);
}

/* Contador de filas de la matriz a partir del estado dado */
/*** Parámetros ***/
/* state -> puntero a la fila de la matriz a partir de la cueal si quere empezar a contar.
/*** Return ***/
/* int con el número de filas. */
int numStates(State* state){
  int i;
  /* Si hay estado siguiente, pasamos  este y sumamos 1 al contador */
  for(i=0; state; i++){
    state = state->nextState;
  }
  return i;
}

/* Función auxiliar que comprueba si el estado con los elementos pasados en el array elems
es el estado que se encuentra en la fila correspondiente a state */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado que se quiere buscar.
/* numElems -> longitud del array elems.
/* state -> puntero a la fila de la matriz de transiciones en la que se quiere buscar.
/*** Return ***/
/* 1 si el estado es el mismo que el estado de la fila de la matriz o 0 en caso contrario. */
int stateEqual(int* elems, int numElems, State* state){
  int i, j, found=0;
  
  /* Si tienen distinto número de elementos devolvemos false */
  if(state->numElems != numElems){
    return 0;
  }

  /* Recorremos los dos arrays (el pasado y el de la estructura) y comprobamos si tienen los mismos elementos. */
  for(i=0; i<numElems; i++){
    for(j=0; j<state->numElems; j++){
      if(elems[i] == state->elems[j]){
        found = 1;
        break;
      }
    }
    /* Si alguno de los elementos de elems no esta en el array de la estructura devolvemos false. */
    if(found == 0){
      return 0;
    }
    found = 0;
  }

  /* Si son el mismo devolvemos true */
  return 1;
}  

/* Genera una nueva fila de la matriz y la añade a esta*/
/*** Parámetros ***/
/* newStateElems -> array con los estados del afnd que componen el estado del AFD a añadir.
/* numElems -> longitud del array newStateElems.
/* state -> puntero a la estructura de la matriz de transiciones a la que se quiere añadir el estado.
/*** Return ***/
/* 0 si el estado ya estaba en la matriz, 1 si se ha añadido y -1 en caso de error. */
int addState(int* newStateElems, int numElems, State* state){
  State* newState;
  /* Si la fila (estado) en el que estamos el igual al que se quiere añadir,
  devolvemos 0 y no añadimos la fila, pues ya existe el estado. */
  if(stateEqual(newStateElems, numElems, state)){
    return 0;
  }

  /* Si hay fila siguiente en la matriz pasamos a esta */
  if(state->nextState){
    return addState(newStateElems, numElems, state->nextState);
  }

  /* Si no hay fila siguiente (es la última), creamos la nueva fila, la añadimos
  despues de esta última y devolvemos 1. */
  newState = createState(newStateElems, numElems);
  if(newState == NULL){
    return -1;
  }
  state->nextState = newState;
  return 1;
}


/* RECURSIVA Devuelve el índice de un estado en la matriz de transiciones, es decir,
devuelve en que fila está ese estado. */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado que se quiere buscar.
/* numElems -> longitud del array elems.
/* state -> puntero a la estructura de la matriz de transiciones en la que se quiere buscar.
/* index -> contador con el índice de la fila de la matriz en la que estamos buscando en esta iteración.
/*** Return ***/
/* Índice de la fila de la matriz correspondiente al estado, o -1 en caso de que el estado no esté en la matriz. */
int index_rec(int* elems, int numElems, State* state, int index){
  /* Si la estructura state que se le pasa es NULL, se ha llegado al final de la matriz,
  no se encuentra el estado correspondiente a elems en la matriz, devuelve -1 */
  if(!state){
    return -1;
  }

  /* Si el estado es el de la fila actual de la matriz, devolvemos index. */
  if(stateEqual(elems, numElems, state)){
    return index;
  }

  /*Si no, llamamos recursivamente a la función con la siguiente fila de la matriz sumando 1 al index. */
  return index_rec(elems, numElems, state->nextState, index++);
}

/* PRINCIPAL Devuelve el índice de un estado en la matriz de transiciones, es decir,
devuelve en que fila está ese estado. */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado que se quiere buscar.
/* numElems -> longitud del array elems.
/* state -> puntero a la estructura de la matriz de transiciones en la que se quiere buscar.
/*** Return ***/
/* Índice de la fila de la matriz correspondiente al estado, o -1 en caso de que el estado no esté en la matriz. */
int index_main(int* elems, int numElems, State* state){
  /* Llamamos a la función recursiva con indice 0 */
  return index_rec(elems, numElems, state, 0);
}






