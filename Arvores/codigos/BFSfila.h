#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

typedef struct nodo Nodo;

typedef struct fila Fila;

Fila* BFSfila_criavazia();

int BFSfila_vazia (Fila* fila);

Fila* BFSfila_insere (Fila* fila, Arv* a);

Arv* BFSfila_remove (Fila* fila);

void BFSlibera_fila (Fila* fila);
