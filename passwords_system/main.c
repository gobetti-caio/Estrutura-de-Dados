#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Atendimento
{
    char* nome;
}Atendimento;

int main(){

    Atendimento* fila[10];

    char nome[16], comando[16];
    int n, size = 0;
    int incio = 0;
    int fim = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s",comando);
        if (!strcmp(comando,"ADICIONAR"))
        {
            if (size == 10)
            {
                printf("FILA CHEIA\n");
            }
            else
            {
                scanf("%s %*d",nome);
                fila[fim]->nome = strdup(nome);
                fim = (fim + 1)%10;
                size++;
            }
        }
        else
        {
            if (size == 0)
            {
               printf("FILA VAZIA\n");
            }
            else
            {
                printf("%s\n", fila[incio]->nome);
                free(fila[incio]->nome);
                incio = (incio + 1)%10;
                size--;
            }
        }
    } 
    return 0;
}