#ifndef TABELASIMBOLOS_H
#define TABELASIMBOLOS_H
#include "NoTrie.h"


class TabelaSimbolos
{
    public:
        TabelaSimbolos();
        void insere(char *entrada, Atributo *atributo);
        Atributo* busca(char *entrada);
        virtual void imprime();
        virtual ~TabelaSimbolos();
    private:
        NoTrie *raiz;
        NoTrie *insereRecursivo(char *entrada, int indice, NoTrie *pai, Atributo *atributo);
        Atributo* buscaRecursivo(char *entrada, int indice, NoTrie *pai);
        void imprimeRecursivo(char *saida, int indice, NoTrie *pai);
        int altura;
};

#endif // TABELASIMBOLOS_H
