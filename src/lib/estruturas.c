#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "user.h"
#include "common.h"
#include "date.h"
#include "estruturas.h"
#include "parser.h"
#include <assert.h>

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

/*
int maisrecente(gconstpointer id1, gconstpointer id2){ //sendo id2 o a colocar
   Date key1 = (Date)malloc(sizeof(struct Date));
   Date key2 = (Date)malloc(sizeof(struct Date));
   key1 = id1;
   key2 = id2;
   time_t t0 = time(NULL);
   int ret1, ret2;
   struct tm d1, d2;
   char buffer[80];

   d1.tm_year = get_year(key1) - 1900;
   d1.tm_mon = get_month(key1) - 1;
   d1.tm_mday = get_day(key1);
   d1.tm_hour = 0;
   d1.tm_min = 0;
   d1.tm_sec = 0;
   d1.tm_isdst = -1;

   ret1 = mktime(&d1);
   if( ret == -1 ) {
      printf("Error: unable to make time using mktime\n");
   }

   d2.tm_year = get_year(key2) - 1900;
   d2.tm_mon = get_month(key2) - 1;
   d2.tm_mday = get_day(key2);
   d2.tm_hour = 0;
   d2.tm_min = 0;
   d2.tm_sec = 0;
   d2.tm_isdst = -1;

   ret2 = mktime(&d2);
   if( ret == -1 ) {
      printf("Error: unable to make time using mktime\n");
   }

   double diff_t1 = difftime(&t0,&d1);
   double diff_t2 = difftime(&t0,&d2);

   if(diff_t1 < diff_t2) return -1;
   else if (diff_t1 > diff_t2) return 1;
   else return 0;

}
*/

User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10], GTree* arv_uposts){
  //assert(id >= 0);
  //assert(reputacao >= 0);
  //assert(nome != NULL);
  //assert(bio != NULL);
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


/*
myDate mycreateDate(int day, int month, int year, int hour, int min, float sec) {
    myDate d = malloc(sizeof(struct mydate));
    d->date = createDate(day,month,year);
    d->hour = hour;
    d->min = min;
    d->sec = sec;
    return d;
}

int myget_day(myDate d) {
    return (get_day(d->date));
}

int myget_month(myDate d) {
    return (get_month(d->date)); //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}

int myget_year(myDate d) {
    return (get_year(d->date));
}

int myget_hour(myDate d) {
    return d->hour;
}

int myget_min(myDate d) {
    return d->min;
}

float myget_sec(myDate d) {
    return d->sec;
}

void myfree_date(myDate d) {
    free(d->date);
    free(d);
}*/
