#include "key.h"
#include <stdlib.h>

struct key{
  long key;
};

Key createKey(long key){
  Key k = malloc(sizeof(struct key));
  k->key = key;
  return k;
}


long getKey(Key k){
  return k->key;
}
