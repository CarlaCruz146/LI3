#include "interface.h"

struct TCD_community{
  GTree *Posts;
  GTree *Users;
  GHashTable *Hdates;
};

typedef struct respostas{
  Heap h;
  Key parent;
} *ResPost;

static ResPost initResPost(long pid);
static int date_equal(Date begin, Date end);
static gboolean nrposts (gpointer key, gpointer value, gpointer user_data);
static int existeTag(Post p, char* tag);
static void postRes(Post p, ArrayD array);
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data);
static gboolean getScCom(gpointer key, gpointer value, gpointer user_data);


static ResPost initResPost(long pid){
  ResPost res = (ResPost)malloc(sizeof(struct respostas));
  res->h = initHeap();
  res->parent = createKey(pid);
  return res;
}

TAD_community init(){
  TAD_community tad = (TAD_community)malloc(sizeof(struct TCD_community));
  tad->Users = g_tree_new_full((GCompareDataFunc) idusercompare, NULL, &free, &myfreeUser);
  tad->Posts = g_tree_new_full((GCompareDataFunc) idpostcompare, NULL, &free, &freePost);
  tad->Hdates = g_hash_table_new_full((GHashFunc) hash, (GEqualFunc) iguais, &destroyDate, &freeArray);
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

static int date_equal(Date begin, Date end){
  int d,m,a,r;
  d = (get_day(begin) == get_day(end)) ? 0 : 1;
  m = (get_month(begin) == get_month(end)) ? 0 : 1;
  a = (get_year(begin) == get_year(end)) ? 0 : 1;

  r = (d + m + a) > 0 ? 1 : 0;

  return r;
}

static gboolean nrposts (gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  long id = getKey(k);
  User user = (User)value;
  HeapU heap = (HeapU) user_data;

  heap_pushU(heap, id,cont_RP(getUserHeap(user)));

  return FALSE;
}

// query 2
LONG_list top_most_active(TAD_community com, int N){
  int i;
  long id;
  long key;
  LONG_list res = create_list(N);
  HeapU heap = initHeapU();
  g_tree_foreach(com->Users,(GTraverseFunc)nrposts, heap);

  for(i=0; i<N; i++){
    id = heap_popU(heap,&key);
    set_list(res, i, id);
  }
  heap_freeU(heap);
  return res;
}


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


static int existeTag(Post p, char* tag){
    int i, c = 0;
    char** tags = getPostTags(p);
    int ntags = getPostNTags(p);
    for(i=0; i<ntags && c == 0; i++){
        if(strcmp(tag, tags[i]) == 0)
            c = 1;
    }

    return c;
}

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    int i, pi, n, c, t=0;
    char** tags;
    gpointer x;
    ArrayD d;
    LONG_list r;
    Heap h = initHeap();
    Post p;
    while(date_equal(begin,end) > 0){
        x = g_hash_table_lookup(com->Hdates, begin);
        d = (ArrayD) x;
        if (d){
            for(i=0; i<getUsed(d); i++){
                p = getInd(d,i);
                if(getPostType(p) == 1){
                int cenas = existeTag(p,tag);
                if(cenas == 1)
                    heap_push(h,p,'D');

                }
            }
        }
        begin = incrementaData(begin);
    }
    x = g_hash_table_lookup(com->Hdates, end);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        p = getInd(d,i);
        if(existeTag(p,tag) == 1)
          heap_push(h,p,'D');
        }
    }
    for(i=0; i<getUsed(d); i++){
        p = getInd(d,i);
        n = getPostNTags(p);
        tags = getPostTags(p);
        for(pi=0; pi<n; pi++){
            if(strcmp(tag,tags[pi]) == 0 && t==0){
                heap_push(h,p,'D');
                t = 1;
            }
         }
    }
    c = heap_count(h);
    r = create_list(c);
    for(i=0; i<c; i++){
      Post p = heap_pop(h,'D');
      set_list(r, i, getPostId(p));
      printf("%ld\n", get_list(r,i));
    }
    return r;
}


// query 5
USER get_user_info(TAD_community com, long id){
  int i;
  long* post_history = malloc(10 * sizeof(long));
  Key kid = createKey(id);
  User u = (User)g_tree_lookup(com->Users,kid);
  char *bio = mygetUserBio(u);
  Heap uposts = getUserHeap(u);
  for(i=0; i<10; i++){
    post_history[i] = getPostId(heap_pop(uposts,'D'));
  }
  USER user = create_user(bio,post_history);
  free(kid);
  return user;
}


// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;
  gpointer x;
  ArrayD d;
  LONG_list r = create_list(N);
  Heap h = initHeap();
  while(date_equal(begin,end) > 0){
          x = g_hash_table_lookup(com->Hdates, begin);
          d = (ArrayD) x;
          if (d){
            for(i=0; i<getUsed(d); i++){
              if(getPostType(getInd(d,i)) == 2)
                heap_push(h,getInd(d,i),'S');
            }
          }
          begin = incrementaData(begin);
    }
    x = g_hash_table_lookup(com->Hdates, end);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        if(getPostType(getInd(d,i)) == 2)
          heap_push(h,getInd(d,i),'S');
      }
    }
    for(i=0; i<N; i++){
      Post p = heap_pop(h,'S');
      set_list(r, i, getPostId(p));
    }
    return r;
}


static void postRes(Post p, ArrayD array){
  int i;
  Post posti;
  for(i=0; i<getUsed(array); i++){
    posti = getInd(array,i);
    if(getPostType(posti) == 2)
      if(getPid(posti) == getPostId(p))
        incPostNRes(p);
  }
}


// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
  int i;
  gpointer x;
  ArrayD d;
  Heap h = initHeap();
  LONG_list r = create_list(N);
  while(date_equal(begin,end) > 0){
    x = g_hash_table_lookup(com->Hdates, begin);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        postRes(getInd(d,i),d);
        heap_push(h,getInd(d,i),'R');
      }
    }
    begin = incrementaData(begin);
  }
  x = g_hash_table_lookup(com->Hdates, end);
  d = (ArrayD) x;
  if (d){
    for(i=0; i<getUsed(d); i++){
      postRes(getInd(d,i),d);
      heap_push(h,getInd(d,i),'R');
    }
  }
  for(i=0; i<N; i++){
    Post p = heap_pop(h,'R');
    set_list(r, i, getPostId(p));
  }
  return r;
}

//insere numa heap (ordenada por ordem cronologica inversa) todos os posts que contêm no seu titulo uma dada palavra
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  getKey(k);
  Post p = (Post)value;
  Heap h = (Heap) user_data;
  if(getPostType(p) == 1){
    if(strstr(getPostTitulo(p),getHeapPal(h)))
      heap_push(h,p,'D');
  }
  return FALSE;
}

// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
  int i;
  Post p;
  LONG_list r = create_list(N);
  Heap h = initHeapPal(word);
  g_tree_foreach(com->Posts, (GTraverseFunc)pContainsWord, h);
  for(i=0; i<N; i++){
    p = heap_pop(h,'D');
    set_list(r, i, getPostId(p));
  }
  return r;
}


/*
// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N);
*/


static gboolean getScCom(gpointer key, gpointer value, gpointer user_data){
  Post p = (Post)value;
  ResPost r = (ResPost) user_data;
  long pid = getKey(r->parent);
  if(getPostType(p) == 2 && getPid(p) == pid){
    heap_push(r->h,p,'M');
  }
  return FALSE;
}

// query 10
long better_answer(TAD_community com, long id){
  Post p;
  ResPost r = initResPost(id);
  g_tree_foreach(com->Posts, (GTraverseFunc)getScCom, r);
  p = heap_pop(r->h,'M');
  return getPostId(p);
}


/*
// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);
*/

TAD_community clean(TAD_community com){
  g_tree_destroy(com->Posts);
  g_hash_table_destroy(com->Hdates);
  return com;
}
