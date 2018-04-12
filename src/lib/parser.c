#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "estruturas.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <gmodule.h>


char* myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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

gint datacompare(gconstpointer data1, gconstpointer data2){ //sendo data1 o a colocar
  myDate key1 = (myDate) data1;
  myDate key2 = (myDate) data2;
  int hour1 = myget_hour(key1);
  int min1 = myget_min(key1);
  int sec1 = myget_sec(key1);
  int hour2 = myget_hour(key2);
  int min2 = myget_min(key2);
  int sec2 = myget_sec(key2);

  long time1 = (hour1*60*60) + (min1*60) + sec1;
  long time2 = (hour2*60*60) + (min2*60) + sec2;

  return time1-time2;
}


void userInfo (xmlDocPtr doc, GTree * arv_users) {
	//printf("USERS: \n");
	xmlNodePtr cur = xmlDocGetRootElement(doc); // Acede à raíz do documento: "<users>"
	cur = cur->xmlChildrenNode; // Vai para o filho: tag <row>

	while (cur != NULL) { //Enquanto houver tags row's:
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //compara as tags

           long id = atol((char*) xmlGetProp(cur, (const xmlChar *) "Id")); //Procura o atributo Id
           //printf("Id: %ld\n", id);

           int rep = atoi((char*)xmlGetProp(cur, (const xmlChar *) "Reputation")); //Procura o atributo Reputation
           //printf("Reputation: %d\n", rep);

           char* nome = (char*)xmlGetProp(cur, (const xmlChar *) "DisplayName"); //Procura o atributo DisplayName
					 //printf("Display Name: %s\n", nome);

           char* bio = (char*) xmlGetProp(cur, (const xmlChar *) "AboutMe"); //Procura o atributo AboutMe					printf("About Me: %s\n", bio);

           User u = mycreateUser(id, rep, nome, bio);

           Key uid = createKey(getUserId(u));
           //printf("1- %ld\n", getKey(uid));

           g_tree_insert(arv_users, uid, u);
           //printf("4- %d\n", g_tree_nnodes(arv_users));
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

char* getHour(char* d){
  int i=0, hi=0, j;
  while(d[i]!='T')
    i++;
  for(j=i+1; d[j]!=':'; j++)
    d[hi++]=d[j];
  d[hi]='\0';
  return d;
}

char* getMin(char* d){
  int i=0, mi=0, j;
  while(d[i]!=':')
    i++;
  for(j=i+1; d[j]!=':'; j++)
    d[mi++]=d[j];
  d[mi]='\0';
  return d;
}

char* getSec(char* d){
  int si=0, j;
  for(j=17; d[j]!='\0'; j++)
    d[si++]=d[j];
  d[si]='\0';
  return d;
}



void postsInfo(xmlDocPtr doc, GTree * arv_posts) {
	 xmlNodePtr cur = xmlDocGetRootElement(doc);
	 cur = cur->xmlChildrenNode;
   char* aux;

	 while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {

          long id = atol((char*)xmlGetProp(cur, (const xmlChar *) "Id"));

		      int typeid = atoi((char*)xmlGetProp(cur, (const xmlChar *) "PostTypeId"));

          int pid = atoi((char*)xmlGetProp(cur, (const xmlChar *) "ParentId"));

          char* cdate = (char*)xmlGetProp(cur, (const xmlChar *) "CreationDate");

          int year = atoi(getYear(cdate));
          int month = atoi(getMonth(cdate));
          int day = atoi(getDay(cdate));
          int hour = atoi(getHour(cdate));
          int min = atoi(getMin(cdate));
          int sec = atoi(getMin(cdate));

          myDate date = mycreateDate(day,month,year,hour,min,sec);

          int score = atoi((char*)xmlGetProp(cur, (const xmlChar *) "Score"));

          aux = (char*)xmlGetProp(cur, (const xmlChar *) "ViewCount");
          int vcount = aux ? atoi(aux) : 0;

          long ownerid = atol((char*)xmlGetProp(cur, (const xmlChar *) "OwnerUserId"));

          char* title = (char*)xmlGetProp(cur, (const xmlChar *) "Title");

          Post p = createPost(id,typeid,pid,score,vcount,date,ownerid,title);

          Key key = createKey(getPostId(p));

          g_tree_insert(arv_posts, key, p);
				}
			cur = cur->next;
	}
}


void votesInfo(xmlDocPtr doc, xmlNodePtr cur) {

	xmlChar *uri;

	//printf("Votes: \n");

	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
		    uri = xmlGetProp(cur, (const xmlChar *) "Id");
		//    printf("Id: %s\n", uri);

			  uri = xmlGetProp(cur, (const xmlChar *) "PostId");
			//   printf("Post ID: %s\n", uri);

		    uri = xmlGetProp(cur, (const xmlChar *) "VoteTypeId");
			 //  printf("Vote Type ID: %s\n", uri);

				uri = xmlGetProp(cur, (const xmlChar *) "CreationDate");
				//	printf("Creation Date: %s\n", uri);
					xmlFree(uri);
				}

			cur = cur->next;
	}
}



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

	postsInfo (doc2, arv_posts);
	xmlFreeDoc(doc2);

	votesInfo (doc3, cur3);
	xmlFreeDoc(doc3);
}



/*
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
