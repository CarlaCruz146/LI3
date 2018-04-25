#include "mypost.h"

struct post{
  long id;
  int type; // 1 ou 2 (pergunta ou resposta)
  long pid;
  int score;
  int vcount;
  Date date;
  long owner;
  int numcom;
  int nres;
  char * titulo;
  char** tag;
};

struct arrayd{
  Post* array;
  long used;
  long size;
  long res;
  long per;
};

/**
  *@brief   Função que dará cast ao void recebido para uma data e depois dará free à mesma.
  *@param   Recebe um apontador.
*/
void destroyDate (void *d){
  Date aux = (Date) d;
  free_date(aux);
}

/**
  *@brief   Função que cria um array dinâmico que conterá o array, o seu tamanho o que já fora usado e também teŕa contadores para o número de perguntas e respostas.
  *@param   Recebe o comprimente que o array terá.
*/
ArrayD createArray(long comp){
  ArrayD a = malloc (sizeof(struct arrayd));
  a->array = malloc(comp * sizeof(struct post));
  a->used = 0;
  a->size = comp;
  a->res = 0;
  a->per = 0;
  return a;
}
/**
  *@brief   Função que retorna o número de perguntas contidas naquele array.
  *@param   Recebe um array dinâmico.
*/
long getPer(ArrayD d){
  if(d) return d->per;
  else return -1;
}

/**
  *@brief   Função que retorna o número de respostas contidas naquele array.
  *@param   Recebe um array dinâmico.
*/
long getRes(ArrayD d){
  if(d) return d->res;
  else return -1;
}

/**
  *@brief   Função que retorna o tamanho allocado para aquele array.
  *@param   Recebe um array dinâmico.
*/
long getSize(ArrayD d){
  if(d) return d->size;
  else return -1;
}

/**
  *@brief   Função que retorna o tamanho usado naquele array.
  *@param   Recebe um array dinâmico.
*/
long getUsed(ArrayD d){
  if(d) return d->used;
  else return -1;
}

/**
  *@brief   Função que retorna o Post contido no array, naquela posição i.
  *@param   Recebe um array dinâmico e um índice.
*/
Post getInd(ArrayD d, int i){
  if (d)
    return (d->array[i]);
  else return NULL;
}


/**
  *@brief   Função que insere um Post no array.
  *@param   Recebe um array dinâmico e um determinado Post.
*/
void insereArray(ArrayD a, Post p){
  if (a-> used == a->size){
    a->size *= 2;
    a->array = realloc (a->array, a->size * (sizeof(struct post)));
  }
  int type = getPostType(p);
  if (type == 1) a->per++;
  if (type == 2) a->res++;
  a->array[a->used++] = p;
}

/**
  *@brief   Função que liberta a memória alocada pelo array dinâmico.
  *@param   Recebe um apontador void.
*/
void freeArray(void *a){
  ArrayD aux = (ArrayD) a;
  if(aux){
    free(aux->array);
    free(aux);
  }
}

/**
*@brief   Função que inicializa um post, retornando o mesmo.
*/
Post initPost(){
  Post p = malloc(sizeof(struct post));
  return p;
}

/**
  *@brief   Função que com base nos parâmetros irá fazer a criação de um Post.
  *@param   Recebe um id, o type, o parent id, o score, o viewcount, a data de criação, o criador, o número de comentários, o número de respostas e o título.
*/
Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner, int numcom, int nres, char* titulo, char** tags){
  Post p = malloc(sizeof(struct post));
  p->id = id;
  p->type = type;
  p->pid = pid;
  p->score = score;
  p->vcount = vcount;
  p->date = date;
  p->owner = owner;
  p->numcom = numcom;
  p->nres = nres;
  p->titulo = mystrdup(titulo);
  p->tag = tags;
  return p;
}

/**
  *@brief   Função que retornará o id de um dado Post.
  *@param   Recebe um Post.
*/
long getPostId(Post p){
  if(p) return p->id;
  return -1;
}

/**
  *@brief   Função que retornará o tipo de um dado Post.
  *@param   Recebe um Post.
*/
int getPostType(Post p){
  if(p) return p->type;
  return -1;
}

/**
  *@brief   Função que retornará o parent id do Post recebido.
  *@param   Recebe um Post.
*/
long getPid(Post p){
  if(p) return p->pid;
  return -1;
}

/**
  *@brief   Função que retornará o score de um dado Post.
  *@param   Recebe um Post.
*/
int getPostScore(Post p){
  if(p) return p->score;
  return -1;
}

/**
  *@brief   Função que retornará o view count do Post.
  *@param   Recebe um Post.
*/
int getPostVCount(Post p){
  if(p) return p->vcount;
  return -1;
}

/**
  *@brief   Função que retornará a data de criação do Post recebido.
  *@param   Recebe um Post.
*/
Date getPostDate(Post p){
  if (p){
  int day = get_day(p->date);
  int month = get_month(p->date);
  int year = get_year(p->date);
  Date d = createDate(day,month,year);
  return d;
  }
  return NULL;
}

/**
  *@brief   Função que retornará o criador do Post.
  *@param   Recebe um Post.
*/
long getPostOwner(Post p){
  if(p) return p->owner;
  return -1;
}

/**
  *@brief   Função que retornará o número de comentários de um dado Post.
  *@param   Recebe um Post.
*/
int getPostNumCom(Post p) {
  if (p) return p->numcom;
  return -1;
}


/**
  *@brief   Função que incrementa o número de respostas de um dado Post.
  *@param   Recebe um Post.
*/
int getPostNRes(Post p) {
  if (p) return p->nres;
  else return -2;
}

/**
  *@brief   Função que incrementa o número de respostas de um dado Post.
  *@param   Recebe um Post.
*/
void incPostNRes(Post p) {
  p->nres++;
}

/**
  *@brief   Função que retornará o título de um dado Post.
  *@param   Recebe um Post.
*/
char* getPostTitulo(Post p){
  if(p) return mystrdup(p->titulo);
  return NULL;
}

/**
  *@brief   Função que dará free de um Post, depois de ser realizado o cast.
  *@param   Recebe um apontador.
*/
void freePost(void *p){
  Post aux = (Post) p;
  if(aux) {
    free(aux->date);
    free(aux->titulo);
    free(aux);
  }
}
