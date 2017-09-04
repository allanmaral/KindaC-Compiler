#ifndef TABELASIMBOLOS_H_INCLUDED
#define TABELASIMBOLOS_H_INCLUDED

#include "Trie.h"

/** Lista de Tokens
 *
 */
#define DEFINICAO_TIPO   1
#define ESTRUTURA        2
#define CLASSE           3
#define PUBLICO          4
#define PRIVADO          5
#define INTEIRO          6
#define REAL             7
#define BOLEANO          8
#define CARACTERE        9
#define SE              10
#define SENAO           11
#define ENQUANTO        12
#define ESCOLHA         13
#define DESVIA          14
#define IMPRIME         15
#define LE_LINHA        16
#define RETORNA         17
#define LANCA           18
#define TENTA           19
#define PEGA            20
#define CASO            21
#define NOVO            22
#define VERDADEIRO      23
#define FALSO           24
#define ESSE            25
#define ID              26
#define COLCHETE_ESQ    27
#define COLCHETE_DIR    28
#define CHAVE_ESQ       29
#define CHAVE_DIR       30
#define PARENTESE_ESQ   31
#define PARENTESE_DIR   32
#define MAIOR           34
#define MENOR           35
#define MAIOR_IGUAL     36
#define MENOR_IGUAL     37
#define COMPARACAO      38
#define ATRIBUICAO      39
#define ADICAO          40
#define SUBTRACAO       41
#define DIVISAO         42
#define ASTERISCO       43
#define OU              44
#define PONTO           45
#define DOIS_PONTOS     46
#define PONTO_VIRGULA   47
#define PONTEIRO        48
#define E_COMERCIAL     49
#define E               50
#define DIFERENTE       51
#define PORCENTO        52
#define OU_CC           53
#define NUM_INTEIRO     54
#define LITERAL         55
#define NEGACAO         56
#define VIRGULA         57
#define NUM_REAL        58

#ifndef EOF
    #define EOF         -1
#endif // EOF

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
