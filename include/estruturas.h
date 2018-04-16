#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

#include "user.h"
#include "common.h"
#include "date.h"
#include <gmodule.h>


typedef struct post* Post;
typedef struct userint* User;
typedef struct key* Key;
typedef struct arrayd *ArrayD;


ArrayD createArray(long comp);
long getPer(ArrayD d);
long getRes(ArrayD d);
long getSize(ArrayD d);
long getUsed(ArrayD d);
Post getInd (ArrayD d, int i);

void insereArray(ArrayD a, Post p);
void freeArray(ArrayD a);


Key createKey(long key);
long getKey(Key k);

//int maisrecente(gconstpointer id1, gconstpointer id2);
User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10], GTree* arv_uposts);
long getUserId(User u);
int getUserReputacao(User u);
char* getUserName(User u);
char* mygetbio(User u);
void myfreeUser(User u);

Post initPost();
Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner, char* titulo);
long getPostId(Post p);
int getPostType(Post p);
long getPid(Post p);
int getPostScore(Post p);
int getPostVCount(Post p);
Date getPostDate(Post p);
long getPostOwner(Post p);
char* getPostTitulo(Post p);
void freePost(Post p);

#endif
