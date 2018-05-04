/**
 * @file arrayT.c
 * @brief Ficheiro que contém a implementação de um Array com uma tag(char*) e o número de ocorrências.
 */

#include "arrayT.h"

struct tagnum {
  char* tag;
  int num;
};

struct arraytagnum {
  long size;
  long used;
  TNum * tags;
};
/**
  *@brief   Insere um par Tag-Num no array.
  *@param   ATnum array de pares Tag-Num.
  *@param   TNum par Tag-Num.
  *@return  ATNum array de pares.
*/
ATNum insere_tagnum(ATNum a, TNum t ){
  if (a-> used == a->size){
    a->size *= 2;
    a->tags = realloc (a->tags, a->size * (sizeof(TNum)));
  }
  a->tags[a->used++] = (TNum)t;
  return a;
}

/**
  *@brief   Incrementa o número de ocorrências da tag.
  *@param   TNum par Tag-Num.
  *@return  ATNum array de pares.
*/
TNum incTNum(TNum pair) {
  int n = get_num_tnum(pair);
  n++;
  set_num_tnum(pair,n);
  return pair;
}

TNum create_tnum_pair(char* fst, int snd) {
  TNum t = malloc(sizeof(struct tagnum));
  t->tag = mystrdup(fst);
  t->num = snd;
  return t;
}

void set_tag_tnum(TNum pair, char* str) {
  free(pair->tag);
  pair->tag = mystrdup(str);
}

void set_num_tnum(TNum pair, int num) {
  pair->num = num;
}

char* get_tag_tnum(TNum pair) {
   return pair ? mystrdup(pair->tag) : NULL;
}

int get_num_tnum(TNum pair) {
  return pair ? pair->num : 0;
}

void free_tnum(TNum pair) {
  if(pair) {
    free(pair->tag);
    free(pair);
  }
}

TNum get_atnum_tnum(ATNum pares, int index){
  return pares->tags[index];
}

long get_atnum_used(ATNum a){
  if(a) return a->used;
  else return 0;
}

long get_atnum_size(ATNum pares) {
  if (pares) return pares->size;
  return 0;
}

ATNum init_atnum(long N){
  ATNum a = malloc (sizeof(struct arraytagnum));
  a->tags = malloc(N * sizeof(struct arraytagnum));
  a->size = N;
  a->used = 0;
  int i;
  for(i = 0; i < N; i++){
    create_tnum_pair(NULL,0);
  }
  return a;
}

void bubbleTNumSort(ATNum pares){
  int tam = get_atnum_used(pares);
  int i,j; int num = 0, num2 = 0;
  TNum tagnum = NULL, tagnum2 = NULL, aux = create_tnum_pair(NULL, 0);
  for(i = 0; i < tam; i++){
    tagnum = get_atnum_tnum(pares,i);
    for(j = i+1; j < tam; j++){
      tagnum2 = get_atnum_tnum(pares,j);
      num2=get_num_tnum(tagnum2);
      num = get_num_tnum(tagnum);
      char* c =get_tag_tnum(tagnum);
      if(num2 > num){
        set_tag_tnum (aux,c);
        set_num_tnum(aux,num);

        set_tag_tnum (tagnum,get_tag_tnum(tagnum2));
        set_num_tnum (tagnum,num2);

        set_tag_tnum (tagnum2,get_tag_tnum(aux));
        set_num_tnum (tagnum2,get_num_tnum(aux));

      }
    }
  }
}


/*
TNum order_atnum(ATNum pares,int N){
  int l = get_atnum_used(pares);
  int i = 0;
  init_atnum(N);
  for(i = 0; i < l; i++){
}
*/
