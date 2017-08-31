#include <stdio.h>
//#include <sys/resource.h>

#include "AnalisadorLexico.h"
#include "TabelaSimbolos.h"
#include "Tokens.h"
#include "GerenciadorErro.h"

void finalizaPrograma()
{
    imprimeListaErros();
    destroiAnalizadorLexico();
    destroiTabelaSimbolos();
    destroiGerenciadorErro();
}

int main(){
    //struct rlimit lim;
    //lim.rlim_cur = 1024000000;
    //lim.rlim_cur = 32000000;
    //lim.rlim_max = -1;
    //setrlimit(RLIMIT_STACK, &lim);

    // Funcção chamada na saida do programa, garante que memoria será desalocada
    atexit(finalizaPrograma);

    inicializaGerenciadorErro();
    inicializaTabelaSimbolos();
    iniciaAnalisadorLexico((char*)"./Text.txt");
    int token = 0;
    while(token != EOF){
        token = proximoToken();
        ImprimeToken(token);
    }
    imprimeTabela(TABELA_LITERAL);
    imprimeTabela(TABELA_ID);
    imprimeTabela(TABELA_INTEIRO);
    imprimeTabela(TABELA_REAL);
    imprimeTabela(TABELA_RESERVADA);
    getchar();
    return 0;
}


