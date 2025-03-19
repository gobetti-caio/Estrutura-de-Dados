#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash_fn(HashTable *h, void *key)
{
    char *str = (char *)key;
    long hash_val = 0;
    int base = 127;

    for (size_t i = 0; i < strlen(str); i++)
        hash_val = (base * hash_val + str[i]) % hash_table_size(h);

    return hash_val;
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int cmp_items(const void *a, const void *b)
{
    const HashTableItem *item_a = *(const HashTableItem **)a;
    const HashTableItem *item_b = *(const HashTableItem **)b;
    return strcmp(item_a->key, item_b->key);
}

int main() {
    int n;
    scanf("%d", &n);

    int table_size = 1000; 
    HashTable *hash_table = hash_table_construct(table_size, hash_fn, cmp_str);

    char temp[100];
    for (int i = 0; i < n; i++) {
        scanf("%s", temp);

        void *val = hash_table_get(hash_table, temp);
        if (val)
        {
            int *count = (int *)val;
            (*count)++;
        }
        else
        {
            char *name = strdup(temp);
            int *count = malloc(sizeof(int));
            *count = 1;
            hash_table_set(hash_table, name, count);
        }
    }

    Vector *v = hash_to_vector(hash_table);
    vector_sort(v, cmp_items);

    int size = vector_size(v);
    for(int i = 0; i < size; i++) {
        void *pair = vector_pop_front(v);
        printf("%s %d\n", (char *)((HashTableItem *)pair)->key, *(int *)((HashTableItem *)pair)->val);
    }

    vector_destroy(v);
    hash_table_destroy(hash_table);

    return 0;
}