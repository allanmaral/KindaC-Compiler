#include "GerenciadorErro.h"
#include <stdio.h>

/** \brief Traduz o codigo de erro em string e envia para o stderr
 *
 * \param codigo int Codigo do erro a ser impresso
 * \param linha int Linha onde o erro ocorreu
 * \param coluna int Coluna onde o erro ocorreu
 *
 */
void saidaErro(int codigo, int linha, int coluna)
{
    switch(codigo)
    {
    case ErroCaractereInvalido:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Caractere Invalido", linha, coluna);
        break;
    case ErroCaractereVazio:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Caractere Vazio", linha, coluna);
        break;
    case ErroFaltaAspaSimples:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Faltando Caractere ' de terminacao", linha, coluna);
        break;
    case ErroFaltaAspasDupla:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Faltando Caractere \" de terminacao", linha, coluna);
        break;
    case ErroFimDeArquivoInesperado:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Final de Arquivo Inexperado", linha, coluna);
        break;
    case ErroComentarioNaoTerminado:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Bloco de Cometario Nao Terminado", linha, coluna);
        break;
    case ErroNumeroMalFormado:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Numero Mal Formado", linha, coluna);
        break;
    case ErroArquivoInvalido:
        fprintf(stderr, "[l:%d, c:%d] - Erro: Arquivo Invalido", linha, coluna);
        break;
    default:
        fprintf(stderr, "[l:%d, c:%d] - Erro não definido (%d)", linha, coluna, codigo);
    }
}
