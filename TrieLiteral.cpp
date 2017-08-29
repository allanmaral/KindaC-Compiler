#include "TrieLiteral.h"

TrieLiteral::TrieLiteral():Trie(){
    raiz = new No_Trie();
    altura = 0;
}
void TrieLiteral::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}
void TrieLiteral::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"          TABELA DE LITERAIS           \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieLiteral::~TrieLiteral() { }
