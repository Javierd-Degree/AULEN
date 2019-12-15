CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
OBJS = afnd.o lista_estados.o diccionario_pares.o estado_compuesto.o minimiza.o
EJS = ejemplo1 ejemplo2 ejemplo3 ejemplo4
######################################################################################################################################

all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) -c -g afnd.c

lista_estados.o: lista_estados.c lista_estados.h
	$(CC) -c -g lista_estados.c

diccionario_pares.o: diccionario_pares.c diccionario_pares.h
	$(CC) -c -g diccionario_pares.c

estado_compuesto.o: estado_compuesto.c estado_compuesto.h
	$(CC) -c -g estado_compuesto.c

minimiza.o: minimiza.c minimiza.h
	$(CC) -c -g minimiza.c

ejemplo1: $(OBJS)
	$(CC) $(CFLAGS) ejemplo1.c $(OBJS) -o ejemplo1
	./ejemplo1
	mkdir -p ./results
	dot -Tpng afnd.dot > ./results/Ejemplo1.png
	dot -Tpng afd_min.dot > ./results/Ejemplo1_min.png

ejemplo2: $(OBJS)
	$(CC) $(CFLAGS) ejemplo2.c $(OBJS) -o ejemplo2
	./ejemplo2
	dot -Tpng afnd.dot > ./results/Ejemplo2.png
	dot -Tpng afd_min.dot > ./results/Ejemplo2_min.png

ejemplo3: $(OBJS)
	$(CC) $(CFLAGS) ejemplo3.c $(OBJS) -o ejemplo3
	./ejemplo3
	dot -Tpng afnd.dot > ./results/Ejemplo3.png
	dot -Tpng afd_min.dot > ./results/Ejemplo3_min.png

ejemplo4: $(OBJS)
	$(CC) $(CFLAGS) ejemplo4.c $(OBJS) -o ejemplo4
	./ejemplo4
	dot -Tpng afnd.dot > ./results/Ejemplo4.png
	dot -Tpng afd_min.dot > ./results/Ejemplo4_min.png

clean:
	rm -rf *.o *.dot *.png *.gch $(EJS)
