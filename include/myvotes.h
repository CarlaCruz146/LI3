#ifndef __VOTES_H__
#define __VOTES_H__

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include "common.h"
#include "date.h"
#include "parser.h"
#include <gmodule.h>

typedef struct votes* Vote;

long getVoteId(Vote v);
long getVPostId(Vote v);
Vote mycreateVote(long id, long postid);
void myfreeVote(Vote v);

#endif
