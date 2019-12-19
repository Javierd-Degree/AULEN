#include <stdlib.h>
#include <stdio.h>
#include "estado_compuesto.h"

/*
Metodo que permite crear la estructura CompoundState, insertando el primer
elemento que pertenecera al nuevo estado.
Parametros
  numElems -> Numero de estados del automata anterior.
  firstElem -> primer estado del automata anterior que pertene a este nuevo
Return
  Estructura CompoundState
*/
CompoundState *createCompoundState(int numElems, int firstElem){
  CompoundState *state;

  if(numElems<=0 || firstElem<0 || firstElem>=numElems){
    printf("Error al crear un estado con %d elementos y el estado %d\n", numElems, firstElem);
    return NULL;
  }

  state = (CompoundState *)malloc(sizeof(CompoundState));
  if (state == NULL){
    return NULL;
  }

  state->states = (int *)calloc(numElems, sizeof(int));
  if (state->states == NULL){
    free(state);
    return NULL;
  }

  state->states[firstElem] = 1;
  state->numElems = numElems;

  state->next = NULL;

  return state;
}

/* Destructor de la estructura CompoundState.
Parámetros
    state -> puntero a la estructura que se quiere borrar.
 */
void destroyCompoundState(CompoundState *state){
  if (state == NULL){
    return;
  }

  destroyCompoundState(state->next);
  free(state->states);
  free(state);
}

/* Metodo auxiliar para printIndistinguible */
void printUniqueCompoundState(CompoundState *state){
  int i;

  if (state == NULL){
    return;
  }
  printf("{");
  for (i=0; i < state->numElems; i++){
    if (state->states[i] == 1){
      printf("%d, ", i);
    }
  }
  printf("}");
}

/*
Metodo que permite imprimir un CompoundState por pantalla para debuggear.
Parametros
  state -> CompoundState a imprimir
*/
void printIndistinguible(CompoundState *state){
  CompoundState *aux;
  aux = state;

  while (aux != NULL) {
    printUniqueCompoundState(aux);
    aux = aux->next;
  }
  printf("\n");
}

/*
Marca un par de estados del antiguo automata como indistinguibles.
Parametros
  state -> CompoundState que almacena los nuevos estados
  first -> primer elemento del par de estados indistinguibles
  second -> segundo elemento del par de estados indistinguibles
Return
  -1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addIndistinguibleCompoundState(CompoundState *state, int first, int second){
  CompoundState *new;

  if (state == NULL){
    return -1;
  }

  if (state->states[first] == 1){
    state->states[second] = 1;
  }else if(state->next != NULL){
    return addIndistinguibleCompoundState(state->next, first, second);
  }else{
    new = createCompoundState(state->numElems, first);
    new->states[second] = 1;

    state->next = new;
  }

  return 0;
}

/* Metodo auxiliar recursivo para getStateIndexOnCompoundState */
int getIndexStateAux(CompoundState *state, int q, int n){
  if (state == NULL || q < 0 || q >= state->numElems){
    return -1;
  }

  if (state->states[q] == 1){
    return n;
  }
  return getIndexStateAux(state->next, q, n+1);
}

/*
Metodo que permite obtener el índice en la lista de nuevos estados
en el que se encuentra el estado q del autómata anterior.
Parametros
  state -> CompoundState en el que buscar
  q -> indice del estado en el automata anterior
Return
  Indice del estado en el nuevo automata o -1 si no se ha encontrado.
*/
int getStateIndexOnCompoundState(CompoundState *state, int q){
  return getIndexStateAux(state, q, 0);
}

/*
Metodo que permite obtener el numero de nuevos estados.
Parametros
  state -> CompoundState en el que buscar
Return
  Numero de estados nuevos.
*/
int getNumCompoundStates(CompoundState *state){
  if (state == NULL){
    return 0;
  }

  return 1+getNumCompoundStates(state->next);
}

/*
Metodo que permite recorrer la lista enlazada de nuevos estados obteniendo el siguiente.
Parametros
  state -> CompoundState cuyo siguiente queremos
Return
  Siguiente estado.
*/
CompoundState *getNextCompoundState(CompoundState *state){
  return state->next;
}

/*
Metodo que permite obtener el array interno de un CompoundState
en el que se almacena con 1's y 0's que estados contiene.
Parametros
  state -> CompoundState cuyo iformacion queremos
Return
  Lista de enteros que indica que estados representa.
*/
int *getCompoundStateStates(CompoundState *state){
  return state->states;
}

/*
Metodo que permite obtener la longitud el array devuelto por getCompoundStateStates
Parametros
  state -> CompoundState cuyo iformacion queremos
Return
  Entero que representa la longitud de getCompoundStateStates.
*/
int getCompoundStateStatesLen(CompoundState *state){
  return state->numElems;
}
