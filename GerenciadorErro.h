/** \brief Enumeração dos tipos de erros
 */
typedef enum {
    ErroCaractereInvalido   = 1,
    ErroCaractereVazio,
    ErroFaltaAspaSimples,
    ErroFaltaAspasDupla,
    ErroFimDeArquivoInesperado,
    ErroComentarioNaoTerminado,
    ErroNumeroMalFormado,
    ErroArquivoInvalido
} Erros;

/** \brief Traduz o codigo de erro em string e envia para o stderr
 *
 * \param codigo int Codigo do erro a ser impresso
 * \param linha int Linha onde o erro ocorreu
 * \param coluna int Coluna onde o erro ocorreu
 *
 */
void saidaErro(int codigo, int linha, int coluna);
