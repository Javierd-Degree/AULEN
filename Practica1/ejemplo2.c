#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd= AFNDNuevo("afnd", 6, 3);

	AFNDInsertaSimbolo(p_afnd,"+");
	AFNDInsertaSimbolo(p_afnd, "0");
	AFNDInsertaSimbolo(p_afnd,".");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);
	
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q1", "q2");
	AFNDInsertaLTransicion(p_afnd, "q3", "q4");
	AFNDInsertaLTransicion(p_afnd, "q4", "q5");
	AFNDCierraLTransicion(p_afnd);


	AFNDADot(p_afnd);

	afd = AFNDTransforma(p_afnd);
	AFNDADot(afd);

	AFNDElimina(p_afnd);
	AFNDElimina(afd);

	return 0;
}
