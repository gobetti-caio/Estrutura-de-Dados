#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

int main()
{
    int N;
    Deque *f = deque_construct();

    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int n;
        char oper[50]; 
        scanf("%s", oper);
        if (!strcmp(oper,"PUSH_BACK"))
        {
            scanf("%d", &n);
            deque_push_back(f,n);
        }
        else if(!strcmp(oper,"PUSH_FRONT"))
        {
            scanf("%d", &n);
            deque_push_front(f,n);
        }
        else if(!strcmp(oper,"POP_BACK"))
            printf("%d\n",deque_pop_back(f));
        else if(!strcmp(oper,"POP_FRONT"))
            printf("%d\n", deque_pop_front(f));
    }

    deque_destroy(f);
    return 0;
}