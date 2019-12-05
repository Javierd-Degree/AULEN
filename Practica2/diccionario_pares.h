#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H

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

/* Inicializa una lista de nodos */
TupleNode* initTupleNode(int a, int b)

/* Libera la memoria usada por una lista de nodos */
void destroyTupleNode(TupleNode* node);

/* Añade un nodo a la lista de nodos */
int addTupleNode(TupleNode *value, int a, int b);

/* Inicializa un diccionario */
TupleDict* initTupleDict(int a, int b, TupleNode *value);

/* Libera la memoria usada por un diccionario, incluyendo todas las listas de valores */
void destroyTupleDict(TupleDict* dict);

/* Añade un par clave, valor al diccionario*/
int addTupleDict(TupleDict *dict, int a, int b, TupleNode *value);

/* Devuelve el valor asociado a una clave del diccionario */
TupleNode* getTupleDict(TupleDict *dict, int a, int b);


#endif
