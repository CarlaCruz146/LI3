#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "key.h"
#include "myuser.h"
#include "mypost.h"
#include <gmodule.h>

char* myconcat(const char *s1, const char *s2);

gint hash (gconstpointer a);

Date incrementaData (Date data);

gboolean iguais (gconstpointer a, gconstpointer b);

int idusercompare(gconstpointer id1, gconstpointer id2);

int idpostcompare(gconstpointer id1, gconstpointer id2);

void userInfo (xmlDocPtr doc, GTree * arv_users);

void postsInfo(xmlDocPtr doc, GTree * arv_posts, GHashTable *datash);

void votesInfo (xmlDocPtr doc, xmlNodePtr cur);

void parseDo(char *docname, char *docname2, char *docname3, GTree * arv_users, GTree * arv_posts);


#endif
