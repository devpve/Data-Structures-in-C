
/********************************************************************************************************/
/* Bibliotecas usadas 
    grafo.h: header com as rotinas de grafo implementada com uma lista de adjacência.
    lista.h: header com as rotinas de lista.                                            */

#include "grafo.h"
#include "lista.h"
#include "fila.h"
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
Grafo* criaGrafoVazio (TipoValorVertice vertices, TipoValorAresta arestas, int tipoGrafo) {

    if ( vertices < 1 ) {
    
    printf("\nNumero de vertices fora de escala!"); 
    printf("\nPrograma encerrado.\n");
    exit(1);

    }

    if ( arestas < 0 ) {

      printf("\nNumero de arestas fora de escala!");  
      printf("\nPrograma encerrado.\n");
      exit(1);

    }

    /* Aloca dinamicamente a estrutura abstrata do grafo */
        Grafo *aux = (Grafo*) malloc(sizeof(Grafo));


    /* Aloca dinamicamente a estrutura básica do grafo.
     Essa estrutura funciona como um header onde os campos de
     ponteiro vão nos permitir alocar o que for preciso e apenas 
     quando for necessário. */

        aux->NumVertices = vertices;
        aux->NumArestas = arestas;
        aux->dirigido = tipoGrafo;


      /* Declaramos um contador simples e após disso declararemos nosso
      vetor de ponteiros do tipo lista onde cada posição apontará para 
      NULL no começo e ao decorrer do programa poderemos fazer qualquer
      posição apontar para uma lista */

        int i;

        aux -> adjlst = (Lista**) malloc(vertices*sizeof(Lista*));

          for (i = 0; i < vertices; i++) aux -> adjlst[i] = NULL;
     

    /* Retornamos nosso grafo */    
    return aux;
}

/********************************************************************************************************/
void insereAresta (TipoValorVertice origem, TipoValorVertice destino, TipoPeso peso, Grafo* grafo){

    /* O vértice de origem no vetor de ponteiros apontará para uma lista com o elemento de destino e o peso correspondente */
    grafo -> adjlst[origem] = lista_insere (grafo -> adjlst[origem], destino, peso);
    /* Se o grafo não for dirigido teremos que fazer o caminho contrário */
    if(!grafo->dirigido) lista_insere(grafo -> adjlst[destino], origem, peso);

}


/********************************************************************************************************/
short temAdjacentes (TipoValorVertice vertice, Grafo *grafo){
 
  if (grafo->adjlst[vertice] != NULL) /*lista de adjacência NÃO é vazia!*/
    return 1;

  return 0;
}


/********************************************************************************************************/
short existeAresta (TipoValorVertice origem, TipoValorVertice destino, Grafo *grafo){

  if (!temAdjacentes(origem, grafo)) 
    return 0; 

  Lista* aux = grafo -> adjlst[origem];

  if (aux -> info == destino) return 1;
  /* 
     Esta função tem complexidade linear ( O(|V|) ) pois teremos que percorrer
     a sequência de vértices na Lista de Adjacencia de u.
  */
  for ( aux = aux -> prox; aux != grafo -> adjlst[origem]; aux = aux -> prox)
    if (aux -> info == destino) return 1;
  /*
     Se chegou aqui é porque o vértice v não está na lista de adjacencia de u
  */
  return 0;
}

/********************************************************************************************************/
static Lista *ponteiroPARAultimoNODOAdjacenteDevolvido;
/********************************************************************************************************/

TipoValorVertice primeirodaLista(Lista* fila, TipoPeso *peso) {
  if (fila == NULL) return -1; 
  /* 
     Vou usar um efeito colateral horroroso!!!!!!!!!
     A variável vai armazenar o endereço do último nodo "visitado"
     na Lista de Adjacência.
*/
    ponteiroPARAultimoNODOAdjacenteDevolvido = fila->prox;
  *peso = fila -> prox -> peso; //retorno do valor do peso na aresta
  return fila -> prox -> info;
}

/********************************************************************************************************/
/*
   A próxima função retorna o primeiro vértice v da sequência de 
   vértices adjacentes ao vértice  u.
*/
TipoValorVertice primeiroAdjacente (TipoValorVertice u, Grafo *grafo, TipoPeso *peso) {

  if (grafo->adjlst[u] != NULL) //lista de adjacência não é vazia.
    {
      TipoPeso psp;
      TipoValorVertice w = primeirodaLista(grafo->adjlst[u],&psp);
      /*
         Complexidade: O(1). Vide primeirodaLista   
      */
      *peso = psp; //retorno do valor do peso na aresta
      return w;
    } 
  /*
     Se chegou aqui é porque não tem adjacentes! Nesse caso retornamos -1 
     já que os valores para os vértices são positivos.
  */
  printf("\nO vertice %d nao tem adjacentes.",u);
  printf("\nO endereco retornado sera -1\n");
  return -1;
}
/****************************************************************************************************************/
TipoValorVertice  proximoAdjacente (TipoValorVertice u, Grafo *grafo, TipoValorVertice adjant, TipoPeso *peso) {

  Lista* aux = ponteiroPARAultimoNODOAdjacenteDevolvido;
  aux = aux->prox;

  // ponto de parada: quando voltamos a 1ª célula da Lista de Adjacência
  if (aux == grafo->adjlst[u]->prox) return -1;

  //Nesta representação vamos ignorar o parâmetro adjant
  *peso = aux->peso;
  ponteiroPARAultimoNODOAdjacenteDevolvido = aux;
  return aux->info;
}
/********************************************************************************************************/

void liberaGrafo (Grafo *grafo){

  TipoValorVertice num = grafo -> NumVertices;
  TipoValorVertice i;

  for ( i = 0; i < num; i++ ){
    if (grafo -> adjlst[i] != NULL)
        
        libera_lista(grafo -> adjlst[i]);
  
  }


  free(grafo);

}