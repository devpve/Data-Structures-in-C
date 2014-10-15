#include <stdlib.h>

typedef struct arv Arv;

typedef int infotype;

Arv* arv_criavazia();

Arv* arv_criafolha (infotype valor, Arv* pai);

infotype arv_vazia (Arv* a);

Arv* arv_insere (Arv* a, infotype valor, Arv* pai);

Arv* arv_libera (Arv* a);




	