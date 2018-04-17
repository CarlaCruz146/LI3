#ifndef _heap_h_
#define _heap_h_

#include "estruturas.h"

typedef struct heap *Heap;

Heap initHeap();
Heap heap_push(Heap heap, long id, Post post);
int existe_heap(Heap heap, long valor);
int heap_count(Heap heap);
void heap_free(Heap heap);

#endif
