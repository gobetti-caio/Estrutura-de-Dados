#ifndef STACK_H
#define STACK_H

#include "vector.h"

//make a empty stack
Vector* stack_construct();

//destroys the queue
void stack_destruct(Vector* s);

//return the number of elements in the stack
int stack_size(Vector* s);

//inserts a element int the begining of thje stack
void push(Vector* s, void* i);

//take off the element in the final of the stack
void* pop(Vector* s);

#endif