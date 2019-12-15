#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "minimiza.h"

int main(int argc, char ** argv)
{
	
	AFND * p_afnd, * min_afd;

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


	min_afd = AFNDMinimiza(p_afnd);
	AFNDADot(min_afd);
	AFNDADot(p_afnd);

	AFNDElimina(p_afnd);
	AFNDElimina(min_afd);

	return 0;

	
}
