#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "FowardList.h"


// NODE IMPLEMENTATION //

Node *node_construct(data_type value, Node *next)
{
    Node* new = (Node*)calloc(1,sizeof(Node));

    new->value = value;
    new->next = NULL;

    return new;
}

data_type node_value(Node *node)
{
    return node->value;
}

Node *node_next(Node *node)
{
    return node->next;
}

void node_destroy(Node *n)
{
    free(n);
}


//FOWARD LIST IMPLEMENTATION


ForwardList *forward_list_construct()
{
    ForwardList* new = (ForwardList*)calloc(1,sizeof(ForwardList));

    new->head = NULL;
    new->size = 0;

    return new;
}


void forward_list_destroy(ForwardList *l)
{
    Node* aux = l->head;
    while (l->head)
    {
        l->head = l->head->next;
        node_destroy(aux);
        aux = l->head;
    }
    free(l);
}


int forward_list_size(ForwardList *l)
{
    return l->size;
}


void forward_list_push_front(ForwardList *l, data_type data)
{
    l->head = node_construct(data, l->head);
    l->size++;
}


void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node* aux = l->head;
    while (aux)
    {
        print_fn(aux->value);
        aux = aux->next;
    }
}


data_type forward_list_get(ForwardList *l, int i)
{
    if (i> l->size)
    {
        return 0;
    }

    Node* aux = l->head;
    for (int c = 0; c < i; c++)
    {
        aux = aux->next;
    }
    return aux->value;
}


data_type forward_list_pop_front(ForwardList *l)
{
    data_type aux = l->head->value;
    l->head = l->head->next;

    return aux;
}


void forward_list_clear(ForwardList *l)
{
    Node* aux = l->head;
    while (l->head)
    {
        l->head = l->head->next;
        node_destroy(aux);
        aux = l->head;
    }
    l->head = NULL;
    l->size = 0;
}


void forward_list_remove(ForwardList *l, data_type val)
{
    Node* aux = l->head;
    Node* aux2;
    while (aux)
    {   
        aux2 = aux;
        aux = aux->next;
        if (aux->value == val)
        {
            aux2 = aux->next;
            node_destroy(aux);
            aux = aux2->next;
        }
    }
}


void forward_list_cat(ForwardList *l, ForwardList *m)
{
    Node* aux = l->head;
    while (aux->next)
    {   
        aux = aux->next;
    }
    aux->next = m->head;
    free (m);
}


void forward_list_sort(ForwardList *l)
{
    
}


/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
ForwardList *forward_list_reverse(ForwardList *l);

/**
 * @brief Removes all duplicate values from the linked list.
 * Removes all duplicate values from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The linked list must be sorted.
 */
void forward_list_unique(ForwardList *l);
