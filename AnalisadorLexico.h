#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Leitor.h"

#define DEFINICAO_TIPO   1
#define ESTRUTURA        2
#define CLASSE           3
#define PUBLICO          4
#define PRIVADO          5
#define INTEIRO          6
#define REAL             7
#define BOLEANO          8
#define CARACTERE        9
#define SE              10
#define SENAO           11
#define ENQUANTO        12
#define ESCOLHA         13
#define DESVIA          14
#define IMPRIME         15
#define LE_LINHA        16
#define RETORNA         17
#define LANCA           18
#define TENTA           19
#define PEGA            20
#define CASO            21
#define NOVO            22
#define VERDADEIRO      23
#define FALSO           24
#define ESSE            25
#define ID              26
#define COLCHETE_ESQ    27
#define COLCHETE_DIR    28
#define CHAVE_ESQ       29
#define CHAVE_DIR       30
#define PARENTESE_ESQ   31
#define PARENTESE_DIR   32
#define MAIOR           34
#define MENOR           35
#define MAIOR_IGUAL     36
#define MENOR_IGUAL     37
#define COMPARACAO      38
#define ATRIBUICAO      39
#define ADICAO          40
#define SUBTRACAO       41
#define DIVISAO         42
#define ASTERISCO       43
#define OU              44
#define PONTO           45
#define DOIS_PONTOS     46
#define PONTO_VIRGULA   47
#define PONTEIRO        48
#define E_COMERCIAL     49
#define E               50
#define DIFERENTE       51
#define PORCENTO        52
#define OU_CC           53
#define NUM_INTEIRO     54
#define NUM_REAL        58
#define LITERAL         55
#define NEGACAO         56
#define VIRGULA         57
#define ERRO            99

#ifndef EOF
    #define EOF         -1
#endif // EOF

 /** \brief Automato
  */
typedef struct _Automato{
    char   *lexema;           /**< Vetor de caracteres adicionados ao lexema  */
    int     estado;           /**< Estado atual do automato  */
    int     posicaoLexema;    /**< Posicao a adicionar um caractere no lexema  */
    int     tamLexema;        /**< Tamanho total do vetor de caracters lexema  */
    int     linha;            /**< Linha atual do arquivo  */
    int     coluna;           /**< Coluna atual do arquivo  */
} Automato;

 /** \brief Construtor do analisador lexico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(char *caminho);

 /** \brief Função que obtem um caractere do leitor e incrementa uma coluna no automato
  *
  *  \return caractere obtido
  */
char pegarProximoCaractere();

 /** \brief Funcao que define as transicoes do automato
  *
  */
int proximoToken();

 /** \brief Procedimento que adiciona um caractere ao vetor de caracters (lexema)
  *
  *  \param caractere a ser adicionado
  */
void incrementaLexema(char caractere);

/** \brief Destrutor do Analizador Lexico
  *
  */
void desalocaParametrosAnalizadorLex();


#endif // ANALISADORLEXICO_H
