#ifndef TRIE_H
#define TRIE_H
#include "No_Trie.h"
#include "Tokens.h"

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
        int calcularTamanhoLexema(char* lexema);
        virtual void imprimeLexema(char* entrada, Atributo * atr);
        virtual void imprimeCabecalho();
    private:
        void insereRecursivo(char* entrada, int indice, No_Trie *raiz, Atributo* atributo);
        void imprimeRecursivo(char* saida, int indice, No_Trie *n);
        Atributo *buscaRecursivo(char *entrada, int indice, No_Trie *pai);
};

#endif // TRIE_H
