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



int main(int argc, char **argv){
  TAD_community tad = init();

  clock_t t0, t1, t2, t3;
  char* path = "/home/nikes/li3/Grupo51/src";
  load(tad,path);

  t0 = clock();
  USER u = get_user_info(tad, 10);
  char* bio = get_bio(u);
  printf("%s\n", bio);
  long* posts = get_10_latest_posts(u);
  int i;
  for(i=0; i<10; i++)
    printf("%ld\n", posts[i]);
  free_user(u);
  t0 = clock() - t0;
  double a1 = ((double) t0) /CLOCKS_PER_SEC *1000;
  printf("Q5: %f ms \n",a1 );

  t1 = clock();
  Date begin = createDate(13,10,2010);
  Date end = createDate(13,10,2010);
  LONG_list l = most_voted_answers(tad, 5, begin, end);
  for(i=0; i<5; i++)
    printf("%ld\n", get_list(l,i));
  t1 = clock() - t1;
  a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
  printf("Q6: %f ms \n",a1 );

  t2 = clock();
  Date begin2 = createDate(13,10,2010);
  LONG_list l2 = most_answered_questions(tad, 1, begin2, begin2);
  for(i=0; i<1; i++)
    printf("%ld\n", get_list(l2,i));
  t2 = clock() - t2;
  a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
  printf("Q7: %f ms \n",a1 );

  t3 = clock();
  LONG_list l3 = contains_word(tad, "Nexus", 10);
  for(i=0; i<10; i++)
    printf("%ld\n", get_list(l3,i));
  t3 = clock() - t3;
  a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
  printf("Q8: %f ms \n",a1);
  //srand(time(NULL));
//  t1 = clock();
//  info_from_post(tad, rand() % 187277);
//  t1= clock()- t1;
//  double a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
//  printf("Q1: %f ms \n",a1 );

  //Date begin = createDate(1,1,2008);
//  Date end = createDate(1,2,2020);
//  t3=clock();
//  LONG_pair pair = total_posts(tad, begin, end);
//  t3=clock()-t3;
//  double a5 = ((double) t3) / CLOCKS_PER_SEC *1000;
//  printf("Q3:%f ms\n",a5 );

//  long fst = get_fst_long(pair);
//  long snd = get_snd_long(pair);
  //printf("Perguntas: %ld e Respostas: %ld\n", fst,snd );
  //printf("%s e %s\n", get_fst_str(pair), get_snd_str(pair)  );

  //Date date = createDate(29,3,1998);
  //Date date2 = createDate(14,8,2018);
  //long id1 = 13424533;
  //long id2 = 353333;



  //Post p1 = createPost(id1,1,-2,13,15,date,4534223,0,"ola");
  //printf("welele\n");
  //Post p2 = createPost(id2,2,13424,10,10,date2,2534342,0,"alo");
  //printf("im a banana\n");
  //heap_push(h, p1);
  //printf("banana\n");
  //heap_push(h, p2);
  //Post post = heap_pop(h);
  //printf("%ld\n", getPostId(post));


  tad = clean(tad);
  free(tad);
//free_date(begin);
//  free_date(end);
//  free_date(date);
//  free_date(date2);
//  freePost(p1);
//  freePost(p2);
//  freePost(post);
//  free_long_pair(pair);
//  heap_free(h);
  return 0;
}
