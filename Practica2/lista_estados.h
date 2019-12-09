#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H


/* Estructura para un nodo dentro de la lista enlazada */
struct _State{
	/* Indice del estado */
	int index;
	/* Puntero al siguiente estado */
	struct _State *nextState;
};

typedef struct _State State;

/* Estructura para la lista enlazada */
struct _LList{
	/* Puntero al primer elemento de la lista */
	struct _State *head;
};

typedef struct _LList LList;


/* Creador de la estructura LList (Definida en lista_estados.h).
Return
    LList* con la lista creada
*/
LList* createLList();

/* Destructor de la estructura LList.
Parámetros
    list -> puntero a la estructura que se quiere borrar.
 */
void deleteLList(LList* list);

/* Determina si la lista esta vacia o no.
Parámetros
    list -> puntero a la estructura que se quiere borrar.
Return
	1 si esta vacia, 0 si no
*/
int isLListVoid(LList *list);

/* Añade un nuevo elemento a la lista, si no está ya
Parametros
	list -> puntero a la lista
	index -> contenido del elemento a insertar
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addToLList(LList* list, int elem);

/* Devuelve el numero de elementos de la lista
Parametros
	list -> puntero a la lista
Return
	Numero de elementos de la lista
*/
int getLListLength(LList* list);

/* Imprime los elementos de la lista
Parametros
	list -> puntero a la lista
*/
void printLList(LList* list);

/* Devuelve el valor del elemento de la lista en la posicion n-esima
Es responsabilidad del programador asegurar que la lista tiene suficientes 
elementos como para que el elemento en la posicion n-esima existe.
Parametros
	list -> puntero a la lista
	n -> posicion del elemento de la lista que se quiere obtener
Return
	Valor del elemento de la lista en la posicion n-esima
*/
int getLListValue(LList* list, int n);

/* Elimina el primer elemento de la lista
Parametros
	list -> puntero a la lista
*/
void removeLListFirstElem(LList* list);


/* Compara dos listas
Parametros
  list1 -> puntero a la primera lista
  list2 -> puntero a la segunda lista
Return
  1 si son iguales, 0 si no
*/
int cmpLList(LList* list1, LList* list2);

#endif
