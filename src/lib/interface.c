#include "interface.h"

struct TCD_community{
  GTree *Posts;
  GTree *Users;
  GHashTable* Hdates;
  GTree *Votes;
};

TAD_community init(){
  TAD_community tad = (TAD_community)malloc(sizeof(struct TCD_community));
  tad->Users = g_tree_new_full((GCompareDataFunc) idusercompare, NULL, &free, &myfreeUser);
  tad->Posts = g_tree_new_full((GCompareDataFunc) idpostcompare, NULL, &free, &freePost);
  tad->Hdates = g_hash_table_new_full((GHashFunc) hash, (GEqualFunc) iguais, &destroyDate, &freeArray);
  tad->Votes = g_tree_new_full((GCompareDataFunc) idvotecompare, NULL, &free, &myfreeVote);
  return tad;
}


// query 0
TAD_community load(TAD_community com, char* dump_path){
  char* us = (char*) myconcat(dump_path,"/Users.xml");
  xmlDocPtr us2 = xmlParseFile(us);
  userInfo(us2, com->Users);
  free(us);
  xmlFreeDoc(us2);

  char* pos = (char*) myconcat(dump_path, "/Posts.xml");
  xmlDocPtr pos2 = xmlParseFile(pos);
  postsInfo(pos2, com->Posts, com->Hdates, com->Users);
  free(pos);
  xmlFreeDoc(pos2);

/*
  char* vt = (char*) myconcat(dump_path,"/exemplo3.xml");
  xmlDocPtr vt2 = xmlParseFile(vt);
  votesInfo(vt2,com->Votes);
  printf("olaaaaa\n");
  free(vt);
  xmlFreeDoc(vt2);
*/
  return com;
}


//query 1
STR_pair info_from_post(TAD_community com, long id){
  Key k = createKey(id);
  Post p = (Post)g_tree_lookup(com->Posts, k);
  Key pid,owner;
  User u;
  STR_pair res;
  freekey(k);

  if(getPostType(p) == 1){
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    res = create_str_pair(getPostTitulo(p),getUserName(u));
    freekey(owner);
    return res;
  }
  if(getPostType(p) == 2){
    pid = createKey(getPid(p));
    p = g_tree_lookup(com->Posts, pid);
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    res = create_str_pair(getPostTitulo(p),getUserName(u));
    freekey(pid);
    freekey(owner);
    return res;
  }
  res = create_str_pair("","");
  return res;
}

Date cenas(TAD_community com){
  Key kowner = createKey(7);
  User u = g_tree_lookup(com->Users, kowner);
  Post p = heap_pop(getUserHeap(u));
  Date date = getPostDate(p);
  return date;
}

static int date_equal(Date begin, Date end){
  int d,m,a,r;
  d = (get_day(begin) == get_day(end)) ? 0 : 1;
  m = (get_month(begin) == get_month(end)) ? 0 : 1;
  a = (get_year(begin) == get_year(end)) ? 0 : 1;

  r = (d + m + a) > 0 ? 1 : 0;

  return r;
}
/*
// query 2
LONG_list top_most_active(TAD_community com, int N);
*/
// query 3

LONG_pair total_posts(TAD_community com, Date begin, Date end){
  long fst = 0;
  long snd = 0;
  gpointer x;
  ArrayD d;
  while(date_equal(begin,end) > 0){
          x = g_hash_table_lookup(com->Hdates, begin);
          d = (ArrayD) x;
          if (d){
            fst += getPer(d);
            snd += getRes(d);
          }
          begin = incrementaData(begin);
  }
  x = g_hash_table_lookup(com->Hdates, end);
  d = (ArrayD) x;
  if (d){
    fst += getPer(d);
    snd += getRes(d);
  }
  LONG_pair pair = create_long_pair(fst,snd);
  return pair;
}




// query 4
//LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

// query 5
USER get_user_info(TAD_community com, long id){
  int i;
  long* post_history = malloc(10 * sizeof(long));
  Key kid = createKey(id);
  User u = (User)g_tree_lookup(com->Users,kid);
  char *bio = mygetUserBio(u);
  Heap uposts = getUserHeap(u);
  for(i=0; i<10; i++){
    post_history[i] = getPostId(heap_pop(uposts));
  }
  USER user = create_user(bio,post_history);
  return user;
}

/*
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

*/

TAD_community clean(TAD_community com){
  g_tree_destroy(com->Users);
  g_tree_destroy(com->Posts);
  g_hash_table_destroy(com->Hdates);
  g_tree_destroy(com->Votes);
  return com;
}
