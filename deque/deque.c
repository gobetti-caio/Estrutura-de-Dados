
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define CAPACITY 100

typedef int data_type;

struct Deque
{
    data_type* data;
    int front;
    int rear;
    int size;
};

Deque *deque_construct()
{
    Deque* new =(Deque*)calloc(1,sizeof(Deque));

    new->data = (data_type*)calloc(CAPACITY,sizeof(data_type*));
    new->front = 0;
    new->rear = 0;
    new->size = 0;

    return new; 
}

void deque_push_back(Deque *f, int item)
{
    if (f->size == CAPACITY)
    {
        printf("deque cheio");
        return;
    }
    else
    {
        f->data[f->rear] = item;
        f->rear = (f->rear + 1)%CAPACITY;
        f->size++;
    }
}

void deque_push_front(Deque *f, int item)
{
    if (!f || f->size == CAPACITY)
    {
        printf("Comando invalido");
    }
    else
    {
        f->front = (f->front - 1 + CAPACITY)%CAPACITY;
        f->data[f->front] = item;
        f->size++;
    }
}

int deque_pop_back(Deque *f)
{
    if (!f || f->size == 0)
    {
        printf("Comando invalido");
        return -1;
    }
    else
    {
        f->rear = (f->rear - 1 + CAPACITY)%CAPACITY;
        data_type temp = f->data[f->rear];
        f->size--;
        return temp;
    }
    
}
int deque_pop_front(Deque *f)
{
    if (!f || f->size == 0)
    {
        printf("Comando invalido");
        return -1;
    }
    else
    {
        data_type temp = f->data[f->front];
        f->front = (f->front + 1)%CAPACITY;
        f->size--;
        return temp;
    }   
}

void deque_destroy(Deque *f)
{
    free(f->data);
    free(f);
}

