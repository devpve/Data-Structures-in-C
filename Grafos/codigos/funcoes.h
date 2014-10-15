#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"

FILE* arq_abre (FILE* fp, char nomeArq[]);

Grafo* Constroi_Grafo (Grafo* grafo, FILE* fp);

int ComponentesConexas (Grafo* grafo);

Grafo* ConectaConexas (Grafo* grafo);

void DFS_Grafo (TipoValorVertice vertice, Grafo* grafo);

void BFS_Grafo(TipoValorVertice vertice, Grafo* grafo);

void Dijkstra_Grafo(Grafo* grafo, TipoValorVertice);

void Kruskal_Grafo();

