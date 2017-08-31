/** \brief Enumeração dos tipos de erros
 */
typedef enum {
    ErroCaractereInvalido   = 1,
    ErroCaractereVazio,
    ErroFaltaAspaSimples,
    ErroFaltaAspasDupla,
    ErroFimDeArquivoInesperado,
    ErroComentarioNaoTerminado,
    ErroCaractereMalFormado,
    ErroNumeroMalFormado,
    ErroArquivoInvalido
} Erros;

/** \brief Inicializa o gerenciador de erro
 *  Qualquer erro existente sera removido
 */
void inicializaGerenciadorErro();

/** \brief Destroi o gerenciador de erro
 */
void destruirGerenciadorErro();

/** \brief Salva o erro na lista
 *
 * \param codigo int Codigo do erro a ser impresso
 * \param linha int Linha onde o erro ocorreu
 * \param coluna int Coluna onde o erro ocorreu
 *
 */
void saidaErro(int codigo, int linha, int coluna);

/** \brief Imprime o proximo erro da lista no stderr
 */
void proximoErro();

/** \brief Imprime a lista de erros
 */
void imprimeListaErros();
