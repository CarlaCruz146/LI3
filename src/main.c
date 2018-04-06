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
  printf("cenas1\n");
  xmlDocPtr pos2 = xmlParseFile(pos);
  char *us;
  us = argv[2];
  printf("cenas2\n");
  xmlDocPtr us2 = xmlParseFile(us);
  printf("cenas3\n");

  GTree *arv_users = g_tree_new_full((GCompareDataFunc) idusercompare, NULL, NULL, (GDestroyNotify) myfreeUser);
  printf("cenas4\n");
  GTree *arv_posts = g_tree_new_full((GCompareDataFunc) idpostcompare, NULL , NULL, (GDestroyNotify) freePost );
printf("cenas5\n");
  postsInfo(pos2, arv_posts);
  printf("cenas6\n");
  userInfo(us2, arv_users);
  printf("cenas7\n");
  
  gconstpointer c = argv[3];  
 // long c2 = getKey((Key) c2);
  long procura = (long)g_tree_lookup(arv_posts,c);
  printf("%ld\n",procura);

  //Key pid = createKey(4);
  //Post p = (Post)g_tree_lookup(arv_posts, pid);
  //assert(p!=NULL);

  g_tree_destroy(arv_posts);
  printf("cenas8\n");
  g_tree_destroy(arv_users);
  printf("cenas9\n");

  //Key uid = createKey(1);
  //User u = (User)g_tree_lookup(arv_users, uid);
  //assert(u!=NULL);
  //printf("%s\n",getUserName(u) );
  //g_tree_foreach(arv_users, (GTraverseFunc)iterator, NULL);
  //printf("dldasjdlk\n");
  xmlFreeDoc(pos2);
  xmlFreeDoc(us2);
}
