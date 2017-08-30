#ifndef TABELASIMBOLOS_H_INCLUDED
#define TABELASIMBOLOS_H_INCLUDED

#include "TrieReal.h"
#include "TrieIdentificador.h"
#include "TrieInteiro.h"
#include "TrieLiteral.h"
#include "TrieReservada.h"
#include "Tokens.h"

#define TABELA_ID 1
#define TABELA_REAL 2
#define TABELA_INTEIRO 3
#define TABELA_LITERAL 4
#define TABELA_RESERVADA 5

void inicializaTabelaSimbolos();
Atributo* buscaTabela(const int tabela, char* entrada);
void insereTabela(const int tabela, char* entrada, Atributo* atr);
void imprimeTabela(const int tabela);
void destroiTabelaSimbolos();

#endif // TABELASIMBOLOS_H_INCLUDED
