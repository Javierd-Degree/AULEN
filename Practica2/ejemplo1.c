#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "minimize.h"
#include "lista_estados.h"

int main(int argc, char ** argv)
{
	AFND * p_afnd;
	int* accesibles;
	int i, numEstados;


	LList * list;
	list = createLList(5);
	/* printState(state); */
	addToLList(list, 4);
	addToLList(list, 3);
	addToLList(list, 5);
	addToLList(list, -1);
	addToLList(list, 12);
	printLList(list);
	printf("Num elementos %d\n", getLListLength(list));
	deleteLList(list);


	p_afnd= AFNDNuevo("afnd", 6, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", FINAL);

	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "1", "q3");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q0");


	AFNDInsertaTransicion(p_afnd, "q4", "0", "q5");
	AFNDInsertaTransicion(p_afnd, "q4", "1", "q5");
	AFNDInsertaTransicion(p_afnd, "q5", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q5", "1", "q4");


	numEstados = AFNDNumEstados(p_afnd);
	accesibles = estadosAccesibles(p_afnd);
	for(i=0; i<numEstados; i++){
		if (accesibles[i] == 1)
			printf("%d\t", i);
	}

	printf("\n");

	free(accesibles);
	AFNDElimina(p_afnd);

	return 0;
}
