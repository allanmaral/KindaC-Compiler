#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Tokens.h"

#define TAMANHO_LEXEMA 32
#define TAMANHO_BUFFER 4096

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

int proximoToken();

 /** \brief Procedimento que adiciona um caractere ao vetor de caracters (lexema)
  *
  *  \param caractere a ser adicionado
  */
void desalocaParametrosAnalizadorLex();


#endif // ANALISADORLEXICO_H
