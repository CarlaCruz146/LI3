#include "myuser.h"

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
  //Heap uposts;
};


User mycreateUser(long id, int reputacao, char* nome, char* bio){
  if(id>=-1){
    User u = malloc(sizeof(struct userint));
    u->id = id;
    u->reputacao = reputacao;
    u->nome = mystrdup(nome);
    u->bio = mystrdup(bio);
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


void myfreeUser(void *u){
  User aux = (User) u;
  if (aux){
    free(aux->nome);
    free(aux->bio);
    free(aux);
  }
}
