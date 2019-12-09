#include <stdlib.h>
#include <stdio.h>
#include "diccionario_pares.h"


int tupleEquals(int a1, int b1, int a2, int b2){
  return (a1==a2 && b1==b2) || (a1==b2 && b1==a2);
}


/* Creador de la estructura TupleNode (Definida en diccionario_pares.h).
Inicializa la estructura insertando el primer elemento de la lista.
Parámetros
  a -> primer elemento del par a insertar
  b -> segundo elemento del par a insertar
Return
    TupleNode* con la lista creada
*/
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

/* Libera la memoria usada por una lista de nodos
Parámetros
  node -> puntero a la lista a borrar
*/
void destroyTupleNode(TupleNode* node){
  if (node == NULL){
    return;
  }
  
  if (node->next != NULL){
    destroyTupleNode(node->next);
  }

  free(node);
}

/* Añade un nodo a la lista de nodos 
Parámetros
  value -> lista en la que insertar el nuevo nodo
  a -> primer elemento del par a insertar
  b -> segundo elemento del par a insertar
Return
  -1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado
*/
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

/* Devuelve el nodo siguiente a uno dado
Parámetros
  node -> nodo cuyo siguiente queremos obtener
Return
  nodo siguiente al dado
*/
TupleNode* getNextTupleNode(TupleNode *node){
  if (node == NULL){
    return NULL;
  }

  return node->next;
}

/* Creador de la estructura TupleDict (Definida en diccionario_pares.h),
que inicializa la estructura insertando el primer par (clave:valor)
Parámetros
  a -> primer elemento del par usado como clave
  b -> segundo elemento del par usado como clave
  value -> lista de nodos guardada como valor para la clave (a, b)
Return
    TupleDict* con el diccionario creado
*/
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

/* Libera la memoria usada por un diccionario, incluyendo todas las listas de valores 
Parámetros
  dict -> puntero al diccionario a borrar.
*/
void destroyTupleDict(TupleDict* dict){
  if (dict == NULL){
    return;
  }

  if (dict->next != NULL){
    destroyTupleDict(dict->next);
  }

  destroyTupleNode(dict->value);
  free(dict);
}

/* Añade un par clave, valor al diccionario
Parámetros
  dict -> diccionario al que queremos añadir el par clave:valor
  a -> primer elemento del par usado como clave
  b -> segundo elemento del par usado como clave
  value -> lista de nodos guardada como valor para la clave (a, b)
Return
  -1 si ha habido algún error, 0 si ya estaba insertado, 1 si se ha insertado 
*/
int addTupleDict(TupleDict *dict, int a, int b, TupleNode *value){
  TupleDict *new;
  if (tupleEquals(dict->keyA, dict->keyB, a, b)){
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

/* Devuelve el valor asociado a una clave del diccionario 
Parámetros
  dict -> diccionario en el que buscamos
  keyA -> primer elemento del par usado como clave
  keyB -> segundo elemento del par usado como clave
Return
  Lista de nodos asociada a la clave (keyA, keyB) o NULL si no existe 
*/
TupleNode* getTupleDictValue(TupleDict *dict, int keyA, int keyB){
  if (tupleEquals(dict->keyA, dict->keyB, keyA, keyB)){
    return dict->value;
  }

  if (dict->next != NULL){
    return getTupleDictValue(dict->next, keyA, keyB);
  }


  return NULL;
}

/* Imprime el contenido de un TupleNode 
Parámetros
  node -> lista de nodos cuyo contenido queremos mostrar
*/
void printTupleNode(TupleNode *node){
  if (node->next != NULL){
    printf("(%d, %d), ", node->a, node->b);
    printTupleNode(node->next);
  }else{
    printf("(%d, %d)", node->a, node->b);
  }
}

/* Imprime el contenido del diccionario
Parámetros
  dict -> diccionario cuyo contenido queremos mostrar
*/
void printTupleDict(TupleDict *dict){
  if (dict == NULL){
    return;
  }

  printf("(%d, %d): [", dict->keyA, dict->keyB);
  printTupleNode(dict->value);
  printf("]\n");
  printTupleDict(dict->next);
}