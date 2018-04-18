#include "estruturas.h"


struct post{
  long id;
  int type; // 1 ou 2 (pergunta ou resposta)
  long pid;
  int score;
  int vcount;
  Date date;
  long owner;
  char * titulo;
};

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
  long posts[10];
  GTree* arv_uposts;
  //Heap uposts;
};

struct key{
  long key;
};

struct arrayd{
  Post* array;
  long used;
  long size;
  long res;
  long per;
};

ArrayD createArray(long comp){
  ArrayD a = malloc (sizeof(struct arrayd));
  a->array = malloc(comp * sizeof(struct post));
  a->used = 0;
  a->size = comp;
  a->res = 0;
  a->per = 0;
  return a;
}

long getPer(ArrayD d){
  if(d) return d->per;
  else return -1;
}

long getRes(ArrayD d){
  if(d) return d->res;
  else return -1;
}

long getSize(ArrayD d){
  if(d) return d->size;
  else return -1;
}

long getUsed(ArrayD d){
  if(d) return d->used;
  else return -1;
}

Post getInd(ArrayD d, int i){
  if (d)
    return (d->array[i]);
  else return NULL;
}


void insereArray(ArrayD a, Post p){
  if (a-> used == a->size) {
    a->size *= 2;
    a->array = realloc (a->array, a->size * (sizeof(struct post)));
    }
  int type = getPostType(p);
  if (type == 1) a->per++;
  if (type == 2) a->res++;
  a->array[a->used++] = p;
}


void freeArray(ArrayD a){
  free(a->array);
  free(a);
}


Key createKey(long key){
  Key k = malloc(sizeof(struct key));
  k->key = key;
  return k;
}


long getKey(Key k){
  return k->key;
}


User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10], GTree* arv_uposts){
  if(id>=-1){
    int i;
    User u = malloc(sizeof(struct userint));
    u->id = id;
    u->reputacao = reputacao;
    u->nome = mystrdup(nome);
    u->bio = mystrdup(bio);
    for(i=0; i!=9; i++);
      (u->posts)[i] = posts[i];
    u->arv_uposts = arv_uposts;
    return u;
  }
  return NULL;
}


long getUserId(User u){
  if(u) return u->id;
  return -2;
}


int getUserRep(User u){
  if(u) return u->reputacao;
  return -1;
}


char* getUserName(User u){
  if(u) return mystrdup(u->nome);
  return NULL;
}


char* mygetbio(User u){
  if(u) return mystrdup(u->bio);
  return NULL;
}


void myfreeUser(User u){
  if (u){
    free(u->nome);
    free(u->bio);
    free(u);
  }
}


Post initPost(){
  Post p = malloc(sizeof(struct post));
  return p;
}


Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner, char* titulo){
  Post p = malloc(sizeof(struct post));
  p->id = id;
  p->type = type;
  p->pid = pid;
  p->score = score;
  p->vcount = vcount;
  p->date = date;
  p->owner = owner;
  p->titulo = mystrdup(titulo);
  return p;
}


long getPostId(Post p){
  if(p) return p->id;
  return -1;
}


int getPostType(Post p){
  if(p) return p->type;
  return -1;
}


long getPid(Post p){
  if(p) return p->pid;
  return -1;
}


int getPostScore(Post p){
  if(p) return p->score;
  return -1;
}


int getPostVCount(Post p){
  if(p) return p->vcount;
  return -1;
}


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


long getPostOwner(Post p){
  if(p) return p->owner;
  return -1;
}


char* getPostTitulo(Post p){
  if(p) return mystrdup(p->titulo);
  return NULL;
}


void freePost(Post p){
  if(p) {
    free(p->date);
    free(p->titulo);
    free(p);
  }
}
