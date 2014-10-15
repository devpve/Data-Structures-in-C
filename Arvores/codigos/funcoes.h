#include "arvore.h"
#include "fila.h"
#include "BFSfila.h"

FILE* arq_abre (FILE* fp);

infotype* arq_leCaminhamentoDFS (FILE *fp, infotype *vet, infotype *cont);

Fila* arq_leCaminhamentoPreordem (FILE *fp, infotype *cont);

void ConferePercorrimentos (infotype *vetDFS, Fila* fila_preordem, infotype tamDFS, infotype tamPreordem);

int particiona (Fila* preordem, infotype *vetDFS, infotype inicio, infotype tamanho, infotype x);

Arv* arv_reconstroi (Arv* arv, Fila* preordem, infotype *vetDFS, infotype inicio, infotype tamanho);

void arv_Preordem (Arv* arv);

void arv_DFS (Arv* arv);

void arv_Posordem (Arv* arv);

void arv_BFS (Arv* arv);

