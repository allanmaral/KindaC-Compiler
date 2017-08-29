#include "TrieReservada.h"

TrieReservada::TrieReservada():Trie(){
    raiz = new No_Trie();
    altura = 0;
}
void TrieReservada::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"\"%s\"\n", saida);
}
void TrieReservada::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"     TABELA DE PALAVRAS RESERVADAS     \n");
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"LEXEMA                   Token numérico\n");
}
TrieReservada::~TrieReservada() { }
