#ifndef __POSTS_H__
#define __POSTS_H__

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "date.h"
#include "parser.h"
#include <gmodule.h>

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
Post createPost(long id, int type, long pid, int score, int vcount, Date date, long owner,int numcom, char* titulo);
long getPostId(Post p);
int getPostType(Post p);
long getPid(Post p);
int getPostScore(Post p);
int getPostVCount(Post p);
Date getPostDate(Post p);
long getPostOwner(Post p);
int getPostNumCom(Post p);
char* getPostTitulo(Post p);
void freePost(void *p);

#endif
