#include "TCD.h"

typedef struct TCD{
  GTree *posts;
  GTree *users;
};

GTree getUsers(TCD tcd){
  if (tcd){
    GTree users = tcd->users;
    return users;
  }
  return NULL;
}

GTree getPosts(TCD tcd){
  if (tcd){
    GTree posts = tcd->posts;
    return posts;
  }
  return NULL;
}


int idusercompare(const void* id1, const void* id2){ //sendo id1 o a colocar
  long key1 = *(long *) id1;
  long key2 = *(long *) id2;
  if (key1 == key2)
    return 0; //o elemento é o mesmo
  if (key1 < key2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}


int idpostcompare(const void* id1, const void* id2){ //sendo id1 o a colocar
  long key1 = *(long *) id1;
  long key2 = *(long *) id2;
  if (key1 == key2)
    return 0; //o elemento é o mesmo
  if (key1 < key2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}

// ver se esta bem porque as datas sao confusas
int datacompare(Date data1, Date data2){ //sendo data1 o a colocar
  Date key1 = (Date) data1;
  Date key2 = (Date) data2;

  if (key1->ano < key2->ano)
    return 1;
  if (key1->ano > key2->ano)
    return (-1);
  if (key1->ano == key2->ano){
    if(key1->mes < key2->mes)
      return 1;
    if(key1->mes > key2->mes)
      return (-1);
    else{
        if(key1->dia < key2->dia)
          return 1;
        if(key1->dia > key2->dia)
          return (-1);
        else return 0;
    }
    }
}

TCD init(){
  TCD tcd = malloc(sizeof(struct(TCD)));
  //tcd->users =g_tree_new_full(idusercompare(), NULL, NULL, );
  //tcd->posts = g_tree_new_full(idpostcompare(), NULL, NULL, );
  return tcd;
}


void insereUser(TCD tcd, User u){
  assert ( u!= NULL);
  g_tree_insert(tcd->users, u->id, u);
}
