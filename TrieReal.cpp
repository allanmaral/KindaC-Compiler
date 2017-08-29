#include "TrieReal.h"

TrieReal::TrieReal():Trie(){
    raiz = new No_Trie();
    altura = 0;
}
void TrieReal::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}
void TrieReal::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE REAIS             \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieReal::~TrieReal() { }
