#include "myuser.h"

struct userint{
  long id;
  int reputacao;
  char* nome;
  char* bio;
  int nposts;
  Heap uposts;
};


User mycreateUser(long id, int reputacao, char* nome, char* bio, int nposts, Heap uposts){
  if(id>=-1){
    User u = malloc(sizeof(struct userint));
    u->id = id;
    u->reputacao = reputacao;
    u->nome = mystrdup(nome);
    u->bio = mystrdup(bio);
    u->nposts = nposts;
    u->uposts = uposts;
    return u;
  }
  return NULL;
}

Heap getUserHeap(User u){
  if(u) return u->uposts;
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


char* mygetUserBio(User u){
  if(u) return mystrdup(u->bio);
  return NULL;
}

int getUserNPosts(User u){
  if(u) return u->nposts;
  return -1;
}

void incUserNPosts(User u){
  u->nposts++;
}

void myfreeUser(void *u){
  User aux = (User) u;
  if (aux){
    free(aux->nome);
    free(aux->bio);
    heap_free(aux->uposts);
    free(aux);
  }
}
