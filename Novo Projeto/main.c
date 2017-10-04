#include <stdio.h>
#include <string.h>

#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"
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
    FILE* arquivo = stdin;
    if ( argc == 2 ) {
        char caminhoArquivo[strlen(args[1])+5];
        strcpy(caminhoArquivo, args[1]);
        // Se não tiver a extenção .cpm, adicione
        if(strstr(caminhoArquivo, ".cpm") == NULL ){
            strcat(caminhoArquivo, ".cpm");
        }
        arquivo = fopen(caminhoArquivo, "r");
        if(!arquivo){
            fprintf(stderr, "Arquivo invalido!");
            exit(1);
        }
    } else if( argc > 2){
               fprintf(stderr, "Argumento invalido!\nExemplo de uso:\n\tKindaC teste.cpm\n\tKindaC teste\n\tKindaC\n");
               exit(1);
           }

    // Função chamada na saída do programa, garante que memória será desalocada
    atexit(finalizaPrograma);
    inicializaGerenciadorErro();
    iniciaAnalisadorLexico(arquivo);
    InicializarAnalizadorSintatico();
    Programa();
    /*int token = 0;
    while(token != TOKEN_EOF){
        token = proximoToken();
        if((token >= DEFINICAO_TIPO && token <= TOKEN_EOF)) {
            if(token == ID || token == NUM_INTEIRO || token == NUM_REAL || token == LITERAL) {
                fprintf(stdout, "%s.%s\n", tokenLiteral[token-1], pegarLexema());
            } else{
                  fprintf(stdout, "%s\n", tokenLiteral[token-1]);
              }
        } else{
            fprintf(stdout, "Valor invalido! Token:%d\n", token);
        }
    }*/
    imprimeListaErros();
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

