#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "fila.h"

typedef int infotype;
typedef int TipoValorVertice;
typedef int TipoValorAresta;
typedef int TipoPeso;

typedef struct grafo Grafo; 

Grafo* criaGrafoVazio (TipoValorVertice vertices, TipoValorAresta arestas, int tipoGrafo);

void insereAresta (TipoValorVertice origem, TipoValorVertice destino, TipoPeso peso, Grafo* grafo);

short temAdjacentes(TipoValorVertice vertice, Grafo* grafo);

short existeAresta (TipoValorVertice origem, TipoValorVertice destino, Grafo *grafo);

TipoValorVertice primeirodaLista(Lista* lista, TipoPeso *peso);

TipoValorVertice primeiroAdjacente (TipoValorVertice u, Grafo *grafo, TipoPeso *peso);

TipoValorVertice  proximoAdjacente (TipoValorVertice u, Grafo *grafo, TipoValorVertice adjant, TipoPeso *peso);

void liberaGrafo (Grafo* grafo);