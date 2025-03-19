#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "forward_list.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};


HashTableItem *hash_table_item_construct(void *key, void *val) {
    HashTableItem *item = calloc(1,sizeof(HashTableItem));
    
    item->key = key;
    item->val = val;
    return item;
}


struct HashTableIterator {
    HashTable *hash_table;
    int bucket_index;
    Node *current_node;
    int current_element;
};


void* get_key(HashTableItem* hi)
{
    return hi->key;
}


void* get_val(HashTableItem* hi)
{
    return hi->val;
}


void set_val(HashTableItem* hi, void* val)
{
    hi->val = val;
}


void hash_pair_destroy(HashTableItem *item)
{
    free(item->key);
    free(item->val);
    free(item);
}


int return_size(HashTable* h)
{
    return h->table_size;
}


HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable* new = calloc(1,sizeof(HashTable));

    new->buckets = calloc(table_size,sizeof(ForwardList*));
    new->table_size = table_size;
    new->hash_fn = hash_fn;
    new->cmp_fn = cmp_fn;
    new->n_elements = 0;

    return new;
}


// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val)
{
    int key_val = h->hash_fn(h,key);

    if (h->buckets[key_val] == NULL)
    {
        h->buckets[key_val] = forward_list_construct();
        forward_list_push_front(h->buckets[key_val], hash_table_item_construct(key,val));
        h->n_elements++;
        return NULL;
    }
    else
    {
        Node* aux = h->buckets[key_val]->head;
        while (aux)
        {
            if (h->cmp_fn(get_key(aux->value),key) == 0)
            {
                void* oldval = get_val(aux->value);
                set_val(aux->value,val);
                return oldval;
            }
            aux = aux->next;
        }
        forward_list_push_front(h->buckets[key_val],hash_table_item_construct(key,val));
        h->n_elements++;
        return NULL;
    }
}


// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key)
{
    int key_val = h->hash_fn(h,key);

    if (h->buckets[key_val] == NULL)
        return NULL;
    else
    {
        Node* aux = h->buckets[key_val]->head;
        while (aux)
        {
            if (h->cmp_fn(get_key(aux->value),key) == 0)
            {
                return get_val(aux->value);
            }
            aux = aux->next; 
        }
        return NULL;
    }
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key)
{
    int key_val = h->hash_fn(h, key);
    if (!h->buckets[key_val])
        return NULL;

    Node *aux = h->buckets[key_val]->head;
    Node *prev = NULL;

    while (aux)
    {
        HashTableItem *pair = aux->value;
        
        if (h->cmp_fn(pair->key, key) == 0)
        {
            void *val = pair->val; 
            
            if (!prev)
                h->buckets[key_val]->head = aux->next;
            else
                prev->next = aux->next;

            free(aux); 
            free(pair); 

            h->n_elements--;
            return val;
        }
        prev = aux;
        aux = aux->next;
    }
    return NULL;
}



// numero de buckets
int hash_table_size(HashTable *h)
{
    return h->table_size;
}


void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;
            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                hash_pair_destroy(pair);
                n = n->next;
            }
            forward_list_destroy(h->buckets[i]);
        }
    }
    free(h->buckets);
    free(h);
}


HashTableIterator *hash_table_iterator(HashTable *h) {
    HashTableIterator *it = (HashTableIterator *)calloc(1, sizeof(HashTableIterator));
    it->hash_table = h;
    it->bucket_index = 0;
    it->current_node = NULL;
    it->current_element = 0;

    while (it->bucket_index < h->table_size && h->buckets[it->bucket_index] == NULL) {
        it->bucket_index++;
    }

    if (it->bucket_index < h->table_size) {
        it->current_node = h->buckets[it->bucket_index]->head;
    }

    return it;
}


int hash_table_iterator_is_over(HashTableIterator *it) {
    return (it->current_element >= it->hash_table->n_elements);
}


HashTableItem *hash_table_iterator_next(HashTableIterator *it) {
    if (hash_table_iterator_is_over(it)) {
        return NULL;
    }

    if (it->current_node == NULL) {
        it->bucket_index++;
        while (it->bucket_index < it->hash_table->table_size && it->hash_table->buckets[it->bucket_index] == NULL) {
            it->bucket_index++;
        }

        if (it->bucket_index < it->hash_table->table_size) {
            it->current_node = it->hash_table->buckets[it->bucket_index]->head;
        } else {
            return NULL;
        }
    }

    HashTableItem *pair = (HashTableItem *)it->current_node->value;

    it->current_node = it->current_node->next;
    it->current_element++;

    return pair;
}


void hash_table_iterator_destroy(HashTableIterator *it) {
    free(it);
}


Vector *hash_to_vector(HashTable *h)
{
    Vector* v = vector_construct();
    HashTableIterator *it = hash_table_iterator(h);

    while (!hash_table_iterator_is_over(it))
    {
        HashTableItem *pair = hash_table_iterator_next(it);
        vector_push_back(v, pair);
    }
    return v;
}