#ifndef ESTADOCOMPUESTO_H
#define ESTADOCOMPUESTO_H


/* Estructura para un estado compuesto por estados indistinguibles
El array states tiene tamaño el número de estados del array, e indica para
cada estado del array si está o no incluido en el estado
 */
struct _CompoundState{
	int* states;
  int numElems;
  struct _CompoundState * next;
}_CompoundState;

typedef struct _CompoundState CompoundState;

CompoundState *createCompoundState(int numElems, int firstElem);

void destroyCompoundState(CompoundState *state);

int addIndistinguibleCompoundState(CompoundState *state, int first, int second);

void printIndistinguible(CompoundState *state);

int getStateIndexOnCompoundState(CompoundState *state, int q);

int getNumCompoundStates(CompoundState *state);

CompoundState *getNextCompoundState(CompoundState *state);

int *getCompoundStateStates(CompoundState *state);

int getCompoundStateStatesLen(CompoundState *state);

#endif
