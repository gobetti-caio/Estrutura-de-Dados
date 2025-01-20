
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

//Creates a empty deque
Deque *deque_construct();

//adds a element in the rear of the deque
void deque_push_back(Deque *f, int item);

//adds a element in the front of the deck
void deque_push_front(Deque *f, int item);

//removes the element in the rear of the deque
int deque_pop_back(Deque *f);

//removes the elemnt in the front of the  deque
int deque_pop_front(Deque *f);

//detroys the deque
void deque_destroy(Deque *f);

#endif