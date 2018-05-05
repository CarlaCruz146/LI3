#include "util.h"

struct respostas{
  Heap h;
  Key parent;
};

struct duplo{
  LONG_list ll;
  TNum tnum;
  int pos;
};



/**
  *@brief   Retorna uma estrutura ResPost inicializada.
  *@param   long id de uma pergunta.
  *return   ResPost estrutura inicializada.
*/
ResPost initResPost(long pid){
  ResPost res = (ResPost)malloc(sizeof(struct respostas));
  res->h = initHeap();
  res->parent = createKey(pid);
  return res;
}

/**
  *@brief   Retorna o ID guardado na estrutura.
  *@param   ResPost.
  *return   Key ID.
*/
Key getResPostParent(ResPost r){
    return r->parent;
}

/**
  *@brief   Retorna a heap guardada na estrutura.
  *@param   ResPost.
  *return   Heap.
*/
Heap getResPostHeap(ResPost r){
    return r->h;
}

/**
  *@brief   Função que inicializa uma LONG_list.
  *@param   int tamanho da LONG_list.
  *return   LONG_list criada e inicializada.
*/
LONG_list init_ll(int N){
  LONG_list ll = create_list(N);
  int i = 0;
  while(i < N) {
    set_list(ll,i,-2);
    i++;
  }
  return ll;
}

/**
  *@brief   Função que inicializa a estrutura Duplos.
  *@param   int tamanho da LONG_list do duplos.
  *return   Duplos inicializado
*/
Duplos initDuplos(int N){
  Duplos res = (Duplos)malloc(sizeof(struct duplo));
  res->ll = init_ll(N);
  res->tnum = create_tnum_pair(NULL,0);
  res->pos = -1;
  return res;
}

void set_duplos_pos(Duplos dup, int i){
  dup->pos = i;
}

Duplos set_duplos_tnum(Duplos dup, TNum tn){
  if(dup)
    dup->tnum = tn;
  return dup;
}

Duplos insere_Duplos(LONG_list ll, TNum tn,int N, int i){
  Duplos res = initDuplos(N);
  res->ll = ll;
  res->tnum = tn;
  res->pos = i;
  return res;
}

LONG_list get_duplos_ll(Duplos dup){
  if(dup)
    return dup->ll;
  return NULL;
}

TNum get_duplos_tnum(Duplos dup){
  if(dup) return dup->tnum;
  return NULL;
}

int get_duplos_pos(Duplos dup){
  if (dup) return dup->pos;
  return -1;
}