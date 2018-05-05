#include "interface.h"

struct TCD_community{
  GTree *Posts;
  GTree *Users;
  GHashTable *Hdates;
  GTree *Tags;
};

typedef struct respostas{
  Heap h;
  Key parent;
} *ResPost;

typedef struct duplo{
  LONG_list ll;
  TNum tnum;
  int pos;
} *Duplos;

/**
  *@brief   Função que inicializa uma LONG_list.
  *@param   int tamanho da LONG_list.
  *return   LONG_list criada e inicializada.
*/
static LONG_list init_ll(int N);

/**
  *@brief   Função que inicializa um duplos.
  *@param   int tamanho da LONG_list do duplos.
  *return   Duplos inicializado
*/
static Duplos initDuplos(int N);

static void set_duplos_pos(Duplos dup, int i);

static Duplos set_duplos_tnum(Duplos dup, TNum tn);

static Duplos insere_Duplos(LONG_list ll, TNum tn,int N, int i);

static LONG_list get_duplos_ll(Duplos dup);

static TNum get_duplos_tnum(Duplos dup);

static int get_duplos_pos(Duplos dup);

static gboolean user_heap (gpointer key, gpointer value,gpointer user_data);
static LONG_list topN (TAD_community com ,int N);
static int checkT(ATNum a, char* tag);
static ATNum get_allTags(TAD_community com,ATNum pairs,LONG_list ll, Date begin, Date end);
static gboolean tags_tree (gpointer key, gpointer value,gpointer user_data);


/**
  *@brief   Função que concatena duas strings.
  *@param   char* string 1.
  *@param   char* string 2.
  *return   char* string resultante.
*/
static char* myconcat(const char *s1, const char *s2);

/**
  *@brief   Retorna uma estrutura ResPost inicializada.
  *@param   long id de uma pergunta.
  *return   ResPost estrutura inicializada.
*/
static ResPost initResPost(long pid);

/**
  *@brief   Compara duas datas.
  *@param   long id de uma pergunta.
  *return   int 1 se as datas forem diferentes e 0 se forem iguais.
*/
static int date_equal(Date begin, Date end);

/**
  *@brief   Para todos os Users, insere os seus IDs numa heap e ordena-os segundo o número de posts do User correspondente ao ID.
  *@param   gpointer ID do User.
  *@param   gpointer User.
  *@param   gpointer HeapU.
  *return   gboolean True quando itera por todos os Users.
*/
static gboolean nrposts (gpointer key, gpointer value, gpointer user_data);

/**
  *@brief   Verifica se uma dada tag se encontra no array de tags de um dado Post.  *@param   gpointer ID do User.
  *@param   Post post.
  *@param   char* tag a procurar.
  *return   int 1 se ela existir, 0 se não existir.
*/
static int existeTag(Post p, char* tag);

/**
  *@brief   Insere todos os Posts numa heap (ordenada por ordem cronologica inversa) todos os posts que contêm no seu titulo uma dada palavra.
  *@param   gpointer ID do Post.
  *@param   gpointer Post.
  *@param   gpointer Heap.
  *return   gboolean True quando itera na totalidade a árvore os Posts.
*/
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data);

/**
  *@brief   Para todos os Posts de tipo resposta, insere-os numa heap e ordena-os segundo a classificação média do post.
  *@param   gpointer ID do Post.
  *@param   gpointer Post.
  *@param   gpointer estrutura ResPost.
  *return   gboolean True quando itera por todos os Posts.
*/
static gboolean getScCom(gpointer key, gpointer value, gpointer user_data);


static char* myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

static ResPost initResPost(long pid){
  ResPost res = (ResPost)malloc(sizeof(struct respostas));
  res->h = initHeap();
  res->parent = createKey(pid);
  return res;
}

static Duplos initDuplos(int N){
  Duplos res = (Duplos)malloc(sizeof(struct duplo));
  res->ll = init_ll(N);
  res->tnum = create_tnum_pair(NULL,0);
  res->pos = -1;
  return res;
}

static void set_duplos_pos(Duplos dup, int i){
  dup->pos = i;
}

static Duplos set_duplos_tnum(Duplos dup, TNum tn){
  if(dup)
    dup->tnum = tn;
  return dup;
}

static Duplos insere_Duplos(LONG_list ll, TNum tn,int N, int i){
  Duplos res = initDuplos(N);
  res->ll = ll;
  res->tnum = tn;
  res->pos = i;
  return res;
}

static LONG_list get_duplos_ll(Duplos dup){
  if(dup)
    return dup->ll;
  return NULL;
}

static TNum get_duplos_tnum(Duplos dup){
  if(dup) return dup->tnum;
  return NULL;
}

static int get_duplos_pos(Duplos dup){
  if (dup) return dup->pos;
  return -1;
}

TAD_community init(){
  TAD_community tad = (TAD_community)malloc(sizeof(struct TCD_community));
  tad->Users = g_tree_new_full((GCompareDataFunc) idusercompare, NULL, &free, &myfreeUser);
  tad->Posts = g_tree_new_full((GCompareDataFunc) idpostcompare, NULL, &free, &freePost);
  tad->Hdates = g_hash_table_new_full((GHashFunc) hash, (GEqualFunc) iguais, &destroyDate, &freeArray);
  tad->Tags = g_tree_new_full((GCompareDataFunc) idtagcompare,NULL,&free,&freeTag);
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

  char* tg = (char*)myconcat(dump_path,"/Tags.xml");
  xmlDocPtr tg2 = xmlParseFile(tg);
  tagsInfo(tg2,com->Tags);
  free(tg);
  xmlFreeDoc(tg2);

  return com;
}

//query 1
STR_pair info_from_post(TAD_community com, long id){
  Key k = createKey(id);
  Post p = (Post)g_tree_lookup(com->Posts, k);
  Key pid,owner;
  User u;
  STR_pair res;
  char* tit,*name;
  freekey(k);

  if(getPostType(p) == 1){
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    tit = getPostTitulo(p);
    name = getUserName(u);
    res = create_str_pair(tit,name);
    freekey(owner);
    free(tit);
    free(name);
    return res;
  }
  if(getPostType(p) == 2){
    pid = createKey(getPid(p));
    p = g_tree_lookup(com->Posts, pid);
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    tit = getPostTitulo(p);
    name = getUserName(u);
    res = create_str_pair(tit,name);
    freekey(pid);
    freekey(owner);
    free(tit);
    free(name);
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
  LONG_list res = create_list(N);
  HeapU heap = initHeapU();
  g_tree_foreach(com->Users,(GTraverseFunc)nrposts, heap);

  for(i=0; i<N; i++){
    id = heap_popU(heap);
    set_list(res, i, id);
  }
  heap_freeU(heap);
  return res;
}


// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
  long fst = 0;
  long snd = 0; 
  //long r = 0;
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
  free_date(begin);
  free_date(end);
  LONG_pair pair = create_long_pair(fst,snd);
  return pair;
}


static int existeTag(Post p, char* tag){
    int i, c = 0;
    char** tags = getPostTags(p);
    int ntags = getPostNTags(p);
    for(i=0; i<ntags && c == 0; i++){
        printf("TAG %d: %s POST %ld\n", i, tags[i], getPostId(p));
        if(strcmp(tag, tags[i]) == 0)
            c = 1;
    }
    return c;
}

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    int i, c;
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
        printf("%ld\n",getPostId(p));
        if(existeTag(p,tag) == 1)
          heap_push(h,p,'D');
        }
    }
    c = heap_count(h);
    printf("%d",c);
    r = create_list(c);
                printf("Deixa arder-3 - %d\n",c);
    for(i=0; i<c; i++){
      printf("I: %d\n", i);
      Post p = heap_pop(h,'D');
      printf("I: %d pop feito \n",i);
      set_list(r, i, getPostId(p));
      printf("--- %ld\n", get_list(r,i));
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
    free_date(begin);
    free_date(end);
    heap_free(h);
    return r;
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
        heap_push(h,getInd(d,i),'R');
      }
    }
    begin = incrementaData(begin);
  }
  x = g_hash_table_lookup(com->Hdates, end);
  d = (ArrayD) x;
  if (d){
    for(i=0; i<getUsed(d); i++){
      heap_push(h,getInd(d,i),'R');
    }
  }
  for(i=0; i<N; i++){
    Post p = heap_pop(h,'R');
    printf("ID:%ld NRES:%d\n", getPostId(p), getPostNRes(p));
    set_list(r, i, getPostId(p));
  }
  free_date(begin);
  free_date(end);
  heap_free(h);
  return r;
}


//insere numa heap (ordenada por ordem cronologica inversa) todos os posts que contêm no seu titulo uma dada palavra
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  getKey(k);
  Post p = (Post)value;
  Heap h = (Heap) user_data;
  char* tit = getPostTitulo(p);
  if(getPostType(p) == 1){
    if(strstr(tit,getHeapPal(h)))
      heap_push(h,p,'D');
  }
  free(tit);
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
 // heap_free(h);
  return r;
}

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
  int i,j;
  Post p,p1,p2,p3;
  LONG_list r = create_list(N);
  Heap heap = initHeap();
  Key k1 = createKey(id1);
  Key k2 = createKey(id2);
  User u1 = (User) g_tree_lookup(com->Users,k1);
  User u2 = (User) g_tree_lookup(com->Users,k2);
  freekey(k1);
  freekey(k2);
  Heap h1 = getUserHeap(u1);
  Heap h2 = getUserHeap(u2);
  for(i=0; i< heap_count(h1); i++){
      p1 = getIndP(h1,i);
      for(j=0; j<heap_count(h2); j++){
          p2 = getIndP(h2,j);
          if(getPostType(p1) == 2 && getPostType(p2) == 1 && getPostId(p2) == getPid(p1))
              if(p2) heap = heap_push(heap,p2,'D');
          if(getPostType(p1) == 2 && getPostType(p2) == 2 && getPid(p2) == getPid(p1)){
              Key k3 = createKey(getPid(p1));
              p3 = (Post) g_tree_lookup(com->Posts,k3);
              freekey(k3);
              if(p3) heap = heap_push(heap,p3,'D');
          }
          if(getPostType(p1) == 1 && getPostType(p2) == 2 && getPid(p2) == getPostId(p1))
              if(p1) heap = heap_push(heap,p1,'D');
      }
  }
  for(i=0; i<N; i++){
    p = heap_pop(heap,'D');
    set_list(r, i, getPostId(p));
  }
  heap_free(heap);
  return r;
}


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


static LONG_list init_ll(int N){
  LONG_list ll = create_list(N);
  int i = 0;
  while(i < N) {
    set_list(ll,i,-2);
    i++;
  }
  return ll;
}

static gboolean user_heap (gpointer key, gpointer value,gpointer user_data){
  User u = (User) value;
  HeapU us = (HeapU) user_data;
  long id = getUserId(u);
  long rep =(long) getUserRep(u);
  us = heap_pushU(us,id,rep);
  return FALSE;
}

static LONG_list topN (TAD_community com ,int N){
  LONG_list ll = init_ll(N);
  HeapU us = initHeapU();
  g_tree_foreach(com->Users, (GTraverseFunc)user_heap, us);
  for(int i = 0; i < N; i++) {
    set_list(ll,i,heap_popU(us));
  }
  return ll;
}

// 0 se não pertence, o valor do índice se pertence
static int checkT(ATNum a, char* tag){
  long l = get_atnum_used(a); //Pega no número de casas usadas;
  if(l==0){
    return -1;
  }
  int i;
  char* c = NULL;
  TNum par = NULL;
  for(i = 0 ; i < l ; i++){
    par = get_atnum_tnum(a,i); //Pega no par;
    c = get_tag_tnum(par); //obtém a tag
    if (c != NULL) //se a tag existe
      if (strcmp (c,tag) == 0 ) return i; //compara as tags, e se forem iguais retorna o indice
  }
return -1;
}

static ATNum get_allTags(TAD_community com,ATNum pairs,LONG_list ll, Date begin, Date end){
  User u = NULL; Heap posts = NULL;
  Post p = NULL; TNum new = create_tnum_pair(NULL, 0);
  Date d;
  int tam = get_ll_size(ll);
  int i,j,k,t = 0,c;
  char* aux;
  for(i = 0; i < tam;i++){            //Percorre a long-list com os top N users
    u = g_tree_lookup(com->Users,createKey(get_list(ll,i)));      //procura o User da long list, na Àrvore dos users;
    posts = getUserHeap(u);     //vai buscar todos os posts desse gajo
    t = heap_count(posts);    //conta o numero total de posts
    for(j = 0; j < t; j++){     //Percorre a àrvore com todos os posts desse men
      p = getIndP(posts,j);     //Pega no post
      d = getPostDate(p);
      if((maisRecente (begin,d)== 1 || maisRecente (begin,d) == 0 ) && (maisRecente (d,end)==1 || maisRecente (d,end) == 0)){ //compara se a data está nesse intervalo
        int numtags =getPostNTags(p);
   //vê o nº de tags do post

        for(k = 0; k < numtags;k++){
          //Percorre asx tags todas
          aux = getTagI(p,k);
          if(aux) {
            c=checkT(pairs,aux);      //Verifica se determinada tag já está no array de pares
              if(c == -1) {
                TNum aux2 = create_tnum_pair(aux,1);       //se não estiver, cria um par e introduz no array
                insere_tagnum(pairs,aux2);
            }
            else{
            new = get_atnum_tnum(pairs,c);
            new = incTNum(new);
            }
          }
        }
      }
    }
  }
  return pairs;
}


static gboolean tags_tree (gpointer key, gpointer value,gpointer user_data){
  Tag t = (Tag) value;
  long id = getTagId(t);
  Duplos dup = (Duplos) user_data;
  TNum tn = get_duplos_tnum(dup);
  LONG_list ll = get_duplos_ll(dup);
    if (strcmp(getTagName(t),get_tag_tnum(tn))==0) {
        set_list(ll,get_duplos_pos(dup),id);
        return TRUE;
    }
    return FALSE;
  }

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
  LONG_list ll = topN(com,N);
  LONG_list tagsmu = init_ll(N);
  ATNum tn = init_atnum(N);
  TNum aux = NULL;
  tn = get_allTags(com,tn,ll,begin,end);
  bubbleTNumSort(tn);
  Duplos dup = insere_Duplos(tagsmu, NULL ,N,0);
  int i;
  for(i = 0; i < N; i++){
    aux = get_atnum_tnum(tn,i);
    set_duplos_tnum(dup,aux);
    set_duplos_pos(dup,i);
    g_tree_foreach(com->Tags,(GTraverseFunc)tags_tree,dup);
  }
 
  return tagsmu;
}

TAD_community clean(TAD_community com){
  g_tree_destroy(com->Posts);
  g_hash_table_destroy(com->Hdates);
  g_tree_destroy(com->Users);
  return com;   
}
