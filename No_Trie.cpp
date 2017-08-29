#include "No_Trie.h"

No_Trie::No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++) { caracteres[i] = NULL; }
    atributos = NULL;
    chave = false;
}

No_Trie* No_Trie::pegarCaractere(char c) { return caracteres[(int)c]; }
void No_Trie::atribuirCaractere(char c, No_Trie* n) { caracteres[(int)c] = n; }
Atributo* No_Trie::pegarAtributo() { return atributos; }
void No_Trie::atribuirAtributo(Atributo *p) { atributos = p; }
void No_Trie::atribuirChave(bool c) { chave = c; }
bool No_Trie::EChave() { return chave; }
No_Trie::~No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        if(caracteres[i] != NULL){ delete caracteres[i]; }
    }
    if(atributos != NULL){ delete atributos; }
}
