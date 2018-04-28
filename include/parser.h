#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <gmodule.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "key.h"
#include "myuser.h"
#include "mypost.h"
#include "heap.h"


gint hash (gconstpointer);

Date incrementaData (Date);

gboolean iguais (gconstpointer, gconstpointer);

int idusercompare(gconstpointer, gconstpointer);

int idpostcompare(gconstpointer, gconstpointer);

void userInfo (xmlDocPtr, GTree*);

void postsInfo(xmlDocPtr, GTree*, GHashTable*, GTree*);

int count_tags(char*);

char** takeTag(char*);

#endif
