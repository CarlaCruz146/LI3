#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "heap.h"

#define PAI(i) (i-1)/2
#define ESQUERDO(i) 2*i + 1
#define DIREITO(i) 2*i + 2

/*
#define PAI_P(i) heap->produto[(i-1)/2]
#define PAI_Q(i) heap->quantidade[(i-1)/2]
#define PAI_C(i) heap->custo[(i-1)/2]

#define FILHO_E_P(i) heap->produto[2*i+1]
#define FILHO_E_Q(i) heap->quantidade[2*i+1]
#define FILHO_E_C(i) heap->custo[2*i+1]

#define FILHO_D_P(i) heap->produto[2*i+2]
#define FILHO_D_Q(i) heap->quantidade[2*i+2]
#define FILHO_D_C(i) heap->custo[2*i+2]

#define NODO_P(i) heap->produto[i]
#define NODO_Q(i) heap->quantidade[i]
#define NODO_C(i) heap->custo[i]
*/


static Heap swap(Heap heap,int n1,int n2);
static Heap bubbleDown(Heap heap,int n);
static Heap bubbleUp(Heap heap,int i);


struct heap {
    int tamanho;
    int pos;
    Post* post;
    long* id;
};


Heap initHeap(){
    int i;
    Heap heap = malloc(sizeof(struct heap));
    heap->tamanho = 5;
    heap->pos = 0;
    heap->id = (long*) malloc(5 * sizeof(long));
    for(i=0; i<5; i++)
      heap->post[i] = initPost();
    return heap;
}


Heap heap_push(Heap heap, long id, Post post){
//  int index;

//    index = existe_heap(heap,id);
    if(heap->tamanho-1 == heap->pos) {
        heap->tamanho *= 2;
        heap->id = realloc(heap->id,heap->tamanho *sizeof(long));
        heap->post = realloc(heap->post,heap->tamanho *sizeof(Post));
    }

//    if(index == -1) {
        heap->id[heap->pos] = id;
        heap->post[heap->pos] = post;
        heap = bubbleUp(heap,heap->pos);
        heap->pos++;
//    }
return heap;
}



int existe_heap(Heap heap, long valor) {
    int i;
    int resultado = -1;
    for(i = 0; i < heap->pos; i++) {
        if(valor == heap->id[i]) return i;
    }
    return resultado;
}


long heap_pop(Heap heap) {
    if(heap->pos==0) return 0;
    long r = heap->id[0];
    heap->pos--;
    heap->id[0] = heap->id[(heap->pos)];
    heap->post[0] = heap->post[(heap->pos)];

    heap = bubbleDown(heap,heap->pos);

    return r;
}


static Heap bubbleDown(Heap heap, int n) {
    int i,m;
    i=0;
    while(ESQUERDO(i) < n) {
        if(DIREITO(i) < n) m = heap->id[(ESQUERDO(i))] > heap->id[(DIREITO(i))] ? ESQUERDO(i) : DIREITO(i);
        else m = ESQUERDO(i);

        if(heap->id[(i)] < heap->id[(m)]) {
            heap = swap(heap,i,m);
            i = m;
        }
        else return heap;
    }
   return heap;
}


static Heap bubbleUp(Heap heap, int i){
    while(i > 0 && heap->id[(PAI(i))] < heap->id[(i)]){
        heap=swap(heap,i,PAI(i));
        i = PAI(i);
    }
    return heap;
}



static Heap swap(Heap heap,int n1,int n2) {
    long n = heap->id[(n1)];
    Post p = heap->post[(n1)];

    heap->id[(n1)] = heap->id[(n2)];
    heap->post[(n1)] = heap->post[(n2)];

    heap->id[(n2)] = n;
    heap->post[(n2)] = p;

    return heap;
}


int heap_count(Heap heap){
    return heap->pos;
}

void heap_free(Heap heap){
    int i;
    for(i = 0; i < heap->pos; i++) {
        free(heap->post[i]);
    }
    free(heap->id);
    free(heap);
}
