#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "common.h"
#include "date.h"
#include "estruturas.h"

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
  USER user;
};

User createUser(long id, int reputacao, char* nome, USER user){
  User u = malloc(sizeof(struct userint));
  u->id = id;
  u->reputacao = reputacao;
  u->nome = mystrdup(nome);
  return u;
}

long getUserId(User u){
  if(u) return u->id;
  return -1;
}

int getUserReputacao(User u){
  if(u) return u->reputacao;
  return -1;
}

char* getUserNome(User u){
  if(u) return u->nome;
  return NULL;
}

USER getUser(User u){

  if(u){
    USER usr;

    usr = create_user(get_bio(u->user),get_10_latest_posts(u->user));
    return usr;
  }
  return NULL;
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
  if(p) return p->data;
  return NULL;
}

long getPostOwner(Post p){
  if(p) return p->owner;
  return -1;
}

char* getPostTitulo(Post p){
  if(p) return p->titulo;
  return NULL;
}

void freePost(Post p){
  if(p) {
    free(p->titulo);
    free(p);
  }
}
