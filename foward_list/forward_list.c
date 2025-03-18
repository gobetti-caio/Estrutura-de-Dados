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
    printf("[");
    if (aux)
    {
        while (aux)
        {
            node_print(aux, print_fn);
            aux = aux->next;
            if (aux)
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
    Node *aux = l->head;
    data_type val = l->head->value;
    l->head = l->head->next;
    node_destroy(aux);
    l->size--;

    return val;
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


ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *reverse = forward_list_construct();
    while (l->size != 0)
    {
        forward_list_push_front(reverse, forward_list_pop_front(l));
    }
    return reverse;
}

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
    Node *aux2 = NULL;

    while (aux != NULL)
    {
        if (aux->value == val)
        {
            if (aux2 == NULL)
            {
                l->head = aux->next;
                node_destroy(aux);
                aux = l->head;
            }
            else
            {
                aux2->next = aux->next;
                node_destroy(aux);
                aux = aux2->next;
            }
            l->size--;
        }
        else
        {
            aux2 = aux;
            aux = aux->next;
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
    while (m->size != 0)
    {
        forward_list_push_front(l, forward_list_pop_front(m));
    }
    free(m);
}


void forward_list_sort(ForwardList *l)
{
    if (l->size < 2)
    {
        return;
    }

    Node *current;
    Node *nextNode;
    data_type trader;
    bool swap = true;

    while (swap)
    {
        swap = false;
        current = l->head;

        while (current->next != NULL)
        {
            nextNode = current->next;
            if (current->value > nextNode->value)
            {
                trader = current->value;
                current->value = nextNode->value;
                nextNode->value = trader;
                swap = true;
            }
            current = current->next;
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
