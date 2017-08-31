#include <stdio.h>
#include <string.h>
//#include <sys/resource.h>

#include "AnalisadorLexico.h"
#include "TabelaSimbolos.h"
#include "Tokens.h"
#include "GerenciadorErro.h"

#define TAMANHO_NOME_ARQUIVO 1024

/** \brief Destroi objetos alocados durante a execução do programa
 *  Funcao chamada na saida do programa
 */
void finalizaPrograma();

/** \brief Adiciona a extenção .cpm ao nome do arquivo, se necessario
 *
 * \param nomeArquivo char* string de caracteres a ser modificada
 */
void adicionaExtencao(char* nomeArquivo);


/** \brief Ponto de entrada do programa
 */
int main(int argc, char** args){
    char nomeArquivo[TAMANHO_NOME_ARQUIVO];
    //struct rlimit lim;
    //lim.rlim_cur = 1024000000;
    //lim.rlim_cur = 32000000;
    //lim.rlim_max = -1;
    //setrlimit(RLIMIT_STACK, &lim);


    nomeArquivo[0] = '\0';
    if(argc == 1){                  // Le o nome do arquivo do stdin
        fscanf(stdin, "%s", nomeArquivo);
    } else if ( argc == 2 ) {       // Le o nome do arquivo da lista de argumento
        strcpy(nomeArquivo, args[1]);
    } else {
        fprintf(stderr, "Argumento invalido!\nExempo de uso:\n\tKindaC teste.cpm\n\tKindaC teste\n\tKindaC\n");
        exit(1);
    }

    adicionaExtencao(nomeArquivo);
    fprintf(stdout, "Nome: %s\n", nomeArquivo);

    // Funcção chamada na saida do programa, garante que memoria será desalocada
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
    //getchar();
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

void adicionaExtencao(char* nomeArquivo)
{
    int i, possuiExtensao;
    i = 0, possuiExtensao = 0;
    // Adiciona a extenção .cpm se não houver
    while(nomeArquivo[i]){
        if(i+3 < TAMANHO_NOME_ARQUIVO) { //Evita erro de acesso a memoria não alocada
            if(strcmp(&nomeArquivo[i], ".cpm") == 0) { possuiExtensao = 1; break; }
        } else {
            fprintf(stderr, "Nome do arquivo excede o tamanho suportado!\n");
            exit(1);
        }
        i++;
    }
    if(!possuiExtensao){ strcpy(&nomeArquivo[i], ".cpm"); nomeArquivo[i+4] = '\0'; }
}

