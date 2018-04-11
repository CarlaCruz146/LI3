#include <date.h>
#include <stdio.h>
#include "estruturas.h"
#include "user.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "parser.h"
#include <glib.h>
#include <assert.h>
#include "interface.h"


gboolean iterator(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  getKey(k);
  printf("Key- %ld\n",getKey(k));
  Post p = (Post)value;
  printf("Pid %ld\n", getPostId(p));
  printf("%ld\n", getPostOwner(p));
  return FALSE;
}


gboolean freePostaux(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  getKey(k);
  Post p = (Post)value;
  freePost(p);
  free(k);
  return FALSE;
}


int main(int argc, char **argv){
/*
  char *pos;
  pos = "/home/pedro90/Desktop/LI/Grupo51/src/Posts.xml" ;
  xmlDocPtr pos2 = xmlParseFile(pos);

  char *us;
  us = "/home/pedro90/Desktop/LI/Grupo51/src/Users.xml";
  xmlDocPtr us2 = xmlParseFile(us);

  GTree *arv_users = g_tree_new((GCompareFunc) idusercompare);
  GTree *arv_posts = g_tree_new((GCompareFunc) idpostcompare);
  //postsInfo(pos2, arv_posts);
  //userInfo(us2, arv_users);
*/
  TAD_community tad = init();
  char* path = "/home/pedro90/Desktop/LI/Grupo51/src";

  tad = load(tad,path);

  //Por enquanto nao sabemos se esta funçao esta a fazer algo de util
  //g_tree_foreach(arv_posts, (GTraverseFunc)freePostaux, NULL);
  //g_tree_destroy(arv_posts);


  //g_tree_destroy(arv_users);


  //Key uid = createKey(1);
  //User u = (User)g_tree_lookup(arv_users, uid);
  //assert(u!=NULL);
  //printf("%s\n",getUserName(u) );
  //g_tree_foreach(arv_posts, (GTraverseFunc)iterator, NULL);
  //printf("dldasjdlk\n");
  //xmlFreeDoc(pos2);
  //xmlFreeDoc(us2);
  return 0;
}
