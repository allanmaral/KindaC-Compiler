#include <stdio.h>
#include <string.h>
#include "ASA.h"
#include "AnalisadorLexico.h"
#include "AnalisadorSintatico.h"
#include "GerenciadorErro.h"
#include "Visitante.h"
#include "AnalisadorSemantico.h"
#include "VisitanteRI.h"
#include "CanonizadorRI.h"
#include "Gerador.h"

/** \brief Destrói objetos alocados durante a execução do programa
 *  Função chamada na saida do programa
 */
void finalizaPrograma();

/** \brief Ponto de entrada do programa
 */
int main(int argc, char** args){
    FILE* arquivo = stdin;
    FILE* arqAss  = stdout;
    if ( argc == 2| argc == 3 ) {
        char caminhoArquivo[strlen(args[1])+5];
        char *caminhoSaida;
        if(argc==2){
            caminhoSaida=(char*)malloc(sizeof(char) * (strlen(args[1])+5));
        }else{
            caminhoSaida=(char*)malloc(sizeof(char) * (strlen(args[2])+5));
            strcpy(caminhoSaida, args[2]);
        }
        strcpy(caminhoArquivo, args[1]);
        // Se não tiver a extenção .cpm, adicione
        if(strstr(caminhoArquivo, ".cpm") == NULL ){
            if(argc==2){
                strcpy(caminhoSaida, caminhoArquivo);
                strcat(caminhoSaida, ".asm");
            }
            strcat(caminhoArquivo, ".cpm");
        }else{
            if(argc==2){
                for(int i = 0;i<(strlen(args[1])-4);i++){
                    caminhoSaida[i]=caminhoArquivo[i];
                }
                strcat(caminhoSaida, ".asm");
            }
         }
        if(strstr(caminhoSaida, ".asm") == NULL ){
             strcat(caminhoSaida, ".asm");
        }
        arquivo = fopen(caminhoArquivo, "r");
        arqAss  = fopen(caminhoSaida,"w+");
        free(caminhoSaida);
        if(!arquivo){
            fprintf(stderr, "Arquivo invalido!");
            exit(1);
        }
    } else if( argc > 3){
               fprintf(stderr, "Argumento invalido!\n");
               fprintf(stderr, "Exemplos de uso:\n\tKindaC\n\tKindaC <arquivo_entrada>\n\tKindaC <arquivo_entrada> <arquivo_saida>\n");
               exit(1);
           }

    // Função chamada na saída do programa, garante que memória será desalocada
    atexit(finalizaPrograma);
    inicializaGerenciadorErro();
    iniciaAnalisadorLexico(arquivo);
    NoPrograma* programa = Programa();
    // Imprime a ASA
    //VisitanteImpressao vp;
    //vp.visita(programa);
    // Semantico
    AnalisadorSemantico as;
    as.visita(programa);
    VisitanteTradutor vt;
    vt.visita(programa);
    VisitanteImpressaoRI vtri;
    vtri.visita(vt.pegarFragmento());

    fprintf(stdout, "#####################Canonizador ###########################\n");

    CanonizadorRI canRI;
    canRI.visita(vt.pegarFragmento());
    vtri.visita(vt.pegarFragmento());

    Gerador *ger = new Gerador(arqAss);
    ger->visita(vt.pegarFragmento());
    delete ger;

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

