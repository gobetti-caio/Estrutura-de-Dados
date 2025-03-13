#include <stdio.h>
#include <math.h>
#include <string.h>


unsigned long long hash_func(int base, const char *str)
{
    unsigned long long int hash = 0;
    int size = strlen(str);
    int exp = size - 1;

    for (int i = 0; i < size; i++)
    {
        hash = hash + (str[i] * pow(base, exp));
        exp--;
    }
    return hash;
}

int main() {
    char str[1024]; 
    int base, n;

    
    scanf("%d %d", &base, &n);
    for (int k = 0; k < n; k++)
    {
        scanf("%s", str);
        printf("%llu\n", hash_func(base, str));
    }

    return 0;
}
