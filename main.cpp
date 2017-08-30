#include <stdio.h>
#include "AnalisadorLexico.h"
int main()
{
   // printf() displays the string inside quotation
   printf("Hello, World!");
   iniciaAnalisadorLexico("./Text.txt");
   int c = 0;
   while(c != EOF){
        c = proximoToken();
        printf("%d\n",c);
   }
   return 0;
}
