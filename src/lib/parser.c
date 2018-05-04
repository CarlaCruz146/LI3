#include "parser.h"

gint hash (gconstpointer a){
  Date b = (Date) a;
  int hash = 7;
  hash = 31* hash + get_day(b);
  hash = 31* hash + get_month(b);
  hash = 31* hash + get_year(b);
  return hash;
}

Date incrementaData (Date data){
  int day1 = get_day(data);
  int month1 = get_month(data);
  int year1 = get_year(data);
  int dayn = day1;
  int monthn = month1;
  int yearn = year1;
  free_date(data);
  Date newd;

  if (month1 == 0 || month1 == 2 || month1 == 4 || month1 == 6 || month1 == 7 || month1 == 9){
    if (day1 == 31){
      dayn = 1;
      monthn++;
    }
    else{
      dayn++;
    }
    newd = createDate(dayn,monthn,yearn);
    return newd;
  }
  if (month1 == 1){
    if ((year1 % 4) == 0){
      if (day1==29){
          dayn = 1;
          monthn++;
      }
      else dayn++;
    }
    else if(day1==28){
      dayn = 1;
      monthn++;
    }else dayn++;
    newd = createDate(dayn,monthn,yearn);
    return newd;
  }
  if (month1 == 3 || month1 == 5 || month1 == 8 || month1 == 10){
    if (day1 == 30){
      dayn = 1;
      monthn++;
    }
    else{
      dayn++;
    }
    newd = createDate(dayn,monthn,yearn);
    return newd;
  }
  if (month1 == 11){
    if (day1 == 31){
      dayn = 1;
      monthn = 0;
      yearn++;
    }
    else{
      dayn++;
    }
    newd = createDate(dayn,monthn,yearn);
    return newd;
  }
  return NULL;
}

static int date_equal(Date begin, Date end){
  int d,m,a,r;
  d = (get_day(begin) == get_day(end)) ? 0 : 1;
  m = (get_month(begin) == get_month(end)) ? 0 : 1;
  a = (get_year(begin) == get_year(end)) ? 0 : 1;

  r = (d + m + a) > 0 ? 1 : 0;

  return r;
}

gboolean iguais (gconstpointer a, gconstpointer b){
  Date data1 = (Date) a;
  Date data2 = (Date) b;
  if(date_equal(data1,data2)==0)
      return TRUE;
  else return FALSE;
}

int idusercompare(gconstpointer id1, gconstpointer id2){ //sendo id2 o a colocar
  long key1 = getKey((Key) id1);
  long key2 = getKey((Key) id2);

  return key1-key2;
}


int idpostcompare(gconstpointer id1, gconstpointer id2){ //sendo id2 o a colocar
  long key1 = getKey((Key) id1);
  long key2 = getKey((Key) id2);

  return key1-key2;
}

int idtagcompare(gconstpointer id1, gconstpointer id2){ //sendo id2 o a colocar
  long key1 = getKey((Key) id1);
  long key2 = getKey((Key) id2);
  return key1-key2;
}

gint datacompare(gconstpointer data1, gconstpointer data2){ //sendo data1 o a colocar
  Date key1 = (Date) data1;
  Date key2 = (Date) data2;
  int day1 = get_day(key1);
  int month1 = get_month(key1);
  int year1 = get_year(key1);
  int day2 = get_day(key2);
  int month2 = get_month(key2);
  int year2 = get_year(key2);

  if(year1 < year2) return -1;
  if(year1 > year2) return 1;
  if(year1 == year2){
    if(month1 < month2) return -1;
    else
    if (month1 > month2) return 1;
    else
    {
      if(day1 < day2) return -1;
      else
      if(day1 > day2) return 1;
      else
      return 0;
    }
  }
  return 0;
}



void userInfo (xmlDocPtr doc, GTree * arv_users) {

	xmlNodePtr cur = xmlDocGetRootElement(doc); // Acede à raíz do documento: "<users>"
	cur = cur->xmlChildrenNode; // Vai para o filho: tag <row>

	while (cur != NULL) { //Enquanto houver tags row's:
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //compara as tags

           xmlChar* id1 = xmlGetProp(cur, (const xmlChar *) "Id"); //Procura o atributo Id
           long id = atol((char*) id1);

           xmlChar* rep1 = xmlGetProp(cur, (const xmlChar *) "Reputation"); //Procura o atributo Reputation
           int rep = atoi((char*) rep1);

           xmlChar* n = xmlGetProp(cur, (const xmlChar *) "DisplayName"); //Procura o atributo DisplayName
           char* nome = ((char*) n);

           xmlChar* b = xmlGetProp(cur, (const xmlChar *) "AboutMe"); //Procura o atributo AboutMe
           char* bio = ((char*) b);

           Heap uposts = initHeap();

           User u = mycreateUser(id, rep, nome, bio, 0, uposts);

           Key uid = createKey(getUserId(u));

           g_tree_insert(arv_users, uid, u);

           xmlFree(id1);
           xmlFree(rep1);
           xmlFree(n);
           xmlFree(b);

         }
			cur = cur->next;
    }
    xmlCleanupParser();
}


char* getYear(char* d){
    int i=0;
    while(d[i]!='-')
      i++;
    d[i]='\0';
    return d;
  }

char* getMonth(char* d){
    int j, w=0;
    for(j=0;j<5;j++)
      ;
    while(j<7)
      d[w++]=d[j++];
    d[w]='\0';
    return d;
}

char* getDay(char* d){
    int a, b=0;
    for(a=0;a<8;a++)
      ;
    while(a<10)
      d[b++]=d[a++];
    d[b]='\0';
    return d;
}

void inseredatas(GHashTable *hdate, Date date, Post p){
  gpointer x = g_hash_table_lookup(hdate, date);
  if( x == NULL){
    ArrayD a = createArray(1);
    insereArray(a,p);
    g_hash_table_insert(hdate,date,a);
  }
  else{
    free_date(date);
    ArrayD d = (ArrayD) x;
    insereArray(d,p);
  }
}

int count_tags(char* tags){
    int i, num = 0;
    for(i = 0; tags[i] != '\0'; i++)
        if(tags[i] == '<')
            num++;
    return num;
}

char** takeTag(char* tags){
    if(!tags) return NULL;

    int i, j, i_tag, i_list = 0;
    int num_tags = count_tags(tags);
    char** list = malloc((num_tags + 1) * sizeof(char*));

    for(i = 0; tags[i] != '\0'; i++){
        if(tags[i] == '<'){
            for(j = i+1; tags[j] != '>'; j++)
                ;
            i++;

            char* tag = malloc((j - i + 1) * sizeof(char));
            i_tag = 0;
            for(; tags[i] != '>'; i++)
                tag[i_tag++] = tags[i];

            tag[i_tag] = '\0';
            list[i_list++] = tag;
        }
    }
    list[i_list] = NULL;
    return list;
}

int nTags(char** list){
    if(list == NULL) return 0;

    int i, num = 0;
    for(i = 0; list[i]; i++)
        num++;
    return num;
}


void postsInfo(xmlDocPtr doc, GTree * arv_posts, GHashTable *datash, GTree * arv_users) {
	 xmlNodePtr cur = xmlDocGetRootElement(doc);
	 cur = cur->xmlChildrenNode;
   char* aux;

	 while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

          xmlChar* id1 = xmlGetProp(cur, (const xmlChar *) "Id");
          long id = atol((char*) id1);

          xmlChar* ti = xmlGetProp(cur, (const xmlChar *) "PostTypeId");
		    	int typeid = atoi((char*) ti);

          xmlChar* pid1 = xmlGetProp(cur, (const xmlChar *) "ParentId");
          aux =(char*) (pid1);
          long pid = aux ? atol (aux) : -2;

          xmlChar* cdate1 = xmlGetProp(cur, (const xmlChar *) "CreationDate");
          char* cdate = (char*) cdate1;

          int year = atoi(getYear(cdate));
          int month = atoi(getMonth(cdate));
          int day = atoi(getDay(cdate));

          Date date = createDate(day,month,year);

          xmlChar* score1 = xmlGetProp(cur, (const xmlChar *) "Score");
          int score = atoi((char*) score1);

          xmlChar* vc = xmlGetProp(cur, (const xmlChar *) "ViewCount");
          aux = (char*) vc ;
            int vcount = aux ? atoi(aux) : 0;
          
          xmlChar* ac = xmlGetProp(cur, (const xmlChar *) "AnswerCount");
          aux = (char*) ac ;
            int nres = aux ? atoi(aux) : 0;

          xmlChar* oi = xmlGetProp(cur, (const xmlChar *) "OwnerUserId");
          long ownerid = atol((char*) oi);

          xmlChar* cc = xmlGetProp(cur,(const xmlChar *) "CommentCount");
          aux = (char*) cc;
          int comcount = aux ? atoi(aux) : 0;

          xmlChar* t = xmlGetProp(cur, (const xmlChar *) "Title");
          char* title = (char*) t;

          xmlChar* aux = xmlGetProp(cur,(const xmlChar *) "Tags");
          char* tags =aux ? (char*) aux : NULL;
          char** str = takeTag(tags);
          int ntags = nTags(str);

          Key kowner = createKey(ownerid);
          User u = (User)g_tree_lookup(arv_users, kowner);
          int ownerRep = getUserRep(u);
          freekey(kowner);

          Post p = createPost(id,typeid,pid,score,vcount,date,ownerid,ownerRep,comcount, nres, title, str, ntags);
          //printf("tranquilo\n");
          Heap h = getUserHeap(u);
         // printf("Vai arder?\n");
          heap_push(h, p, 'D');
        //  printf("ardeeeeu\n");

          Key key = createKey(id);
      //    printf("key\n");
          Date dnova = (getPostDate(p));
    //      printf("date\n");

          g_tree_insert(arv_posts, key, p);
  //printf("insert\n");
          inseredatas(datash, dnova, p);
//printf("insere data\n");
          for(int i=0; i<ntags; i++)
              free(str[i]);
          free(str);

          xmlFree(id1);
          xmlFree(ti);
          xmlFree(pid1);
          xmlFree(cdate1);
          xmlFree(score1);
          xmlFree(vc);
          xmlFree(oi);
          xmlFree(ac);
          xmlFree(cc);
          xmlFree(t);
          xmlFree(aux);
				}
			cur = cur->next;
	}
  xmlCleanupParser();
}

void tagsInfo (xmlDocPtr doc, GTree * arv_tags) {

	xmlNodePtr cur = xmlDocGetRootElement(doc); // Acede à raíz do documento: "<tags>"
	cur = cur->xmlChildrenNode; // Vai para o filho: tag <row>

	while (cur != NULL) { //Enquanto houver tags row's:
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //compara as tags

           xmlChar* id1 = xmlGetProp(cur, (const xmlChar *) "Id"); //Procura o atributo Id
           long id = atol((char*) id1);

           xmlChar* name1 = xmlGetProp(cur, (const xmlChar *) "TagName"); //Procura o atributo TagName
           char* name =  (char*) name1;


           Tag t = createTag(id, name);

           Key uid = createKey(getTagId(t));

           g_tree_insert(arv_tags, uid, t);

           xmlFree(id1);
           xmlFree(name1);
         }
			cur = cur->next;
    }
    xmlCleanupParser();
}
