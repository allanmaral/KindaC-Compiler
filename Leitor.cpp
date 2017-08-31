#include <stdlib.h>
#include "Leitor.h"
#include "GerenciadorErro.h"

LeitorArquivo* leitor;

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
int inicializarLeitor(const char* caminhoArquivo) {
    leitor = (LeitorArquivo*) malloc(sizeof(LeitorArquivo));
    leitor->file = fopen(caminhoArquivo, "r");
    // Se for um arquivo valido
    if(leitor->file) {
        // Inicialçiza o leitor
        leitor->buffer = (char**)malloc(sizeof(char*)*2);
        leitor->buffer[0] = (char*)malloc(TAMANHO_BUFFER*sizeof(char));
        leitor->buffer[1] = (char*)malloc(TAMANHO_BUFFER*sizeof(char));
        leitor->tamanhoBuffer = TAMANHO_BUFFER;
        leitor->bufferAtual = 0;
        leitor->caractereAtual = -1;
        leitor->preencherProximoBuffer = 0;
        return ARQUIVO_ABERTO;
    }
    // Arquivo invalido
    else {
        // Inicializa o leitor com estados de erro
        leitor->buffer = NULL;
        leitor->tamanhoBuffer = -1;
        leitor->bufferAtual = -1;
        leitor->caractereAtual = -1;
        return ARQUIVO_INVALIDO;
    }
}

/** \brief Destrutor do leitor de arquivo
 *
 * \param arquivo LeitorArquivo* arquivo a ser destruido
 *
 */
void destruirLeitor(){
    if(leitor->file){ fclose(leitor->file); }
    if(leitor->buffer) {
        free(leitor->buffer[0]);
        free(leitor->buffer[1]);
    }
    free(leitor->buffer);

    leitor->file = NULL;
    leitor->buffer = NULL;
    leitor->tamanhoBuffer = -1;
    leitor->bufferAtual = -1;
    leitor->caractereAtual = -1;
}


/** \brief Preenche o buffer do arquivo
 *  Cuida de erro e fim de arquivo ao ler o buffer
 * \param indiceBuffer int Indicide do buffer que sera preenchido
 * \param arquivo LeitorArquivo* Leitor contendo o buffer
 *
 */
void preencherBuffer(int indiceBuffer){
    int elementosLidos;
    // Le o arquivo
    elementosLidos = fread(leitor->buffer[indiceBuffer], 1, leitor->tamanhoBuffer, leitor->file);
    // Se não ler o mesmo numero de elementos, pode ser erro ou fim de arquivo
    if(elementosLidos < leitor->tamanhoBuffer) {
        leitor->buffer[indiceBuffer][elementosLidos] = (char)0;
    }
}

/** \brief Lê o próximo caracter de um arquivo
 *
 * \param arquivo LeitorArquivo* Arquivo a ser lido
 * \return char Caracter lido
 *
 */
char lerProximoCaractere() {
    // Verifica se o arquivo é valido
    if(leitor->file) {
        // Verifica se o arquivo já foi lido antes
        if(leitor->caractereAtual == -1) {
            // Preenche os buffers
            preencherBuffer(0);
            preencherBuffer(1);
            leitor->caractereAtual = 0;
        }
        // Se tiver passado do tamanho do buffer, passa pro próximo
        if(leitor->caractereAtual >= leitor->tamanhoBuffer) {
            leitor->caractereAtual = 0;
            leitor->bufferAtual = (leitor->bufferAtual+1) % 2;
            leitor->preencherProximoBuffer = 1;
        }
        // Se o buffer anterior ainda não tiver sido atualizado e não for mais necessario
        if(leitor->preencherProximoBuffer && leitor->caractereAtual > TAMANHO_BUFFER/2) {
            preencherBuffer((leitor->bufferAtual+1) % 2);
            leitor->preencherProximoBuffer = 0;
        }
        char resultado = leitor->buffer[leitor->bufferAtual][leitor->caractereAtual];
        // Incrementa a posição do cursor
        leitor->caractereAtual += 1;
        return resultado;
    }
    else{ saidaErro(ErroArquivoInvalido, 0, 0); return (char)0;}
}
