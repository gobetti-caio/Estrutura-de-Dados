#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"


typedef struct Node
{
    KeyValPair *pair;
    struct Node* left;
    struct Node* right;
}Node;

struct BinaryTree
{
    Node* root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

KeyValPair *key_val_pair_construct(void *key, void *val)
{
    KeyValPair* new_pair = calloc(1,sizeof(KeyValPair));

    new_pair->key = key;
    new_pair->value = val;

    return new_pair;
}



Node* node_construct(KeyValPair* pair)
{
    Node* new_node = calloc(1,sizeof(Node));
    
    new_node->pair = pair;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)
{
    BinaryTree* new_tree = calloc(1,sizeof(BinaryTree));
    
    new_tree->cmp_fn = cmp_fn;
    new_tree->key_destroy_fn = key_destroy_fn;
    new_tree->val_destroy_fn = val_destroy_fn;
    new_tree->root = NULL;
    
    return new_tree;
}


void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
    if (!bt->root)
    {
        bt->root = node_construct(key_val_pair_construct(key, value));
        return;
    }

    Node *aux = bt->root;
    Node *parent = NULL;
    int cmp = 0;

    while (aux) {
        cmp = bt->cmp_fn(aux->pair->key, key);
        parent = aux;  

        if (cmp > 0)
            aux = aux->left;
        else if (cmp < 0)
            aux = aux->right;
        else
        {
            bt->val_destroy_fn(aux->pair->value); 
            aux->pair->value = value;  
            return;
        }
    }

    if (cmp > 0)
        parent->left = node_construct(key_val_pair_construct(key, value));
    else
        parent->right = node_construct(key_val_pair_construct(key, value));
}


KeyValPair *binary_tree_pop_min(BinaryTree *bt)
{
    if (!bt->root) return NULL;
    
    Node* aux = bt->root;
    Node* parent = NULL;
    
    if (!aux->left)
    {
        bt->root = aux->right;
        KeyValPair *min = aux->pair;
        free(aux);
        return min;
    }

    while(aux->left)
    {
        parent = aux;
        aux = aux->left;
    }

    parent->left = aux->right;
    KeyValPair *min = aux->pair;
    free(aux);
    return min;    
}


KeyValPair *binary_tree_pop_max(BinaryTree *bt)
{
    if (!bt->root) return NULL;

    Node* aux = bt->root;
    Node* parent = NULL;

    if (!aux->right)       
    {   
        bt->root = aux->left;
        KeyValPair *max = aux->pair;
        free(aux);
        return max;
    }
    
    while (aux->right) 
    {
        parent = aux;
        aux = aux->right;
    }
    parent->right = aux->left;
    KeyValPair *max = aux->pair;
    free(aux);
    return max; 
}


void *binary_tree_get(BinaryTree *bt, void *key)
{
    Node* aux = bt->root;
    while (aux->left)
    {
        if(bt->cmp_fn(aux->pair->key, key) > 0)
            aux = aux->left;
        else if (bt->cmp_fn(aux->pair->key, key) < 0)
            aux = aux->right;
        else 
            return aux->pair->value;
    }
    return NULL;
}


void key_val_pair_destroy(KeyValPair *kvp)
{
    free(kvp);
}


void node_destroy_recursive(Node* node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)
{
    if (!node) return;
    
    node_destroy_recursive(node->left, key_destroy_fn, val_destroy_fn);
    node_destroy_recursive(node->right, key_destroy_fn, val_destroy_fn);

    key_val_pair_destroy(node->pair); 
    free(node);
}



void binary_tree_destroy(BinaryTree *bt)
{
    if(bt->root)
    node_destroy_recursive(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
    return;
}


Vector *binary_tree_levelorder_traversal(BinaryTree *bt)
{
    
}