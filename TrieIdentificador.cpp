#include "TrieIdentificador.h"

TrieIdentificador::TrieIdentificador():Trie(){
    raiz = new No_Trie();
    altura = 0;
}
void TrieIdentificador::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}
void TrieIdentificador::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"       TABELA DE IDENTIFICADORES       \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieIdentificador::~TrieIdentificador() { }
