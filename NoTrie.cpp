#include "NoTrie.h"

NoTrie::NoTrie()
{
    esquerda = NULL;
    direita = NULL;
    meio = NULL;
    propriedade = NULL;
    chave = false;
}
NoTrie* NoTrie::pegarEsquerda(){

    return esquerda;

}
NoTrie* NoTrie::pegarDireita(){

    return direita;

}
NoTrie* NoTrie::pegarMeio(){

    return meio;

}
char NoTrie::pegarCaractere(){

    return caractere;

}
bool NoTrie::pegarChave(){

    return chave;

}
Atributo* NoTrie::pegarAtributo(){

    return propriedade;

}
void NoTrie::atribuirEsquerda(NoTrie *n){

    esquerda = n;

}
void NoTrie::atribuirDireita(NoTrie *n){

    direita = n;

}
void NoTrie::atribuirMeio(NoTrie *n){

    meio = n;

}
void NoTrie::atribuirCaractere(char c){

    caractere = c;

}
void NoTrie::atribuirChave(bool c){

    chave = c;

}
void NoTrie::atribuirAtributo(Atributo *a){

    propriedade = a;

}
NoTrie::~NoTrie()
{
    if(esquerda != NULL){

        delete esquerda;

    }
    if(direita != NULL){

        delete direita;

    }
    if(meio != NULL){

        delete meio;

    }
    if(propriedade != NULL){

        delete propriedade;

    }
}
