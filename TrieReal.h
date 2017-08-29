#ifndef TRIEREAL_H
#define TRIEREAL_H
#include "Trie.h"

class TrieReal:public Trie{
    public:
        TrieReal();
        virtual ~TrieReal();
    protected:
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
};

#endif // TRIEREAL_H
