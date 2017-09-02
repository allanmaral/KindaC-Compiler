#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Tokens.h"

#define TAMANHO_LEXEMA 32
#define TAMANHO_BUFFER 4096
#define MODO_ARQUIVO 77
#define MODO_ENTRADA 7

 /** \brief Autômato
  */
typedef struct _Automato{
    char   *lexema;           /**< Vetor de caracteres adicionados ao lexema  */
    int     estado;           /**< Estado atual do autômato  */
    int     posicaoLexema;    /**< Posição a adicionar um caractere no lexema  */
    int     tamLexema;        /**< Tamanho total do vetor de caracteres lexema  */
    int     linha;            /**< Linha atual do arquivo  */
    int     coluna;           /**< Coluna atual do arquivo  */
    char    caractere;        /**< Último caractere lindo pelo autômato*/
    int modo;                 /**< Modo de entrada de caracteres */
} Automato;

 /** \brief Construtor do analisador léxico
  *
  * \param caminho char* Caminho do arquivo a ser lido
  * \param modo int Modo de como o autômato pegara caracteres do leitor ou do terminal
  */
void iniciaAnalisadorLexico(char *caminho);

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

 /** \brief Destrutor do Analisador Léxico
  *
  */
void destruirAnalizadorLexico();


#endif // ANALISADORLEXICO_H
