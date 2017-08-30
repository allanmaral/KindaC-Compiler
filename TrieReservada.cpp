#include "TrieReservada.h"

TrieReservada::TrieReservada():Trie(){
    raiz = new No_Trie();
    altura = 0;
    inicializarReservada();
}
void TrieReservada::imprimeLexema(char* saida, Atributo *atr){
    int tam = calcularTamanhoLexema(saida);
    tam = 26 - tam;
    fprintf(stdout,"%s", saida);
    while(tam > 1){
        fprintf(stdout," ");
        tam--;
    }
    fprintf(stdout," %i\n", atr->pegarToken());
}
void TrieReservada::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"     TABELA DE PALAVRAS RESERVADAS     \n");
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"LEXEMA                   Token numerico\n");
}
void TrieReservada::inicializarReservada(){
    Atributo* auxiliar;
    auxiliar = new Atributo(); auxiliar->atribuirToken(DEFINICAO_TIPO); insere("typedef", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESTRUTURA);      insere("struct", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CLASSE);         insere("class", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PUBLICO);        insere("public", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PRIVADO);        insere("private", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(INTEIRO);        insere("int", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(REAL);           insere("float", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(BOLEANO);        insere("bool", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CARACTERE);      insere("char", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(SE);             insere("if", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(SENAO);          insere("else", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ENQUANTO);       insere("while", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESCOLHA);        insere("switch", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(DESVIA);         insere("break", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(IMPRIME);        insere("print", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(LE_LINHA);       insere("readln", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(RETORNA);        insere("return", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(LANCA);          insere("throw", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(TENTA);          insere("try", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PEGA);           insere("catch", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CASO);           insere("case", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(NOVO);           insere("new", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(VERDADEIRO);     insere("true", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(FALSO);          insere("false", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESSE);           insere("this", auxiliar);
}
TrieReservada::~TrieReservada() { }
