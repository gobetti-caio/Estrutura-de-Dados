#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

struct product
{
    char* name;
    float price;
    float discount;
    int qtd;
    int sales;
};

Product *product_constructor(const char *name, float price, int qtd)
{
    Product* new = (Product*)calloc(1,sizeof(Product));


    if ( price < 0 || qtd < 0)
    {
       printf("\n VALOR INVALIDO \n");

       return NULL;
    }
    
    new->name = strdup(name);
    new->price = price;
    new->qtd = qtd;
    new->discount = 0;
    new->sales = 0;

    return new;
}

const char *product_get_name(Product *product)
{
    return product->name;
}

float product_get_price(Product *product)
{
    return product->price;
}

float product_get_discount(Product *product)
{
    return product->discount;
}

int product_get_qtd(Product *product)
{
    return product->qtd;
}

int product_get_sales(Product *product)
{
    return product->sales;
}

void product_set_name(Product *product, const char *name)
{
    free(product->name);
    product->name = strdup(name);
}

void product_set_price(Product *product, float price)
{
    if (price < 0)
    {
        printf("\n VALOR INVALIDO\n");
        return;
    }
    
    product->price = price;
}
void product_set_discount(Product *product, float discount)
{
    if ( discount < 0 || discount > 1)
    {
        printf("VALOR INVALIDO\n");
        return;
    }
    
    product->discount = discount;
}

void product_sell(Product *product, int quantity)
{
    if (quantity > product->qtd)
    {
        printf("ESTOQUE INSUFICIENTE\n");
        return;
    }
    
    product->qtd = product->qtd - quantity;
    product->sales = product->sales + quantity;
}
void product_buy(Product *product, int quantity)
{
    if (quantity < 0)
    {
        printf("VALOR INVALIDO");
        return;
    }

    product->qtd = product->qtd + quantity;
}

float product_get_price_with_discount(Product *product)
{
    float newprice;

    newprice = product->price - (product->price * product->discount);

    return newprice;
}
void product_print(Product *product)
{
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n",product->name, product->price, product->discount, product_get_price_with_discount(product), product->qtd, product->sales);
}

int product_compare_name(const void* prod1, const void* prod2)
{
    Product* product1 = *((Product**)prod1);
    Product* product2 = *((Product**)prod2);

    return strcmp(product1->name, product2->name);
}

int product_compare_price(const void* prod1, const void* prod2)
{
    Product* product1 = *((Product**)prod1);
    Product* product2 = *((Product**)prod2);

    if(product1->price < product2->price) return -1;
    if(product1->price > product2->price) return 1;
    return 0;
}

int product_compare_sales(const void* prod1, const void* prod2)
{
    Product* product1 = *((Product**)prod1);
    Product* product2 = *((Product**)prod2);

    return (product1->sales - product2->sales);
}

void product_destructor(Product *product)
{
    free(product->name);
    free(product);
}

void sort_by_name(Product** lista, int size)
{
    qsort(lista,size, sizeof(Product*),product_compare_name);
}

void sort_by_price(Product** lista, int size)
{
    qsort(lista,size, sizeof(Product*),product_compare_price);
}

void sort_by_sales(Product** lista, int size)
{
    qsort(lista,size, sizeof(Product*),product_compare_sales);
}