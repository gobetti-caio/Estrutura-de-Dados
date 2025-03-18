#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define TAMMAX 10
#define GROWNRATE 2

Vector *vector_construct() {
  Vector *new = (Vector *)calloc(1, sizeof(Vector));

  new->data = (data_type *)calloc(TAMMAX, sizeof(data_type));
  new->size = 0;
  new->allocated = TAMMAX;

  return new;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size >= (v->allocated)) {
        v->data = (data_type *)realloc(v->data, GROWNRATE * v->allocated * sizeof(data_type));
        v->allocated = 2 * v->allocated;
    }
  v->data[v->size] = val;
  v->size++;
}


data_type vector_get(Vector *v, int i)
{
    if (i < 0 || i >= v->size)
    {
        printf("Indice Invalido");
        return 0;
    }

    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val)
{
    if (i < 0 || i >= v->size)
    {
        printf("Indice Invalido");
        return ;
    }

    v->data[i] = val;
}

int vector_size(Vector *v)
{
    return v->size;
}


int vector_find(Vector *v, data_type val)
{
    for (int i = 0; i < v->size; i++)
    {
        if (v->data[i] == val)
        {
            return i;
        }
    }
    return -1;
}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

data_type vector_max(Vector *v)
{
    data_type maior = v->data[0];
    for (int i = 0; i < v->size; i++)
    {
        if(v->data[i] > maior)
            maior = v->data[i];
    }
    return maior;
}

data_type vector_min(Vector *v)
{
    data_type menor = v->data[0];
    for (int i = 0; i < v->size; i++)
    {
        if(v->data[i] < menor)
            menor = v->data[i];
    }
    return menor;
}

int vector_argmax(Vector *v)
{
    return vector_find(v, vector_max(v));
}

int vector_argmin(Vector *v)
{
    return vector_find(v, vector_min(v));
}

data_type vector_remove(Vector *v, int i)
{
    if (i < 0 || i >= v->size) {
        printf("Indice invalido\n");
        return 0; // ou um valor sentinel, dependendo do uso
    }
    data_type removed = v->data[i];
    while (i < v->size - 1) {
        v->data[i] = v->data[i + 1];
        i++;
    }
    v->size--;
    return removed;
}


data_type vector_pop_front(Vector *v)
{
    return vector_remove(v,0);

}

data_type vector_pop_back(Vector *v)
{
    return vector_remove(v,(v->size-1));

}

void vector_insert(Vector *v, int i, data_type val)
{
    if (v->size >= (v->allocated)) {
        v->data = (data_type *)realloc(v->data, GROWNRATE * v->allocated);
        v->allocated = 2 * v->allocated;
    }
    for (int c = v->size; c > i; c--)
    {
        v->data[c] = v->data[c-1];
    }
    v->data[i] = val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j)
{
    if ( i < 0 ||  j < 0 || i > v->size || j > v->size)
    {
        printf ("indices ivalidos");
    }
    data_type aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vector_sort(Vector *v, int (*cmp)(const void *, const void *)) {
    if (v && cmp) {
        qsort(v->data, v->size, sizeof(data_type), cmp);
    }
}

int vector_binary_search(Vector *v, data_type val)
{
    int start = 0;
    int  end = (v->size-1);

    if (v->size == 0)
        return -1;
    

    while (start <= end)
    {
        int mid = (start+end)/2;

        if (val == v->data[mid])
        {
            return mid;
        }
        else if(val < v->data[mid])
        {
            end = mid -1;
        }
        else
        {
            start = mid + 1;
        }
    }

    return -1;
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v)
{
    int start = 0;
    int end = v->size-1;

    while (start<= end)
    {
        vector_swap(v,start,end);
        start++;
        end--;
    }
}