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

/*
Metodo que permite crear la estructura CompoundState, insertando el primer
elemento que pertenecera al nuevo estado.
Parametros
	numElems -> Numero de estados del automata anterior.
	firstElem -> primer estado del automata anterior que pertene a este nuevo
Return
	Estructura CompoundState
*/
CompoundState *createCompoundState(int numElems, int firstElem);

/* Destructor de la estructura CompoundState.
Parámetros
    state -> puntero a la estructura que se quiere borrar.
 */
void destroyCompoundState(CompoundState *state);

/*
Marca un par de estados del antiguo automata como indistinguibles.
Parametros
	state -> CompoundState que almacena los nuevos estados
	first -> primer elemento del par de estados indistinguibles
	second -> segundo elemento del par de estados indistinguibles
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addIndistinguibleCompoundState(CompoundState *state, int first, int second);

/*
Metodo que permite imprimir un CompoundState por pantalla para debuggear.
Parametros
	state -> CompoundState a imprimir
*/
void printIndistinguible(CompoundState *state);

/*
Metodo que permite obtener el índice en la lista de nuevos estados
en el que se encuentra el estado q del autómata anterior.
Parametros
	state -> CompoundState en el que buscar
	q -> indice del estado en el automata anterior
Return
	Indice del estado en el nuevo automata o -1 si no se ha encontrado.
*/
int getStateIndexOnCompoundState(CompoundState *state, int q);

/*
Metodo que permite obtener el numero de nuevos estados.
Parametros
	state -> CompoundState en el que buscar
Return
	Numero de estados nuevos.
*/
int getNumCompoundStates(CompoundState *state);

/*
Metodo que permite recorrer la lista enlazada de nuevos estados obteniendo el siguiente.
Parametros
	state -> CompoundState cuyo siguiente queremos
Return
	Siguiente estado.
*/
CompoundState *getNextCompoundState(CompoundState *state);

/*
Metodo que permite obtener el array interno de un CompoundState
en el que se almacena con 1's y 0's que estados contiene.
Parametros
	state -> CompoundState cuyo iformacion queremos
Return
	Lista de enteros que indica que estados representa.
*/
int *getCompoundStateStates(CompoundState *state);

/*
Metodo que permite obtener la longitud el array devuelto por getCompoundStateStates
Parametros
	state -> CompoundState cuyo iformacion queremos
Return
	Entero que representa la longitud de getCompoundStateStates.
*/
int getCompoundStateStatesLen(CompoundState *state);

#endif
