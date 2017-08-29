#ifndef TRIEIDENTIFICADOR_H
#define TRIEIDENTIFICADOR_H
#include "Trie.h"

class TrieIdentificador:public Trie{
    public:
        TrieIdentificador();
        virtual ~TrieIdentificador();
    protected:
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
};

#endif // TRIEIDENTIFICADOR_H
