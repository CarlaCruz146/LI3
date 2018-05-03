#include "mytags.h"

struct tag{
  long id;
  char* name;
};

Tag initTag(){
  Tag t = malloc(sizeof(struct tag));
  return t;
}

Tag createTag(long id, char* name){
  Tag t = initTag();
  t->id = id;
  t->name= mystrdup(name);
  return t;
}

long getTagId(Tag t){
    if (t) return t->id;
    return -1;
}

char* getTagName(Tag t){
  if(t) return mystrdup(t->name);
  return NULL;
}

void freeTag(void * t){
  Tag aux = (Tag) t;
  if(aux){
    free(aux->name);
    free(aux);
  }
}
