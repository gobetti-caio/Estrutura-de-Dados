#ifndef QUEUE_H
#define QUEUE_H

#include "vector.h"

//make a empty queue
Vector* queue_construct();

//destroys the queue
void queue_destruct(Vector* q);

//return the number of elements in the queue
int queue_size(Vector* q);

//inserts a element int the begining of thje queue
void queue_insert(Vector* q, void* i);

//take off the element in the final od the queueu
void* queue_remove(Vector* q);

#endif