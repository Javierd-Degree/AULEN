#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "minimize.h"

int main(int argc, char ** argv)
{
	
	AFND * p_afnd;
	int *accesibles;
	int i, numEstados, numAccesibles;

	p_afnd= AFNDNuevo("afnd", 3, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "C",INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd, "D", FINAL);
	AFNDInsertaEstado(p_afnd, "E", NORMAL);

	AFNDInsertaTransicion(p_afnd, "C", "0", "D");
	AFNDInsertaTransicion(p_afnd, "D", "0", "D");
	AFNDInsertaTransicion(p_afnd, "C", "1", "E");
	AFNDInsertaTransicion(p_afnd, "E", "0", "C");
	AFNDInsertaTransicion(p_afnd, "E", "1", "E");
	AFNDInsertaTransicion(p_afnd, "D", "1", "E");


	numEstados = AFNDNumEstados(p_afnd);

	/* Obtenemos una lista que contenga unicamente los estados accesibles */
	accesibles = estadosAccesibles(p_afnd);
	for (i=0, numAccesibles=0; i<numEstados; i++){
		if (accesibles[i] == 1){
			accesibles[numAccesibles] = i;
			numAccesibles++;
		}
	}

	estadosDistinguibles(p_afnd, accesibles, numAccesibles);

	free(accesibles);
	AFNDElimina(p_afnd);

	return 0;

	
}
