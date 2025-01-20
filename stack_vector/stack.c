#include "stack.h"

Vector* stack_construct()
{
    Vector* stack = vector_construct();

    return stack;
}

void stack_destruct(Vector* s)
{
    vector_destroy(s);
}

int stack_size(Vector* s)
{
    return vector_size(s);
}

void push(Vector* s, void* i)
{
    vector_push_back(s,i);
}

void* pop(Vector* s)
{
    return vector_pop_back(s);
}