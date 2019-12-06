CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
OBJS = afnd.o lista_estados.o diccionario_pares.o minimize.o
EJS = ejemplo1 ejemplo2 ejemplo3
######################################################################################################################################

all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) -c -g afnd.c

lista_estados.o: lista_estados.c lista_estados.h
	$(CC) -c -g lista_estados.c

diccionario_pares.o: diccionario_pares.c diccionario_pares.h
	$(CC) -c -g diccionario_pares.c

minimize.o: minimize.c minimize.h
	$(CC) -c -g minimize.c

ejemplo1: $(OBJS)
	$(CC) $(CFLAGS) ejemplo1.c $(OBJS) -o ejemplo1

ejemplo2: $(OBJS)
	$(CC) $(CFLAGS) ejemplo2.c $(OBJS) -o ejemplo2

ejemplo3: $(OBJS)
	$(CC) $(CFLAGS) ejemplo3.c $(OBJS) -o ejemplo3

clean:
	rm -rf *.o *.dot *.png *.gch $(EJS)
