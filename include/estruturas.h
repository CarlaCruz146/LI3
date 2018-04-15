#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

#include "user.h"
#include "common.h"
#include "date.h"


typedef struct post* Post;
typedef struct userint* User;
typedef struct key* Key;
typedef struct arrayd *ArrayD;

ArrayD creatArray(long comp);
ArrayD insereArray(ArrayD a, Post p);
void freeArray(ArrayD a);

Key createKey(long key);
long getKey(Key k);

User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10]);
long getUserId(User u);
int getUserReputacao(User u);
char* getUserName(User u);
char* mygetbio(User u);
void myfreeUser(User u);

<<<<<<< HEAD
Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner, char* titulo);
||||||| merged common ancestors
Post createPost(long id, int type, int pid, int score, int vcount, myDate date, long owner, char* titulo);
=======
Post createPost(long id, int type, long pid, int score, int vcount, myDate date, long owner, char* titulo);
>>>>>>> a87cf02db0034a222a6ecdf39f78666795849855
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
