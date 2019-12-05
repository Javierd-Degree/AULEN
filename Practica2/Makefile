CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EJS = ejemplo1
######################################################################################################################################

all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) -c -g afnd.c

lista_estados.o: lista_estados.c lista_estados.h
	$(CC) -c -g lista_estados.c

diccionario_pares.o: diccionario_pares.c diccionario_pares.h
	$(CC) -c -g diccionario_pares.c

minimize.o: minimize.c minimize.h lista_estados.o diccionario_pares.o
	$(CC) -c -g minimize.c lista_estados.o diccionario_pares.o

ejemplo1: afnd.o lista_estados.o minimize.o
	$(CC) $(CFLAGS) ejemplo1.c afnd.o lista_estados.o minimize.o -o ejemplo1


clean:
	rm -rf *.o *.dot *.png $(EJS)
