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
  int score;
  int vcount;
  Date data;
  long owner;
  char * titulo;
};

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
};

User mycreateUser(long id, int reputacao, char* nome, char* bio){
  assert(id >= 0);
  assert(reputacao >= 0);
  assert(nome != NULL);
  assert(bio != NULL);
  User u = malloc(sizeof(struct userint));
  u->id = id;
  u->reputacao = reputacao;
  u->nome = mystrdup(nome);
  u->bio = mystrdup(bio);
  return u;
}

long getUserId(User u){
  if(u) return u->id;
  return -1;
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


Post createPost(long id, int type, int score, int vcount, Date data, long owner, char* titulo){
  Post p = malloc(sizeof(struct post));
  p->id = id;
  p->type = type;
  p->score = score;
  p->vcount = vcount;
  p->data = data;
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

int getPostScore(Post p){
  if(p) return p->score;
  return -1;
}

int getPostVCount(Post p){
  if(p) return p->vcount;
  return -1;
}

Date getPostData(Post p){
  if (p){
  int dia = get_day(p->data);
  int mes = get_month(p->data);
  int ano = get_year(p->data);
  Date d = createDate(dia,mes,ano);
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
    free(p->titulo);
    free(p);
  }
}
