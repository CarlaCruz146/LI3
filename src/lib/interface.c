#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"
#include "estruturas.h"
#include <gmodule.h>
#include "parser.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

  char* pos = (char*) myconcat(dump_path, "/Posts.xml");
  xmlDocPtr pos2 = xmlParseFile(pos);

  char* us = (char*) myconcat(dump_path,"/Users.xml");

  xmlDocPtr us2 = xmlParseFile(us);

  postsInfo(pos2, com->Posts);

  userInfo(us2, com->Users);

  free(pos);
  free(us);

  return com;
}


// query 1

STR_pair info_from_post(TAD_community com, long id){


  STR_pair ret = create_str_pair("Null","Null");

  printf("%ld\n",id);

  Key idd = createKey (id); //Cria uma key para procurar na estrutura dos Posts

  Post p = (Post)g_tree_lookup(com->Posts, idd); //Procura o post com o id dado

  if (getPostType(p) == 1 ) { //Verifica se é pergunta

      long owner_id = getPostOwner(p); //Vai buscar o id de quem fez o post

      Key owid = createKey (owner_id); //Cria uma key para procurar o user na estrutura dos users

      User u = (User)g_tree_lookup(com->Users,owid); //procura o user

      ret = create_str_pair(getPostTitulo(p),getUserName(u)); //Devolve o par com o titulo e o nick do autor
  }


  if (getPostType(p) == 2) { //Verifica se é resposta

    Key pid = createKey(getPid(p)); //Cria uma key com o id da pergunta a qual foi respondida

    p = (Post)g_tree_lookup(com->Posts,pid); //Procura essa pergunta

    Key oid = createKey(getPostOwner(p)); //Cria uma key com o id de quem fez o post

    User u = (User)g_tree_lookup(com->Users,oid); //procura o user através do seu id


    ret = create_str_pair(getPostTitulo(p),getUserName(u)); //Devolve o par com o titulo da pergunta e quem fez a pergunta
  }

  else ret = create_str_pair("","");

  printf("%s \n %s \n", get_fst_str(ret), get_snd_str(ret));

  free(p);

  return ret;
}






/*
STR_pair info_from_post(TAD_community com, long id){
  Key k = createKey(id);
  Post p = (Post)g_tree_lookup(com->Posts, k);

  if(getPostType(p) == 2){
    Key pid = createKey(getPid(p));
    p = g_tree_lookup(com->Posts, pid);
  }
  Key owner = createKey(getPostOwner(p));
  User u = g_tree_lookup(com->Users, owner);

  STR_pair res = create_str_pair(getPostTitulo(p),getUserName(u));
  return res;
}
*/
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
