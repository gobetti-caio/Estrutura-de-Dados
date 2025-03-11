#include <stdio.h>
#include <math.h>

int main() {
    char str[1024]; 
    unsigned long long int s;
    int n;
    unsigned long long int hash = 0; 
    int i = 0;

    
    scanf("%llu %d", &s, &n);
    getchar(); 
    for (int k = 0; k < n; k++)
    {
    
        while (scanf("%c", &str[i]) == 1 && str[i] != '\n')
        {
            i++;
        }
        str[i] = '\0';
    
        for (int j = 0; j < i; j++)
        {
            hash += (str[j] * pow(s, i - j - 1));
        }
    
        printf("%llu\n", hash);
        hash = 0;
        i = 0;
    }
    

    return 0;
}
