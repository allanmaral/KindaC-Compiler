#ifndef TRIE_H
#define TRIE_H
#include "No_Trie.h"

class Trie{
    public:
        Trie();
        Atributo* busca(char *entrada);
        void insere(char* entrada, Atributo* atributo);
        void imprime();
        virtual ~Trie();

    protected:
        int altura;
        No_Trie *raiz;
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
        int calcularTamanhoLexema(char *str);
    private:
        void imprimeRecursivo(char* saida, int indice, No_Trie *n);
};

#endif // TRIE_H
