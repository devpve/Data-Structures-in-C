#include "fila.h"

struct nodo {

	infotype info;
	struct nodo* prox;

};

struct fila { 

	Nodo* inicio;
	Nodo* fim;

};

Fila* fila_criavazia (Fila* f) {
 	 
 	f = (Fila*) malloc(sizeof(Fila));

 	if ( f == NULL) {

		printf("Não há memória suficiente.\n");
		exit (1);

	}

	f -> inicio = NULL;
	f -> fim = NULL;

	return f;

}


int fila_vazia (Fila* f){

	return ( f-> inicio == NULL);

}

void fila_insere (Fila* f, infotype valor){

	Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));

	nodo -> info = valor;
	nodo -> prox = NULL;

	if (fila_vazia(f)){

		f -> inicio = nodo;

	}

	else {

		f -> fim -> prox = nodo;

	}

	f -> fim = nodo;

}

infotype fila_remove (Fila* f){
	
	infotype valor = 0;

	if (fila_vazia (f)){

		printf("Fila vazia");
		exit(1);	

	}

	Nodo* nodo = f -> inicio;

	valor = nodo -> info;

	f -> inicio = nodo -> prox;

	if (fila_vazia(f)){

		f -> fim = NULL;

	}

	free (nodo);

	return valor;

}

void libera_fila (Fila *f){

	Nodo* q = f -> inicio;

	while (q != NULL){

		Nodo* t = q -> prox;
		free(q);
		q = t;
	}

	free(f);

}
