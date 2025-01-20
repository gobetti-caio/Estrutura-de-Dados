#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

int main()
{
    int n;
    char string[32];
    char oper[16];

    Vector* stack = stack_construct();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", oper);
        if (!strcmp(oper,"PUSH"))
        {
            scanf("%s", string);
            char* inserted = strdup(string);
            push(stack,inserted);
        }
        else
        {
            printf("%s\n", (char*)pop(stack));
        }
    }
    stack_destruct(stack);
    return 0;
}