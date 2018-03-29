#include "TCD.h"

int idusercompare(const void* id1, const void* id2){ //sendo id1 o a colocar
  if (id1 == id2)
    return 0; //o elemento é o mesmo
  if (id1 > id2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}


int idpostcompare(const void* id1, const void* id2){ //sendo id1 o a colocar
  if (id1 == id2)
    return 0; //o elemento é o mesmo
  if (id1 > id2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}


int datacompare(Date data1, Date data2){ //sendo data1 o a colocar
  if (data1->ano > data2->ano)
    return 1;
  if (data1->ano < data2->ano)
    return (-1);
  if (data1->ano == data2->ano)
    if(data1->mes > data2->mes)
      return 1;
    if(data1->mes < data2->mes)
      return (-1);
    else{
        if(data1->dia > data2->dia)
          return 1;
        if(data1->dia < data2->dia)
          return (-1);
        else return 0;
    }
}

TCD init(){
TCD tcd = malloc(sizeof(struct(TCD)));
tcd->users =g_tree_new();
tcd->posts = g_tree_new();

return tcd;
}


void insereUser(TCD tcd, User u){
  assert ( u!= NULL);
  g_tree_insert(tcd->users, u->id, u);
}
