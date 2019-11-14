CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
EJS = ejemplo1 ejemplo2 ejemplo3 ejemplo4
######################################################################################################################################

all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) -c afnd.c

ejemplo1: afnd.o
	$(CC) $(CFLAGS) ejemplo1.c state.c afnd.o transforma.c -o ejemplo1
	./ejemplo1
	dot -Tpng afnd.dot > Ejemplo1.png
	dot -Tpng afd.dot > Ejemplo1_sol.png

ejemplo2: afnd.o
	$(CC) $(CFLAGS) ejemplo2.c state.c afnd.o transforma.c -o ejemplo2
	./ejemplo2
	dot -Tpng afnd.dot > Ejemplo2.png
	dot -Tpng afd.dot > Ejemplo2_sol.png

ejemplo3: afnd.o
	$(CC) $(CFLAGS) ejemplo3.c state.c afnd.o transforma.c -o ejemplo3
	./ejemplo3
	dot -Tpng afnd.dot > Ejemplo3.png
	dot -Tpng afd.dot > Ejemplo3_sol.png

ejemplo4: afnd.o
	$(CC) $(CFLAGS) ejemplo4.c state.c afnd.o transforma.c -o ejemplo4
	./ejemplo4
	dot -Tpng afnd.dot > Ejemplo4.png
	dot -Tpng afd.dot > Ejemplo4_sol.png

clean:
	rm -rf *.o *.dot *.png $(EJS)
