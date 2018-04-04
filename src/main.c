#include <date.h>
#include <stdio.h>
#include "estruturas.h"
#include "user.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "parser.h"
#include <glib.h>
#include <assert.h>


gboolean iterator(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  printf("2- %ld\n",getKey(k));
  User u = (User) value;
  printf("%ld\n", getUserId(u));
  printf("%s\n", getUserName(u));
  return FALSE;
}

int main(int argc, char **argv){
  if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
  }

  char *doc;
  doc = argv[1];
  xmlDocPtr doc2 = xmlParseFile(doc);
  GTree *arv_users = g_tree_new((GCompareFunc) idusercompare);



  //xmlNodePtr cur;
  userInfo(doc2, arv_users);
  Key uid = createKey(1);
  User u = (User)g_tree_lookup(arv_users, uid);
  assert(u!=NULL);
  printf("%s\n",getUserName(u) );
  g_tree_foreach(arv_users, (GTraverseFunc)iterator, NULL);
  //printf("dldasjdlk\n");
}
