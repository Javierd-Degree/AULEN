#include <stdio.h>
#include <stdlib.h>
#include "lista_estados.h"


/* Creador de la estructura State (Definida en lista_estados.h).
Parámetros
    index -> Indice del primer estado
Return
    State* con la fila de la matriz generada.
*/
State* createState(int index){
  State* newState;

  /* Reservamos memoria */
  newState = (State*)malloc(sizeof(State));
  if(newState == NULL){
    return NULL;
  }
  /* Inicializamos los atributos */
  newState->index = index;
  newState->nextState = NULL;
  return newState;
}

/* Destructor de la estructura State.
Parámetros
    state -> puntero a la estructura que se quiere borrar.
 */
void deleteState(State* state){
  /* Si hay más estados en la matriz, los destruimos */
  if(state->nextState){
    deleteState(state->nextState);
  }
  /* Liberamos la estructura State */
  free(state);
}

/* Creador de la estructura LList (Definida en lista_estados.h).
Return
    LList* con la lista creada
*/
LList* createLList(){
  LList* list;

  /* Reservamos memoria */
  list = (LList*)malloc(sizeof(LList));
  if(list == NULL){
    return NULL;
  }

  /* Inicializamos los atributos */
  list->head = NULL;
  return list;
}

/* Destructor de la estructura LList.
Parámetros
    list -> puntero a la estructura que se quiere borrar.
 */
void deleteLList(LList* list){
  if (list->head != NULL){
  	deleteState(list->head);
  }
 
  /* Liberamos la estructura State */
  free(list);
}


/* Determina si la lista esta vacia o no.
Parámetros
    list -> puntero a la estructura que se quiere borrar.
Return
	1 si esta vacia, 0 si no
*/
int isLListVoid(LList *list){
	return list->head == NULL;
}


/* Funcion recursiva auxiliar.
Añade un nuevo elemento a la lista, en orden ascendente, si no está ya
Parametros
	state -> puntero a la lista
	index -> contenido del elemento a insertar
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addStateAux(State* state, int index){
  State* newState;

  if (state == NULL){
  	return -1;
  }

  /* Comprobamos si el nodo está insertado o no */
  if (state->index == index){
    return 0;
  }

  /* Si hay fila siguiente en la matriz pasamos a esta */
  if(state->nextState && (index >= state->nextState->index)){
    return addStateAux(state->nextState, index);
  }

  /* Si no hay fila siguiente (es la última), creamos la nueva fila, la añadimos
  despues de esta última y devolvemos 1. */
  newState = createState(index);
  if(newState == NULL){
    return -1;
  }
  newState->nextState = state->nextState;
  state->nextState = newState;
  return 1;
}

/* Añade un nuevo elemento a la lista, en orden ascendente, si no está ya
Parametros
	list -> puntero a la lista
	elem -> contenido del elemento a insertar
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addToLList(LList* list, int elem){
	State * aux;
	if (list == NULL){
		return -1;
	}

	if (list->head == NULL){
		list->head = createState(elem);
		return 1;
	}

	if (list->head->index > elem){
		aux = createState(elem);
		aux->nextState = list->head;
		list->head = aux;
		return 1;
	}else if(list->head->index == elem){
		return 0;
	}

	return addStateAux(list->head, elem);
}

/* Funcion recursiva auxiliar 
Devuelve el numero de elementos de la lista
Parametros
	state -> puntero a la lista
Return
	Numero de elementos de la lista
*/
int getLListLengthAux(State* state){
  if (state == NULL){
  	return 0;
  }
  return 1 + getLListLengthAux(state->nextState);
}

/* Devuelve el numero de elementos de la lista
Parametros
	list -> puntero a la lista
Return
	Numero de elementos de la lista
*/
int getLListLength(LList* list){
	return getLListLengthAux(list->head);
}

/* Funcion recursiva auxiliar 
Imprime los elementos de la lista
Parametros
	state -> puntero a la lista
*/
void printLListAux(State* state){
  if (state == NULL){
  	printf("\n");
  	return;
  }

  printf("%d\t", state->index);
  printLListAux(state->nextState);
  return;
}

/* Imprime los elementos de la lista
Parametros
	list -> puntero a la lista
*/
void printLList(LList* list){
	printLListAux(list->head);
}

/* Funcion recursiva auxiliar
Devuelve el valor del elemento de la lista en la posicion n-esima
Parametros
	state -> puntero a la lista
	n -> posicion del elemento de la lista que se quiere obtener
Return
	Valor del elemento de la lista en la posicion n-esima
*/
int getLListValueAux(State* state, int n){
  if (n == 0){
  	return state->index;
  }
  return getLListValueAux(state->nextState, n-1);
}

/* Devuelve el valor del elemento de la lista en la posicion n-esima
Es responsabilidad del programador asegurar que la lista tiene suficientes 
elementos como para que el elemento en la posicion n-esima exista.
Parametros
	list -> puntero a la lista
	n -> posicion del elemento de la lista que se quiere obtener
Return
	Valor del elemento de la lista en la posicion n-esima
*/
int getLListValue(LList* list, int n){
	return getLListValueAux(list->head, n);
}

/* Elimina el primer elemento de la lista
Parametros
	list -> puntero a la lista
*/
void removeLListFirstElem(LList* list){
  State* aux;
  if (list->head == NULL){
  	return;
  }

  aux = list->head->nextState;
  free(list->head);
  list->head = aux;
}


/* Funcion recursiva auxiliar
Compara dos listas. Como los elementos se almacenan de forma ordenada, es muy simple.
Parametros
  state1 -> puntero a la primera lista
  state2 -> puntero a la segunda lista
Return
  1 si son iguales, 0 si no
*/
int cmpLListAux(State* state1, State* state2){
  if ((state1 == NULL && state2 != NULL) || (state1 != NULL && state2 == NULL)){
    return 0;
  }

  if (state1->index != state2->index){
    return 0;
  }

  return cmpLListAux(state1->nextState, state2->nextState);
}

/* Compara dos listas
Parametros
  list1 -> puntero a la primera lista
  list2 -> puntero a la segunda lista
Return
  1 si son iguales, 0 si no
*/
int cmpLList(LList* list1, LList* list1){
  return cmpLListAux(list1->head, list2->head);
}
