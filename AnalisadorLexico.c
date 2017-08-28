#include "AnalisadorLexico.h"

Analisador* automato;

void iniciaAnalisadorLexico(char *arquivo){
    automato=malloc(sizeof(Analisador));
    automato->lexema = (char*)malloc(32);
    automato->nomeArquivo   = arquivo;// inicializar o leitor
    automato->posicaoLexema =0;
    automato->tamLexema     =32;

}

void incrementaLexema(char caractere){
    if(automato->posicaoLexema >= automato->tamLexema){
        automato->tamLexema += 32;
        automato->lexema=(char *)realloc(automato->lexema, automato->tamLexema);

    }
    automato->lexema[automato->posicaoLexema] = caractere;
    automato->posicaoLexema++;
}

int a(){

    char caractere; //= leitor->ultimoCaractereLido();    ///Arrumar
    ///Arrumar Acumulador de Lexema
    int estado = 1;     int pronto = 1;
    while(pronto != 0){
        switch ( estado ){
            case 1 :
                if(isspace(caractere)){
                    if(caractere == '\n'){
                        ///Não Incrementar Lexema
                        caractere = leitor->proximoCaractere();
                        ///Zera Coluna
                        ///Incrementa Linha
                    }
                    else{
                        ///Não Incrementar Lexema
                        caractere = leitor->proximoCaractere();
                        ///Incrementa Coluna
                    }
                }
                else if(isalpha(caractere)){
                    estado = 2;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(isdigit(caractere)){
                    estado = 3;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    switch(caractere){
                        case '.':
                            estado = 4;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '\'':
                            estado = 9;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '"':
                            estado = 12;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '/':
                            estado = 14;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case EOF:
                            return EOF;
                        break;
                        case '|':
                            estado = 18;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '&':
                            estado = 19;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '-':
                            estado = 20;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '=':
                            estado = 21;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '<':
                            estado = 22;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '>':
                            estado = 23;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
                        break;
                        case '!':
                            estado = 24;
                            ///Incrementar Lexema
                            caractere = leitor->proximoCaractere();
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
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    ///Verificar na tabela de tokens reservados
                    ///Verificar na tabela de ids ou adicionar
                    return lexema;
                }
            break;
            case 3 :
                if(isdigit(caractere)){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == '.'){
                    estado = 5;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar INTEIRO
                }
            break;
            case 4 :
                if(isdigit(caractere)){
                    estado = 5;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{ return PONTO; }
            break;
            case 5 :
                if(isdigit(caractere)){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == 'e' || caractere == 'E'){
                    estado = 6;
                    caractere = leitor->proximoCaractere();
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar REAL
                }
            break;
            case 6 :
                if(isdigit(caractere)){
                    estado = 7;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == '+' || caractere == '-'){
                    estado = 8;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    printf("Erro: Numero Mal Formado");             ///Acrescentar Linha e Coluna
                    return -1;                                      ///Arrumar o Retorno
                }
            break;
            case 7 :
                if(isdigit(caractere)){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    ///Verificar na tabela de numeros ou adicionar
                    return lexema;  ///Salvar Real
                }
            break;
            case 8 :
                if(isdigit(caractere)){
                    estado = 7;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
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
                else if(caractere == EOF){
                    printf("Erro: Faltando Caractere ' de terminacao");    ///Acrescentar Linha e Coluna
                    return EOF;
                }
                else if(caracter == '\\'){
                    estado = 10;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    estado = 11;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 10 :
                if(caractere == EOF){
                    printf("Erro: Faltando Caractere ' de terminacao");     ///Acrescentar Linha e Coluna
                    return EOF;
                }
                else{
                    estado = 11;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 11 :
                if(caractere == '\''){
                    ///Incrementar Lexema
                    ///Verificar na tabela de ids ou adicionar
                    return lexema;      ///Arrumar o retorno
                }
                else{
                    //printf("Warrning: Caractere Mal Formado");        ///Acrescentar Linha e Coluna
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return -1;                                          /// Arrumar Reotorno
                }
            break;
            case 12 :
                if(caractere == '\\'){
                    estado = 13;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == EOF){
                    printf("Erro: Faltando Caractere \" de terminação");    ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else if(caractere == '"'){                                  ///Acrescentar Linha e Coluna
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    ///Verificar na tabela de literais ou adicionar
                    return lexema;
                }
                else{
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 13 :
                if(caractere == EOF){
                    printf("Erro: Faltando Caractere \" de terminação");    ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else{
                    estado = 12;
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 14 :
                if(caractere == '\\'){
                    estado = 15;
                    ///Resetar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == '*'){
                    estado = 16;
                    ///Resetar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{ return DIVISAO; }
            break;
            case 15 :
                if(caractere == EOF){
                    printf("Erro: Final de Arquivo Inexperado");    ///Acrescentar Linha e Coluna
                    return EOF;                                      ///Arrumar o Retorno
                }
                else if(caractere == '\n'){
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    estado = 1;
                }
                else{
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 16 :
                if(caractere == '*'){
                    estado = 17;
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == EOF){
                    printf("Erro: Bloco de Cometario Nao Terminado");       ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else{
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 17 :
                if(caractere == '*'){
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else if(caractere == EOF){
                    printf("Erro: Bloco de Cometario Nao Terminado");       ///Acrescentar Linha e Coluna
                    return EOF;                                             ///Arrumar o Retorno
                }
                else if(caractere == '/'){
                    estado = 1;
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
                else{
                    estado = 16;
                    ///Não Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                }
            break;
            case 18 :
                if(caractere == '|'){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return OU_CC;
                }
                else{ return OU; }
            break;
            case 19 :
                if(caractere == '|'){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return E;
                }
                else{ return E_COMERCIAL; }
            break;
            case 20 :
                if(caractere == '>'){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return PONTEIRO;
                }
                else{ return SUBTRACAO; }
            break;
            case 21 :
                if(caractere == '='){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return COMPARACAO;
                }
                else{ return ATRIBUICAO; }
            break;
            case 22 :
                if(caractere == '='){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return MENOR_IGUAL;
                }
                else{ return MENOR; }
            break;
            case 23 :
                if(caractere == '='){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return MAIOR_IGUAL;
                }
                else{ return MAIOR; }
            break;
            case 24 :
                if(caractere == '='){
                    ///Incrementar Lexema
                    caractere = leitor->proximoCaractere();
                    return DIFERENTE;
                }
                else{ return NEGACAO; }
            break;
        }
    }
}

void desalocaParametrosAnalizadorLex(){
    free(automato->lexema);
    free(automato->nomeArquivo);
    free(automato);
}
