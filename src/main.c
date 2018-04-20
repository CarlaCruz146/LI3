#include <date.h>
#include <stdio.h>
#include <time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <glib.h>
#include "user.h"
#include "parser.h"
#include "interface.h"
#include "mypost.h"
#include "myuser.h"
#include "key.h"
#include "heap.h"



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
  TAD_community tad = init();


  clock_t t0;
  clock_t t1;
  clock_t t3;
  char* path = "/home/pedro90/Desktop/LI3/Grupo51/src";

  //printf("ola3\n" );
  t0 = clock();
  tad = load(tad,path);
  t0= clock()- t0 ;
  double a0 = ((double) t0)/CLOCKS_PER_SEC;
  printf("LOAD: %f s \n",a0 );
  //printf("ola\n" );

  //srand(time(NULL));
  t1 = clock();
  info_from_post(tad, rand() % 187277);
  t1= clock()- t1;
  double a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
  printf("Q1: %f ms \n",a1 );

  Date begin = createDate(1,1,2008);
  Date end = createDate(1,2,2020);
  t3=clock();
  LONG_pair pair = total_posts(tad, begin, end);
  t3=clock()-t3;
  double a5 = ((double) t3) / CLOCKS_PER_SEC *1000;
  printf("Q3:%f ms\n",a5 );

  long fst = get_fst_long(pair);
  long snd = get_snd_long(pair);
  printf("Perguntas: %ld e Respostas: %ld\n", fst,snd );

  //printf("%s e %s\n", get_fst_str(pair), get_snd_str(pair)  );

  Date date = createDate(29,3,1998);
  Date date2 = createDate(14,8,2018);
  long id1 = 13424533;
  long id2 = 353333;
  printf("dsfs\n");
  Heap h = initHeap();
  Post p1 = createPost(id1,1,-2,13,15,date,4534223,0,"ola");
  printf("welele\n");
  Post p2 = createPost(id2,2,13424,10,10,date2,2534342,0,"alo");
  printf("im a banana\n");

  heap_push(h, p1);
  printf("banana\n");
  heap_push(h, p2);
  Post post = heap_pop(h);
  printf("%ld\n", getPostId(post));


  //g_tree_destroy(arv_users);



  //xmlFreeDoc(pos2);
  //xmlFreeDoc(us2);
  return 0;
}
