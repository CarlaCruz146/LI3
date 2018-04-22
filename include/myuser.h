#ifndef __MYUSER_H__
#define __MYUSER_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "parser.h"
#include <gmodule.h>

typedef struct userint* User;

User mycreateUser(long id, int reputacao, char* nome, char* bio);
long getUserId(User u);
int getUserReputacao(User u);
char* getUserName(User u);
char* mygetbio(User u);
void myfreeUser(void *u);

#endif
