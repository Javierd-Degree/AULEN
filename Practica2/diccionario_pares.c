#include <stdlib.h>
#include <stdio.h>
#include "diccionario_pares.h"

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
  if (node == NULL){
    return;
  }
  
  if (node->next != NULL){
    destroyTupleNode(node->next);
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

TupleNode* getNextTupleNode(TupleNode *node){
  if (node == NULL){
    return NULL;
  }

  return node->next;
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
  if (dict == NULL){
    return;
  }

  if (dict->next != NULL){
    destroyTupleDict(dict->next);
  }

  destroyTupleNode(dict->value);
  free(dict);
}

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

TupleNode* getTupleDictValue(TupleDict *dict, int keyA, int keyB){
  if (tupleEquals(dict->keyA, dict->keyB, keyA, keyB)){
    return dict->value;
  }

  if (dict->next != NULL){
    return getTupleDictValue(dict->next, keyA, keyB);
  }


  return NULL;
}

void printTupleNode(TupleNode *node){
  if (node->next != NULL){
    printf("(%d, %d), ", node->a, node->b);
    printTupleNode(node->next);
  }else{
    printf("(%d, %d)", node->a, node->b);
  }
}

void printTupleDict(TupleDict *dict){
  if (dict == NULL){
    return;
  }

  printf("(%d, %d): [", dict->keyA, dict->keyB);
  printTupleNode(dict->value);
  printf("]\n");
  printTupleDict(dict->next);
}