#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFINICAO_TIPO   1
#define ESTRUTURA        2
#define CLASSE           3
#define PUBLICO          4
#define PRIVATE          5
#define INTEIRO          6
#define REAL             7
#define BOLEANO          8
#define CARACTERE        9
#define SE              10
#define ENTAO           11
#define ENQUANTO        12
#define DESVIA          13
#define IMPRIME         14
#define LE_LINHA        15
#define RETORNA         16
#define LANCA           17
#define TENTA           18
#define PEGA            19
#define CASO            20
#define NOVO            21
#define VERDADEIRO      22
#define FALSO           23
#define ESSE            24
#define IF              25
#define COLCHETE_ESQ    26
#define COLCHETE_DIR    27
#define CHAVE_ESQ       28
#define CHAVE_DIR       29
#define PARENTESE_ESQ   30
#define PARENTESE_DIR   31
#define MAIOR           32
#define MENOR           33
#define MAIOR_IGUAL     34
#define MENOR_IGUAL     35
#define COMPARACAO      36
#define ATRIBUICAO      37
#define ADICAO          38
#define SUBTRACAO       49
#define DIVISAO         40
#define ASTERISCO       41
#define OU              42
#define PONTO           43
#define DOIS_PONTOS     44
#define PONTO_VIRGULA   45
#define PONTEIRO        46
#define E_COMERCIAL     47
#define E               48
#define DIFERENTE       59
#define PORCENTO        50
#define OU_CC           51
#define NUM_INTEIRO     52
#define LITERAL         53
#define NEGACAO         54
#define VIRGULA         55
//#define EOF           56

typedef struct Analizador_Lexico{
    char *nomeArquivo;//atributo do leitor
    char *lexema;
    int estado;
    int posicaoLexema;
    int tamLexema;
    int linha;
    int coluna;

} Analisador;

void iniciaAnalisadorLexico(char *arquivo);
int a();
void leCaractere(char c);
void incrementaLexema(char caractere);
void desalocaParametrosAnalizadorLex();
