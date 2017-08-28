#include <stdio.h>


#define ARQUIVO_INVALIDO 0
#define ARQUIVO_ABERTO   1

 /** \brief Leitor de arquivo
  */
 typedef struct _LeitorArquivo
{
    char**  buffer;          /**< Buffer de leitura  */
    int     tamanhoBuffer;   /**< Tamanho de cada buffer de leitura */
    int     bufferAtual;     /**< Indice do buffer de leitura ativo */
    int     caractereAtual;  /**< Indice do ultimo caractere lido no buffer de leitura ativo */
    FILE*   file;            /**< Arquivo aberto */
    int     preencherProximo;
} LeitorArquivo;


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
int InicializarLeitor(LeitorArquivo* arquivo, const char* caminhoArquivo, int tamanhoBuffer);

/** \brief Destrutor do leitor de arquivo
 *
 * \param arquivo LeitorArquivo* arquivo a ser destruido
 *
 */
void DestruirLeitor(LeitorArquivo* arquivo);

/** \brief Lê o próximo caracter de um arquivo
 *
 * \param arquivo LeitorArquivo* Arquivo a ser lido
 * \return char Caracter lido
 *
 */
char ProximoCaractere(LeitorArquivo* arquivo);
