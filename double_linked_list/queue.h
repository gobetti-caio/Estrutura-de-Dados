#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

//make a empty queue
List* queue_construct();

//destroys the queue
void queue_destruct(List* q);

//return the number of elements in the queue
int queue_size(List* q);

//inserts a element int the begining of thje queue
void queue_insert(List* q, void* i);

//take off the element in the final od the queueu
void* queue_remove(List* q);

#endif