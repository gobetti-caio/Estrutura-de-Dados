
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "forward_list.h"

void print_data(data_type data)
{

    printf("%s\n",(char*)data);
}

int main()
{
    int num_instructions;
    scanf("%d", &num_instructions);

    ForwardList *list = forward_list_construct();

    for (int i = 0; i < num_instructions; i++)
    {
        char command[20];

        scanf("\n%s", command);

        if (strcmp(command, "PUSH_FRONT") == 0)
        {
            char *value = calloc(20, sizeof(char));
            scanf("%s\n", value);

            forward_list_push_front(list, value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            int idx;
            scanf("%d", &idx);

            forward_list_pop_index(list,idx); 
        }
    }

    forward_list_print(list, print_data);

    forward_list_destroy(list);

    return 0;
}