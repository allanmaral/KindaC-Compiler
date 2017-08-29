#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "Atributo.h"
#include "TabelaSimbolos.h"

Automato* automato;
LeitorArquivo* leitor;

/** \brief Construtor do analisador lexico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(char *caminho){
    automato = (Automato*)malloc(sizeof(Automato));
    automato->lexema = (char*) malloc(32);
    automato->posicaoLexema = 0;
    automato->tamLexema     = 32;

    leitor = (LeitorArquivo*)malloc(sizeof(LeitorArquivo));
    int i = inicializarLeitor(leitor, caminho, 4096);
    if(i == 0) exit(1);
}

 /** \brief Função que obtem um caractere do leitor e incrementa uma coluna no automato
  *
  *  \return caractere obtido
  */
char pegarProximoCaractere(){
    automato->coluna++;
    return proximoCaractere(leitor);
}

/** \brief Procedimento que adiciona um caractere ao vetor de caracters (lexema)
  *
  *  \param caractere a ser adicionado
  */
void incrementaLexema(char caractere){
    //Verifica se nao existe posicao disponivel realocando caso necessario
    if(automato->posicaoLexema >= automato->tamLexema -1){
        automato->tamLexema += 32;
        automato->lexema=(char *)realloc(automato->lexema, automato->tamLexema);

    }
    //Adiciona o caractere
    automato->lexema[automato->posicaoLexema] = caractere;
    automato->posicaoLexema++;
    //Garante que o lexema sempre termine com \0
    automato->lexema[automato->posicaoLexema] = '\0';
}

/** \brief Funcao que define as transicoes do automato
  *
  */
int proximoToken(){
    automato->posicaoLexema = 0;
    int pronto = 1; automato->estado = 1;
    char caractere = pegarProximoCaractere();
    while(pronto != 0){
        switch ( automato->estado ){
            case 1 :
                if(isspace(caractere)){
                    if(caractere == '\n'){
                        automato->coluna = 0;
                        caractere = pegarProximoCaractere();
                        automato->linha++;
                    }
                    else{ caractere = pegarProximoCaractere(); }
                }
                else if(isalpha(caractere)){
                    automato->estado = 2;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(isdigit(caractere)){
                    automato->estado = 3;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    switch(caractere){
                        case '.':
                            automato->estado = 4;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '\'':
                            automato->estado = 9;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '"':
                            automato->estado = 12;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '/':
                            automato->estado = 14;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '|':
                            automato->estado = 18;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '&':
                            automato->estado = 19;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '-':
                            automato->estado = 20;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '=':
                            automato->estado = 21;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '<':
                            automato->estado = 22;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '>':
                            automato->estado = 23;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;
                        case '!':
                            automato->estado = 24;
                            incrementaLexema(caractere);
                            caractere = pegarProximoCaractere();
                        break;

                        case ';' : return PONTO_VIRGULA; break;
                        case ':' : return DOIS_PONTOS;   break;
                        case ',' : return VIRGULA;       break;
                        case '[' : return COLCHETE_ESQ;  break;
                        case ']' : return COLCHETE_DIR;  break;
                        case '(' : return PARENTESE_ESQ; break;
                        case ')' : return PARENTESE_DIR; break;
                        case '{' : return CHAVE_ESQ;     break;
                        case '}' : return CHAVE_DIR;     break;
                        case '+' : return ADICAO;        break;
                        case '%' : return PORCENTO;      break;
                        case '*' : return ASTERISCO;     break;
                        case '\0': return EOF;           break;

                        default:
                            saidaErro(ErroCaractereInvalido, automato->linha, automato->coluna);
                            return ERRO;
                    }
                }
            break;
            case 2 :
                if(isalnum(caractere)){
                    automato->estado = 2;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    Atributo *auxiliar = buscaTabela(TABELA_RESERVADA, automato->lexema);
                    if(auxiliar != NULL){ return auxiliar->pegarToken(); }
                    else{
                        auxiliar = (Atributo*)malloc(sizeof(Atributo));
                        auxiliar->atribuirToken(LITERAL);
                        insereTabela(TABELA_ID, automato->lexema, auxiliar);
                        return ID;
                    }
                }
            break;
            case 3 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '.'){
                    automato->estado = 5;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    automato->estado = 6;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
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
                if(isdigit(caractere)){
                    automato->estado = 5;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    automato->estado = 6;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{ return PONTO; }
            break;
            case 5 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    automato->estado = 6;
                    caractere = pegarProximoCaractere();
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
                if(isdigit(caractere)){
                    automato->estado = 7;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '+' || caractere == '-'){
                    automato->estado = 8;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    saidaErro(ErroNumeroMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 7 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_REAL);
                    insereTabela(TABELA_REAL, automato->lexema, auxiliar);
                    return NUM_REAL;
                }
            break;
            case 8 :
                if(isdigit(caractere)){
                    automato->estado = 7;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    saidaErro(ErroNumeroMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 9 :
                if(caractere == '\''){
                    saidaErro(ErroCaractereVazio, automato->linha, automato->coluna);
                    incrementaLexema(caractere);
                    return ERRO;
                }
                else if(caractere == '\0'){
                    saidaErro(ErroFaltaAspaSimples, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(caractere == '\\'){
                    automato->estado = 10;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else{
                    automato->estado = 11;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
            break;
            case 10 :
                if(caractere == '\0'){
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    automato->estado = 11;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
            break;
            case 11 :
                if(caractere == '\''){
                    incrementaLexema(caractere);
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    insereTabela(TABELA_LITERAL, automato->lexema, auxiliar);
                    return LITERAL;
                }
                else if(caractere == '\0'){
                    saidaErro(ErroFaltaAspaSimples, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 12 :
                if(caractere == '\\'){
                    automato->estado = 13;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '\0'){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(caractere == '"'){
                    incrementaLexema(caractere);
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    insereTabela(TABELA_LITERAL, automato->lexema, auxiliar);
                    return LITERAL;
                }
                else{
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
            break;
            case 13 :
                if(caractere == '\0'){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    automato->estado = 12;
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                }
            break;
            case 14 :
                if(caractere == '\\'){
                    automato->estado = 15;
                    automato->posicaoLexema = 0;
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '*'){
                    automato->estado = 16;
                    automato->posicaoLexema = 0;
                    caractere = pegarProximoCaractere();
                }
                else{ return DIVISAO; }
            break;
            case 15 :
                if(caractere == '\0'){
                    return EOF;
                }
                else if(caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    caractere = pegarProximoCaractere();
                    automato->estado = 1;
                }
                else{ caractere = pegarProximoCaractere(); }
            break;
            case 16 :
                if(caractere == '*'){
                    automato->estado = 17;
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '\0'){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else{ caractere = pegarProximoCaractere(); }
            break;
            case 17 :
                if(caractere == '*'){ caractere = pegarProximoCaractere(); }
                else if(caractere == '\0'){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(caractere == '/'){
                    automato->estado = 1;
                    caractere = pegarProximoCaractere();
                }
                else if(caractere == '\n'){
                    automato->estado = 16;
                    automato->linha++;
                    automato->coluna = 0;
                    caractere = pegarProximoCaractere();
                }
                else{
                    automato->estado = 16;
                    caractere = pegarProximoCaractere();
                }
            break;
            case 18 :
                if(caractere == '|'){
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                    return OU_CC;
                }
                else{ return OU; }
            break;
            case 19 :
                if(caractere == '|'){
                    incrementaLexema(caractere);
                    caractere = pegarProximoCaractere();
                    return E;
                }
                else{ return E_COMERCIAL; }
            break;
            case 20 :
                if(caractere == '>'){
                    incrementaLexema(caractere);
                    return PONTEIRO;
                }
                else{ return SUBTRACAO; }
            break;
            case 21 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    return COMPARACAO;
                }
                else{ return ATRIBUICAO; }
            break;
            case 22 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    return MENOR_IGUAL;
                }
                else{ return MENOR; }
            break;
            case 23 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    return MAIOR_IGUAL;
                }
                else{ return MAIOR; }
            break;
            case 24 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    return DIFERENTE;
                }
                else{ return NEGACAO; }
            break;
        }
    }
        return 0;
}

/** \brief Destrutor do Analizador Lexico
  *
  */
void desalocaParametrosAnalizadorLex(){
    destruirLeitor(leitor);
    free(automato->lexema);
    free(automato);
}
