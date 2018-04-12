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
  printf("cenas1\n");
  char* pos = (char*) myconcat(dump_path, "/exemplo2.xml");
  xmlDocPtr pos2 = xmlParseFile(pos);
  printf("cenas2\n" );
  char* us = (char*) myconcat(dump_path,"/exemplo.xml");
  xmlDocPtr us2 = xmlParseFile(us);
  printf("cenas5\n" );
  postsInfo(pos2, com->Posts);
  printf("crenas3\n" );
  userInfo(us2, com->Users);
  printf("cenas4\n" );
  free(pos);
  free(us);

  return com;

}


// query 1
STR_pair info_from_post(TAD_community com, long id){
  Key k = createKey(id);
  Post p = g_tree_lookup(com->Posts, k);

  if(getPostType(p) == 2){
    Key pid = createKey(getPid(p));
    p = g_tree_lookup(com->Posts, pid);
  }
  Key owner = createKey(getPostOwner(p));
  User u = g_tree_lookup(com->Users, owner);

  STR_pair res = create_str_pair(getPostTitulo(p),getUserName(u));
  return res;
}

/*
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
