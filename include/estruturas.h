#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

#include "user.h"
#include "common.h"
#include "date.h"


typedef struct post* Post;
typedef struct userint* User;
typedef struct key* Key;

Key createKey(long key);
long getKey(Key k);

User mycreateUser(long id, int reputacao, char* nome, char* bio);
long getUserId(User u);
int getUserReputacao(User u);
char* getUserName(User u);
char* mygetbio(User u);
void myfreeUser(User u);

Post createPost(long id, int type, int score, int vcount, Date data, long owner, char* titulo);
long getPostId(Post p);
int getPostType(Post p);
int getPostScore(Post p);
int getPostVCount(Post p);
Date getPostData(Post p);
long getPostOwner(Post p);
char* getPostTitulo(Post p);
void freePost(Post p);

#endif
