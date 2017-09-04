#ifndef TABELASIMBOLOS_H_INCLUDED
#define TABELASIMBOLOS_H_INCLUDED

#include "Trie.h"

#define TABELA_ID 1
#define TABELA_REAL 2
#define TABELA_INTEIRO 3
#define TABELA_LITERAL 4
#define TABELA_RESERVADA 5

/** \brief buscaTabela
 *  Função para fazer a busca de um atributo dentro de uma tabela por um lexema
 * \param
 * tablela: referência a qual tabela será feita a busca
 * \param
 * \return
 * Retorna o atributo referente ao lexema buscado
 */
Atributo* buscaTabela(const int tabela, char* entrada);
/** \brief insereTabela
 *  Função para inserir um lexema com o seu atributo dentro de uma das tabelas
 * \param
 * tabela: referência a qual tabela será feita a inserção
 * \param
 */
void insereTabela(const int tabela, char* entrada, Atributo* atr);
/** \brief imprimeTabela
 *  Função para realizar a impressão de uma das tabelas
 * \param
 * tabela: tabela a ser impressa
 * \param
 */
void imprimeTabelas();

#endif // TABELASIMBOLOS_H_INCLUDED
