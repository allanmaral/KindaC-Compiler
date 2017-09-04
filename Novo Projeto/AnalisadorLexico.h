#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
