#include "stack.h"

List* stack_construct()
{
    List* stack = list_construct();

    return stack;
}

void stack_destruct(List* s)
{
    list_destroy(s);
}

int stack_size(List* s)
{
    return list_size(s);
}

void push(List* s, void* i)
{
    list_push_back(s,i);
}

void* pop(List* s)
{
    return list_pop_back(s);
}