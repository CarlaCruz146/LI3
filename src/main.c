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
<<<<<<< HEAD
#include <time.h>

/*
||||||| merged common ancestors


=======
#include "heap.h"

>>>>>>> Nikes
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
<<<<<<< HEAD

  clock_t t;
  char* path = "/home/carlacruz/Desktop/LI3/Grupo51/src";
||||||| merged common ancestors
  char* path = "/home/carlacruz/Desktop/LI3/Grupo51/src";
=======
  char* path = "/home/nikes/li3/Grupo51/src";
>>>>>>> Nikes

  //printf("ola3\n" );

  tad = load(tad,path);
  //printf("ola\n" );

  //srand(time(NULL));
  info_from_post(tad, rand() % 187277);

  Date begin = createDate(1,1,2008);
  Date end = createDate(1,2,2020);
  t=clock();
  LONG_pair pair = total_posts(tad, begin, end);
  t=clock()-t;
  double a5 = ((double) t) / CLOCKS_PER_SEC *1000;
  printf("Q3:%f ms\n",a5 );

  long fst = get_fst_long(pair);
  long snd = get_snd_long(pair);
  printf("Perguntas: %ld e Respostas: %ld\n", fst,snd );

  //printf("%s e %s\n", get_fst_str(pair), get_snd_str(pair)  );
  //Por enquanto nao sabemos se esta funçao esta a fazer algo de util
  //g_tree_foreach(arv_posts, (GTraverseFunc)freePostaux, NULL);
  //g_tree_destroy(arv_posts);
  //Date date = createDate(29,3,1998);
  //Date date2 = createDate(14,8,2018);
  //long id1 = 13424533;
  //long id2 = 353333;
  printf("dsfs\n");
  Heap h = initHeap();
  //Post p1 = createPost(id1,1,-2,13,15,date,4534223,"ola");
  printf("welele\n");
  //Post p2 = createPost(id2,2,13424,10,10,date2,2534342,"alo");
  printf("im a banana");

  printf("banana");
  //heap_push(h, id1, p1);
  //heap_push(h, id2, p2);


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
