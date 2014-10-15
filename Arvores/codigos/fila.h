#include <stdio.h>
#include <stdlib.h>

typedef int infotype;

typedef struct nodo Nodo;

typedef struct fila Fila;

Fila* fila_criavazia();

int fila_vazia (Fila* fila);

void fila_insere (Fila* fila, infotype a);

infotype fila_remove (Fila* fila);

void libera_fila (Fila* fila);
