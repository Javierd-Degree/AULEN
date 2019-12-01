CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EJS = ejemplo1
######################################################################################################################################

all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) -c -g afnd.c

lista_estados.o: lista_estados.c lista_estados.h
	$(CC) -c -g lista_estados.c

minimize.o: minimize.c minimize.h
	$(CC) -c -g minimize.c

ejemplo1: afnd.o lista_estados.o minimize.o
	$(CC) $(CFLAGS) ejemplo1.c afnd.o lista_estados.o minimize.o -o ejemplo1


clean:
	rm -rf *.o *.dot *.png $(EJS)
