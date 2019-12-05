#include <stdlib.h>
#include "diccionario_pares.h"


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

/*
Funcion auxiliar, NO METER EN EL .h
*/
int tupleEquals(int a1, int b1, int a2, int b2){
  return (a1==a2 && b1==b2) || (a1==b2 && b1==a2);
}

TupleNode* initTupleNode(int a, int b){
  TupleNode *node;
  node = (TupleNode *)malloc(sizeof(TupleNode));
  if (node == NULL){
    return NULL;
  }

  node->a = a;
  node->b = b;
  node->next = NULL;
  return node;
}


void destroyTupleNode(TupleNode* node){
  if (node->next != NULL){
    destroyTupleNode(dict->next);
  }

  free(node);
}

int addTupleNode(TupleNode *value, int a, int b){
  TupleNode *new;
  if (tupleEquals(value->a, value->b, a, b)){
    return 0;
  }

  if (value->next != NULL){
    return addTupleNode(value->next, a, b);
  }

  new = initTupleNode(a, b);
  if (new == NULL){
    return -1;
  }

  value->next = new;
  return 1;
}

TupleDict* initTupleDict(int a, int b, TupleNode *value){
  TupleDict *dict;
  dict = (TupleDict *)malloc(sizeof(TupleDict));
  if (dict == NULL){
    return NULL;
  }

  dict->keyA = a;
  dict->keyB = b;
  dict->value = value;
  dict->next = NULL;
  return dict;
}


void destroyTupleDict(TupleDict* dict){
  if (dict->next != NULL){
    destroyTupleDict(dict->next);
  }

  destroyTupleNode(dict->value);
  free(dict);
}

int addTupleDict(TupleDict *dict, int a, int b, TupleNode *value){
  TupleDict *new;
  if (tupleEquals(dict->keyA, value->keyB, a, b)){
    return 0;
  }

  if (dict->next != NULL){
    return addTupleDict(dict->next, a, b, value);
  }

  new = initTupleDict(a, b, value);
  if (new == NULL){
    return -1;
  }

  dict->next = new;
  return 1;
}

TupleNode* getTupleDict(TupleDict *dict, int a, int b){
  if (tupleEquals(dict->keyA, value->keyB, a, b)){
    return dict->value;
  }

  if (dict->next != NULL){
    return getTupleDict(dict->next, a, b);
  }


  return NULL;
}
