#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"
#include "date.h"
#include "estruturas.h"
#include <assert.h>

struct post{
  long id;
  int type; // 1 ou 2 (pergunta ou resposta)
  long pid;
  int score;
  int vcount;
  myDate date;
  long owner;
  char * titulo;
};

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
  long posts[10];
};

struct mydate {
  Date date;
  int hour;
  int min;
  int sec;
};


struct key{
  long key;
};


Key createKey(long key){
  Key k = malloc(sizeof(struct key));
  k->key = key;
  return k;
}

long getKey(Key k){
  return k->key;
}


User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10]){
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
    for(i=0; i<10; i++);
      u->posts[i] = posts[i];
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


Post createPost(long id, int type, long pid, int score, int vcount, myDate date, long owner, char* titulo){
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

myDate getPostDate(Post p){
  if (p){
  int day = myget_day(p->date);
  int month = myget_month(p->date);
  int year = myget_year(p->date);
  int hour = myget_hour(p->date);
  int min = myget_min(p->date);
  float sec = myget_sec(p->date);
  myDate d = mycreateDate(day,month,year,hour,min,sec);
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
}
