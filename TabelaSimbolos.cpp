#include "TabelaSimbolos.h"

TabelaSimbolos::TabelaSimbolos()
{
    raiz = NULL;
    altura = -1;
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

void TabelaSimbolos::insere(char *entrada, Atributo *atributo){

    raiz = insereRecursivo(entrada, 0, raiz, atributo);

}
/** \brief
 *  Função auxiliar para o metodo de inserção
 * \param
 *  entrada: lexema a ser inserido na tabela
 *  atributo: atributo associado ao lexema
 *  pai: nó da árvore trie a ser analisado
 * \param
 * \return
 *  Ponteiro para o nó que foi analisado
 *  vazio
 */
NoTrie *TabelaSimbolos::insereRecursivo(char *entrada, int indice, NoTrie *pai, Atributo *atributo){

    if(pai == NULL){///Caso encontre uma nó nulo, cria um novo nó e atribui o caracter correspondente a ele

        pai = new NoTrie();
        pai->atribuirCaractere(entrada[indice]);
        if(entrada[indice+1] == '\0'){///se tiver chegado no fim da string, marca esse nó como chave e termina a recursão

            pai->atribuirChave(true);
            pai->atribuirAtributo(atributo);
            altura = indice + 2;

        }else{///se não tiver chegado no fim da string, desce um nivel na árvore

            pai->atribuirMeio(insereRecursivo(entrada, indice + 1, NULL, atributo));

        }
    }else{

        if(entrada[indice] == pai->pegarCaractere()){///verifica se o caminho que tomou é prefixo de algum outro lexema já inserido

            if(entrada[indice + 1] == '\0'){///se sim, e se tiver chegado no fim da string, encerra a recursão

                pai->atribuirChave(true);
                pai->atribuirAtributo(atributo);

            }else{

                pai->atribuirMeio(insereRecursivo(entrada, indice + 1, pai->pegarMeio(), atributo));

            }

        }else if(entrada[indice] > pai->pegarCaractere()){///caso não tenha encontrado o caracter ainda, e o caracter for maior do que o armazenado no pai, desce a direita

            pai->atribuirDireita(insereRecursivo(entrada, indice, pai->pegarDireita(), atributo));

        }else{ /// se não, desce à esquerda

            pai->atribuirEsquerda(insereRecursivo(entrada, indice, pai->pegarEsquerda(), atributo));

        }

    }
    return pai;
}

/** \brief
 *  Função para imprimir todos os lexemas guardados dentro da tabela
 * \param
 * \param
 * \return
 *
 */

void TabelaSimbolos::imprime(){

    char saida[altura];
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

void TabelaSimbolos::imprimeRecursivo(char *saida, int indice, NoTrie *pai){

    if(pai != NULL){

        if(pai->pegarChave()){

            saida[indice] = pai->pegarCaractere();
            saida[indice + 1] = '\0';
            printf("[%s]", saida);

        }
        imprimeRecursivo(saida,indice, pai->pegarDireita());
        imprimeRecursivo(saida,indice, pai->pegarEsquerda());
        saida[indice] = pai->pegarCaractere();
        imprimeRecursivo(saida,indice + 1, pai->pegarMeio());

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

Atributo* TabelaSimbolos::busca(char *entrada){

    return buscaRecursivo(entrada, 0, raiz);

}
/** \brief
 *  Função recursiva auxiliar que percorre a trie
 * \param
 *  entrada: lexema a ser buscado
 *  indice: indice da string de entrada que será analisado
 *  pai: no da trie a ser analisado
 * \param
 * \return
 *  Atributo associado ao lexema buscado
 */

Atributo* TabelaSimbolos::buscaRecursivo(char *entrada, int indice, NoTrie *pai){

    if(pai != NULL){

        if(entrada[indice + 1] == '\0'){ /// se terminou de verificar a string

            if(pai->pegarCaractere() == entrada[indice]){ /// e o caractere do nó casa com o caractere buscado

                if(pai->pegarChave()){ /// e esse nó é uma chave, entao encontramos o lexema

                    return pai->pegarAtributo();

                }

            }

        }else{

            if(pai->pegarCaractere() == entrada[indice]){/// caso não estejamos no fim da string e o caractere buscado casa com o que está armazenado no nó, desce um nível no meio

                return buscaRecursivo(entrada, indice + 1, pai->pegarMeio());

            }else if(entrada[indice] > pai->pegarCaractere()){ /// caso o caractere seja maior, desce à direita

                return buscaRecursivo(entrada, indice, pai->pegarDireita());

            }else{ /// se não, desce à esquerda

                return buscaRecursivo(entrada, indice, pai->pegarEsquerda());

            }

        }
    }
    return NULL;

}
TabelaSimbolos::~TabelaSimbolos()
{
    if(raiz != NULL){

        delete raiz;

    }
}
