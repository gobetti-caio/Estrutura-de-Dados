#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "forward_list.h"

void node_print(Node *n, void (*print_fn)(data_type))
{
    print_fn(n->value);
}

ForwardList *forward_list_construct()
{
    ForwardList *new = (ForwardList *)calloc(1, sizeof(ForwardList));

    new->head = NULL;
    new->size = 0;

    return new;
}

int forward_list_size(ForwardList *l)
{
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data)
{
    if (l->size == 0)
        l->head = node_construct(data, NULL);
    else
    {
        l->head = node_construct(data, l->head);
    }
    l->size++;
}

void forward_list_push_back(ForwardList *l, data_type data)
{
    if (l->size == 0)
        l->head = node_construct(data, NULL);
    else
    {
        Node *aux = l->head;

        while (aux->next)
        {
            aux = aux->next;
        }
        aux->next = node_construct(data, NULL);
    }
    l->size++;
}

void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *aux = l->head;
    if (aux)
    {
        while (aux)
        {
            node_print(aux, print_fn);
            aux = aux->next;
        }
    }
    else
    {
        printf("\n");
        return;
    }
}

data_type forward_list_get(ForwardList *l, int i)
{
    if (i > l->size)
    {
        return 0;
    }

    Node *aux = l->head;
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

data_type forward_list_pop_index(ForwardList *l, int index)
{
    if (index >= l->size)
    {
        printf("INVALID INDEX\n");
        return 0;
    }

    Node *aux = l->head;
    Node *aux2;
    data_type n;

    if (index == 0)
    {
        l->head = aux->next;
        n = aux->value;
        node_destroy(aux);
    }
    else
    {
        for (int c = 0; c < index - 1; c++)
        {
            aux = aux->next;
        }
        aux2 = aux->next;
        aux->next = aux2->next;
        n = aux2->value;
        node_destroy(aux2);
    }

    l->size--;
    return n;
}

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
/*ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList* reverse = forward_list_construct();


}
*/

void forward_list_clear(ForwardList *l)
{
    Node *aux = l->head;
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
    Node *aux = l->head;
    Node *aux2;
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

/**
 * @brief Removes all duplicate values from the linked list.
 * Removes all duplicate values from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The linked list must be sorted.
 */
// void forward_list_unique(ForwardList *l);

void forward_list_cat(ForwardList *l, ForwardList *m)
{
    Node *aux = l->head;
    while (aux->next)
    {
        aux = aux->next;
    }
    aux->next = m->head;
    free(m);
}

/**
 * @brief Sorts the linked list.
 * Sorts the linked list.
 * @param l
 * Pointer to the linked list.
 */
void forward_list_sort(ForwardList *l)
{
    if (l->size < 1)
    {
        return;
    }
    
    Node *biggest = l->head;
    data_type trader = NULL;
    Node *aux = l->head;

    for (int i = l->size ; i > 0 ; i--)
    {
        for (int c = 0; c < i; c++)
        {
            aux = aux->next;
            if (biggest > aux)
            {
                trader = aux->value;
                aux->value = biggest->value;
                biggest->value = trader;
                biggest = aux;
            }
            else
            {
                biggest = aux;
            }
        }
    }
}

void forward_list_destroy(ForwardList *l)
{
    Node *aux = l->head;
    while (l->head)
    {
        l->head = l->head->next;
        node_destroy(aux);
        aux = l->head;
    }
    free(l);
}

ListIterator *list_iterator_construct(ForwardList *l)
{
    ListIterator *it = (ListIterator *)calloc(1, sizeof(ListIterator));

    it->current = l->head;
    return it;
}

void list_iterator_destroy(ListIterator *it)
{
    free(it);
}

data_type *list_iterator_next(ListIterator *it)
{
    data_type *n = &(it->current->value);
    it->current = it->current->next;
    return n;
}

bool list_iterator_is_over(ListIterator *it)
{
    return (it->current == NULL);
}
