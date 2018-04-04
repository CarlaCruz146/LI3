#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "estruturas.h"
#include "parser.h"
//#include "TCD.h"

#include <gmodule.h>

gint idusercompare(gconstpointer id1, gconstpointer id2){ //sendo id1 o a colocar
  long key1 = getKey((Key) id1);
  long key2 = getKey((Key) id2);
  printf("%ld : %ld\n",key1, key2);
  if (key1 == key2)
    return 0; //o elemento é o mesmo
  if (key1 < key2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}


gint idpostcompare(const void* id1, const void* id2){ //sendo id1 o a colocar
  long key1 = *(long *) id1;
  long key2 = *(long *) id2;
  if (key1 == key2)
    return 0; //o elemento é o mesmo
  if (key1 < key2)
    return 1; //vai para a direita
  else return (-1); //vai para a esquerda
}



void userInfo (xmlDocPtr doc, GTree * arv_users) {
	//printf("USERS: \n");

	xmlNodePtr cur = xmlDocGetRootElement(doc); // Acede à raíz do documento: "<users>"
	cur = cur->xmlChildrenNode; // Vai para o filho: tag <row>

	// GTree *arv_users = g_tree_new(idusercompare);

	while (cur != NULL) { //Enquanto houver tags row's:
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) { //compara as tags
				 long id = atol((char*) xmlGetProp(cur, (const xmlChar *) "Id")); //Procura o atributo Id
         //printf("Id: %ld\n", id);
		     int rep = atoi((char*)xmlGetProp(cur, (const xmlChar *) "Reputation")); //Procura o atributo Reputation
         //printf("Reputation: %d\n", rep);

/*
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			   uri = xmlGetProp(cur, (const xmlChar *) "CreationDate"); //Procura o atributo CreationDate
			  // printf("Creation Date: %s\n", uri);
			   xmlFree(uri);
		   }
*/

					char* nome = (char*)xmlGetProp(cur, (const xmlChar *) "DisplayName"); //Procura o atributo DisplayName
					//printf("Display Name: %s\n", nome);
					char* bio = (char*) xmlGetProp(cur, (const xmlChar *) "AboutMe"); //Procura o atributo AboutMe					printf("About Me: %s\n", bio);
          User u = mycreateUser(id, rep, nome, bio);
          Key uid = createKey(getUserId(u));
          printf("1- %ld\n", getKey(uid));
          g_tree_insert(arv_users, uid, u);
          printf("4- %d\n", g_tree_nnodes(arv_users));
    }
			cur = cur->next;

	}
}



void postsInfo(xmlDocPtr doc, xmlNodePtr cur) {

	xmlChar *uri;

	//printf("POSTS: \n");

	cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
		    uri = xmlGetProp(cur, (const xmlChar *) "Id");
		//    printf("Id Post: %s\n", uri);
		    xmlFree(uri);
				}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			   uri = xmlGetProp(cur, (const xmlChar *) "PostTypeId");
			//   printf("Post Type ID: %s\n", uri);
			   xmlFree(uri);
		    }

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			   uri = xmlGetProp(cur, (const xmlChar *) "CreationDate");
			  // printf("Creation Date: %s\n", uri);
			   xmlFree(uri);
		   }

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
					uri = xmlGetProp(cur, (const xmlChar *) "Score");
					//printf("Score: %s\n", uri);
					xmlFree(uri);
				}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
						uri = xmlGetProp(cur, (const xmlChar *) "ViewCount");
					//	printf("View Count: %s\n", uri);
						xmlFree(uri);
				}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
							uri = xmlGetProp(cur, (const xmlChar *) "OwnerUserId");
						//	printf("Owner User Id: %s\n", uri);
							xmlFree(uri);
					}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
								uri = xmlGetProp(cur, (const xmlChar *) "Body");
							//	printf("Title: %s\n", uri);
								xmlFree(uri);
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
		    xmlFree(uri);
				}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			   uri = xmlGetProp(cur, (const xmlChar *) "PostId");
			//   printf("Post ID: %s\n", uri);
			   xmlFree(uri);
		    }

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
			   uri = xmlGetProp(cur, (const xmlChar *) "VoteTypeId");
			 //  printf("Vote Type ID: %s\n", uri);
			   xmlFree(uri);
		   }

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"row"))) {
					uri = xmlGetProp(cur, (const xmlChar *) "CreationDate");
				//	printf("Creation Date: %s\n", uri);
					xmlFree(uri);
				}

			cur = cur->next;
	}
}



void parseDo(char *docname, char *docname2, char *docname3, GTree * arv_users) {

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

	postsInfo (doc2, cur2);
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
