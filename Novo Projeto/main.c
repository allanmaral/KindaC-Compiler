#include <stdio.h>
#include <string.h>
#include "ASA.h"
#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"
#include "GerenciadorErro.h"
#include "VisitanteImpressao.h"

/** \brief Destrói objetos alocados durante a execução do programa
 *  Função chamada na saida do programa
 */
void finalizaPrograma();

/** \brief Ponto de entrada do programa
 */
int main(int argc, char** args){
    FILE* arquivo = stdin;
    if ( argc == 2 ) {
        char caminhoArquivo[strlen(args[1])+5];
        strcpy(caminhoArquivo, args[1]);
        // Se não tiver a extenção .cpm, adicione
        if(strstr(caminhoArquivo, ".cpm") == NULL ){
            strcat(caminhoArquivo, ".cpm");
        }
        arquivo = fopen(caminhoArquivo, "r");
        if(!arquivo){
            fprintf(stderr, "Arquivo invalido!");
            exit(1);
        }
    } else if( argc > 2){
               fprintf(stderr, "Argumento invalido!\nExemplo de uso:\n\tKindaC teste.cpm\n\tKindaC teste\n\tKindaC\n");
               exit(1);
           }

    // Função chamada na saída do programa, garante que memória será desalocada
    atexit(finalizaPrograma);
    inicializaGerenciadorErro();
    iniciaAnalisadorLexico(arquivo);
    NoPrograma* programa = Programa();
    // Imprime a ASA
    VisitanteImpressao vp;
    vp.visita(programa);
    imprimeListaErros();
    delete programa; // Destroi a ASA
    return 0;
}

/** \brief Destrói objetos alocados durante a execução do programa
 */
void finalizaPrograma(){
    imprimeListaErros();
    destruirAnalizadorLexico();
    destruirGerenciadorErro();
}

