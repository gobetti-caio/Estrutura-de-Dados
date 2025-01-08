#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

const int SIZE = 20;
const int GROW_RATE = 2;

typedef int (*CmpFn)(const void *, const void *);

struct Heap
{
    void **nodes;
    int size;
    int capacity;
    CmpFn cmp_fn;
};

Heap *heap_constructor(int cmp_fn(const void *, const void *))
{
    Heap *heap = (Heap*)calloc(1, sizeof(Heap));

    heap->nodes = (void**)calloc(SIZE, sizeof(void*));
    heap->size = 0;
    heap->capacity = 10;
    heap->cmp_fn = cmp_fn;

    return heap;
}

void _swap_nodes(Heap *heap, int a, int b)
{
    void *temp = heap->nodes[a];
    heap->nodes[a] = heap->nodes[b];
    heap->nodes[b] = temp;
}

void _heapify_up(Heap *heap, int idx)
{
    while (idx > 0)
    {
        int parent = (idx - 1) / 2;

        if (heap->cmp_fn(heap->nodes[idx], heap->nodes[parent]) > 0)
            _swap_nodes(heap, idx, parent);

        idx = parent;
    }
}

void heap_push(Heap *heap, void *data)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= GROW_RATE;
        heap->nodes = realloc(heap->nodes, sizeof(void *) * heap->capacity);
    }

    heap->nodes[heap->size] = data;
    heap->size++;

    _heapify_up(heap, heap->size - 1);
}

void *heap_pop(Heap *heap)
{
    void* temp = heap->nodes[0];
    heap->size--;

    if (heap->size > 0 )
    {
        heap->nodes[0] = heap->nodes[heap->size];
        int idx = 0;
        while (1)
        {
            int larg = idx;
            int leftChild = (2 * idx + 1);
            int rigthChild = (2 * idx + 2);
            if (leftChild < heap->size && heap->cmp_fn(heap->nodes[leftChild],heap->nodes[larg]) > 0 )
            {
                larg = leftChild;
            }
            if (rigthChild < heap->size && heap->cmp_fn(heap->nodes[rigthChild],heap->nodes[larg]) > 0 )
            {
                larg = rigthChild;
            }
            if (larg == idx)
            {
                break;
            }
            _swap_nodes(heap, idx, larg);
            idx = larg;
        }
    }
    
    return temp;
}

int heap_size(Heap *heap)
{
    return heap->size;
}

void heap_destroy(Heap *heap)
{
    free(heap->nodes);
    free(heap);
}