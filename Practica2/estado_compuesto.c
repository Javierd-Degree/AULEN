#include <stdlib.h>
#include <stdio.h>
#include "estado_compuesto.h"

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

void destroyCompoundState(CompoundState *state){
  if (state == NULL){
    return;
  }

  destroyCompoundState(state->next);
  free(state->states);
  free(state);
}

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

void printIndistinguible(CompoundState *state){
  CompoundState *aux;
  aux = state;

  while (aux != NULL) {
    printUniqueCompoundState(aux);
    aux = aux->next;
  }
  printf("\n");
}

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

int getIndexStateAux(CompoundState *state, int q, int n){
  if (state == NULL || q < 0 || q >= state->numElems){
    return -1;
  }

  if (state->states[q] == 1){
    return n;
  }
  return getIndexStateAux(state->next, q, n+1);
}

/* Devuelve un el índice en el state que contiene al estado q del automata inicial, o -1 en caso contrario*/
int getStateIndexOnCompoundState(CompoundState *state, int q){
  return getIndexStateAux(state, q, 0);
}

int getNumCompoundStates(CompoundState *state){
  if (state == NULL){
    return 0;
  }

  return 1+getNumCompoundStates(state->next);
}

CompoundState *getNextCompoundState(CompoundState *state){
  return state->next;
}

int *getCompoundStateStates(CompoundState *state){
  return state->states;
}

int getCompoundStateStatesLen(CompoundState *state){
  return state->numElems;
}
