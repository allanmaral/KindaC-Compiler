#ifndef TRIERESERVADA_H
#define TRIERESERVADA_H
#include "Trie.h"

class TrieReservada:public Trie{
    public:
        TrieReservada();
        virtual ~TrieReservada();
    protected:
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
        void inicializarReservada();
};

#endif // TRIERESERVADA_H
