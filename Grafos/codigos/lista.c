#include "lista.h"

/* Referência ao struct lista */
struct lista {

	infotype info;
	infotype peso;
	struct lista* prox;

};

/* Criaremos um nodo que representa o começo da lista */
Lista* lista_criavazia (Lista* lst) {
 	 
 	lst = (Lista*) malloc(sizeof(Lista));

 	if ( lst == NULL) {

		printf("Não há memória suficiente.\n");
		exit (1);

	}

	lst -> prox = NULL;

	return lst;

}

/* Retorna se a lista está vazio ou não, ou seja o ponteiro aponta pra NULL */
int lista_vazia (Lista* lst){

	return (lst == NULL);

}

/* Como a lista é representado por nodos simplesmente bastar criar um novo nodo e colocá-lo
no início da lista se ela estiver vazia */
Lista* lista_insere (Lista* lst, infotype valor, infotype peso){

	Lista* aux = (Lista *) malloc(sizeof(Lista));

	aux -> info = valor;
	aux -> peso = peso;

	if (lista_vazia(lst)){

		aux -> prox = aux;
	}

	else {

		aux -> prox = lst -> prox;
		lst -> prox = aux;
	}

	return aux;

}

/* Libera a memória alocada pela lista, como usamos uma representação simples de lista sem nodo header 
teremos que liberar os nodos simplesmente */
void libera_lista (Lista* lst){

  if (lst == NULL) return;

  Lista *aux = lst -> prox;
  Lista *ant = lst;

  do {

    ant = aux;
    aux = aux -> prox;
    free(ant);

  } while (aux != lst);

}
