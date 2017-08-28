#include "Leitor.h"
#include <stdlib.h>

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
int InicializarLeitor(LeitorArquivo* arquivo, const char* caminhoArquivo, int tamanhoBuffer) {
    arquivo->file = fopen(caminhoArquivo, "r");
    // Se for um arquivo valido
    if(arquivo->file) {
        // Inicialçiza o leitor
        arquivo->buffer = (char**)malloc(sizeof(char*)*2);
        arquivo->buffer[0] = (char*)malloc(tamanhoBuffer*sizeof(char));
        arquivo->buffer[1] = (char*)malloc(tamanhoBuffer*sizeof(char));
        arquivo->tamanhoBuffer = tamanhoBuffer;
        arquivo->bufferAtual = 0;
        arquivo->caractereAtual = -1;
        arquivo->preencherProximo = 0;
        return ARQUIVO_ABERTO;
    }
    // Arquivo invalido
    else {
        // Inicializa o leitor com estados de erro
        arquivo->buffer = NULL;
        arquivo->tamanhoBuffer = -1;
        arquivo->bufferAtual = -1;
        arquivo->caractereAtual = -1;
        return ARQUIVO_INVALIDO;
    }
}

/** \brief Destrutor do leitor de arquivo
 *
 * \param arquivo LeitorArquivo* arquivo a ser destruido
 *
 */
void DestruirLeitor(LeitorArquivo* arquivo)
{
    if(arquivo->file)
    {
        fclose(arquivo->file);
    }
    if(arquivo->buffer) {
            free(arquivo->buffer[0]);
            free(arquivo->buffer[1]);
        }
    free(arquivo->buffer);

    arquivo->file = NULL;
    arquivo->buffer = NULL;
    arquivo->tamanhoBuffer = -1;
    arquivo->bufferAtual = -1;
    arquivo->caractereAtual = -1;
}


/** \brief Preenche o buffer do arquivo
 *  Cuida de erro e fim de arquivo ao ler o buffer
 * \param indiceBuffer int Indicide do buffer que sera preenchido
 * \param arquivo LeitorArquivo* Leitor contendo o buffer
 *
 */
void PreencherBuffer(int indiceBuffer, LeitorArquivo* arquivo)
{
    int elementosLidos, i;
    // Le o arquivo
    elementosLidos = fread(arquivo->buffer[indiceBuffer], 1, arquivo->tamanhoBuffer, arquivo->file);
    // Se não ler o mesmo numero de elementos, pode ser erro ou fim de arquivo
    if(elementosLidos < arquivo->tamanhoBuffer) {
        for(i = elementosLidos-1; i < arquivo->tamanhoBuffer; i++) arquivo->buffer[indiceBuffer] = (char)0;
    }
}

/** \brief Lê o próximo caracter de um arquivo
 *
 * \param arquivo LeitorArquivo* Arquivo a ser lido
 * \return char Caracter lido
 *
 */
char ProximoCaractere(LeitorArquivo* arquivo) {
    // Verifica se o arquivo é valido
    if(arquivo->file) {
        // Verifica se o arquivo já foi lido antes
        if(arquivo->caractereAtual == -1) {
            // Preenche os buffers
            PreencherBuffer(0, arquivo);
            PreencherBuffer(1, arquivo);
        }

        // Incrementa a posição do cursor
        arquivo->caractereAtual += 1;
        // Se tiver passado do tamanho do buffer, passa pro próximo
        if(arquivo->caractereAtual >= arquivo->tamanhoBuffer) {
            arquivo->caractereAtual = 0;
            arquivo->bufferAtual = (arquivo->bufferAtual+1) % 2;
            arquivo->preencherProximo = 1;
        }
        // Se o buffer anterior ainda não tiver sido atualizado e não for mais necessario
        if(arquivo->preencherProximo && arquivo->caractereAtual > 2048) {
            PreencherBuffer((arquivo->bufferAtual+1) % 2, arquivo);
            arquivo->preencherProximo = 0;
        }

        return arquivo->buffer[arquivo->bufferAtual][arquivo->caractereAtual];
    }
    else {
        return (char)0; // Tem que tratar o erro aqui
    }
}
