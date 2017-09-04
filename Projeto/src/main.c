#include <stdio.h>
#include <string.h>

#include "AnalisadorLexico.h"
#include "TabelaSimbolos.h"
#include "GerenciadorErro.h"

/** Lista de Literais dos Tokens
 */
char tokenLiteral[59][16] = {
        "DEFINICAO_TIPO", "ESTRUTURA", "CLASSE", "PUBLICO", "PRIVADO",
        "INTEIRO", "REAL", "BOLEANO", "CARACTERE", "SE", "SENAO",
        "ENQUANTO", "ESCOLHA", "DESVIA", "IMPRIME", "LE_LINHA", "RETORNA",
        "LANCA", "TENTA", "PEGA", "CASO", "NOVO", "VERDADEIRO", "FALSO",
        "ESSE", "ID", "COLCHETE_ESQ", "COLCHETE_DIR", "CHAVE_ESQ",
        "CHAVE_DIR", "PARENTESE_ESQ", "PARENTESE_DIR", "", "MAIOR", "MENOR",
        "MAIOR_IGUAL", "MENOR_IGUAL", "COMPARACAO", "ATRIBUICAO", "ADICAO",
        "SUBTRACAO", "DIVISAO", "ASTERISCO", "OU", "PONTO", "DOIS_PONTOS",
        "PONTO_VIRGULA", "PONTEIRO", "E_COMERCIAL", "E", "DIFERENTE", "PORCENTO",
        "OU_CC", "NUM_INTEIRO", "LITERAL", "NEGACAO", "VIRGULA", "NUM_REAL", "EOF"
};

/** \brief Destrói objetos alocados durante a execução do programa
 *  Função chamada na saida do programa
 */
void finalizaPrograma();


/** \brief Ponto de entrada do programa
 */
int main(int argc, char** args){
    char* nomeArquivo = NULL;
    if(argc == 1){                  // altera o modo para obter caracteres do stdin
       nomeArquivo = NULL;
    } else if ( argc == 2 ) {       // Lê o nome do arquivo da lista de argumento
        nomeArquivo = args[1];
    } else {
        fprintf(stderr, "Argumento invalido!\nExemplo de uso:\n\tKindaC teste.cpm\n\tKindaC teste\n\tKindaC\n");
        exit(1);
    }

    // Função chamada na saída do programa, garante que memória será desalocada
    atexit(finalizaPrograma);
    inicializaGerenciadorErro();
    iniciaAnalisadorLexico(nomeArquivo);
    int token = 0;
    while(token != EOF){
        token = proximoToken();
        if((token > 0 && token < 58) || token == EOF) {
            if(token == ID || token == NUM_INTEIRO || token == NUM_REAL || token == LITERAL) {
                fprintf(stdout, "%s.%s\n", tokenLiteral[token-1], pegarLexema());
            } else if(token == EOF) {
                       fprintf(stdout, "%s\n", tokenLiteral[58]);
                   } else {
                         fprintf(stdout, "%s\n", tokenLiteral[token-1]);
                     }
        } else {
            fprintf(stdout, "Valor invalido! Token:%d\n", token);
        }
    }
    imprimeTabelas();
    return 0;
}

/** \brief Destrói objetos alocados durante a execução do programa
 */
void finalizaPrograma()
{
    imprimeListaErros();
    destruirAnalizadorLexico();
    destruirGerenciadorErro();
}

