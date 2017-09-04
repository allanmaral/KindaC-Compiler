#include <stdlib.h>
#include <stdio.h>

#ifndef ATRIBUTO_H
#define ATRIBUTO_H

class Atributo{
    public:
        Atributo();
        int pegarToken();
        void atribuirToken(int t);
        ~Atributo();
    private:
        int token;
};

#endif // PROPRIEDADE_H

#ifndef NO_TRIE_H
#define NO_TRIE_H
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

#ifndef TRIE_H
#define TRIE_H

class Trie{
    public:
        Trie();
        /** \brief busca
         *  Função que busca um lexema na trie e retorna o atributo associado a ele
         * \param
         *  entrada: lexema a ser buscado
         * \param
         * \return
         *  Atributo associado a esse lexema
         */
        Atributo* busca(char *entrada);
        /** \brief insere
         *  Função para fazer a inserção de lexemas dentro da tabela de simbolos
         * \param
         *  entrada: lexema a ser inserido na tabela
         *  atributo: atributo associado ao lexema
         * \param
         * \return
         *  vazio
         */
        void insere(char* entrada, Atributo* atributo);
        /** \brief imprime
         *  Função para imprimir todos os lexemas guardados dentro da tabela
         */
        void imprime();
        virtual ~Trie();

    protected:
        int altura;
        No_Trie *raiz;
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
        /** \brief calcularTamanhoLexema
         *  FUnção para calcular o tamanho de lexemas
         * \param
         * lexema: lexema para ser calculado o seu tamanho
         * \return
         *  Tamanho do lexema
         */
        int calcularTamanhoLexema(char *str);
    private:
        /** \brief imprimeRecursivo
         *  Função recursiva auxiliar para percorrer a trie
         * \param
         *  saida: string parcial que é usada na impressão
         * \param
         * \return
         *
         */
        void imprimeRecursivo(char* saida, int indice, No_Trie *n);
};

#endif // TRIE_H

#ifndef TRIEIDENTIFICADOR_H
#define TRIEIDENTIFICADOR_H

class TrieIdentificador:public Trie{
    public:
        TrieIdentificador();
        virtual ~TrieIdentificador();
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

#endif // TRIEIDENTIFICADOR_H

#ifndef TRIEINTEIRO_H
#define TRIEINTEIRO_H

class TrieInteiro:public Trie{
    public:
        TrieInteiro();
        virtual ~TrieInteiro();
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

#endif // TRIEINTEIRO_H

#ifndef TRIELITERAL_H
#define TRIELITERAL_H

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

#ifndef TRIEREAL_H
#define TRIEREAL_H

class TrieReal:public Trie{
    public:
        TrieReal();
        virtual ~TrieReal();
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

#endif // TRIEREAL_H

#ifndef TRIERESERVADA_H
#define TRIERESERVADA_H

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

#ifndef ATRIBUTO_H
#define ATRIBUTO_H

class Atributo{
    public:
        Atributo();
        int pegarToken();
        void atribuirToken(int t);
        ~Atributo();
    private:
        int token;
};

#endif // PROPRIEDADE_H
