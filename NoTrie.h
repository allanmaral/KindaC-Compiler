#ifndef NOTRIE_H
#define NOTRIE_H
#include "Atributo.h"


class NoTrie
{
    public:
        NoTrie();
        NoTrie* pegarEsquerda();
        NoTrie* pegarDireita();
        NoTrie* pegarMeio();
        char pegarCaractere();
        bool pegarChave();
        Atributo* pegarAtributo();
        void atribuirEsquerda(NoTrie *n);
        void atribuirDireita(NoTrie *n);
        void atribuirMeio(NoTrie *n);
        void atribuirCaractere(char c);
        void atribuirChave(bool c);
        void atribuirAtributo(Atributo *a);
        ~NoTrie();
    private:
        char caractere;
        bool chave;
        Atributo *propriedade;
        NoTrie *esquerda;
        NoTrie *direita;
        NoTrie *meio;
};

#endif // NOTRIE_H
