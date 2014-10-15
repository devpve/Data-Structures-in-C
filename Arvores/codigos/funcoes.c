#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>

/* Referência de struct arv */
struct arv {
    
    infotype info;
    struct arv* pai;
    struct arv* esq;
    struct arv* dir;

} ; 

typedef struct arv Arv;


/* Função para abrir um arquivo */
FILE* arq_abre (FILE* fp){

    char nomeArq[30];
    
    do {

        printf ("\n\nInforme o nome do arquivo contendo o percorrimento DFS\n");
        scanf ("%s", nomeArq);

        /* Abrimos o arquivo para leitura e retornarmos um ponteiro para o mesmo */
        fp = fopen (nomeArq, "r");

        if (!fp){
            
            printf("\nVocê informou o nome do arquivo errado ou ele não existe, tente novamente.");
        
        }
        
    } while (!fp);

    
    return fp;
}



/* Lê o percorrimento DFS do arquivo considerando que cada número ocupa uma linha */
infotype* arq_leCaminhamentoDFS (FILE *fp, infotype *vet, infotype *contador){

    /* Cria um loop que lerá todos os números do arquivo e armazenará num vetor de inteiros
    contendo as números do arquivo  */
    infotype valor = 0, i = 0;
  
    /* Calculamos o tamanho do arquivo */
    while (!feof(fp)){

        fscanf (fp, "%d\n", &valor);

        *contador = *contador + 1;

    }

    /* Alocamos um vetor dinamicamente com o tamanho */
    vet = (infotype *) malloc (sizeof (infotype) * (*contador) );

     if (vet == NULL) {

        printf("Não há memória suficiente.\n");
        
        exit (1);

    }

    /* Voltamos o ponteiro para o começo do arquivo e colocamos os valores dele no vetor */
    rewind (fp);

    while (!feof(fp)){

        fscanf(fp, "%d\n", &vet[i]);

        i++;

    }
     
    return vet;

}

Fila* arq_leCaminhamentoPreordem (FILE *fp, infotype *contador){

    Fila* f = fila_criavazia();
    infotype valor = 0;

    while (!feof(fp)){

        /* Lemos o valor do arquivo, inserimos na fila, e incrementamos o tamanho */
        fscanf (fp, "%d\n", &valor);

        fila_insere (f, valor);

        *contador = *contador + 1;

    }

    /* Retornamos a fila com todos os elementos do arquivo do percorrimento preordem */
    return f;

}

void ConferePercorrimentos (infotype *vetDFS, Fila* fila_preordem, infotype tamDFS, infotype tamPreordem){

    infotype i, x = 0;

    if (tamDFS != tamPreordem){

        printf("\nOs percorrimentos são diferentes.");
        exit(1);

    }

    printf("\nConferindo os dois percorrimentos...\n");
    while (!fila_vazia (fila_preordem)) {

        i = 0;
        
        x = fila_remove (fila_preordem);

        while (i <= tamDFS){

            if (vetDFS[i] != x){

                i++;

            }

            else 

                break;

        }

        if (i > tamDFS){

            printf("\nOs percorrimentos são diferentes.\n");
            exit(1);

        }
    }

    printf("\nOs percorrimentos são iguais, continuando...\n");
}

int particiona (Fila* preordem, int *vetDFS, infotype inicio, infotype tamanho, infotype x){

    int i, pivo = 0;

    for (i = 0; i < tamanho; i++){

        if (vetDFS[i] == x){

            pivo = i;
            break;

        }
            
    }

    return pivo;

 }


Arv* arv_reconstroi (Arv* arv, Fila* preordem, infotype *vetDFS, infotype inicio, infotype tamanho){

    infotype pivo, x = 0;
   
   /* Enquanto houver elementos na fila do percorrimento preordem significa que ainda temos que
   percorrer a árvore e reconstrui-la */

    while (!fila_vazia(preordem)){

        x = fila_remove (preordem);

        arv = arv_insere (arv, x, arv);

        /* Encontramos o pivô do vetor DFS que representa a raiz da árvore */
        pivo = particiona (preordem, vetDFS, inicio, tamanho, x);

        /* Constrói subárvore esquerda recursivamente com a raiz da árvore sendo
        a raiz da subárvore esquerda */
        arv = arv_reconstroi (arv, preordem, vetDFS, inicio, pivo - 1);

        /* Constrói subárvore direita recursivamente com a raiz da árvore sendo
        a raiz da subárvore direita */
        arv = arv_reconstroi (arv, preordem, vetDFS, pivo + 1, tamanho);

    }

    return arv;
}



/* Préordem usando campo pai. http://haixiaoyang.wordpress.com/2012/04/06/pre-order-traverse-of-a-binary-tree-with-parent-pointer/ */
void arv_Preordem (Arv* arv){

    Arv* aux = arv;

    while (aux != NULL){

        printf("%d ", aux -> info);

        if (aux -> esq != NULL){

            aux = aux -> esq;
        }

        else if (aux -> dir != NULL){

            aux = aux -> dir;
        }

            else {

                while (aux -> pai != NULL && aux != aux -> pai -> esq)
                    aux = aux -> pai;

                if (aux -> pai == NULL) 
                    break;

                else aux = aux -> pai -> dir;

            }
    }

}


/* Pósordem usando campo pai */
void arv_Posordem (Arv* arv){

    Arv* aux = arv;

     if (aux -> esq != NULL){

            aux = aux -> esq;
        }

    if (aux -> dir != NULL){

            aux = aux -> dir;
    }

   

}

/* DFS não recursivo */
void arv_DFS (Arv* arv){

    
	/* O percorrimento em DFS não pode conter um campo pai, não pode ser usado uma pilha. Usaremos os campos dir das folhas
	que forem nulos para alterar a árvore. No final a árvore terá que voltar a sua forma original sem nenhuma mudança nos
	campos de endereçamento. 

    Código encontrado e levemente adaptado de:

      http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
    Acessado em  05/06/2014 */

	if (arv_vazia(arv)) return;

    Arv* aux = arv_criavazia();
    Arv* pre = arv_criavazia();

    aux = arv;


    /* Enquanto aux não for nulo percorreremos a árvore usando o caminhamento DFS */
    while (aux != NULL){

        /* Se não houver elementos a esquerda não há necessidade de descer a árvore 
        logo imprimimos o nodo atual e continuamos para a direita */
        if (aux -> esq == NULL){

            printf("%d ", aux -> info);
            aux = aux -> dir;

        }

        /* Existe elementos em aux -> esq logo fará: */
        else { 

            /* O pre receberá o elemento aux -> esq que é o atual */
            pre = aux -> esq;

            /* Enquanto houver algo a direita do aux -> esq e 
            e este elemento for diferente do aux que representa o irmao
            de aux -> esq, avancaçaremos a direita do aux -> esq  */

            while (pre -> dir != NULL && pre -> dir != aux) 

                pre = pre -> dir;


            if (pre -> dir == NULL){

                pre -> dir = aux;
                aux = aux -> esq;

            }

            /* Voltamos na árvore para colocar NULL nos campos a direita que utilizamos anteriormente e fazendo
            a impressão preordem */
            else { 

                pre -> dir = NULL;
                printf ("%d ", aux -> info);
                aux = aux -> dir;
            }

        }

    }

}


/* Para o BFS usaremos uma fila de prioridade, enfileirando a árvore com seus ponteiros para podermos
imprimir em largura, ou seja nível a nível. Como trataremos de ponteiros usaremos funções diferentes
das encontradas em fila.h, usaremos a BFSfila.h Código baseado em notas de aula. */

void arv_BFS (Arv* arv){

    Fila* fila = BFSfila_criavazia();

    Arv* nodo = arv_criavazia();

    fila = BFSfila_insere (fila, arv);

    while (!BFSfila_vazia(fila)){

        nodo = BFSfila_remove(fila);

        printf("%d ", nodo -> info);

        if (nodo -> esq != NULL){

            fila = BFSfila_insere (fila, nodo -> esq);

        }

        if (nodo -> dir != NULL){

            fila = BFSfila_insere (fila, nodo -> dir);
 
        }

    }

    /* Terminou de imprimir */ 
    BFSlibera_fila (fila);

}
