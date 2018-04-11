#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"
#include "estruturas.h"
#include <gmodule.h>
#include "parser.h"
#include "interface.h"

struct TCD_community{
  GTree *Posts;
  GTree *Users;
};

TAD_community init(){
  TAD_community tad = (TAD_community)malloc(sizeof(struct TCD_community));
  tad->Users = g_tree_new((GCompareFunc) idusercompare);
  tad->Posts = g_tree_new((GCompareFunc) idpostcompare);
  return tad;
}


// query 0
TAD_community load(TAD_community com, char* dump_path){

  char* pos = concat(dump_path, "/Posts.xml");
  xmlDocPtr pos2 = xmlParseFile(pos);

  char *us;
  us = concat(dump_path,"/Users.xml");
  xmlDocPtr us2 = xmlParseFile(us);

  postsInfo(pos2, com->Posts);
  userInfo(us2, com->Users);

  free(pos);
  free(us);

  return com;

}

/*
// query 1
STR_pair info_from_post(TAD_community com, int id);


// query 2
LONG_list top_most_active(TAD_community com, int N);

// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end);

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

// query 5
USER get_user_info(TAD_community com, long id);

// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);

// query 8
LONG_list contains_word(TAD_community com, char* word, int N);

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

// query 10
LONG_list better_answer(TAD_community com, int id);

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

TAD_community clean(TAD_community com);
*/
