#include "arvore.h"

struct arv {
	
	infotype info;
	struct arv* pai;
	struct arv* esq;
	struct arv* dir;

} ; 


Arv* arv_criavazia (){
	
	return NULL;

}

Arv* arv_criafolha (infotype valor, Arv* pai){

	Arv* a = (Arv *) malloc (sizeof(Arv));

	a -> info = valor;

	a -> esq = NULL;

	a -> dir = NULL;

	a -> pai = pai;

	return a;

}


infotype arv_vazia (Arv* a){

	return (a == NULL);

}

Arv* arv_insere (Arv* a, infotype valor, Arv* pai){
 
    if (arv_vazia(a)){

            a = arv_criafolha (valor, pai);

    }

    else {

        if (valor < a -> info){

           a -> esq = arv_insere (a -> esq, valor, a);

        }

        else {

            a -> dir = arv_insere (a -> dir, valor, a);

        }

    }
    
    return a;
}



Arv* arv_libera (Arv* a){

	if (!arv_vazia(a)){

		arv_libera (a -> esq);  /* libera sae */
		arv_libera (a -> dir);  /* libera sad */
		free(a);

	}

	return NULL;
}

