#ifndef STATE_H
#define STATE_H


/* Estructur para la matriz de transiciones del AFD nuevo. */
struct _State{
	/* Array con los estados del AFND inicial qie componen el estado del AFD nuevo
	(ej, si el estado es q0q1q3, este array será [0, 1, 3]). */
	int* elems;
	/* Entero que indica la longitud del array elems. */
	int numElems;
	/* Array que contiene los índices (en el nuevo AFD) de los estados a los que se puede
	ir desde el estado en el que estamos. Tiene longitud numSimbolos, el primer elemento del
	array es el estado al que se va con el simbolo 0, luego con el 1... etc. */
	int* connections;
	/* Puntero al siguiente estado (siguiente fila de la matriz). */
	struct _State *nextState;
};

typedef struct _State State;

/* Creador de la estructura State. */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado del AFD.
/* numElems -> longitud del array elems.
/*** Return ***/
/* State* con la fila de la matriz generada. */
State* createState(int* elems, int numElems);

/* Destructor de la estructura State. Libera tanto la fila del state que se pasa,
como todas las siguientes */
/*** Parámetros ***/
/* state -> puntero a la estructura que se quiere borrar.
/*** Return ***/
/* void */
void deleteState(State* state);

/* Función que devuelve el número de estados que hay en la matriz
(número de filas) a partir del State pasado. */
/*** Parámetros ***/
/* state -> puntero a la fila de la matriz a partir de la cueal si quere empezar a contar.
/*** Return ***/
/* int con el número de filas. */
int numStates(State* state);

/* Genera una nueva fila de la matriz y la añade a esta*/
/*** Parámetros ***/
/* newStateElems -> array con los estados del afnd que componen el estado del AFD a añadir.
/* numElems -> longitud del array newStateElems.
/* state -> puntero a la estructura de la matriz de transiciones a la que se quiere añadir el estado.
/*** Return ***/
/* 0 si el estado ya estaba en la matriz, 1 si se ha añadido y -1 en caso de error. */
int addState(int* newStateElems, int numElems, State* state);

/* Devuelve el índice de un estado en la matriz de transiciones, es decir,
devuelve en que fila está ese estado. */
/*** Parámetros ***/
/* elems -> array con los estados del afnd que componen el estado que se quiere buscar.
/* numElems -> longitud del array elems.
/* state -> puntero a la estructura de la matriz de transiciones en la que se quiere buscar.
/*** Return ***/
/* Índice de la fila de la matriz correspondiente al estado, o -1 en caso de que el estado no esté en la matriz. */
int index_main(int* elems, int numElems, State* state);

#endif


