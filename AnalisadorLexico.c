#include "AnalisadorLexico.h"


Automato* automato;
LeitorArquivo* leitor;

/** \brief Construtor do analisador lexico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(char *caminho){
    automato=malloc(sizeof(Automato));
    automato->lexema = (char*) malloc(32);
    automato->posicaoLexema =0;
    automato->tamLexema     =32;

    leitor=malloc(sizeof(LeitorArquivo));
    if(!inicializarLeitor(leitor,caminho,32)){


       exit(1);
    }
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
int a(){
    int lexema;
    char caractere; //= leitor->ultimoCaractereLido();    ///Arrumar
    ///Arrumar Acumulador de Lexema
    int estado = 1;     int pronto = 1;
    while(pronto != 0){
        switch ( estado ){
            case 1 :
                if(isspace(caractere)){
                    if(caractere == '\n'){
                        ///Não Incrementar Lexema
                        caractere = proximoCaractere(leitor);
                        automato->coluna=0;
                        automato->linha++;
                    }
                    else{
                        ///Não Incrementar Lexema
                        caractere = proximoCaractere(leitor);
                        automato->coluna++;
                    }
                }
                else if(isalpha(caractere)){
                    estado = 2;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(isdigit(caractere)){
                    estado = 3;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    switch(caractere){
                        case '.':
                            estado = 4;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '\'':
                            estado = 9;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '"':
                            estado = 12;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '/':
                            estado = 14;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '\0':
                            return EOF;
                        break;
                        case '|':
                            estado = 18;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '&':
                            estado = 19;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '-':
                            estado = 20;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '=':
                            estado = 21;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '<':
                            estado = 22;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '>':
                            estado = 23;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;
                        case '!':
                            estado = 24;
                            incrementaLexema(caractere);
                            caractere = proximoCaractere(leitor);
                        break;

                        case ';': return PONTO_VIRGULA; break;
                        case ':': return DOIS_PONTOS;   break;
                        case ',': return VIRGULA;       break;
                        case '[': return COLCHETE_ESQ;  break;
                        case ']': return COLCHETE_DIR;  break;
                        case '(': return PARENTESE_ESQ; break;
                        case ')': return PARENTESE_DIR; break;
                        case '{': return CHAVE_ESQ;     break;
                        case '}': return CHAVE_DIR;     break;
                        case '+': return ADICAO;        break;
                        case '%': return PORCENTO;      break;
                        case '*': return ASTERISCO;     break;

                        default:
                            printf("Erro: Caractere Inválido");         ///Acrescentar Linha e Coluna
                            return -1;                                  ///Arrumar o Retorno
                        break;
                    }
                }
            break;
            case 2 :
                if(isalnum(caractere)){
                    estado = 2;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    ///Verificar na tabela de tokens reservados
                    ///Verificar na tabela de ids ou adicionar
                    return lexema;
                }
            break;
            case 3 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '.'){
                    estado = 5;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar INTEIRO
                }
            break;
            case 4 :
                if(isdigit(caractere)){
                    estado = 5;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{ return PONTO; }
            break;
            case 5 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    caractere = proximoCaractere(leitor);
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar REAL
                }
            break;
            case 6 :
                if(isdigit(caractere)){
                    estado = 7;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '+' || caractere == '-'){
                    estado = 8;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    printf("Erro: Numero Mal Formado");             ///Acrescentar Linha e Coluna
                    return -1;                                      ///Arrumar o Retorno
                }
            break;
            case 7 :
                if(isdigit(caractere)){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar Real
                }
            break;
            case 8 :
                if(isdigit(caractere)){
                    estado = 7;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    printf("Erro: Numero Mal Formado");             ///Acrescentar Linha e Coluna
                    return -1;                                      ///Arrumar o Retorno
                }
            break;
            case 9 :
                if(caractere == '\''){
                    printf("Erro: Caractere Vazio");                ///Acrescentar Linha e Coluna
                    return -1;                                      ///Arrumar o Retorno
                }
                else if(caractere == '\0'){
                    printf("Erro: Faltando Caractere ' de terminacao");    ///Acrescentar Linha e Coluna
                    return EOF;
                }
                else if(caractere == '\\'){
                    estado = 10;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else{
                    estado = 11;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 10 :
                if(caractere == '\0'){
                    printf("Erro: Faltando Caractere ' de terminacao");     ///Acrescentar Linha e Coluna
                    return EOF;
                }
                else{
                    estado = 11;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 11 :
                if(caractere == '\''){
                    incrementaLexema(caractere);
                    ///Verificar na tabela de ids ou adicionar
                    return lexema;      ///Arrumar o retorno
                }
                else{
                    //printf("Warrning: Caractere Mal Formado");        ///Acrescentar Linha e Coluna
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return -1;                                          /// Arrumar Reotorno
                }
            break;
            case 12 :
                if(caractere == '\\'){
                    estado = 13;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '\0'){
                    printf("Erro: Faltando Caractere \" de terminação");    ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else if(caractere == '"'){                                  ///Acrescentar Linha e Coluna
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    ///Verificar na tabela de literais ou adicionar
                    return lexema;
                }
                else{
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 13 :
                if(caractere == '\0'){
                    printf("Erro: Faltando Caractere \" de terminação");    ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else{
                    estado = 12;
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 14 :
                if(caractere == '\\'){
                    estado = 15;
                    ///Resetar Lexema
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '*'){
                    estado = 16;
                    ///Resetar Lexema
                    caractere = proximoCaractere(leitor);
                }
                else{ return DIVISAO; }
            break;
            case 15 :
                if(caractere == '\0'){
                    printf("Erro: Final de Arquivo Inexperado");    ///Acrescentar Linha e Coluna
                    return EOF;                                      ///Arrumar o Retorno
                }
                else if(caractere == '\n'){
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                    estado = 1;
                }
                else{
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 16 :
                if(caractere == '*'){
                    estado = 17;
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '\0'){
                    printf("Erro: Bloco de Cometario Nao Terminado");       ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else{
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 17 :
                if(caractere == '*'){
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
                else if(caractere == '\0'){
                    printf("Erro: Bloco de Cometario Nao Terminado");       ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else if(caractere == '/'){
                    estado = 1;
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
                else{
                    estado = 16;
                    ///Não Incrementar Lexema
                    caractere = proximoCaractere(leitor);
                }
            break;
            case 18 :
                if(caractere == '|'){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return OU_CC;
                }
                else{ return OU; }
            break;
            case 19 :
                if(caractere == '|'){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return E;
                }
                else{ return E_COMERCIAL; }
            break;
            case 20 :
                if(caractere == '>'){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return PONTEIRO;
                }
                else{ return SUBTRACAO; }
            break;
            case 21 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return COMPARACAO;
                }
                else{ return ATRIBUICAO; }
            break;
            case 22 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return MENOR_IGUAL;
                }
                else{ return MENOR; }
            break;
            case 23 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
                    return MAIOR_IGUAL;
                }
                else{ return MAIOR; }
            break;
            case 24 :
                if(caractere == '='){
                    incrementaLexema(caractere);
                    caractere = proximoCaractere(leitor);
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
