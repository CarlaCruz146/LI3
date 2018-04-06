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
  getKey(k);
  printf("Key- %ld\n",getKey(k));
  Post p = (Post)value;
  printf("Pid %ld\n", getPostId(p));
  printf("%ld\n", getPostOwner(p));
  return FALSE;
}

int main(int argc, char **argv){
  if (argc <= 1) {
		printf("Usage: %s docname\n", argv[0]);
		return(0);
  }

  char *pos;
  pos = argv[1];
  xmlDocPtr pos2 = xmlParseFile(pos);
  GTree *arv_users = g_tree_new((GCompareFunc) idusercompare);
  GTree *arv_posts = g_tree_new((GCompareFunc) idpostcompare);

  char *us;
  us = argv[2];
  xmlDocPtr us2 = xmlParseFile(us);

  userInfo(us2, arv_users);
  postsInfo(pos2, arv_posts);

  Key pid = createKey(4);
  Post p = (Post)g_tree_lookup(arv_posts, pid);
  assert(p!=NULL);
//  g_tree_foreach(arv_posts, (GTraverseFunc)iterator, NULL);
  //g_tree_free(arv_posts);
  //Key uid = createKey(1);
  //User u = (User)g_tree_lookup(arv_users, uid);
  //assert(u!=NULL);
  //printf("%s\n",getUserName(u) );
  //g_tree_foreach(arv_users, (GTraverseFunc)iterator, NULL);
  //printf("dldasjdlk\n");
}
