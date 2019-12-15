#ifndef MINIMIZA_H
#define MINIMIZA_H

#include "afnd.h"
#include "lista_estados.h"
#include "diccionario_pares.h"

/* Metodo que permite minimizar un automata finito determinista
Parametros
	afd -> puntero al automata finito determinista a simplificar 
Return
	Nuevo autómata con los estados inaccesibles eliminados 
	y con agrupación de estados distinguibles
*/
AFND * AFNDMinimiza(AFND * afd);

#endif
