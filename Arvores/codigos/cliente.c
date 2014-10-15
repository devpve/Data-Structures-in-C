/*******************************************************************************************************
    UnB - Universidade de Brasília
    Estrutura de Dados - Turma A - 1/2014
    Professor: José Loureiro Ralha
    Nome: Paulo Victor Gonçalves Farias
    Matrícula: 13/0144754
 ------------------------------------------

   >>> O trabalho será divido em 3 etapas:

    1 - O programa receberá uma arquivo contendo os dois percorrimentos (DFS e Preordem)
    de uma árvore original, e construirá a árvore original que gerou estes percorrimentos.

    2 - Realizará os três percorrimentos sobre essa árvore.

    3 - Realiza um ultimo percorrimento BFS que mostrará a estrutura da árvore binária
    por nível.


********************************************************************************************************/

#include <stdio.h>
#include "funcoes.h"

/* Referência ao struct arv */
struct arv {
    
    infotype info;
    struct arv* pai;
    struct arv* esq;
    struct arv* dir;

} ; 

typedef struct arv Arv;
/******************************************************************************************************/

int main() { 

/******************************************************************************************************

     >>> Declaração de variáveis usadas:

        Ponteiro para o arquivo contendo o percorrimento DFS
        Ponteiro para o arquivo contendo o percorrimento preordem

        Vetor de inteiros para armazenar o percorrimento DFS, preordem.

        Cria uma variável para a árvore binária que será reconstruída                                */


    FILE* fp_dfs = NULL;
    FILE* fp_preordem = NULL;

    Fila* fila_preordem = fila_criavazia();

    int *vetDFS = NULL, tamDFS = 0, tamPreordem = 0, x = 0;

    Arv* arv_bin = arv_criavazia();

/******************************************************************************************************

  >>> ETAPA 1:

        > 1.1 : Lê os caminhamentos de dois arquivos 
        > 1.2 : Reconstrói a árvore binária        
                                        
                                                                                                     */

    /* > 1.1 */

        
        fp_dfs = arq_abre(fp_dfs);
        
        fp_preordem = arq_abre(fp_preordem);

        /* Passamos o ponteiro para o arquivo, o vetorDFS e passamos o endereço de 
        tamDFS como referência para ele ser recebido da função */

        vetDFS = arq_leCaminhamentoDFS (fp_dfs, vetDFS, &tamDFS);

        fila_preordem = arq_leCaminhamentoPreordem (fp_preordem, &tamPreordem);

    /* > 1.2 */

        /* Chama a função de reconstrução da árvore binária utilizando o vetor DFS contendo
        as informações sobre o percorrimento DFS e a fila dos elementos do vetor Preordem,
        colocamos a raiz na árvore primeiramente, que no caso é o primeiro elemento da fila */

        x = fila_remove (fila_preordem);

        arv_bin = arv_insere (arv_bin, x, NULL);

        arv_bin = arv_reconstroi (arv_bin, fila_preordem, vetDFS, 0, tamDFS);


/********************************************************************
    >>> ETAPA 2 
        
        > 2.1: Realiza os percorrimentos préordem e pósordem
        utilizando um campo de ponteiro pai. 

        > 2.2: Realiza o percorrimento DFS (busca em profundidade) usando 
        campos de ponteiros NULL da direita das folhas da árvore.

                                                                         */

    /* 2.1 */
    printf("\n\n Percorrimento Préordem: ");
    arv_Preordem (arv_bin);

    printf("\n\n Percorrimento Pósordem: ");
    arv_Posordem (arv_bin);

    /* 2.2 */
    printf("\n\n Percorrimento DFS (percorrimento em profundidade): ");
    arv_DFS (arv_bin);

/********************************************************************

    >>> ETAPA 3 

        > Realiza um percorrimento BFS (busca em largura) 
        mostrando a estrutura da árvore 

                                                                    */
    printf("\n\n Percorrimento BFS (percorrimento em largura): ");

    arv_BFS (arv_bin);

/********************************************************************
        Libera a memória alocada, e termina o programa */

    free (vetDFS);

    libera_fila (fila_preordem);

    arv_libera (arv_bin);

    fclose(fp_dfs);

    fclose(fp_preordem);
    
    /* Fim do programa */

    printf("\n\n Fim ... encerrando. \n");
    
    return 0;
}
