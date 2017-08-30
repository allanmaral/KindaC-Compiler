#include <stdio.h>
#include "AnalisadorLexico.h"
#include "TabelaSimbolos.h"
int main()
{
   // printf() displays the string inside quotation
   inicializaTabelaSimbolos();
   iniciaAnalisadorLexico("./Text.txt");
   int c = 0;
   while(c != EOF){
        c = proximoToken();
   }
   imprimeTabela(TABELA_LITERAL);
   imprimeTabela(TABELA_ID);
   imprimeTabela(TABELA_INTEIRO);
   imprimeTabela(TABELA_REAL);
   imprimeTabela(TABELA_RESERVADA);
   getchar();
   destroiTabelaSimbolos();
   return 0;
}
