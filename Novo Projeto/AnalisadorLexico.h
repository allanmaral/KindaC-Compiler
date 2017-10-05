#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/** Lista de Tokens
 *
 */
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
#define LITERAL         55
#define NEGACAO         56
#define VIRGULA         57
#define NUM_REAL        58
#define TOKEN_EOF       59
#define TRES_PONTOS     60

#ifndef EOF
    #define EOF         -1
#endif // EOF

 /** \brief Construtor do analisador léxico
  *
  * \param caminho char* Caminho do arquivo a ser lido
  * \param modo int Modo de como o autômato pegara caracteres do leitor ou do terminal
  */
void iniciaAnalisadorLexico(FILE* arquivo);

 /** \brief Função que obtém um caractere do leitor e incrementa uma coluna no autômato
  *
  *  \return caractere obtido
  */

int proximoToken();

 /** \brief Função que obtem um lexema do analisador léxico
  *
  *  \return lexema obtido
  */
char* pegarLexema();

/** \brief Função que obtem a linha do arquivo lido pelo automato
 *
 *  \return linha atual do arquivo
 */
int pegarLinha();

/** \brief Função que obtem a coluna do arquivo lido pelo automato
 *
 *  \return coluna atual do arquivo
 */
int pegarColuna();

 /** \brief Destrutor do Analisador Léxico
  *
  */
void destruirAnalizadorLexico();

void imprimeTabelaPalavrasReservadas();
#endif // ANALISADORLEXICO_H
