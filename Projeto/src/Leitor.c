#include <stdlib.h>
#include <string.h>
#include "Leitor.h"
#include "GerenciadorErro.h"

#define TAMANHO_NOME_ARQUIVO 1024
#define TAMANHO_BUFFER 4096

static char*   buffer = NULL;          /**< Buffer de leitura  */
static int     caractereAtual;  /**< Indice do ultimo caractere lido no buffer de leitura ativo */
static FILE*   file = NULL;            /**< Arquivo aberto */

/** \brief Construtor do leitor de arquivo
  *
  * \param arquivo LeitorArquivo*
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  * \param tamanhoBuffer unsigned int tamanho do buffer de leitura
  * \return int Retorna o resultado a operação:
  * \return 0 - ARQUIVO_INVALIDO
  * \return 1 - ARQUIVO_ABERTO
  *
  */
int inicializarLeitor(const char* caminhoArquivo){
    if(caminhoArquivo) {
        char arquivo[TAMANHO_NOME_ARQUIVO];
        strcpy(arquivo, caminhoArquivo);
        // Se não tiver a extenção .cpm, adicione
        if(strstr(caminhoArquivo, ".cpm") == NULL ) {
            strcat(arquivo, ".cpm");
        }
        file = fopen(arquivo, "r");
    } else {
        file = stdin;
    }

    // Se for um arquivo valido
    if(file){
        // Inicialçiza o leitor
        buffer = (char*)malloc(TAMANHO_BUFFER*sizeof(char));
        caractereAtual = TAMANHO_BUFFER;
        return ARQUIVO_ABERTO;
    } else { // Arquivo invalido
        // Inicializa o leitor com estados de erro
        buffer = NULL;
        caractereAtual = TAMANHO_BUFFER;
        return ARQUIVO_INVALIDO;
    }
}

/** \brief Destrutor do leitor de arquivo
 *
 * \param arquivo LeitorArquivo* arquivo a ser destruido
 *
 */
void destruirLeitor(){
    if(file && file != stdin) { fclose(file); }
    free(buffer);

    file = NULL;
    buffer = NULL;
    caractereAtual = TAMANHO_BUFFER;
}

/** \brief Lê o próximo caracter de um arquivo
 *
 *
 * \return char Caracter lido
 *
 */
char lerProximoCaractere(){
    // Verifica se o arquivo é valido
    if(file){
        // Se tiver passado do tamanho do buffer, volta pro inicio
        if(caractereAtual >= TAMANHO_BUFFER){
            int elementosLidos;
            // Le o arquivo
            elementosLidos = fread(buffer, 1, TAMANHO_BUFFER, file);
            // Se não ler o mesmo numero de elementos, pode ser erro ou fim de arquivo
            if(elementosLidos < TAMANHO_BUFFER){
                buffer[elementosLidos] = (char)0;
            }
            caractereAtual = 0;
        }
        //char resultado = buffer[caractereAtual++];
        // Incrementa a posição do cursor
        //leitor->caractereAtual += 1;
        return buffer[caractereAtual++];
    }
    else { saidaErro(ErroArquivoInvalido, 0, 0); return (char)0;}
}
