#include "GerenciadorErro.h"
#include <stdio.h>
#include <stdlib.h>

/** \brief Lista de erros
 *
 */
char ErroLiteral[ErroTamanhoEnumerador][256] = {
    "Erro: Caractere invalido",
    "Erro: Caractere vazio",
    "Erro: Faltando caractere ' de terminacao",
    "Erro: Faltando caractere \" de terminacao",
    "Erro: Final de arquivo inesperado",
    "Erro: Bloco de cometario nao terminado",
    "Erro: Caractere mal formado",
    "Erro: Expoente nao possui digitos",
    "Erro: Arquivo invalido",
    "antes",
    "depois",
    "Erro: Classe herda ela mesma",
    "Erro: Classe herdada nao existe",
    "Erro: Redefinicao da classe ",
    "Erro: Redefinicao da funcao ",
    "Erro: Paramentros com o mesmo nome ",
    " nao e o nome de um tipo ",
    "Erro: Redefinicao da variavel ",
    "Erro Redefinicao do tipo ",
    "Erro: Tamanho do arranjo tem que ser inteiro",
    "Erro: O arranjo tem que conter um tamanho",
    "Erro: Parametro e variavel com o mesmo nome "
};

/** \brief Armazena os dados do erro
 *  Será usado para ordenar erros de diferentes módulos do compilador
 */
typedef struct _erro{
    int codigo;
    int linha;
    int coluna;
    char* tokenEsperado;
    char* tokenEncontrado;
    struct _erro* proximo;
} Erro;

Erro* raiz = NULL;

/** \brief Inicializa o gerenciador de erro
 *  Qualquer erro existente será removido
 */
void inicializaGerenciadorErro(){
    // Se houver algum erro, apague todos
    if(raiz) { destruirGerenciadorErro(); }
    raiz = NULL;
}

/** \brief Destrói o gerenciador de erro
 */
void destruirGerenciadorErro() {
    while(raiz){
        Erro* tmp = raiz->proximo;
        delete raiz;
        raiz = tmp;
    }
    raiz = NULL;
}

/** \brief Traduz o código de erro em string e envia para o stderr
 *
 * \param
 *  codigo int Código do erro a ser impresso
 *  linha int Linha onde o erro ocorreu
 *  coluna int Coluna onde o erro ocorreu
 * \param
 */
void saidaErro(int codigo, int linha, int coluna, char* tokenEncontrado, char* tokenEsperado){
    // Insere erro na lista ordenado pela linha
    Erro* novoErro = (Erro*)malloc(sizeof(Erro));
    novoErro->codigo = codigo;
    novoErro->linha = linha;
    novoErro->coluna = coluna;
    novoErro->tokenEncontrado = tokenEncontrado;
    novoErro->tokenEsperado = tokenEsperado;
    novoErro->proximo = NULL;
    Erro* antecessor = raiz;
    if(raiz){
        while(true){
            if(antecessor->proximo){
                if(antecessor->proximo->linha < linha){
                    antecessor = antecessor->proximo;
                } else if(antecessor->proximo->linha == linha){
                           while(true){
                               if(antecessor->proximo){
                                   if(antecessor->proximo->coluna <= coluna) {
                                       antecessor = antecessor->proximo;
                                   } else { break; }
                               } else { break; }
                           } break;
                       } else { break; }
            } else { break; }
        }
        novoErro->proximo = antecessor->proximo;
        antecessor->proximo = novoErro;
    } else { raiz = novoErro; }
}

/** \brief Imprime o próximo erro da lista no stderr
 */
void proximoErro(){
    fflush(stdout);
    fflush(stderr);
    //Pega o próximo erro da lista
    Erro* erro = raiz;
    if(erro) { raiz = erro->proximo; } else { return; }
    //Imprime a mensagem do erro no stderr
    int linha = erro->linha, coluna = erro->coluna;
    switch(erro->codigo){
        case ErroSintatico:
        case ErroSintaticoDepois:
            fprintf(stderr, "[l:%d, c:%d] - Erro: \"%s\" esperado %s de \"%s\"\n", linha, coluna, erro->tokenEsperado,
            ErroLiteral[erro->codigo], erro->tokenEncontrado);
        break;
        case ErroSemanticoRedefinicaoClasse:
        case ErroSemanticoRedefinicaoFuncao:
        case ErroSemanticoRedefinicaoVariavel:
        case ErroSemanticoConflitoDeDeclaracoes:
        case ErroSemanticoRedefinicaoTipo:
        case ErroSemanticoVariavelIgualParametro:
            fprintf(stderr,"[l:%d, c:%d] - %s\"%s\"\n",linha, coluna, ErroLiteral[erro->codigo], erro->tokenEncontrado);
        break;
        case ErroSemanticoTipoVariavel:
            fprintf(stderr,"[l:%d, c:%d] - Erro: \"%s\"%s\n",linha, coluna, erro->tokenEncontrado, ErroLiteral[erro->codigo]);
        break;
        default:{
            if(erro->codigo >= 0 && erro->codigo < ErroTamanhoEnumerador) {
               fprintf(stderr, "[l:%d, c:%d] - %s\n", linha, coluna, ErroLiteral[erro->codigo]);
            } else{
                 fprintf(stderr, "[l:%d, c:%d] - Erro não definido (%d)\n", linha, coluna, erro->codigo);
              }
        }
    }
    free(erro);
}

/** \brief Imprime a lista de erros
 */
void imprimeListaErros() {
    // Enquanto houver erro na lista, imprime o erro
    while(raiz) { proximoErro(); }
}
