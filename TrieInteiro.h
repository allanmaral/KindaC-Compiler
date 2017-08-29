#ifndef TRIEINTEIRO_H
#define TRIEINTEIRO_H
#include "Trie.h"

class TrieInteiro:public Trie{
    public:
        TrieInteiro();
        virtual ~TrieInteiro();
    protected:
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
};

#endif // TRIEINTEIRO_H
