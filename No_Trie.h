#ifndef NO_TRIE_H
#define NO_TRIE_H
#include "Atributo.h"
#define TAMANHO_ALFABETO 128

class No_Trie{
    public:
        No_Trie();
        No_Trie *pegarCaractere(char c);
        void atribuirCaractere(char c, No_Trie *n);
        Atributo *pegarAtributo();
        void atribuirAtributo(Atributo *p);
        void atribuirChave(bool c);
        bool EChave();
        ~No_Trie();
    private:
        No_Trie *caracteres[TAMANHO_ALFABETO];
        bool chave;
        Atributo *atributos;
};

#endif // NO_TRIE_H
