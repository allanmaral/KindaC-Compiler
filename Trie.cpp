#include "Trie.h"

Trie::Trie(){
    raiz = new No_Trie();
    altura = 0;
}
/** \brief
 *  Função para fazer a inserção de lexemas dentro da tabela de simbolos
 * \param
 *  entrada: lexema a ser inserido na tabela
 *  atributo: atributo associado ao lexema
 * \param
 * \return
 *  vazio
 */
void Trie::insere(char* entrada, Atributo* atributo){

    int indice = 0;
    No_Trie *no = raiz;
    No_Trie *auxiliar = NULL;
    char caractere;

    while(entrada[indice] != '\0'){

        caractere = entrada[indice];
        auxiliar = no->pegarCaractere(caractere);
        if(auxiliar == NULL){
            auxiliar = new No_Trie();
            no->atribuirCaractere(caractere, auxiliar);
            no = auxiliar;
        }else{
            no = no->pegarCaractere(caractere);
        }
        indice++;
    }
    if(altura < indice + 1){

        altura = indice + 1;

    }
    no->atribuirChave(true);
    no->atribuirAtributo(atributo);
}
/** \brief
 *  Função para imprimir todos os lexemas guardados dentro da tabela
 * \param
 * \param
 * \return
 *
 */
void Trie::imprime(){
    imprimeCabecalho();
    char saida[altura + 1];
    imprimeRecursivo(saida, 0, raiz);
}
/** \brief
 *  Função recursiva auxiliar para percorrer a trie
 * \param
 *  saida: string parcial que é usada na impressão
 * \param
 * \return
 *
 */
void Trie::imprimeRecursivo(char* saida, int indice, No_Trie *n){
    if(n->EChave()){
        saida[indice] = '\0';
        imprimeLexema(saida, n->pegarAtributo());
    }
    No_Trie *filho = NULL;
    for(unsigned int caractere = 0; caractere < TAMANHO_ALFABETO; caractere++){
        filho = n->pegarCaractere(caractere);
        if(filho != NULL){
            saida[indice] = caractere;
            imprimeRecursivo(saida, indice + 1, filho);
        }
    }
}
/** \brief
 *  Função que busca um lexema na trie e retorna o atributo associado a ele
 * \param
 *  entrada: lexema a ser buscado
 * \param
 * \return
 *  Atributo associado a esse lexema
 */
Atributo* Trie::busca(char *entrada){
    int indice = 0;
    No_Trie *no = raiz;
    while(entrada[indice] != '\0'){
        no = no->pegarCaractere(entrada[indice]);
        if(no == NULL){
            return NULL;
        }
        indice++;
    }
    if(no->EChave()){
        return no->pegarAtributo();
    }
    return NULL;
}
int Trie::calcularTamanhoLexema(char *lexema){
    int total=0;
    while( lexema[total] != '\0')
        total++;
    return total;
}
void Trie::imprimeLexema(char* saida, Atributo * atr){
    fprintf(stdout,"[%s]\n", saida);
}
void Trie::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"---------------TABELA------------------\n");
    fprintf(stdout,"---------------------------------------\n");
}
Trie::~Trie() { delete raiz; }
