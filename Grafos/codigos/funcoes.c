/*********************************************************************************************************/

/* Bibliotecas usadas 
  - funcoes.h: Contém as funções que usaremos durante a execução do programa.
  - grafo.h: Contém as rotinas de grafo implementado com uma lista de adjacência. */

#include "funcoes.h"
#include <limits.h>
#define VISITADO 1
#define NAOVISITADO 0

/********************************************************************************************************/
/* Referência aos registros usados e definições de tipo */
typedef int infotype;

struct lista {

  infotype info;
  infotype peso;
  struct lista* prox;

};

struct fila {

  struct fila* inicio;
  struct fila* fim;
};

struct nodo {

  int vertex;
  struct nodo* prox;

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

/*********************************************************************************************************

  > > Índice de funções usadas:

      1. arq_abre
      2. constroi_Grafo
      3. ComponentesConexas
      4. ConectaConexas
      5. mergulhaFundo
      6. DFS_Grafo
      7. BFS_Grafo
      8. Djikstra_Grafo
      9. Kruskal_Grafo


*********************************************************************************************************

  1. arq_abre

       > > Argumentos: ponteiro para um arquivo, uma string (vetor de caracteres)
    
       > > Descrição: perguntamos o nome do arquivo de entrada e tentaremos abri-lo para leitura, caso
       o ponteiro aponte para NULL, não foi possível abrir o arquivo ou o nome informado foi errado.
       Perguntamos se o usuário quer tentar novamente. Caso sim ele entrará novamente na iteração,
       caso contrário terminaremos o programa.

       > > Retorno: ponteiro para um arquivo a ser lido.


                                                                                                               */

FILE* arq_abre (FILE* fp, char nomeArq[]){

  char x;

    do {

      printf("\nInforme o nome do arquivo de entrada:\n");
      scanf("%s", nomeArq);
      getchar();

      fp = fopen (nomeArq, "r");
       
      if (fp == NULL){

        printf("Você informou o nome do arquivo errado ou ele não existe, deseja tentar novamente? (S/N) \n");
        scanf("%c", &x);

      }

      if (x == 'n' || x == 'N'){

        printf("Tchau!\n");
        exit(1);

      }
        
    } while (!fp);

  return fp;

}

/*********************************************************************************************************

  2. constroi_Grafo

       > > Argumentos: ponteiro para um arquivo, uma variável grafo
    
       > > Descrição: construiremos um grafo a partir das informações encontradas no arquivo.

       > > Retorno: um grafo com as informações lidas do arquivo.


                                                                                                               */

Grafo* Constroi_Grafo (Grafo* grafo, FILE* fp){

  int numVertices, numArestas, tipoGrafo, origem, destino, peso;

    /* A 1ª linha contém:
       numVertices numArestas tipoGrafo (0 ou 1) 
                                          (1 para dirigido e 0 para não dirigido) */

    fscanf (fp, "%d ", &numVertices);
    fscanf (fp, "%d ", &numArestas);
    fscanf (fp, "%d\n", &tipoGrafo);

  /* Se o grafo for dirigido chamamos a função criaGrafoVazio com o número de vértices
  de arestas e o tipo */

  if (tipoGrafo == 1)

    grafo = criaGrafoVazio (numVertices, numArestas, tipoGrafo);

  /* Senão, ele é não dirigido, cada vértice aponta para ele mesmo
  e o caminho de volta, por isso 2 * numArestas */

  else 
    
    grafo = criaGrafoVazio (numVertices, 2*numArestas, tipoGrafo);

  /* As próximas linhas do arquivo terão a seguinte estrutura
    VerticeDeOrigem VerticeDeDestino PesoDaAresta */

  /* enquanto não chegarmos ao final inseriremos arestas no grafo com 
  as informações do arquivo */
  while (!feof(fp)){

    fscanf(fp, "%d ", &origem);
    fscanf(fp, "%d ", &destino);
    fscanf(fp, "%d\n", &peso);

    insereAresta (origem, destino, peso, grafo);

  }

  return grafo;

}

/*********************************************************************************************************

  3. ComponentesConexas

       > > Argumentos: um grafo podendo ser dirigido ou não dirigido.
    
       > > Descrição: esta função determinará quantas componentes conexas um grafo possui.

       > > Retorno: um inteiro com a quantidade de componentes conexas de um grafo.


                                                                                                               */

int ComponentesConexas (Grafo* grafo){

  /* Declaramos dois contadores, um para o loop e o outro para o número de componentes conexas,
  uma variável com o número de vértice também é declarada para melhor legibilidade do programa. */

  int i, x = 0, numVertices = grafo -> NumVertices;

  /* Vamos percorrer a lista de adjacência checando a estrutura do grafo */
  for (i = 0; i < numVertices; i++){

    /* Se um grafo não tem nada em sua lista de adjacência significa que ele é isolado dos outros
    portanto representa uma componente, incrementaremos o contador x */
    if (!temAdjacentes (i, grafo)) x++;
    
    /* Se o grafo atual não possuir aresta com o próximo elemento, por exemplo i = 2 e i + 1 = 3: 
      
        1   3  
        |
        2


      Não possuem arestas - OK
      E o número i for maior que 0, no caso do exemplo 2 - OK.
      E checamos outra condição se i - 1 = 1 e i + 1 = 3, possuem aresta, no caso também não - OK
      O contador será incrementado                                                                */

    else if ((!existeAresta(i, i+1, grafo)) && i > 0 && (!existeAresta(i - 1, i + 1, grafo))) x++;

  } /* fim do for */
  
  /* retornamos o contador x */        
  return x;

}

/*********************************************************************************************************

  4. ConectaConexas

      > > Argumentos: um grafo com mais de uma componente conexa, pode ser dirigido ou não, tanto faz. 
    
      > > Descrição: esta função tratará do caso de mais de uma componente conexa, as conectaremos de
      forma sequencial ou seja se: 

            4--5   7
            |
            6
  
      Ligaremos o 6 ao 7. 

      > > Retorno: um grafo com apenas uma componente conexa.



                                                                                                               */

Grafo* ConectaConexas (Grafo* grafo){
  
  /* Declaramos dois contadores, um para o loop e 
  uma variável com o número de vértice também é declarada para melhor legibilidade do programa. */

  int i, numVertices = grafo -> NumVertices;

  for (i = 0; i < numVertices; i++){

    /* Tratamento vértices isolados : */

      /* Se o vértice for isolado inseriremos uma aresta com o próximo vértice como destino. */
      if ((!temAdjacentes (i, grafo))){

        /* Porém apenas faremos isso se ele não for último.*/ 
        if (i + 1 != numVertices && grafo -> dirigido == 1)
                                  /* peso será um nº entre 0 e 10 */
          insereAresta (i, i + 1, rand() % 10, grafo);

        if (i + 1 != numVertices && grafo -> dirigido == 0){

          insereAresta(i, i + 1, rand() % 10, grafo);
          insereAresta(i + 1, i, rand() % 10, grafo);

        }
        
        /* Se o grafo não for dirigido teremos uma aresta voltando para o vértice anterior */
        if (i + 1 == numVertices && grafo -> dirigido == 1)

                            /* peso será um nº entre 0 e 10 */
          insereAresta (i, i - 1, rand() % 10, grafo); /* se o grafo for dirigido e o último elemento dele não tiver nenhum elemento adjacente
                                      teremos que colocar uma aresta voltando para o outro vértice */
        if (i + 1 == numVertices && grafo -> dirigido == 0){

          insereAresta(i - 1, i, rand() % 10, grafo);
          insereAresta(i, i - 1, rand() % 10, grafo);

        }

      }
    
    /* Tratamento para outras estruturas não isoladas porém desconexas entre si */

      /* Se o grafo atual não possuir aresta com o próximo elemento, por exemplo i = 2 e i + 1 = 3: 
      
        1   3  
        |
        2


      Não possuem arestas - OK
      E o número i for maior que 0, no caso do exemplo 2 - OK.
      E checamos outra condição se i - 1 = 1 e i + 1 = 3, possuem aresta, no caso também não - OK
      
      Se o grafo não for dirigido inseriremos 2 arestas uma indo e uma voltando da origem para
      o destino e vice-versa. 
      Caso contrário inseriremos apenas uma da origem para o destino.                             */


      else if ((!existeAresta(i, i+1, grafo)) && i > 0 && (!existeAresta(i - 1, i + 1, grafo)) && i + 1 != numVertices){

          if (grafo -> dirigido == 0){

            insereAresta(i, i + 1, rand() % 10, grafo);
            insereAresta(i + 1, i, rand() % 10, grafo);

          }

          else insereAresta(i, i +1, rand() % 10, grafo);
      
      }

  } /* fim do loop for */

  return grafo;

}


/*********************************************************************************************************

  5. DFS_Grafo:

    5.1: mergulhaFundo:

       > > Argumentos: 
    
       > > Descrição: 

       > > Retorno: nenhum



                                                                                                               */



void mergulhaFundo (TipoValorVertice vertice, Grafo* grafo) {

  Lista* p; /* ponteiro de lista usado para percorrer a lista de adjacência do vertice */
  Lista* q = grafo -> adjlst[vertice] -> prox; /* usado para segurar o início da lista */
  TipoValorVertice v; /* o vértice apontado por p */

  /* Como começamos pelo vertice recebido na função, marcamos ele como visitado */
  grafo -> Visita[vertice] = VISITADO;

  p = q;
  /* enquanto não voltar ao início da Lista de Adjacência do vertice */

  do {

    /* vértice recebe a informação de p */
    v = p -> info;

    if (grafo -> Visita[v] == NAOVISITADO){

      printf(" %d  ", v); 

        mergulhaFundo(v, grafo);

      }

    p = p -> prox;
  

  } while(p!=q);

}
/*********************************************************************************************************

  5.2: DFS_Grafo:

       > > Argumentos: um vértice origem e um grafo.
    
       > > Descrição: algoritmo de percorrimento usado para fazer a busca em profundidade sobre o grafo.

       > > Retorno: nenhum
                                                                                                    */

void DFS_Grafo (TipoValorVertice vertice, Grafo* grafo) {
  
  TipoValorVertice numVertices = grafo -> NumVertices;

  /* Agora será necessário alocar o vetor com a informação de visita para cada vértice */

  grafo -> Visita = (short int*) malloc(numVertices*sizeof(short int));

  /* inicializamos o vetor com NAOVISITADO que significa 0 */
  int i;
  for (i = 0; i < numVertices; i++) grafo -> Visita[i] = NAOVISITADO;
  
  /* Mergulhamos em profundidade no grafo */
  mergulhaFundo(vertice, grafo);

  /* Terminou o percorrimento, libera o vetor de visita */
  free (grafo -> Visita);
  
}


/*********************************************************************************************************

  6. BFS_Grafo
      
       > > Argumentos: 
    
       > > Descrição: 

       > > Retorno: 



                                                                                                               */
void BFS_Grafo (TipoValorVertice origem, Grafo* grafo){
  
  TipoValorVertice numVertices = grafo -> NumVertices;
  /* 
     Só agora será necessário alocar um vetor para marcar: 
       1) os vértices visitados
       2) a distância do vértice corrente ao vértice inicial 
          (medido em arestas)
   */
  grafo -> Visita = (short int*) malloc(numVertices*sizeof(short int));
  grafo-> Distancia = (TipoPeso*) malloc(numVertices*sizeof(TipoPeso));
  /* 
     Agora precisamos iniciar o vetor MARCA com NAOVISITADO 
     pois no início de FS nenhum vértice foi visitado. 
  */
  int i;
  for (i = 0; i < numVertices; i++) grafo -> Visita[i] = NAOVISITADO;
 
  TipoPeso peso;
  TipoValorVertice u, v;
  Fila *Q = criaFila(); //criação da fila auxilar ao percorrimento

  enfilere(Q, origem);

  grafo-> Visita [origem] = VISITADO;
  grafo-> Distancia [origem] = 0;
  printf("BFS: comecei o percorrimento pelo  vértice %d ", origem); 

  while ( !filaVazia(Q) ) { 
    u = desenfilere(Q); 
    /* **************************************** */
    /* Ao invés de um PARA eu vou usar um WHILE */
    /* **************************************** */
    /*   inicialização da variável de controle  */
    v = primeirodaLista(grafo -> adjlst[u], &peso);
    while (v != -1) {

      if (grafo -> Visita[v] == NAOVISITADO) {
          
          enfilere (Q, v);
          grafo-> Distancia[v] = grafo->Distancia[u] + 1;
          grafo-> Visita[v] = VISITADO;
          printf("\nBFS: do vértice %2d continuei para o vértice %2d ",u,v);
          printf("que está a %2d arestas de distância de %2d", grafo -> Visita[v], origem);
      }/* fim do if */
    /* a próxima instrução atualiza a variável de controle do while */
      v = proximoAdjacente(u, grafo, v, &peso);
    }/* fim do while(v != -1) */
  }/* fim do while (!filaVazia)  */
}

/*********************************************************************************************************

  7. Djikstra_Grafo

       > > Argumentos: 
    
       > > Descrição: 

       > > Retorno: 



                                                                                                               */
       
/* ###################################################################### */
/* ###################################################################### */
/*
   O próximo bloco de funções e declarações está relacionado ao algoritmo de
                                   DIJKSTRA

   O algoritmo usa a técnica de programação dinâmica onde os melhores valores
   são escolhidos na esperança de se obter um bom resultado. No caso do 
   algoritmo de Dijkstra esse é de fato o caso. Ao final do processamento 
   obtemos a melhor solução possível.

   Observação: Procurei seguir ao máximo o pseudocódigo apresentado no 
               Cormen et al.
*/
/* ###################################################################### */
/* ###################################################################### */
typedef TipoValorVertice Set;

Set* criaConjuntoVazio(Grafo *grafo) {
  TipoValorVertice nv = grafo -> NumVertices;
  
  Set *conj = (Set*) malloc(nv*sizeof(Set));
  int i;
  /* 
     Vamos iniciar o conjunto conj como VAZIO. 
  */
  for (i=0; i<nv; i++) conj[i] = 0;
  /* 
     A ideia é fazer o índice ser o representante do conjunto. 
     Se nessa posição o valor armazenado for 1, então i pertence 
     ao conjunto. Se todas as posições forem 0, então está vazio. 

     Exercício: implemente o tipo Set e suas funções usando um bitstring.
  */
  return conj;
}


void insereElemento (Set *S, TipoValorVertice u) {  

  S[u] = 1; 

}

/*
   Just in case. Notem que estas funções de impressão não são "exportadas"
*/
void ImprimeAcumulado (Grafo *grafo) {

  TipoValorVertice i, nv = grafo -> NumVertices;

  for (i=0; i<nv; i++) 
    printf("\ngrafo -> Acumulado[%d] = %d",i,grafo -> Acumulado[i]);

}

void ImprimeMARCA (Grafo *grafo) {
  
  TipoValorVertice i, nv = grafo->NumVertices;
  
  for (i=0; i<nv; i++) 
    printf("\ngrafo-> Visita[%d] = %d", i, grafo -> Visita[i]);

}


/*
   Vamos caracterizar a FILA de PRIORIDADES.
   Um nodo de minha fila de prioridades tem dois campos:
     1) um vertice u qualquer,
     2) custo corrente desse vértice u. Esse custo será atualizado 
                                        durante o processamento.

   A minha FILA de PRIORIDADES será implementada sobre um vetor dinâmico
   cujo tamanho depende do grafo que esteja usando DIJKSTRA. Como a fila
   diminui de tamanho a cada remoção, vamos usar um campo para armazenar
   o tamanho corrente da fila e consequentemente qual parte do array 
   podemos mexer.
   A idéia (uma boa ideia tem assento) é colocar na posição ZERO do array 
   o vértice prioritário (que é aquele com o menor custo corrente).
   Com isso o tamanho diminui e o vetor encolhe do fim para o começo.
 
*/
struct nodofp {

  TipoValorVertice vertice;
  TipoPeso custo; //custo corrente associado ao nodo

};

typedef struct filaprio {

  struct nodofp *fila; //array dinâmico de nodofp
  int tam;//tamanho corrente da fila

} FP;


/*
   Função que inicia a Fila de Prioridades.
   Vide comentários no corpo da função.
*/
FP* InitFP (Grafo *grafo, TipoValorVertice source) {

  TipoValorVertice i, nv = grafo -> NumVertices;
  /*
     Vamos alocar o header da Fila de Prioridades.
  */
  FP *fp = (FP*) malloc(sizeof(FP));
  /*
     E agora vamos alocar o array que "segura" a Fila de Prioridades.
  */
  fp -> fila = (struct nodofp*) malloc(nv*sizeof(struct nodofp));

  /* No início, temos que inserir todos os vértices de G associando um 
     custo INFINITO (INT_MAX definido em limits.h) a todos os vértices 
     do grafo exceto o vértice source o qual recebe o valor 0.

     Notem que o vértice de partida (parâmetro denominado source) não tem
     nenhuma relação com o índice do array que "segura" a Fila de Prioridades.
  */
  for (i=0; i<nv; i++) {
    fp->fila[i].vertice = i; 
    fp->fila[i].custo = INT_MAX;
  }
  fp->tam = nv;
  fp->fila[0].vertice = source;
  fp->fila[0].custo = 0;
  return fp;
}


int vaziaFP (FP *queue) {//Fila Vazia; que mais poderia ser?
  if (queue->tam == 0) return 1;
  return 0;
}

/*
   Just in case. Vai que você quer saber quem tá na fila ou como as coisas
                 tão rolando durante o processamento.
*/
void ImprimeFila (FP *fila) {
  int i, tamanho = fila->tam;
  for (i=0; i<tamanho; i++) {
    printf("\n fila->fila[%d].vertice=%d",i, fila->fila[i].vertice);
    printf("  fila->fila[%d].custo=%d",i, fila->fila[i].custo);
  }
  printf("\n fila->tam=%d\n\n",fila->tam);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Após um elemento ter sido removido da Fila de Prioridades e
// devido ao fato de que os valores de custo corrente associados
// aos vértices mudam durante o processamento, vamos realizar a
// procura do melhor vértice. Ao acharmos, e tendo em vista que 
// já entregamos o que estava na posição 0 e esta está disponível 
// para ocupação, passamos o menor corrente para a posição zero.
// Isso vai deixar um buraco no array que tampamos passando o 
// carinha que estava na última posição pro "buraco". Agora só
// falta encolher o tamanho do array que segura a Fila.
/////////////////////////////////////////////////////////////////
void ReorganizaFila (FP *queue, Grafo *grafo) {
  int tamanho=queue->tam;
  int i, posmenor=1;
  TipoValorVertice v;

  if (vaziaFP(queue)) return;//se tá vazia não tem nada que fazer

  // Vamos atualizar os vértices na FILA com os custos correntes.
  // Os custos correntes estão em ACUMULADO.
  for (i=0; i<queue->tam; i++) {
    v = queue->fila[i].vertice;
    queue->fila[i].custo = grafo->Acumulado[v];
  }
  // Agora é procurar o melhor que neste caso é o vértice de menor custo acumulado.
  // Note que este laço é o responsável pela complexidade da função.
  for (i=1; i<tamanho; i++) 
    if (queue->fila[i].custo < queue->fila[posmenor].custo) posmenor = i;

  //coloca na posição zero o vértice de menor custo
  queue->fila[0] = queue->fila[posmenor];

  //no buraco deixado na posição posmenor, colocamos o último elemento da fila
  queue->fila[posmenor] = queue->fila[tamanho - 1];
}



/* Há que lembrar que ao retirarmos um elemento da Fila de Prioridades temos que
   reorganizar o resto da fila usando os custos correntes como critério. 
   Vide comentários que precedem ReorganizaFila.
*/
TipoValorVertice Extract_Min (FP* queue, Grafo *grafo) {
  TipoValorVertice vert = queue->fila[0].vertice;

  ReorganizaFila(queue, grafo);
  queue->tam--;
  return vert;
}


/* ###################################################################### */
/* ###################################################################### */

void Initialize_Single_Source (Grafo *grafo, TipoValorVertice source) {
  TipoValorVertice nv = grafo->NumVertices;

  grafo->Acumulado = (TipoPeso*) malloc(nv*sizeof(TipoPeso));
  grafo->Pai= (TipoValorVertice*) malloc(nv*sizeof(TipoValorVertice));

  TipoValorVertice i;
  for (i=0; i<nv; i++) {
    grafo->Acumulado[i] = INT_MAX; //INT_MAX faz a vez de infinito
    grafo->Pai[i] = -1; //-1 faz a vez de NULL
  }
  grafo->Acumulado[source] = 0;
}


void Relax (TipoValorVertice u, TipoValorVertice v, 
            TipoPeso pesouv, Grafo *grafo) 
{
  if ( grafo->Acumulado[v] > grafo->Acumulado[u] + pesouv ) 
    {
      grafo->Acumulado[v] = grafo->Acumulado[u] + pesouv;
      grafo->Pai[v] = u;
    }
}

/*
  May I help you? 
*/
void Dijkstra_Grafo (Grafo *grafo, TipoValorVertice ptpartida ) {
  TipoPeso peso;
  TipoValorVertice u, v;

  Initialize_Single_Source (grafo, ptpartida);

   /* A ideia aqui é criar CONJUNTOS VAZIOS associados a 
     cada um dos particulares GRAFOS usados no programa.
     Para que essa associação seja possível, vou passar
     os grafos como parâmetros da função de criação! 
  */
  Set *S = criaConjuntoVazio(grafo); /* linha 2 em Cormen */

  FP *Q = InitFP(grafo, ptpartida);  /* linha 3 em Cormen */
  
  while ( !vaziaFP(Q) ) {   
    u = Extract_Min(Q, grafo);       /* linha 5 em Cormen */
 
    insereElemento(S, u);            /* linha 6 em Cormen */

    /* Substitui o laço FOR pelo laço WHILE               */
    /* A única razão para essa substituição               */
    /* é evitar que o FOR se esparrame por várias linhas  */
    /* das transparências onde vou apresentar o código.   */
    v = primeiroAdjacente(u, grafo, &peso);
    // a função acima retorna o peso da aresta (u,v) na variável peso
    while ( v!=-1 ) {
      Relax(u, v, peso, grafo);     /* linha 8 em Cormen */
      v = proximoAdjacente(u, grafo, v, &peso);
    }
  }
}

/*********************************************************************************************************

  8. Kruskal_Grafo

       > > Argumentos: 
    
       > > Descrição: 

       > > Retorno: 



                                                                                                               */
void Kruskal_Grafo(){



}