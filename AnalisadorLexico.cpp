#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "Atributo.h"
#include "TabelaSimbolos.h"
#include "Leitor.h"

Automato* automato;
LeitorArquivo* leitor;

/** \brief Função que obtem um caractere do leitor e incrementa uma coluna no automato
  *
  *  \return caractere obtido
  */
char pegarProximoCaractere(){
    printf("pegar Proximo caractere\n");
    automato->coluna++;
    printf("Somou uma coluna\n");
    printf("Chamou funcao do leitor proximoCaractere\n");
    return proximoCaractere(leitor);
}

/** \brief Construtor do analisador lexico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
 void iniciaAnalisadorLexico(char *caminho){
    printf("Inicialisa analizador\n");
    automato = (Automato*)malloc(sizeof(Automato));
    automato->lexema = (char*) malloc(32);
    automato->posicaoLexema = 0;
    automato->tamLexema     = 32;
    leitor = (LeitorArquivo*) malloc(sizeof(LeitorArquivo));
    int res = inicializarLeitor(leitor, caminho, 4096);
    if(res == ARQUIVO_INVALIDO){
        saidaErro(ErroArquivoInvalido, 0, 0);
        exit(1);
    }
    printf("Arquivo aberto com sucesso\n");
    automato->caractere = pegarProximoCaractere();
    printf("iniciou Corretamente\n");
}

/** \brief Procedimento que adiciona um caractere ao vetor de caracters (lexema)
  *
  *  \param caractere a ser adicionado
  */
void incrementaLexema(){
    //Verifica se nao existe posicao disponivel realocando caso necessario
    if(automato->posicaoLexema >= automato->tamLexema -1){
        automato->tamLexema += 32;
        automato->lexema=(char *)realloc(automato->lexema, automato->tamLexema);

    }
    //Adiciona o caractere
    automato->lexema[automato->posicaoLexema] = automato->caractere;
    automato->posicaoLexema++;
    //Garante que o lexema sempre termine com \0
    automato->lexema[automato->posicaoLexema] = '\0';
    automato->caractere = pegarProximoCaractere();
}

/** \brief Funcao que define as transicoes do automato
  *
  */
int proximoToken(){
    automato->posicaoLexema = 0;
    int pronto = 1; automato->estado = 1;
    while(pronto != 0){
        switch ( automato->estado ){
            case 1 :
                if(isspace(automato->caractere)){
                    if(automato->caractere == '\n'){
                        automato->coluna = 0;
                        automato->caractere = pegarProximoCaractere();
                        automato->linha++;
                    }
                    else{ automato->caractere = pegarProximoCaractere(); }
                }
                else if(isalpha(automato->caractere)){
                    automato->estado = 2;
                    incrementaLexema();
                }
                else if(isdigit(automato->caractere)){
                    automato->estado = 3;
                    incrementaLexema();
                }
                else{
                    switch(automato->caractere){
                        case '.':
                            automato->estado = 4;
                            incrementaLexema();
                        break;
                        case '\'':
                            automato->estado = 9;
                            incrementaLexema();
                        break;
                        case '"':
                            automato->estado = 12;
                            incrementaLexema();
                        break;
                        case '/':
                            automato->estado = 14;
                            incrementaLexema();
                        break;
                        case '|':
                            automato->estado = 18;
                            incrementaLexema();
                        break;
                        case '&':
                            automato->estado = 19;
                            incrementaLexema();
                        break;
                        case '-':
                            automato->estado = 20;
                            incrementaLexema();
                        break;
                        case '=':
                            automato->estado = 21;
                            incrementaLexema();
                        break;
                        case '<':
                            automato->estado = 22;
                            incrementaLexema();
                        break;
                        case '>':
                            automato->estado = 23;
                            incrementaLexema();
                        break;
                        case '!':
                            automato->estado = 24;
                            incrementaLexema();
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
                if(isalnum(automato->caractere)){
                    automato->estado = 2;
                    incrementaLexema();
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
                if(isdigit(automato->caractere)){
                    incrementaLexema();
                }
                else if(automato->caractere == '.'){
                    automato->estado = 5;
                    incrementaLexema();
                }
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
                if(isdigit(automato->caractere)){
                    automato->estado = 5;
                    incrementaLexema();
                }
                else if(automato->caractere == 'e' || automato->caractere == 'E'){
                    automato->estado = 6;
                    incrementaLexema();
                }
                else{ return PONTO; }
            break;
            case 5 :
                if(isdigit(automato->caractere)){
                    incrementaLexema();
                }
                else if(automato->caractere == 'e' || automato->caractere == 'E'){
                    automato->estado = 6;
                    automato->caractere = pegarProximoCaractere();
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
                if(isdigit(automato->caractere)){
                    automato->estado = 7;
                    incrementaLexema();
                }
                else if(automato->caractere == '+' || automato->caractere == '-'){
                    automato->estado = 8;
                    incrementaLexema();
                }
                else{
                    saidaErro(ErroNumeroMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 7 :
                if(isdigit(automato->caractere)){ incrementaLexema(); }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_REAL);
                    insereTabela(TABELA_REAL, automato->lexema, auxiliar);
                    return NUM_REAL;
                }
            break;
            case 8 :
                if(isdigit(automato->caractere)){
                    automato->estado = 7;
                    incrementaLexema();
                }
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
                else if(automato->caractere == '\0'){
                    saidaErro(ErroFaltaAspaSimples, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(automato->caractere == '\\'){
                    automato->estado = 10;
                    incrementaLexema();
                }
                else{
                    automato->estado = 11;
                    incrementaLexema();
                }
            break;
            case 10 :
                if(automato->caractere == '\0'){
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    automato->estado = 11;
                    incrementaLexema();
                }
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
                else if(automato->caractere == '\0'){
                    saidaErro(ErroFaltaAspaSimples, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    saidaErro(ErroCaractereMalFormado, automato->linha, automato->coluna);
                    return ERRO;
                }
            break;
            case 12 :
                if(automato->caractere == '\\'){
                    automato->estado = 13;
                    incrementaLexema();
                }
                else if(automato->caractere == '\0'){
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
                else{
                    incrementaLexema();
                }
            break;
            case 13 :
                if(automato->caractere == '\0'){
                    saidaErro(ErroFaltaAspasDupla, automato->linha, automato->coluna);
                    return EOF;
                }
                else{
                    automato->estado = 12;
                    incrementaLexema();
                }
            break;
            case 14 :
                if(automato->caractere == '\\'){
                    automato->estado = 15;
                    automato->posicaoLexema = 0;
                    automato->caractere = pegarProximoCaractere();
                }
                else if(automato->caractere == '*'){
                    automato->estado = 16;
                    automato->posicaoLexema = 0;
                    automato->caractere = pegarProximoCaractere();
                }
                else{ return DIVISAO; }
            break;
            case 15 :
                if(automato->caractere == '\0'){
                    return EOF;
                }
                else if(automato->caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    automato->caractere = pegarProximoCaractere();
                    automato->estado = 1;
                }
                else{ automato->caractere = pegarProximoCaractere(); }
            break;
            case 16 :
                if(automato->caractere == '*'){
                    automato->estado = 17;
                    automato->caractere = pegarProximoCaractere();
                }
                else if(automato->caractere == '\n'){
                    automato->linha++;
                    automato->coluna = 0;
                    automato->caractere = pegarProximoCaractere();
                }
                else if(automato->caractere == '\0'){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else{ automato->caractere = pegarProximoCaractere(); }
            break;
            case 17 :
                if(automato->caractere == '*'){ automato->caractere = pegarProximoCaractere(); }
                else if(automato->caractere == '\0'){
                    saidaErro(ErroComentarioNaoTerminado, automato->linha, automato->coluna);
                    return EOF;
                }
                else if(automato->caractere == '/'){
                    automato->estado = 1;
                    automato->caractere = pegarProximoCaractere();
                }
                else if(automato->caractere == '\n'){
                    automato->estado = 16;
                    automato->linha++;
                    automato->coluna = 0;
                    automato->caractere = pegarProximoCaractere();
                }
                else{
                    automato->estado = 16;
                    automato->caractere = pegarProximoCaractere();
                }
            break;
            case 18 :
                if(automato->caractere == '|'){
                    automato->caractere = pegarProximoCaractere();
                    return OU_CC;
                }
                else{
                	automato->caractere = pegarProximoCaractere();
                	return OU;
                }
            break;
            case 19 :
                if(automato->caractere == '|'){
                    automato->caractere = pegarProximoCaractere();
                    return E;
                }
                else{
                	automato->caractere = pegarProximoCaractere();
               		return E_COMERCIAL;
               	}
            break;
            case 20 :
                if(automato->caractere == '>'){
                	automato->caractere = pegarProximoCaractere();
                    return PONTEIRO;
                }
                else{
                	automato->caractere = pegarProximoCaractere();
                	return SUBTRACAO;
                }
            break;
            case 21 :
                if(automato->caractere == '='){
                    automato->caractere = pegarProximoCaractere();
                    return COMPARACAO;
                }
                else{
					automato->caractere = pegarProximoCaractere();
					return ATRIBUICAO;
				}
            break;
            case 22 :
                if(automato->caractere == '='){
                    automato->caractere = pegarProximoCaractere();
                    return MENOR_IGUAL;
                }
                else{
					automato->caractere = pegarProximoCaractere();
					return MENOR;
                }
            break;
            case 23 :
                if(automato->caractere == '='){
                    automato->caractere = pegarProximoCaractere();
                    return MAIOR_IGUAL;
                }
                else{
					automato->caractere = pegarProximoCaractere();
					return MAIOR;
	            }
            break;
            case 24 :
                if(automato->caractere == '='){
                    automato->caractere = pegarProximoCaractere();
                    return DIFERENTE;
                }
                else{
					automato->caractere = pegarProximoCaractere();
					return NEGACAO;
				}
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
