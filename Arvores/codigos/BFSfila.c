#include "BFSfila.h"

struct nodo {

	Arv* info;
	struct nodo* prox;

};

struct fila { 

	Nodo* inicio;
	Nodo* fim;

};

Fila* BFSfila_criavazia (Fila* f) {
 	 
 	f = (Fila*) malloc(sizeof(Fila));

 	if ( f == NULL) {

		printf("Não há memória suficiente.\n");
		exit (1);

	}

	f -> inicio = NULL;
	f -> fim = NULL;

	return f;

}


int BFSfila_vazia (Fila* f){

	return ( f-> inicio == NULL);

}

Fila* BFSfila_insere (Fila* f, Arv* endereco){

	Nodo* nodo = (Nodo *) malloc(sizeof(Nodo));

	nodo -> info = endereco;
	nodo -> prox = NULL;

	if (BFSfila_vazia(f)){

		f -> inicio = nodo;

	}

	else {

		f -> fim -> prox = nodo;

	}

	f -> fim = nodo;

	return f;
}

Arv* BFSfila_remove (Fila* f){
	
	Arv* endereco = NULL; 

	if (BFSfila_vazia (f)){

		printf("Fila vazia");
		exit(1);	

	}

	Nodo* nodo = f -> inicio;

	endereco = nodo -> info;

	f -> inicio = nodo -> prox;

	if (BFSfila_vazia(f)){

		f -> fim = NULL;

	}

	free (nodo);

	return endereco;

}

void BFSlibera_fila (Fila *f){

	Nodo* q = f -> inicio;

	while (q != NULL){

		Nodo* t = q -> prox;
		free(q);
		q = t;
	}

	free(f);

}
