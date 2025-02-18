#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

int main()
{
    int n;
    char string[32];
    char oper[16];

    List* queue = queue_construct();

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", oper);
        if (!strcmp(oper,"ENQUEUE"))
        {
            scanf("%s", string);
            char* inserted = strdup(string);
            queue_insert(queue,inserted);
        }
        else
        {
            printf("%s\n", (char*)queue_remove(queue));
        }
    }
    queue_destruct(queue);
    return 0;
}