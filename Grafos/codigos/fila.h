#include <stdio.h>
#include <stdlib.h>

typedef struct fila Fila;

Fila* criaFila ();

int filaVazia (Fila* fila);

void enfilere (Fila* fila, int valor);

int desenfilere (Fila* fila);

void liberaFila (Fila* fila);