#ifndef STACK_H
#define STACK_H

#include "list.h"

//make a empty stack
List* stack_construct();

//destroys the queue
void stack_destruct(List* s);

//return the number of elements in the stack
int stack_size(List* s);

//inserts a element int the begining of thje stack
void push(List* s, void* i);

//take off the element in the final of the stack
void* pop(List* s);

#endif