#include "parser.h"
#include "heap.h"

char* myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

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

int idvotecompare(gconstpointer id1, gconstpointer id2){ //sendo id2 o a colocar
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

           long id = atol((char*) xmlGetProp(cur, (const xmlChar *) "Id")); //Procura o atributo Id
    //       printf("Id: %ld\n", id);

           int rep = atoi((char*)xmlGetProp(cur, (const xmlChar *) "Reputation")); //Procura o atributo Reputation
//           printf("Reputation: %d\n", rep);

           char* nome = (char*)xmlGetProp(cur, (const xmlChar *) "DisplayName"); //Procura o atributo DisplayName
	//				 printf("Display Name: %s\n", nome);

           char* bio = (char*) xmlGetProp(cur, (const xmlChar *) "AboutMe"); //Procura o atributo AboutMe					printf("About Me: %s\n", bio);

           User u = mycreateUser(id, rep, nome, bio);

           Key uid = createKey(getUserId(u));
//           printf("1- %ld\n", getKey(uid));
           g_tree_insert(arv_users, uid, u);
  //         printf("4- %d\n", g_tree_nnodes(arv_users));
         }
			cur = cur->next;
    }
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
    ArrayD a = createArray(2);
    insereArray(a,p);
    g_hash_table_insert(hdate,date,a);
  }
  else{
    free_date(date);
    ArrayD d = (ArrayD) x;
    insereArray(d,p);
  }
}

void postsInfo(xmlDocPtr doc, GTree * arv_posts, GHashTable *datash) {
	 xmlNodePtr cur = xmlDocGetRootElement(doc);
	 cur = cur->xmlChildrenNode;
   char* aux;

	 while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

          long id = atol((char*)xmlGetProp(cur, (const xmlChar *) "Id"));

		    	int typeid = atoi((char*)xmlGetProp(cur, (const xmlChar *) "PostTypeId"));

          aux =(char*)xmlGetProp(cur, (const xmlChar *) "ParentId");
            long pid = aux ? atol (aux) : -2;

          char* cdate = (char*)xmlGetProp(cur, (const xmlChar *) "CreationDate");

          int year = atoi(getYear(cdate));
          int month = atoi(getMonth(cdate));
          int day = atoi(getDay(cdate));

          Date date = createDate(day,month-1,year);

          int score = atoi((char*)xmlGetProp(cur, (const xmlChar *) "Score"));

          aux = (char*)xmlGetProp(cur, (const xmlChar *) "ViewCount");
            int vcount = aux ? atoi(aux) : 0;

          long ownerid = atol((char*)xmlGetProp(cur, (const xmlChar *) "OwnerUserId"));

          char* title = (char*)xmlGetProp(cur, (const xmlChar *) "Title");

          Post p = createPost(id,typeid,pid,score,vcount,date,ownerid,title);

          Key key = createKey(id);
          Date dnova = (getPostDate(p));

          g_tree_insert(arv_posts, key, p);

          inseredatas(datash, dnova, p);


          //ver ownerid, se ja tiver uma heap dele, fazer insert na u->heap
          //caso contrario criar a heap
          //g_tree_insert(arv_uposts, key, )

				}
			cur = cur->next;
	}
}


void votesInfo(xmlDocPtr doc, GTree * arv_votes) {

    xmlNodePtr cur = xmlDocGetRootElement(doc);
    cur = cur->xmlChildrenNode;


	while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

          long id = atol((char*)xmlGetProp(cur, (const xmlChar *) "Id"));
  //     printf("Id: %ld\n", id);

			       long postid = atol((char*)xmlGetProp(cur, (const xmlChar *) "PostId"));
//		   printf("Post ID: %ld\n", postid);


        Vote v = mycreateVote(id,postid);

        Key key = createKey(getVoteId(v));

        g_tree_insert(arv_votes, key, v);

        }

			cur = cur->next;
	}
    printf("2");
}


/*
void parseDo(char *docname, char *docname2, char *docname3, GTree * arv_users, GTree * arv_posts) {

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	if (!doc) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	cur = cur->xmlChildrenNode;
	if (!xmlStrcmp(cur->name, (const xmlChar *) "row")) {
		fprintf(stderr,"document of the wrong type, root node != row ");
		xmlFreeDoc(doc);
		return;
	}


	xmlDocPtr doc2;
	xmlNodePtr cur2;

	doc2 = xmlParseFile(docname2);

	if (!doc2) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}

	cur2 = xmlDocGetRootElement(doc2);

	if (cur2 == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc2);
		return;
	}

	cur2 = cur2->xmlChildrenNode;

	if (!xmlStrcmp(cur2->name, (const xmlChar *) "row")) {
		fprintf(stderr,"document of the wrong type, root node != row ");
		xmlFreeDoc(doc2);
		return;
	}

	xmlDocPtr doc3;
	xmlNodePtr cur3;

	doc3 = xmlParseFile(docname3);

	if (!doc3) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}

	cur3 = xmlDocGetRootElement(doc3);
	if (cur3 == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc3);
		return;
	}

	cur3 = cur3->xmlChildrenNode;
	if (!xmlStrcmp(cur3->name, (const xmlChar *) "row")) {
		fprintf(stderr,"document of the wrong type, root node != row ");
		xmlFreeDoc(doc3);
		return;
	}

	userInfo (doc, arv_users);
	xmlFreeDoc(doc);

	postsInfo (doc2, arv_posts,hdate);
	xmlFreeDoc(doc2);

	votesInfo (doc3, cur3);
	xmlFreeDoc(doc3);
}




int main (int argc, char **argv) {

	char *docname;
	char *docname2;
	char *docname3;

	if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
	}

	docname = argv[1]; //Para os users
	docname2 = argv[2]; //Para os POSTS
	docname3 = argv[3]; //Para os Votos

	parseDo (docname, docname2,docname3);

	return 1;
}
*/
