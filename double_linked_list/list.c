#include <stdio.h>
#include <stdlib.h>

#include "list.h"


List *list_construct()
{
    List* new = (List*)calloc(1,sizeof(List));

    new->head = NULL;
    new->last = NULL;
    new->size = 0;

    return new;
}


int list_size(List *l)
{
    return l->size;
}


void list_push_front(List *l, data_type data)
{
    if (l->size ==0)
        l->head = l->last = node_construct(data,NULL,NULL);
    else
    {
        l->head = node_construct(data,NULL,l->head);
        l->head->next->prev = l->head;
    }
    l->size++;
}


void list_push_back(List *l, data_type data)
{
    if (l->size ==0)
        l->head = l->last = node_construct(data,NULL,NULL);
    else
    {
        l->last = node_construct(data,l->last,NULL);
        l->last->prev->next = l->last;
    }
    l->size++;
}


void list_print(List *l, void (*print_fn)(data_type))
{
    Node* aux = l->head;
    printf("[");
    if(aux)
    {
        while (aux)
        {
            node_print(aux,print_fn);
            aux = aux->next; 
            if(aux)
            printf(", ");
        } 
    }
    else
    {
        printf("]\n");
        return;
    }
    printf("]\n");
}


void list_print_reverse(List *l, void (*print_fn)(data_type))
{
    Node* aux = l->last;
    printf("[");
    if(aux)
    {
        while (aux)
        {
            node_print(aux,print_fn);
            aux = aux->prev; 
            if(aux)
            printf(", ");
        } 
    }
    else
    {
        printf("]\n");
        return;
    }
    printf("]\n");
}


data_type list_get(List *l, int i)
{
    if (i > l->size)
    {
        printf("Index is not valid");
        exit(EXIT_FAILURE);
    }
    
    Node* aux = l->head;
    for (int c = 0; c < i; c++)
    {
        aux = aux->next;
    }
    return aux->value;
}


data_type list_pop_front(List *l)
{
    data_type aux = l->head->value;
    Node* auxN = l->head;

    l->head = l->head->next;
    if (l->last->next)   
        l->head->prev = NULL;
    l->size--;
    node_destroy(auxN);
    return aux;
}


data_type list_pop_back(List *l)
{
    if (l->size == 0)
        exit(EXIT_FAILURE);

    data_type aux = l->last->value;
    Node* auxN = l->last;

    l->last = l->last->prev;
    
    if (l->last)
        l->last->next = NULL;
    else
    {
        l->head = NULL;
    }
    l->size--;
    node_destroy(auxN);
    
    return aux;   
}

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the double linked list.
 * @return List*
 * Pointer to the newly allocated double linked list.
 * 
 *  Destruir a list antiga ou n?
 */

 /*
List *list_reverse(List *l) // sem destruir
{
    List* reverse = list_construct();

    for (int i = 0; i < l->size; i++)
    {
        list_push_front( reverse, list_get(l,i));
    }
}
*/

List *list_reverse(List *l) // destruindo
{
    List* reverse = list_construct();

    for (int i = 0; i < l->size; i++)
    {
        list_push_front( reverse, list_pop_front(l));
    }

    return reverse;
}


void list_clear(List *l)
{
    Node* aux;
    for (int i = 0; i < l->size; i++)
    {
        aux = l->head;
        l->head = l->head->next;
        node_destroy(aux);
        aux = l->head;
    }
    l->head = l->last = NULL;
}

/*
void list_remove(List *l, data_type val)
{
    Node* aux = l->head;
    for (int i = 0; i < l->size; i++)
    {
        if (aux->value == val)
        {
            if (!aux->next)
            {
                aux->next->prev = aux->prev;

                l->size--
            }
            if (aux->prev)
            {
                aux->prev->next = aux->next;
                l->size--
            }
        }
    }

}
*/


void list_cat(List *l, List *m)
{
    l->last->next = m->head;
    m->head->prev = l->last;
    l->size += m->size;
    free(m);
}


void list_destroy(List *l)
{
    if(!l)
        return;
    Node* aux = l->head;
    while (aux)
    {   
        l->head = l->head->next;
        node_destroy(aux);
        aux = l->head;
    }
    free(l);
}


ListIterator *list_front_iterator(List *l)
{
    ListIterator* it = (ListIterator *)calloc(1, sizeof(ListIterator));

    it->current = l->head;
    return it;
}


ListIterator *list_back_iterator(List *l)
{
    ListIterator* it = (ListIterator *)calloc(1, sizeof(ListIterator));

    it->current = l->last;
    return it;
}


/**
Por que usar ponteiro?
*/
data_type *list_iterator_next(ListIterator *it)
{
    data_type* n = &(it->current->value); 
    it->current = it->current->next;
    return n;
}


data_type *list_iterator_previous(ListIterator *it)
{
    data_type* n = &(it->current->value); 
    it->current = it->current->prev;
    return n;   
}


bool list_iterator_is_over(ListIterator *it)
{
    return (it->current == NULL);
}


void list_iterator_destroy(ListIterator *it)
{
    free(it);
}



