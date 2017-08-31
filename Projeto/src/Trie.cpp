#include "Trie.h"

Trie::Trie() { raiz = new No_Trie(); altura = 0; }

/** \brief insere
 *  Função para fazer a inserção de lexemas dentro da tabela de simbolos
 * \param
 *  entrada: lexema a ser inserido na tabela
 *  atributo: atributo associado ao lexema
 * \param
 */
void Trie::insere(char* entrada, Atributo* atributo){
    int indice = 0;
    No_Trie *no = raiz;
    No_Trie *auxiliar = NULL;
    char caractere;

    while(entrada[indice] != '\0'){ ///Percorre todo os caracteres da entrada
        caractere = entrada[indice];
        auxiliar = no->pegarCaractere(caractere);   ///para cada caractere busca o filho correspondente do nó atual
        if(auxiliar == NULL){   ///se esse filho nao existir, o cria e associa o nó atual a ele
            auxiliar = new No_Trie();
            no->atribuirCaractere(caractere, auxiliar);
            no = auxiliar;
        } else{ ///se o filho existir, apenas desce um nível da árvore
            no = no->pegarCaractere(caractere);
        }
        indice++;
    }
    if(altura < indice + 1) { altura = indice + 1; }
    ///ao chegar no final da string, coloca o nó atual como chave e associa o atributo à ele
    no->atribuirChave(true);
    no->atribuirAtributo(atributo);
}

/** \brief imprime
 *  Função para imprimir todos os lexemas guardados dentro da tabela
 */
void Trie::imprime(){
    imprimeCabecalho();
    char saida[altura + 1];
    imprimeRecursivo(saida, 0, raiz);
}

/** \brief imprimeRecursivo
 *  Função recursiva auxiliar para percorrer a trie
 * \param
 *  saida: string parcial que é usada na impressão
 * \param
 */
void Trie::imprimeRecursivo(char* saida, int indice, No_Trie *n){
    if(n->EChave()){///Para cada nó que for chave, imprime o caminho que foi percorrido pela recursão
        saida[indice] = '\0';
        imprimeLexema(saida, n->pegarAtributo());
    }
    No_Trie *filho = NULL;
    ///Para cada filho não nulo do nó atual,
    for(unsigned int caractere = 0; caractere < TAMANHO_ALFABETO; caractere++){
        ///coloca o caractere correspondente na saida e desce um nível
        filho = n->pegarCaractere(caractere);
        if(filho != NULL){
            saida[indice] = caractere;
            imprimeRecursivo(saida, indice + 1, filho);
        }
    }
}

/** \brief busca
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
    while(entrada[indice] != '\0'){///enquanto percorre toda a entrada buscada
        no = no->pegarCaractere(entrada[indice]);
        if(no == NULL){///se encontrar um nó nulo pelo caminho, a entrada não existe
            return NULL;
        }
        indice++;
    }
    if(no->EChave()){///se não encontrou nenhum nó nulo pelo caminho e o nó que parou é uma chave, então encontrou a entrada
        return no->pegarAtributo();
    }
    return NULL;
}

/** \brief calcularTamanhoLexema
 *  FUnção para calcular o tamanho de lexemas
 * \param
 * lexema: lexema para ser calculado o seu tamanho
 * \return
 *  Tamanho do lexema
 */
int Trie::calcularTamanhoLexema(char *lexema){
    int total = 0;
    while( lexema[total] != '\0') { total++; }
    return total;
}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void Trie::imprimeLexema(char* saida, Atributo * atr){
    fprintf(stdout,"[%s]\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void Trie::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"---------------TABELA------------------\n");
    fprintf(stdout,"---------------------------------------\n");
}
Trie::~Trie() { delete raiz; }
