#include "TabelaSimbolos.h"

Trie *tabelaID;
Trie *tabelaInteiro;
Trie *tabelaReal;
Trie *tabelaLiteral;
Trie *tabelaReservado;

void inicializaTabelaSimbolos(){
    tabelaID = new TrieIdentificador();
    tabelaInteiro = new TrieInteiro();
    tabelaLiteral = new TrieLiteral();
    tabelaReal = new TrieReal();
    tabelaReservado = new TrieReservada();
}
Atributo* buscaTabela(const int tabela, char* entrada){
    switch(tabela){
        case TABELA_ID:
            return tabelaID->busca(entrada);
        break;
        case TABELA_INTEIRO:
            return tabelaInteiro->busca(entrada);
        break;
        case TABELA_REAL:
            return tabelaReal->busca(entrada);
        break;
        case TABELA_LITERAL:
            return tabelaLiteral->busca(entrada);
        break;
        case TABELA_RESERVADA:
            return tabelaReservado->busca(entrada);
    }
    return NULL;
}
void insereTabela(const int tabela, char* entrada, Atributo* atr){
    switch(tabela){
        case TABELA_ID:
            tabelaID->insere(entrada,atr);
        break;
        case TABELA_INTEIRO:
            tabelaInteiro->insere(entrada,atr);
        break;
        case TABELA_REAL:
            tabelaReal->insere(entrada,atr);
        break;
        case TABELA_LITERAL:
            tabelaLiteral->insere(entrada,atr);
        break;
        case TABELA_RESERVADA:
            tabelaReservado->insere(entrada,atr);
    }
}
void imprimeTabela(const int tabela){
    switch(tabela){
        case TABELA_ID:
            tabelaID->imprime();
        break;
        case TABELA_INTEIRO:
            tabelaInteiro->imprime();
        break;
        case TABELA_REAL:
            tabelaReal->imprime();
        break;
        case TABELA_LITERAL:
            tabelaLiteral->imprime();
        break;
        case TABELA_RESERVADA:
            tabelaReservado->imprime();
    }
}
void destroiTabelaSimbolos(){
    delete tabelaID;
    delete tabelaInteiro;
    delete tabelaLiteral;
    delete tabelaReal;
    delete tabelaReservado;
}
