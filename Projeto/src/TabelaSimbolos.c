#include "TabelaSimbolos.h"

TrieIdentificador tabelaID;
TrieInteiro tabelaInteiro;
TrieLiteral tabelaReal;
TrieReal tabelaLiteral;
TrieReservada tabelaReservado;

/** \brief buscaTabela
 *  Função para fazer a busca de um atributo dentro de uma tabela por um lexema
 * \param
 *  tablela: referência a qual tabela será feita a busca
 * \param
 * \return
 *  Retorna o atributo referente ao lexema buscado
 */
Atributo* buscaTabela(const int tabela, char* entrada){
    switch(tabela){
        case TABELA_ID:
            return tabelaID.busca(entrada);
            break;
        case TABELA_INTEIRO:
            return tabelaInteiro.busca(entrada);
            break;
        case TABELA_REAL:
            return tabelaReal.busca(entrada);
            break;
        case TABELA_LITERAL:
            return tabelaLiteral.busca(entrada);
            break;
        case TABELA_RESERVADA:
            return tabelaReservado.busca(entrada);
        default:
            return NULL;
    }
}

/** \brief insereTabela
 *  Função para inserir um lexema com o seu atributo dentro de uma das tabelas
 * \param
 *  tabela: referência a qual tabela será feita a inserção
 * \param
 */
void insereTabela(const int tabela, char* entrada, Atributo* atr){
    switch(tabela){
        case TABELA_ID:
            tabelaID.insere(entrada,atr);
            break;
        case TABELA_INTEIRO:
            tabelaInteiro.insere(entrada,atr);
            break;
        case TABELA_REAL:
            tabelaReal.insere(entrada,atr);
            break;
        case TABELA_LITERAL:
            tabelaLiteral.insere(entrada,atr);
            break;
        case TABELA_RESERVADA:
            tabelaReservado.insere(entrada,atr);
    }
}

/** \brief imprimeTabela
 *  Função para realizar a impressão das tabelas
 */
void imprimeTabelas(){
    tabelaLiteral.imprime();
    tabelaID.imprime();
    tabelaInteiro.imprime();
    tabelaReal.imprime();
    tabelaReservado.imprime();
}
