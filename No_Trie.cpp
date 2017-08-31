#include "No_Trie.h"

No_Trie::No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++) { caracteres[i] = NULL; }
    atributos = NULL;
    chave = false;
}
/** \brief pegarCaractere
 *  Função para retornar o filho correspondente à um caractere informado
 * \param
 * c: caractere a ser buscado no vetor de caracteres
 * \return
 *  O filho buscado a partir do caractere informado
 */
No_Trie* No_Trie::pegarCaractere(char c) { return caracteres[(int)c]; }
/** \brief atribuirCaractere
 *  Função para atribuir à posição do vetor de caractere um nó informadado
 * \param
 * c: caractere correspondente a posição do vetor de caracteres
 * n: nó a ser atribuido nessa posição
 * \param
 */
void No_Trie::atribuirCaractere(char c, No_Trie* n) { caracteres[(int)c] = n; }
/** \brief pegarAtributo
 *  Retornar o atributo armazenado neste nó
 */
Atributo* No_Trie::pegarAtributo() { return atributos; }
/** \brief atribuirAtributo
 *  Função para atribuir um atributo passado como parâmetro a este nó
 * \param
 * p: atributo a ser armazenado
 * \param
 */
void No_Trie::atribuirAtributo(Atributo *p) { atributos = p; }
/** \brief atribuirChave
 *  Função para definir se o npo eh chave ou não
 * \param
 * c: booleano para ser atribuido a variavel da classe 'chave'
 * \param
 */

void No_Trie::atribuirChave(bool c) { chave = c; }
/** \brief EChave
 * Função que retorna se o nó eh um nó chave ou não
 * \param
 * \param
 * \return
 *  Retorna a variavel chave
 *
 */
bool No_Trie::EChave() { return chave; }

No_Trie::~No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        if(caracteres[i] != NULL){ delete caracteres[i]; }
    }
    if(atributos != NULL){ delete atributos; }
}
