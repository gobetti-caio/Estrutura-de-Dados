#include "queue.h"


Vector* queue_construct()
{
    Vector* queue = vector_construct();

    return queue;
}

void queue_destruct(Vector* q)
{
    vector_destroy(q);
}

int queue_size(Vector* q)
{
    return vector_size(q);
}

void queue_insert(Vector* q, void* i)
{
    vector_push_back(q,i);
}

void* queue_remove(Vector* q)
{
    return vector_pop_front(q);
}
