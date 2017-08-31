#include "TrieIdentificador.h"

TrieIdentificador::TrieIdentificador():Trie(){}
/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TrieIdentificador::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}
/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TrieIdentificador::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"       TABELA DE IDENTIFICADORES       \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieIdentificador::~TrieIdentificador() { }
