#include <stdio.h>
#include <string.h>


unsigned long long hash_func(int base, const char *str, int table_size)
{
    unsigned long long int hash = 0;
    int size = strlen(str);
    unsigned long long pow = 1; 

    for (int i = size -1 ; i >= 0; i--)
    {
        hash = (hash + str[i] * pow) % table_size;
        pow *= base; 
    }
    return hash;
}

int main() {
    char str[1024]; 
    int base, n, table_size;

    
    scanf("%d %d %d", &base, &n, &table_size);
    for (int k = 0; k < n; k++)
    {
        scanf("%s", str);
        printf("%llu\n", hash_func(base, str,table_size));
    }

    return 0;
}
