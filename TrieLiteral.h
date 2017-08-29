#ifndef TRIELITERAL_H
#define TRIELITERAL_H
#include "Trie.h"

class TrieLiteral:public Trie{
    public:
        TrieLiteral();
        virtual ~TrieLiteral();
    protected:
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
};

#endif // TRIELITERAL_H
