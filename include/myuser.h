#ifndef __MYUSER_H__
#define __MYUSER_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmodule.h>
#include "user.h"
#include "parser.h"
#include "heap.h"

typedef struct userint* User;

User mycreateUser(long id, int reputacao, char* nome, char* bio, int nposts, Heap uposts);
Heap getUserHeap(User u);
long getUserId(User u);
int getUserRep(User u);
char* getUserName(User u);
char* mygetUserBio(User u);
int getUserNPosts(User u);
void incUserNPosts(User u);
void myfreeUser(void *u);

#endif
