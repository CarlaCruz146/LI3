#include "heapU.h"

#define PAI(i) (i-1)/2
#define ESQUERDO(i) 2*i + 1
#define DIREITO(i) 2*i + 2

static HeapU swapU(HeapU heap,int n1,int n2);
static HeapU bubbleDownU(HeapU heap);
static HeapU bubbleUpU(HeapU heap);

struct heapu {
    long tamanho;
    long pos;
    long* qnt;
    long* ids;
};

HeapU initHeapU(){
    HeapU heap = malloc(sizeof(struct heapu));
    heap->tamanho = 5;
    heap->pos = 0;
    heap->qnt = malloc(5 * sizeof(long));
    heap->ids = malloc(5 * sizeof(long));
    return heap;
}

HeapU heap_pushU(HeapU heap, long id,long qnt){
  if(heap->tamanho-1 == heap->pos) {
      heap->tamanho *= 2;
      heap->ids = realloc(heap->ids,heap->tamanho *sizeof(long));
      heap->qnt = realloc(heap->qnt,heap->tamanho *sizeof(long));
  }
  heap->ids[heap->pos] = id;
  heap->qnt[heap->pos] = qnt;
  heap = bubbleUpU(heap);
  heap->pos++;
  return heap;
}


long heap_popU(HeapU heap) {
    if(heap->pos==0) return 0;
    long r = heap->ids[0];
    heap->pos--;
    heap->qnt[0] = heap->qnt[(heap->pos)];
    heap->ids[0] = heap->ids[(heap->pos)];

    heap = bubbleDownU(heap);

    return r;
}

static HeapU bubbleDownU(HeapU heap){
    int i, m, r;
    i=0;
    int n = heap->tamanho;
    while(ESQUERDO(i) < n){
          if(DIREITO(i) < n){
            r = (heap->qnt[(ESQUERDO(i))] - (heap->qnt[(DIREITO(i))]));
            if (r > 0) m = ESQUERDO(i);
            else m = DIREITO(i);
          }
          else m = ESQUERDO(i);

          if((heap->qnt[i]) - (heap->qnt[m]) < 0){
              heap = swapU(heap,i,m);
              i = m;
          }
          else return heap;
      }
      return heap;
  }



static HeapU bubbleUpU(HeapU heap){
    int i = heap->tamanho;
    while(i > 0 && ((heap->qnt[PAI(i)]) - ((heap->qnt[i]))) < 0){
            heap=swapU(heap,i,PAI(i));
            i = PAI(i);
        }
        return heap;
}


static HeapU swapU(HeapU heap,int n1,int n2) {
    long id = heap->ids[(n1)];
    heap->ids[(n1)] = heap->ids[(n2)];
    heap->ids[(n2)] = id;
    long qnt = heap->qnt[(n1)];
    heap->qnt[(n1)] = heap->qnt[(n2)];
    heap->qnt[(n2)] = qnt;
    return heap;
}

int heap_countU(HeapU heap){
    return heap->pos;
}

void heap_freeU(HeapU heap){
    free(heap->qnt);
    free(heap->ids);
    free(heap);
}
