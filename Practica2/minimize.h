#ifndef MINIMIZE_H
#define MINIMIZE_H

#include "afnd.h"
#include "lista_estados.h"
#include "diccionario_pares.h"


int* estadosAccesibles(AFND* afd);

void *estadosDistinguibles(AFND* afd, int* estadosAccesibles, int numAccesibles);


#endif
