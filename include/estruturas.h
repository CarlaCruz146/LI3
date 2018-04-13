#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

#include "user.h"
#include "common.h"
#include "date.h"


typedef struct post* Post;
typedef struct userint* User;
typedef struct key* Key;
typedef struct mydate* myDate;

Key createKey(long key);
long getKey(Key k);

User mycreateUser(long id, int reputacao, char* nome, char* bio, long posts[10]);
long getUserId(User u);
int getUserReputacao(User u);
char* getUserName(User u);
char* mygetbio(User u);
void myfreeUser(User u);

Post createPost(long id, int type, long pid, int score, int vcount, myDate date, long owner, char* titulo);
long getPostId(Post p);
int getPostType(Post p);
long getPid(Post p);
int getPostScore(Post p);
int getPostVCount(Post p);
myDate getPostData(Post p);
long getPostOwner(Post p);
char* getPostTitulo(Post p);
void freePost(Post p);

myDate mycreateDate(int day, int month, int year, int hours, int min, float sec);
int myget_day(myDate d);
int myget_month(myDate d); // must return a value between 0 and 11
int myget_year(myDate d);
int myget_hour(myDate d);
int myget_min(myDate d);
float myget_sec(myDate d);
void myfree_date(myDate d);

#endif
