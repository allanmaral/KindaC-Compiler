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

 /** \brief Automato
  */
typedef struct _Automato{
    char   *lexema;           /**< Vetor de caracteres adicionados ao lexema  */
    int     estado;           /**< Estado atual do automato  */
    int     posicaoLexema;    /**< Posicao a adicionar um caractere no lexema  */
    int     tamLexema;        /**< Tamanho total do vetor de caracters lexema  */
    int     linha;            /**< Linha atual do arquivo  */
    int     coluna;           /**< Coluna atual do arquivo  */
    char    caractere;        /**< Ultimo caractere lindo pelo automato*/
    int modo;                 /**< Modo de entrada de caracteres */
} Automato;

 /** \brief Construtor do analisador lexico
  *
  * \param caminho char* Caminho do arquivo a ser lido
  * \param modo int Modo de como o automato pegara caracteres do leitor ou do terminal
  */
void iniciaAnalisadorLexico(char *caminho);

 /** \brief Função que obtem um caractere do leitor e incrementa uma coluna no automato
  *
  *  \return caractere obtido
  */

int proximoToken();

 /** \brief Função que obtem um lexema do analisador lexico
  *
  *  \return lexema obtido
  */

char* pegarLexema();

 /** \brief Procedimento que adiciona um caractere ao vetor de caracters (lexema)
  *
  *  \param caractere a ser adicionado
  */
void destruirAnalizadorLexico();


#endif // ANALISADORLEXICO_H
