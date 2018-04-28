#ifndef __MYPOST_H__
#define __MYPOST_H__

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <gmodule.h>
#include "common.h"
#include "date.h"


typedef struct post* Post;
typedef struct arrayd *ArrayD;

void destroyDate (void *d);

ArrayD createArray(long comp);
long getPer(ArrayD d);
long getRes(ArrayD d);
long getSize(ArrayD d);
long getUsed(ArrayD d);
Post getInd (ArrayD d, int i);
void insereArray(ArrayD a, Post p);
void freeArray(void *a);

Post initPost();
Post createPost(long, int, long, int, int, Date, long, int, int, int, char*, char**, int);
int getPostNTags(Post p);
char** getPostTags(Post p);
double calcMedia(Post p);
long getPostId(Post p);
int getPostType(Post p);
long getPid(Post p);
int getPostScore(Post p);
int getPostVCount(Post p);
Date getPostDate(Post p);
long getPostOwner(Post p);
int getPostOwnerRep(Post p);
int getPostNumCom(Post p);
int getPostNRes(Post p);
void incPostNRes(Post p);
char* getPostTitulo(Post p);
void freePost(void *p);

#endif
