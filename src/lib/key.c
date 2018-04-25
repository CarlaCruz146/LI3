#include "key.h"
#include <stdlib.h>

struct key{
  long key;
};

/**
  *@brief   Função que alloca memória para essa key, criando-a.
  *@param   Um long que irá originar uma Key a partir do mesmo.
*/
Key createKey(long key){
  Key k = malloc(sizeof(struct key));
  k->key = key;
  return k;
}

/**
  *@brief   Função que devolve o valor da Key.
  *@param   Recebe uma Key.
*/
long getKey(Key k){
  return k->key;
}

/**
  *@brief   Função que liberta a memória anteriormente alocada para a criação da Key.
  *@param   Recebe a key a libertar.
*/
void freekey (Key k){
   free(k);
}
