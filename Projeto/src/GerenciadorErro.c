#include "GerenciadorErro.h"
#include <stdio.h>
#include <stdlib.h>

/** \brief Armazena os dados do erro
 *  Sera usado para ordenar erros de diferentes modulos do compilador
 */
typedef struct _erro{
    int codigo;
    int linha;
    int coluna;
    struct _erro* proximo;
} Erro;

Erro* raiz = NULL;

/** \brief Inicializa o gerenciador de erro
 *  Qualquer erro existente sera removido
 */
void inicializaGerenciadorErro(){
    // Se ouver algum erro, apague todos
    if(raiz) { destruirGerenciadorErro(); }
    raiz = NULL;
}

/** \brief Destroi o gerenciador de erro
 */
void destruirGerenciadorErro() {
    while(raiz){
        Erro* tmp = raiz->proximo;
        delete raiz;
        raiz = tmp;
    }
    raiz = NULL;
}

/** \brief Traduz o codigo de erro em string e envia para o stderr
 *
 * \param
 *  codigo int Codigo do erro a ser impresso
 *  linha int Linha onde o erro ocorreu
 *  coluna int Coluna onde o erro ocorreu
 * \param
 */
void saidaErro(int codigo, int linha, int coluna){
    // Insere erro na lista ordenado pela linha
    Erro* novoErro = (Erro*)malloc(sizeof(Erro));
    novoErro->codigo = codigo;
    novoErro->linha = linha;
    novoErro->coluna = coluna;
    novoErro->proximo = NULL;
    Erro* antecessor = raiz;
    if(raiz){
        while(antecessor->linha < linha){
            if(antecessor->proximo){
                if(antecessor->proximo->linha < linha){
                    antecessor = antecessor->proximo;
                } else if ((antecessor->proximo->linha == linha)) {
                    while(true) {
                        if(antecessor->proximo) {
                            if(antecessor->proximo->coluna <= coluna) {
                                antecessor = antecessor->proximo;
                            } else { break; }
                        } else { break; }
                    } break;
                } else {break;}
            } else { break; }
        }
        novoErro->proximo = antecessor->proximo;
        antecessor->proximo = novoErro;
    } else { raiz = novoErro; }
}

/** \brief Imprime o proximo erro da lista no stderr
 */
void proximoErro(){
    //Pega o proximo erro da lista
    Erro* erro = raiz;
    if(erro) { raiz = erro->proximo; } else { return; }
    //Imprime a mensagem do erro no stderr
    int linha = erro->linha, coluna = erro->coluna;
    switch(erro->codigo){
        case ErroCaractereInvalido:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Caractere Invalido\n", linha, coluna);
        break;
        case ErroCaractereVazio:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Caractere Vazio\n", linha, coluna);
        break;
        case ErroFaltaAspaSimples:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Faltando Caractere ' de terminacao\n", linha, coluna);
        break;
        case ErroFaltaAspasDupla:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Faltando Caractere \" de terminacao\n", linha, coluna);
        break;
        case ErroFimDeArquivoInesperado:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Final de Arquivo Inesperado\n", linha, coluna);
        break;
        case ErroComentarioNaoTerminado:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Bloco de Cometario Nao Terminado\n", linha, coluna);
        break;
        case ErroNumeroMalFormado:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Expoente nao possui digitos\n", linha, coluna);
        break;
        case ErroArquivoInvalido:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Arquivo Invalido\n", linha, coluna);
        break;
        case ErroCaractereMalFormado:
            fprintf(stderr, "[l:%d, c:%d] - Erro: Caractere Mal Formado\n", linha, coluna);
        break;
        default:
            fprintf(stderr, "[l:%d, c:%d] - Erro não definido (%d)\n", linha, coluna, erro->codigo);
    }
    free(erro);
}

/** \brief Imprime a lista de erros
 */
void imprimeListaErros() {
    // Enquanto houver erro na lista, imprime o erro
    while(raiz) { proximoErro(); }
}
