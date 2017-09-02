#include <stdio.h>
#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "Atributo.h"
#include "TabelaSimbolos.h"
#include "Leitor.h"

Automato* automato;

/** \brief Função que atualiza o caractere do leitor e aumenta uma coluna
  *
  */
void pegarProximoCaractere(){
    automato->coluna++;
    automato->caractere = lerProximoCaractere();
}
char* pegarLexema(){ return automato->lexema ; }

/** \brief Construtor do analisador léxico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(char *caminho){
    automato = (Automato*)malloc(sizeof(Automato));
    automato->lexema = (char*) malloc(TAMANHO_LEXEMA*(sizeof(char)));
    automato->posicaoLexema = 0;
    automato->tamLexema     = TAMANHO_LEXEMA;
    automato->linha         = 1;
    automato->coluna        = 0;
    int res = inicializarLeitor(caminho);
    if(res == ARQUIVO_INVALIDO){
        saidaErro(ErroArquivoInvalido, 0, 0);
        exit(1);
    }
    pegarProximoCaractere();
}

/** \brief Procedimento que adiciona o caractere atual
  *       do autômato ao seu vetor de caracteres (lexema)
  */
void incrementaLexema(){
    //Verifica se não existe posição disponível realocando caso necessário
    if(automato->posicaoLexema >= automato->tamLexema -1){
        automato->tamLexema += TAMANHO_LEXEMA;
        automato->lexema=(char *)realloc(automato->lexema, automato->tamLexema*(sizeof(char)));
    }
    //Adiciona o caractere
    automato->lexema[automato->posicaoLexema] = automato->caractere;
    automato->posicaoLexema++;
    //Garante que o lexema sempre termine com \0
    automato->lexema[automato->posicaoLexema] = '\0';
    pegarProximoCaractere();
}

/** \brief Função que define as transições do autômato
  */
int proximoToken(){
    automato->posicaoLexema = 0;
    int pronto = 1; automato->estado = 1;
    while(pronto != 0){
        switch(automato->estado){
            case 1 :
                if(isspace(automato->caractere)){
                    if(automato->caractere == '\n'){
                        automato->coluna = 0;
                        pegarProximoCaractere();
                        automato->linha++;
                    }
                    else if(automato->caractere == '\t'){
						automato->coluna += 3;
                        pegarProximoCaractere();
                    }
                    else { pegarProximoCaractere(); }
                }
                else if(isalpha(automato->caractere) || automato->caractere == '_'){
                    automato->estado = 2;
                    incrementaLexema();
                }
                else if(isdigit(automato->caractere)){
                    automato->estado = 3;
                    incrementaLexema();
                }
                else{
                    switch(automato->caractere){
                        case '.' : automato->estado =  4; incrementaLexema(); break;
                        case '\'': automato->estado =  9; incrementaLexema(); break;
                        case '"' : automato->estado = 12; incrementaLexema(); break;
                        case '/' : automato->estado = 14; incrementaLexema(); break;
                        case '|' : automato->estado = 18; incrementaLexema(); break;
                        case '&' : automato->estado = 19; incrementaLexema(); break;
                        case '-' : automato->estado = 20; incrementaLexema(); break;
                        case '=' : automato->estado = 21; incrementaLexema(); break;
                        case '<' : automato->estado = 22; incrementaLexema(); break;
                        case '>' : automato->estado = 23; incrementaLexema(); break;
                        case '!' : automato->estado = 24; incrementaLexema(); break;

                        case ';' : pegarProximoCaractere(); return PONTO_VIRGULA; break;
                        case ':' : pegarProximoCaractere(); return DOIS_PONTOS;   break;
                        case ',' : pegarProximoCaractere(); return VIRGULA;       break;
                        case '[' : pegarProximoCaractere(); return COLCHETE_ESQ;  break;
                        case ']' : pegarProximoCaractere(); return COLCHETE_DIR;  break;
                        case '(' : pegarProximoCaractere(); return PARENTESE_ESQ; break;
                        case ')' : pegarProximoCaractere(); return PARENTESE_DIR; break;
                        case '{' : pegarProximoCaractere(); return CHAVE_ESQ;     break;
                        case '}' : pegarProximoCaractere(); return CHAVE_DIR;     break;
                        case '+' : pegarProximoCaractere(); return ADICAO;        break;
                        case '%' : pegarProximoCaractere(); return PORCENTO;      break;
                        case '*' : pegarProximoCaractere(); return ASTERISCO;     break;
                        case EOF : pegarProximoCaractere(); return EOF;           break;
                        case '\0': pegarProximoCaractere(); return EOF;           break;
                        default:
                            saidaErro(ErroCaractereInvalido, automato->linha, automato->coluna);
                            pegarProximoCaractere();
                            return ERRO;
                    }
                }
            break;
            case 2 :
                if(isalnum(automato->caractere)) { incrementaLexema(); }
                else if(automato->caractere == '_') { incrementaLexema(); }
                else{
                    Atributo *auxiliar = buscaTabela(TABELA_RESERVADA, automato->lexema);
                    if(auxiliar != NULL) { return auxiliar->pegarToken(); }
                    else{
                        auxiliar = (Atributo*)malloc(sizeof(Atributo));
                        auxiliar->atribuirToken(LITERAL);
                        insereTabela(TABELA_ID, automato->lexema, auxiliar);
                        return ID;
                    }
                }
            break;
            case 3 :
                if(isdigit(automato->caractere)) { incrementaLexema(); }
                else if(automato->caractere == '.') { automato->estado = 5; incrementaLexema(); }
                else if(automato->caractere == 'e' || automato->caractere == 'E'){
                    automato->estado = 6;
                    incrementaLexema();
                }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_INTEIRO);
                    insereTabela(TABELA_INTEIRO, automato->lexema, auxiliar);
                    return NUM_INTEIRO;
                }
            break;
            case 4 :
                if(isdigit(automato->caractere)) { automato->estado = 5; incrementaLexema(); }
                else if(automato->caractere == 'e' || automato->caractere == 'E'){
                    automato->estado = 6;
                    incrementaLexema();
                }
                else { return PONTO; }
            break;
            case 5 :
                if(isdigit(automato->caractere)) { incrementaLexema(); }
                else if(automato->caractere == 'e' || automato->caractere == 'E'){
                    automato->estado = 6;
                    pegarProximoCaractere();
                }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_REAL);
                    insereTabela(TABELA_REAL, automato->lexema, auxiliar);
                    return NUM_REAL;
                }
            break;
            case 6 :
                if(isdigit(automato->caractere)) { automato->estado = 7; incrementaLexema(); }
                else if(automato->caractere == '+' || automato->caractere == '-'){
                    automato->estado = 8;
                    incrementaLexema();
                }
                else {
                    saidaErro(ErroNumeroMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 7 :
                if(isdigit(automato->caractere)) { incrementaLexema(); }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_REAL);
                    insereTabela(TABELA_REAL, automato->lexema, auxiliar);
                    return NUM_REAL;
                }
            break;
            case 8 :
                if(isdigit(automato->caractere)) { automato->estado = 7; incrementaLexema(); }
                else{
                    saidaErro(ErroNumeroMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 9 :
                if(automato->caractere == '\''){
                    saidaErro(ErroCaractereVazio, automato->linha, automato->coluna);
                    incrementaLexema();
                    return ERRO;
                }
                else if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(automato->caractere == '\\') { automato->estado = 10; incrementaLexema(); }
                else { automato->estado = 11; incrementaLexema(); }
            break;
            case 10 :
                if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return EOF;
                }
                else { automato->estado = 11; incrementaLexema(); }
            break;
            case 11 :
                if(automato->caractere == '\''){
                    incrementaLexema();
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    insereTabela(TABELA_LITERAL, automato->lexema, auxiliar);
                    return LITERAL;
                }
                else if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    saidaErro(ErroFaltaAspaSimples, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 12 :
                if(automato->caractere == '\\') { automato->estado = 13; incrementaLexema(); }
                else if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(automato->caractere == '"'){
                    incrementaLexema();
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    insereTabela(TABELA_LITERAL, automato->lexema, auxiliar);
                    return LITERAL;
                }
                else if(automato->caractere == '\n'){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return ERRO;
                }
                else { incrementaLexema(); }
            break;
            case 13 :
                if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return EOF;
                }
                else { automato->estado = 12; incrementaLexema(); }
            break;
            case 14 :
                if(automato->caractere == '/'){
                    automato->estado = 15;
                    automato->posicaoLexema = 0;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '*'){
                    automato->estado = 16;
                    automato->posicaoLexema = 0;
                    pegarProximoCaractere();
                }
                else { return DIVISAO; }
            break;
            case 15 :
                if(automato->caractere == '\0' || automato->caractere == EOF)
                { 	return EOF; }
                else if(automato->caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    pegarProximoCaractere();
                    automato->estado = 1;
                }
                else if(automato->caractere == '\t'){
                    automato->coluna += 3;
                    pegarProximoCaractere();
                }
                else { pegarProximoCaractere(); }
            break;
            case 16 :
                if(automato->caractere == '*'){
                    automato->estado = 17;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '\t'){
                    automato->coluna += 3;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else { pegarProximoCaractere(); }
            break;
            case 17 :
                if(automato->caractere == '*'){ pegarProximoCaractere(); }
                else if(automato->caractere == '\0' || automato->caractere == EOF){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(automato->caractere == '/'){
                    automato->estado = 1;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '\n'){
                    automato->estado = 16;
                    automato->linha++;
                    automato->coluna = 0;
                    pegarProximoCaractere();
                }
                else if(automato->caractere == '\t'){
                    automato->estado = 16;
                    automato->coluna += 3;
                    pegarProximoCaractere();
                }
                else { automato->estado = 16; pegarProximoCaractere(); }
            break;
            case 18 :
                if(automato->caractere == '|') { pegarProximoCaractere(); return OU_CC; }
                else { return OU; }
            break;
            case 19 :
                if(automato->caractere == '|') { pegarProximoCaractere(); return E; }
                else { return E_COMERCIAL; }
            break;
            case 20 :
                if(automato->caractere == '>') { pegarProximoCaractere(); return PONTEIRO; }
                else { return SUBTRACAO; }
            break;
            case 21 :
                if(automato->caractere == '=') { pegarProximoCaractere(); return COMPARACAO; }
                else { return ATRIBUICAO; }
            break;
            case 22 :
                if(automato->caractere == '=') { pegarProximoCaractere(); return MENOR_IGUAL; }
                else { return MENOR; }
            break;
            case 23 :
                if(automato->caractere == '=') { pegarProximoCaractere(); return MAIOR_IGUAL; }
                else { return MAIOR; }
            break;
            case 24 :
                if(automato->caractere == '=') { pegarProximoCaractere(); return DIFERENTE; }
                else { return NEGACAO; }
            break;
        }
    }
    return 0;
}

/** \brief Destrutor do Analisador Léxico
  *
  */
void destruirAnalizadorLexico() {
    if(automato->modo == MODO_ARQUIVO)
    destruirLeitor();
    free(automato->lexema); free(automato); }
