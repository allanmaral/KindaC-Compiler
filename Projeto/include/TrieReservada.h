#ifndef TRIERESERVADA_H
#define TRIERESERVADA_H
#include "Trie.h"

class TrieReservada:public Trie{
    public:
        TrieReservada();
        virtual ~TrieReservada();
    protected:
        /** \brief imprimeLexema
         *  Função para colocar a string associada a um lexema no stdout
         * \param
         *  saida: lexema a ser impresso
         *  atr: atributo do lexema que será impresso juntamente com ele
         */
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        /** \brief imprimeCabecalho
         *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
         */
        virtual void imprimeCabecalho();
        void inicializarReservada();
};

#endif // TRIERESERVADA_H
