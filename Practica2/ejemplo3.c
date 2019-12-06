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

	p_afnd= AFNDNuevo("afnd", 8, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "A",INICIAL);
	AFNDInsertaEstado(p_afnd, "B", NORMAL);
	AFNDInsertaEstado(p_afnd, "C", FINAL);
	AFNDInsertaEstado(p_afnd, "D", NORMAL);
	AFNDInsertaEstado(p_afnd, "E", NORMAL);
	AFNDInsertaEstado(p_afnd, "F", NORMAL);
	AFNDInsertaEstado(p_afnd, "G", NORMAL);
	AFNDInsertaEstado(p_afnd, "H", NORMAL);

	AFNDInsertaTransicion(p_afnd, "A", "0", "B");
	AFNDInsertaTransicion(p_afnd, "A", "1", "F");
	AFNDInsertaTransicion(p_afnd, "B", "0", "G");
	AFNDInsertaTransicion(p_afnd, "B", "1", "C");
	AFNDInsertaTransicion(p_afnd, "C", "0", "A");
	AFNDInsertaTransicion(p_afnd, "C", "1", "C");

	AFNDInsertaTransicion(p_afnd, "D", "0", "C");
	AFNDInsertaTransicion(p_afnd, "D", "1", "G");
	AFNDInsertaTransicion(p_afnd, "E", "0", "H");
	AFNDInsertaTransicion(p_afnd, "E", "1", "F");
	AFNDInsertaTransicion(p_afnd, "F", "0", "C");
	AFNDInsertaTransicion(p_afnd, "F", "1", "G");
	AFNDInsertaTransicion(p_afnd, "G", "0", "G");
	AFNDInsertaTransicion(p_afnd, "G", "1", "E");
	AFNDInsertaTransicion(p_afnd, "H", "0", "G");
	AFNDInsertaTransicion(p_afnd, "H", "1", "C");


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
