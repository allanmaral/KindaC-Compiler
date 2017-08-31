#ifndef NO_TRIE_H
#define NO_TRIE_H
#include "Atributo.h"
#define TAMANHO_ALFABETO 128

class No_Trie{
    public:
        No_Trie();
        /** \brief pegarCaractere
         *  Função para retornar o filho correspondente à um caractere informado
         * \param
         * c: caractere a ser buscado no vetor de caracteres
         * \return
         *  O filho buscado a partir do caractere informado
         */
        No_Trie *pegarCaractere(char c);
        /** \brief atribuirCaractere
         *  Função para atribuir à posição do vetor de caractere um nó informadado
         * \param
         * c: caractere correspondente a posição do vetor de caracteres
         * n: nó a ser atribuido nessa posição
         * \param
         */
        void atribuirCaractere(char c, No_Trie *n);
        /** \brief pegarAtributo
         *  Retornar o atributo armazenado neste nó
         */
        Atributo *pegarAtributo();
        /** \brief atribuirAtributo
         *  Função para atribuir um atributo passado como parâmetro a este nó
         * \param
         * p: atributo a ser armazenado
         * \param
         */
        void atribuirAtributo(Atributo *p);
        /** \brief atribuirChave
         *  Função para definir se o npo eh chave ou não
         * \param
         * c: booleano para ser atribuido a variavel da classe 'chave'
         * \param
         */
        void atribuirChave(bool c);
        /** \brief EChave
         * Função que retorna se o nó eh um nó chave ou não
         * \param
         * \param
         * \return
         *  Retorna a variavel chave
         *
         */
        bool EChave();
        ~No_Trie();
    private:
        No_Trie *caracteres[TAMANHO_ALFABETO];
        bool chave;
        Atributo *atributos;
};

#endif // NO_TRIE_H
