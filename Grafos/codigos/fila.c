#include "fila.h"
#include "lista.h"

struct lista {

  infotype info;
  infotype peso;
  struct lista* prox;

};

struct fila {

  struct lista* inicio;
  struct lista* fim;

};

Fila* criaFila (void) {
  Fila* fila = (Fila*) malloc(sizeof(Fila));
  //Assumimos que malloc nunca falha!
  //Por isso não manipulamos excessões para malloc
  fila->inicio = fila->fim = NULL;
  return fila;
}

int filaVazia (Fila* fila) {
  return (fila->inicio == NULL);
}

void enfilere (Fila* fila, int valor) {
  Lista* nodo = (Lista*) malloc(sizeof(Lista*));

  nodo -> info = valor;
  nodo -> prox = NULL;
  
  if (fila -> fim != NULL) //verifica se lista não estava vazia
    fila -> fim -> prox = nodo;

  else
    fila -> inicio = nodo;
  
  fila -> fim = nodo;

}

int desenfilere (Fila* fila) {
  Lista* t;
  int v;
  if (filaVazia(fila)) {
    printf("\nFila vazia!\n");
    return -1; 
  }
  t = fila -> inicio;
  v = t->info;
  fila->inicio = t->prox;
  if (fila->inicio == NULL) // verifica se fila ficou vazia
    fila->fim = NULL;
  free(t);
  return v;
}

void liberaFila (Fila* fila) {
  Lista* q = fila->inicio;
  while (q != NULL) {
    Lista* t = q->prox;
    free(q);
    q = t;
  }
  free(fila);
}