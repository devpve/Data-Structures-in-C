#include <stdio.h>
#include <stdlib.h>

/* Rotinas de manipulação do tipo abstrato lista */
typedef int infotype;

typedef struct lista Lista;

Lista* lista_criavazia();

int lista_vazia (Lista* lista);

Lista* lista_insere (Lista* lista, infotype info, infotype peso);

void libera_lista (Lista* lista);
