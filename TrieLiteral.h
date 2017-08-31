#ifndef TRIELITERAL_H
#define TRIELITERAL_H
#include "Trie.h"

class TrieLiteral:public Trie{
    public:
        TrieLiteral();
        virtual ~TrieLiteral();
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
};

#endif // TRIELITERAL_H
