#ifndef DICCIONARIOPARES_H
#define DICCIONARIOPARES_H


/* Consideramos en todo momento que una tupla (a,b)=(b,a) */

/* Estructura para un nodo dentro de la lista enlazada de pares */
struct _TupleNode{
	/* Elementos de la tupla */
	int a, b;
	/* Puntero al siguiente nodo */
	struct _TupleNode *next;
};

typedef struct _TupleNode TupleNode;

/* Estructura que representa un diccionario.
Esta indexado por una tupla, y cada clave almacena una lista de tuplas.*/
struct _TupleDict{
  /* Par de enteros que almacena la clave */
  int keyA, keyB;
	/* Lista de tuplas cuyo primer elemento es la clave */
	TupleNode *value;
	/* Puntero al siguiente nodo */
	struct _TupleDict *next;
};

typedef struct _TupleDict TupleDict;



/* Creador de la estructura TupleNode (Definida en diccionario_pares.h).
Inicializa la estructura insertando el primer elemento de la lista.
Parámetros
	a -> primer elemento del par a insertar
	b -> segundo elemento del par a insertar
Return
    TupleNode* con la lista creada
*/
TupleNode* initTupleNode(int a, int b);

/* Libera la memoria usada por una lista de nodos
Parámetros
	node -> puntero a la lista a borrar
*/
void destroyTupleNode(TupleNode* node);

/* Añade un nodo a la lista de nodos 
Parámetros
	value -> lista en la que insertar el nuevo nodo
	a -> primer elemento del par a insertar
	b -> segundo elemento del par a insertar
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
int addTupleNode(TupleNode *value, int a, int b);

/* Devuelve el nodo siguiente a uno dado
Parámetros
	node -> nodo cuyo siguiente queremos obtener
Return
	nodo siguiente al dado
*/
TupleNode* getNextTupleNode(TupleNode *node);

/* Creador de la estructura TupleDict (Definida en diccionario_pares.h),
que inicializa la estructura insertando el primer par (clave:valor)
Parámetros
	a -> primer elemento del par usado como clave
	b -> segundo elemento del par usado como clave
	value -> lista de nodos guardada como valor para la clave (a, b)
Return
    TupleDict* con el diccionario creado
*/
TupleDict* initTupleDict(int a, int b, TupleNode *value);

/* Libera la memoria usada por un diccionario, incluyendo todas las listas de valores 
Parámetros
	dict -> puntero al diccionario a borrar.
*/
void destroyTupleDict(TupleDict* dict);

/* Añade un par clave, valor al diccionario
Parámetros
	dict -> diccionario al que queremos añadir el par clave:valor
	a -> primer elemento del par usado como clave
	b -> segundo elemento del par usado como clave
	value -> lista de nodos guardada como valor para la clave (a, b)
Return
	-1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado 
*/
int addTupleDict(TupleDict *dict, int a, int b, TupleNode *value);

/* Devuelve el valor asociado a una clave del diccionario 
Parámetros
	dict -> diccionario en el que buscamos
	keyA -> primer elemento del par usado como clave
	keyB -> segundo elemento del par usado como clave
Return
	Lista de nodos asociada a la clave (keyA, keyB) o NULL si no existe 
*/
TupleNode* getTupleDictValue(TupleDict *dict, int keyA, int keyB);

/* Imprime el contenido de un TupleNode 
Parámetros
	node -> lista de nodos cuyo contenido queremos mostrar
*/
void printTupleNode(TupleNode *node);


/* Imprime el contenido del diccionario
Parámetros
	dict -> diccionario cuyo contenido queremos mostrar
*/
void printTupleDict(TupleDict *dict);


#endif
