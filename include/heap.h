#ifndef _heap_h_
#define _heap_h_

#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

typedef struct heap *Heap;

Heap initHeap();
Heap heap_push(Heap heap, Post post);
Post heap_pop(Heap heap);
int heap_count(Heap heap);
void heap_free(Heap heap);

#endif
