
#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

//Creates a empy heap using ass argument the comparision function to e used in the heap
Heap *heap_constructor(int (*cmp_fn)(const void *, const void *));

//adds a element in the heap
void heap_push(Heap *heap, void *data);

//return the size of the heap
int heap_size(Heap *heap);

//removes a element of the heap  
void *heap_pop(Heap *heap);

//destroy the heap
void heap_destroy(Heap *heap);

#endif