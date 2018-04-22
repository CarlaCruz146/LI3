#include "myvotes.h"

struct votes{
  long id;
  long post_id;
};



long getVoteId(Vote v){
  if (v) return v->id;
  return -1;
}

long getVPostId(Vote v){
  if (v) return v->post_id;
  return -1;
}

Vote mycreateVote(long id, long postid){
  if (id > -1){
    Vote v = malloc(sizeof(struct votes));
    v->id = id;
    v->post_id = postid;
    return v;
  }
  return NULL;
}

void myfreeVote(void *v){
  Vote aux = (Vote) v;
  if (aux)
    free(aux);
}
