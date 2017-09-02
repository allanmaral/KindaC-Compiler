#ifndef LEITOR_H
#define LEITOR_H
#include <stdio.h>

#define ARQUIVO_INVALIDO 0
#define ARQUIVO_ABERTO   1

 /** \brief Construtor do leitor de arquivo
  *
  * \param arquivo LeitorArquivo*
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  * \param tamanhoBuffer int tamanho do buffer de leitura
  * \return int Retorna o resultado a operação:
  * \return 0 - ARQUIVO_INVALIDO
  * \return 1 - ARQUIVO_ABERTO
  *
  */
int inicializarLeitor(const char* caminhoArquivo);

/** \brief Destrutor do leitor de arquivo
 *
 *
 */
void destruirLeitor();

/** \brief Lê o próximo caracter de um arquivo
 *
 * \return char Caracter lido
 *
 */
char lerProximoCaractere();

#endif // LEITOR_H
