# I am a comment, and I want to say that the variable CC will be
# the compiler to use. If not set, gcc will be taken by default

CC=gcc

# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

CFLAGS=-c -Wall

all: trabalho3

trabalho3: fila.o lista.o grafo.o funcoes.o cliente.o
	$(CC) fila.o lista.o grafo.o funcoes.o cliente.o -lm -o trabalho3

fila.o: fila.c
	$(CC) $(CFLAGS) fila.c

lista.o: lista.c
	$(CC) $(CFLAGS) lista.c

grafo.o: grafo.c
	$(CC) $(CFLAGS) grafo.c

funcoes.o: funcoes.c
	$(CC) $(CFLAGS) funcoes.c -lm

cliente.o: cliente.c
	$(CC) $(CFLAGS) cliente.c

clean:
	rm -rf *.o  *~

