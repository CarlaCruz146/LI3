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
#include <time.h>

/*
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
*/


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
*///printf("ola1\n");
  TAD_community tad = init();

  clock_t t,q;
  char* path = "/home/carlacruz/Desktop/LI3/Grupo51/src";

  //printf("ola3\n" );

  tad = load(tad,path);
  //printf("ola\n" );

  //srand(time(NULL));
  q = clock();
  STR_pair str = info_from_post(tad, 219);
  q = clock()-q;
  double a1 = ((double) q) / CLOCKS_PER_SEC *1000;
  printf("Q1:%f ms\n",a1 );
  printf("%s & %s\n", get_fst_str(str),get_snd_str(str) );

  Date begin = createDate(1,1,2008);
  Date end = createDate(1,2,2020);
  t=clock();
  LONG_pair pair = total_posts(tad, begin, end);
  t=clock()-t;
  double a3 = ((double) t) / CLOCKS_PER_SEC *1000;
  printf("Q3:%f ms\n",a3 );

  long fst = get_fst_long(pair);
  long snd = get_snd_long(pair);
  printf("Perguntas: %ld e Respostas: %ld\n", fst,snd );

  //printf("%s e %s\n", get_fst_str(pair), get_snd_str(pair)  );
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
