#include "queue.h"


List* queue_construct()
{
    List* queue = list_construct();

    return queue;
}

void queue_destruct(List* q)
{
    list_destroy(q);
}

int queue_size(List* q)
{
    return list_size(q);
}

void queue_insert(List* q, void* i)
{
    list_push_back(q,i);
}

void* queue_remove(List* q)
{
    return list_pop_front(q);
}
