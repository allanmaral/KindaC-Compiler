#include <stdio.h>
#include <string.h>
//#include <sys/resource.h>

#include "AnalisadorLexico.h"
#include "TabelaSimbolos.h"
#include "Tokens.h"
#include "GerenciadorErro.h"

/** \brief Destroi objetos alocados durante a execução do programa
 *  Funcao chamada na saida do programa
 */
void finalizaPrograma();


/** \brief Ponto de entrada do programa
 */
int main(int argc, char** args){
    char* nomeArquivo = NULL;
    if(argc == 1){                  // altera o modo para obter caracters do stdin
       nomeArquivo = NULL;
    } else if ( argc == 2 ) {       // Le o nome do arquivo da lista de argumento
        nomeArquivo = args[1];
    } else {
        fprintf(stderr, "Argumento invalido!\nExemplo de uso:\n\tKindaC teste.cpm\n\tKindaC teste\n\tKindaC\n");
        exit(1);
    }

    // Função chamada na saida do programa, garante que memoria será desalocada
    atexit(finalizaPrograma);
    inicializaGerenciadorErro();
    inicializaTabelaSimbolos();
    iniciaAnalisadorLexico(nomeArquivo);
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
    return 0;
}

/** \brief Destroi objetos alocados durante a execução do programa
 */
void finalizaPrograma()
{
    imprimeListaErros();
    destruirAnalizadorLexico();
    destruirTabelaSimbolos();
    destruirGerenciadorErro();
}

