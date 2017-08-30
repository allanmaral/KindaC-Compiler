#include <stdio.h>
#include "AnalisadorLexico.h"
int main()
{
   // printf() displays the string inside quotation
   printf("Hello, World!");
   iniciaAnalisadorLexico("./Text.txt");
   int c = 0;
   while(c != EOF){
        printf("%d\n",proximoToken());
   }
   return 0;
}
