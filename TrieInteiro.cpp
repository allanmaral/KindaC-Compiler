#include "TrieInteiro.h"

TrieInteiro::TrieInteiro():Trie(){
    raiz = new No_Trie();
    altura = 0;
}
void TrieInteiro::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}
void TrieInteiro::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE INTEIROS          \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieInteiro::~TrieInteiro() { }
