/*******************************************************************************************************
    UnB - Universidade de Brasília
    Estrutura de Dados - Turma A - 1/2014
    Professor: José Loureiro Ralha
    Nome: Paulo Victor Gonçalves Farias
    Matrícula: 13/0144754
    Trabalho3 - Grafos
 -------------------------------------------------------------
 
 Neste trabalho queremos expor funções que manipulam grafos. 

 -------------------------------------------------------------

 > > 1ª Etapa: 
      
      Primeiramente leremos de um arquivo as informações acerca de um grafo.   
    
 > > 2ª Etapa:

      Se o grafo tiver mais de uma componente conexa, inseriremos arestas
      até ela se tornar uma só. 

 > > 3ª Etapa: 

    Realizaremos os percorrimentos DFS e BFS no grafo G' 

 > > 4ª Etapa: 

    Implementação do algoritmo de Djikstra sobre o grafo.

 > > 5ª Etapa:

    Usaremos o algoritmo de Kruskal para determinar a árvore de espalhamento mínimo do grafo.
    
********************************************************************************************************/

/* Bibliotecas usadas 
    funcoes.h: contém a inclusão das bibliotecas padrões <stdio.h> e <stdlib.h> assim como
    a grafo.h e lista. h */

#include "funcoes.h"

/********************************************************************************************************/

/* Referência aos tipos abstratos */

struct lista {

  infotype info;
  infotype peso;
  struct lista* prox;

};

struct grafo {

  TipoValorVertice NumVertices;
  TipoValorAresta NumArestas;
  TipoPeso* Distancia;
  TipoValorVertice* Acumulado;
  TipoValorVertice* Pai;
  short int* Visita;
  Lista** adjlst;
  short int dirigido;

};

/********************************************************************************************************/
 int main(){ 
/********************************************************************************************************/   

/* Variáveis usadas 
 
   - um ponteiro para um arquivo de entrada de onde será lida as informações a respeito do grafo 
   - vetor de caracteres - string com o nome do arquivo
   - um grafo    
                                                                                                  */

FILE *arq_Grafo = NULL;
char arq_Nome[30];
Grafo* grafo_x = NULL;

/*******************************************************************************************************

    > > 1ª Etapa:

        - Leremos o grafo de um arquivo de entrada com as seguintes configurações:

             --> A 1ª linha apresenta três valores inteiros. 
                 Primeiro: número de vértices
                 Segundo: número de arestas
                 Terceiro: 0 e 1 (Se for 1 o grafo é dirigido e se for 0 o grafo não é dirigido)
            
             --> As demais linhas são compostas por três valores inteiros 
                 Primeiro e Segundo: arestas (primeiro valor representa o vértice de origem e 
                 outro o vértice de destino)
                 Terceiro: peso relacionado a aresta

         
                                                                                                    */


    /* Chamamos a função arq_abre para abrir o arquivo, a função retornará um ponteiro para este arquivo*/
    arq_Grafo = arq_abre(arq_Grafo, arq_Nome);

    /* Chamamos a função constrói grafo que retorna um grafo construído com as informações encontradas
    no arquivo */
    grafo_x = Constroi_Grafo(grafo_x, arq_Grafo); 


/*******************************************************************************************************

    > > 2ª Etapa:

        - Uma função que determine as componentes conexas do grafo lido. Vamos chamar esse grafo 
        lido de grafo_x.
        - Se o grafo G tiver mais de uma componente conexa, transformaremos o grafo_x num novo 
        grafo com o mesmo nome, inserindo arestas conectando as componentes conexas. Como o grafo 
        é ponderado escolheremos um valor positivo randômico de 1 a 10 para os pesos das arestas 
        inseridas.


                                                                                                    */

    /* Chamamos a função ComponentesConexas para descobrir se precisaremos tratar do grafo a seguir */
    int x = ComponentesConexas (grafo_x);

        printf("Existem %d componentes conexas\n", x);

        /* Grafo com mais de uma componente conexa, vamos ligá-las */
        if (x > 1){
            
            printf("Grafo com mais de uma componente conexa, conectando-as . . . \n");
            grafo_x = ConectaConexas(grafo_x);
            
            printf("Conectadas com sucesso.\n");

        }


/*******************************************************************************************************

    > > 3ª Etapa:

        - Realizaremos os percorrimentos DFS e BFS no grafo. 
                                                                                                    */

         printf("DFS começando por 0 temos: ");
         DFS_Grafo(0, grafo_x);
         BFS_Grafo(0, grafo_x);

/*******************************************************************************************************

    > > 4ª Etapa:

        - Implementaremos uma função que apresenta o algoritmo de Djikstra sobre o grafo, tomando
        o vértice s de origem como 0. 
                                                                                                    */

        Dijkstra_Grafo(grafo_x, 0);

/*******************************************************************************************************

    > > 5ª Etapa:

        - Encontrar a MST (Minimum Spanning Tree), árvore de espalhamento mínimo do grafo usando
        o algoritmo de Kruskal.


                                                                                                    */
       Kruskal_Grafo(grafo_x, 0);

/*******************************************************************************************************/

    /* Finalizando o programa e liberando a memória alocada pelo grafo */

    liberaGrafo(grafo_x);

    return 0;

}