# I am a comment, and I want to say that the variable CC will be
# the compiler to use. If not set, gcc will be taken by default

CC=gcc

# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

CFLAGS=-c -Wall

all: trabalho2

trabalho2: fila.o arvore.o funcoes.o cliente.o
	$(CC) fila.o arvore.o funcoes.o cliente.o -o trabalho2

fila.o: fila.c
	$(CC) $(CFLAGS) fila.c

arvore.o: arvore.c
	$(CC) $(CFLAGS) arvore.c

funcoes.o: funcoes.c
	$(CC) $(CFLAGS) funcoes.c

cliente.o: cliente.c
	$(CC) $(CFLAGS) cliente.c

clean:
	rm -rf *.o  *~

