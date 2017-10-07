#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "ASA.h"

static int tokenAtual;

/** Lista de Literais dos Tokens
 */
static char tokenLiteral[62][16] = {
        "",                 "DEFINICAO_TIPO",   "ESTRUTURA",        "CLASSE",           "PUBLICO",
        "PRIVADO",          "INTEIRO",          "REAL",             "BOLEANO",          "CARACTERE",
        "SE",               "SENAO",            "ENQUANTO",         "ESCOLHA",          "DESVIA",
        "IMPRIME",          "LE_LINHA",         "RETORNA",          "LANCA",            "TENTA",
        "PEGA",             "CASO",             "NOVO",             "VERDADEIRO",       "FALSO",
        "ESSE",             "ID",               "COLCHETE_ESQ",     "COLCHETE_DIR",     "CHAVE_ESQ",
        "CHAVE_DIR",        "PARENTESE_ESQ",    "PARENTESE_DIR",    "",                 "MAIOR",
        "MENOR",            "MAIOR_IGUAL",      "MENOR_IGUAL",      "COMPARACAO",       "ATRIBUICAO",
        "ADICAO",           "SUBTRACAO",        "DIVISAO",          "ASTERISCO",        "OU",
        "PONTO",            "DOIS_PONTOS",      "PONTO_VIRGULA",    "PONTEIRO",         "E_COMERCIAL",
        "E",                "DIFERENTE",        "PORCENTO",         "OU_CC",            "NUM_INTEIRO",
        "LITERAL",          "NEGACAO",          "VIRGULA",          "NUM_REAL",         "EOF",
        "TRES_PONTOS",      "ASCII"
};

typedef enum {
    EsperadosChaveOuDoisPontos = 0,
    EsperadosDefinicaoClassTipo,
    EsperadosInicializador,
    EsperadosTamanhoEnumerador
} Esperados;

static char esperadosLiteral[EsperadosTamanhoEnumerador][32] = {
        "'{' ou ':'",       "'typedef', 'class' ou Tipo",       "inicializador"
};

void casar(int tokenEsperado){
    // Faz alguma coisa aqui
    if(tokenAtual == tokenEsperado){
        fprintf(stdout, "CASOU: %s\n", tokenLiteral[tokenEsperado]);
    } else {
        fprintf(stdout, "NAO CASOU: LIDO: \"%s\" ESPERADO: \"%s\"\n", tokenLiteral[tokenAtual], tokenLiteral[tokenEsperado]);
      }
      tokenAtual = proximoToken();
}

void pular(int sinc[]){
    int sincronizado = 0;
    // Enquanto ainda nao tiver sido sincronizado, verifica se o token atual pertence ao sinc
    while(!sincronizado) {
        int indice = -1;
        // Percorre a lista de sync
        do {
            indice++;
            if(tokenAtual == sinc[indice]) {
                fprintf(stdout, "###### Sincronizou: %s\n", tokenLiteral[sinc[indice]]);
                sincronizado = 1;
                return;
            }
        } while(sinc[indice] != TOKEN_EOF);
        // Se chegar aqui, o erro ainda nao foi sincronizado
        tokenAtual = proximoToken();
    }
}

void casarOuPular(int token, int* sinc){
    if(tokenAtual == token) {
        casar(token);
    } else {
          saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual], tokenLiteral[token]);
          pular(sinc);
      }
}


//void Programa();
void ProgramaA();       void ProgramaB();       void DeclClasse();      void DeclClasseL();
void DeclLocal();       void DeclLocalL();      void DeclLocalLL();     void DeclVar();
void ListaId();         void ListaIdCont();     void Ponteiro();        void Arranjo();
void ListaForma();      void ListaFormaCont();  void Tipo();            void TipoL();
void ListaSentenca();   void Sentenca();        void SentencaL();       void Se();
void Senao();           void BlocoCaso();       void ListaExpr();       void ListaExprCont();
void Expr();            void ExprAtrib();       void ExprOuBool();      void ExprOuBoolL();
void ExprEBool();       void ExprEBoolL();      void ExprIgualdade();   void ExprIgualdadeL();
void ExprRelacional();  void ExprRelacionalL(); void ExprSoma();        void ExprSomaL();
void ExprMultDivE();    void ExprMultDivEL();   void ExprUnaria();      void ExprAceCamp();
void ExprAceCampL();    void ExprNovo();        void ExprNovoL();       void Primario();
void PrimarioID();      void PrimarioIDL();     void PrimarioL();

void InicializarAnalizadorSintatico(){
    tokenAtual = proximoToken();
}

//static int followPrograma [] = {TOKEN_EOF};
static int sincPrograma [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, ESTRUTURA, CHAVE_ESQ,
                              PONTO_VIRGULA, PARENTESE_ESQ, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
static int firstPrograma [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
void Programa(){
    fprintf(stdout, "Programa\n");
    switch(tokenAtual){
        case DEFINICAO_TIPO:
            casar(DEFINICAO_TIPO);
            casarOuPular(ESTRUTURA, sincPrograma);
            casarOuPular(CHAVE_ESQ, sincPrograma);
            Tipo();
            ListaId();
            casarOuPular(PONTO_VIRGULA, sincPrograma);
            DeclVar();
            casarOuPular(CHAVE_DIR, sincPrograma);
            casarOuPular(ID, sincPrograma);
            casarOuPular(PONTO_VIRGULA, sincPrograma);
            Programa();
        break;
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID:
            Tipo();
            Ponteiro();
            casarOuPular(ID, sincPrograma);
            ProgramaA();
        break;
        case CLASSE:
            DeclClasse();
            Programa();
        break;
        case TOKEN_EOF:
            return; // NULL
        break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual], esperadosLiteral[EsperadosDefinicaoClassTipo]);
            pular(firstPrograma);
            return Programa();
        break;

    }
}

static int followProgramaA [] = {TOKEN_EOF};
static int sincProgramaA [] = {CHAVE_ESQ, INTEIRO, REAL, BOLEANO, CARACTERE, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, PARENTESE_ESQ, NEGACAO,
                               LITERAL, ASCII, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, ENQUANTO, ESCOLHA, DESVIA,
                               IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, DEFINICAO_TIPO, CLASSE, TOKEN_EOF};
void ProgramaA(){
    fprintf(stdout, "ProgramaA\n");
    switch(tokenAtual){
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            ListaForma();
            casarOuPular(PARENTESE_DIR, sincProgramaA);
            casarOuPular(CHAVE_ESQ, sincProgramaA);
            DeclLocalLL();
            casarOuPular(CHAVE_DIR, sincProgramaA);
            Programa();
        break;
        case COLCHETE_ESQ:
            Arranjo();
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followProgramaA);
            ProgramaB();
        break;
        case VIRGULA:
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followProgramaA);
            ProgramaB();
        break;
        case PONTO_VIRGULA:
            casar(PONTO_VIRGULA);
            ProgramaB();
        break;
        default:
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual], esperadosLiteral[EsperadosInicializador]);
            pular(sincProgramaA);
        break;
    }
}

static int followProgramaB [] = {TOKEN_EOF};
void ProgramaB(){
    fprintf(stdout, "ProgramaB\n");
    switch(tokenAtual){
        case DEFINICAO_TIPO:    case INTEIRO:        case REAL:
        case BOLEANO:            case CARACTERE:        case ID:
        case CLASSE:
            Programa();
        break;
        default: /* Epsilon */ break;
    }
}

//static int followDeclClasse [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
static int sincDeclClasse [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, CHAVE_ESQ, DOIS_PONTOS, TOKEN_EOF};
void DeclClasse(){
    fprintf(stdout, "DeclClasse\n");
    switch(tokenAtual){
        case CLASSE:
            casar(CLASSE);
            casarOuPular(ID, sincDeclClasse);
            DeclClasseL();
        break;
    }
}

//static int followDeclClasseL [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
static int sincDeclClasseL [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, CHAVE_ESQ, CHAVE_DIR, PONTO_VIRGULA, TOKEN_EOF};
void DeclClasseL(){
    fprintf(stdout, "DeclClasseL\n");
    switch(tokenAtual){
        case CHAVE_ESQ:
            casar(CHAVE_ESQ);
            DeclLocal();
            casarOuPular(CHAVE_DIR, sincDeclClasseL);
            casarOuPular(PONTO_VIRGULA, sincDeclClasseL);
        break;
        case DOIS_PONTOS:
            casar(DOIS_PONTOS);
            casarOuPular(ID, sincDeclClasseL);
            casarOuPular(CHAVE_ESQ, sincDeclClasseL);
            DeclLocal();
            casarOuPular(CHAVE_DIR, sincDeclClasseL);
            casarOuPular(PONTO_VIRGULA, sincDeclClasseL);
        break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual], esperadosLiteral[EsperadosChaveOuDoisPontos]);
            pular(sincDeclClasseL);
        break;
    }
}

static int followDeclLocal [] = {CHAVE_DIR, TOKEN_EOF};
static int sincDeclLocal [] = {CHAVE_DIR, INTEIRO, REAL, BOLEANO, CARACTERE, ID, PUBLICO, PRIVADO, PARENTESE_ESQ, COLCHETE_ESQ, VIRGULA, PONTO_VIRGULA, TOKEN_EOF};
void DeclLocal(){
    fprintf(stdout, "DeclLocal\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID:
            Tipo();
            Ponteiro();
            casarOuPular(ID, sincDeclLocal);
            DeclLocalL();
        break;
        case PUBLICO:
            casar(PUBLICO);
            casarOuPular(DOIS_PONTOS, sincDeclLocal);
            DeclLocal();
        break;
        case PRIVADO:
            casar(PRIVADO);
            casarOuPular(DOIS_PONTOS, sincDeclLocal);
            DeclLocal();
        break;
        default: /* epsilon */ break;
    }
}

static int followDeclLocalL [] = {CHAVE_DIR, TOKEN_EOF};
void DeclLocalL(){
    fprintf(stdout, "DeclLocalL\n");
    switch(tokenAtual){
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            ListaForma();
            casarOuPular(PARENTESE_DIR, followDeclLocalL);
            casarOuPular(CHAVE_ESQ, followDeclLocalL);
            DeclLocalLL();
            casarOuPular(CHAVE_DIR, followDeclLocalL);
            DeclLocal();
        break;
        case COLCHETE_ESQ:  case VIRGULA:
            Arranjo();
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followDeclLocalL);
            DeclLocal();
        break;
        case PONTO_VIRGULA:
            casar(PONTO_VIRGULA);
            DeclLocal();
        break;
        default: /* ERRO */ break;
    }
}

static int followDeclLocalLL [] = {CHAVE_DIR, TOKEN_EOF};
void DeclLocalLL(){
    fprintf(stdout, "DeclLocalLL\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            Expr();
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followDeclLocalLL);
            ListaSentenca();
        break;
        case CHAVE_ESQ:     case SE:            case ENQUANTO:
        case ESCOLHA:       case DESVIA:        case IMPRIME:
        case LE_LINHA:      case RETORNA:       case LANCA:
        case TENTA:
            SentencaL();
            ListaSentenca();
        break;
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:
            TipoL();
            Ponteiro();
            casarOuPular(ID, followDeclLocalLL);
            Arranjo();
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followDeclLocalLL);
            DeclLocalLL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followDeclVar [] = {CHAVE_DIR, TOKEN_EOF};
void DeclVar(){
    fprintf(stdout, "DeclVar\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID:
            Tipo();
            Ponteiro();
            casarOuPular(ID, followDeclVar);
            Arranjo();
            ListaIdCont();
            casarOuPular(PONTO_VIRGULA, followDeclVar);
            DeclVar();
        break;
        default: /* Epsilon */ break;
    }
}

static int followListaId [] = {PONTO_VIRGULA, TOKEN_EOF};
void ListaId(){
    fprintf(stdout, "ListaId\n");
    switch(tokenAtual){
        case ASTERISCO:
            Ponteiro();
            casarOuPular(ID, followListaId);
            Arranjo();
            ListaIdCont();
        break;
        case ID:
            casar(ID);
            Arranjo();
            ListaIdCont();
        break;
        default: /* ERRO */ break;
    }
}

static int followListaIdCont [] = {PONTO_VIRGULA, TOKEN_EOF};
void ListaIdCont(){
    fprintf(stdout, "ListaIdCont\n");
    switch(tokenAtual){
        case VIRGULA:
            casar(VIRGULA);
            Ponteiro();
            casarOuPular(ID, followListaIdCont);
            Arranjo();
            ListaIdCont();
        break;
        default: /* Epsilon */ break;
    }
}

static int followPonteiro [] = {ID, TOKEN_EOF};
void Ponteiro(){
    fprintf(stdout, "Ponteiro\n");
    switch(tokenAtual){
        case ASTERISCO:
            casar(ASTERISCO);
        break;
        default: /* Epsilon */ break;
    }
}

static int followArranjo [] = {VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void Arranjo(){
    fprintf(stdout, "Arranjo\n");
    switch(tokenAtual){
        case COLCHETE_ESQ:
            casar(COLCHETE_ESQ);
            if(tokenAtual == NUM_INTEIRO || tokenAtual == NUM_REAL) { // NUM REAL AQUI É ERRO
                casarOuPular(NUM_INTEIRO, followArranjo);
            }
            casarOuPular(COLCHETE_DIR, followArranjo);
        break;
        default: /* Epsilon */ break;
    }
}

static int followListaForma [] = {PARENTESE_DIR, TOKEN_EOF};
void ListaForma(){
    fprintf(stdout, "ListaForma\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID:
            Tipo();
            Ponteiro();
            casarOuPular(ID, followListaForma);
            Arranjo();
            ListaFormaCont();
        break;
        default: /* Epsilon */ break;
    }
}

static int followListaFormaCont [] = {PARENTESE_DIR, TOKEN_EOF};
void ListaFormaCont(){
    fprintf(stdout, "ListaFormaCont\n");
    switch(tokenAtual){
        case VIRGULA:
            casar(VIRGULA);
            Tipo();
            Ponteiro();
            casarOuPular(ID, followListaFormaCont);
            Arranjo();
            ListaFormaCont();
        break;
        default: /* Epsilon*/ break;
    }
}

static int followTipo [] = {ID, ASTERISCO, TOKEN_EOF};
void Tipo(){
    fprintf(stdout, "Tipo\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:
            TipoL();
        break;
        case ID:
            casarOuPular(ID, followTipo);
        break;
        default: /*ERRO*/ break;
    }
}

static int followTipoL [] = {ID, ASTERISCO, TOKEN_EOF};
void TipoL(){
    fprintf(stdout, "TipoL\n");
    switch(tokenAtual){
        case INTEIRO:
            casar(INTEIRO);
        break;
        case REAL:
            casar(REAL);
        break;
        case BOLEANO:
            casar(BOLEANO);
        break;
        case CARACTERE:
            casar(CARACTERE);
        break;
        default: /*ERRO*/ break;
    }
}

static int followListaSentenca [] = {CHAVE_DIR, CASO, TOKEN_EOF};
void ListaSentenca(){
    fprintf(stdout, "ListaSentenca\n");
    switch(tokenAtual){
        case CHAVE_ESQ:     case ID:            case ASTERISCO:
        case NUM_INTEIRO:     case NUM_REAL:      case PARENTESE_ESQ:
        case CARACTERE:     case LITERAL:          case E_COMERCIAL:
        case E:               case VERDADEIRO:     case FALSO:
        case ADICAO:        case SUBTRACAO:        case SE:
        case ENQUANTO:        case ESCOLHA:        case DESVIA:
        case RETORNA:       case LANCA:            case TENTA:
        case NEGACAO:         case NOVO:           case LE_LINHA:
        case ESSE:          case IMPRIME:          case ASCII:
            Sentenca();
            ListaSentenca();
        break;
        default: /* Epsilon */ break;
    }
}


static int followSentenca [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL,
                                E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA,
                                DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void Sentenca(){
    fprintf(stdout, "Sentenca\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:         case NUM_INTEIRO:    case ASCII:
        case NUM_REAL:       case PARENTESE_ESQ:     case CARACTERE:
        case LITERAL:       case E_COMERCIAL:         case VERDADEIRO:
        case FALSO:         case ADICAO:            case SUBTRACAO:
        case ESSE:            case NOVO:                  case NEGACAO:
            Expr();
            casarOuPular(PONTO_VIRGULA, followSentenca);
        break;
        case CHAVE_ESQ:     case SE:                case ENQUANTO:
        case ESCOLHA:         case DESVIA:             case RETORNA:
        case LANCA:         case TENTA:                case IMPRIME:
        case LE_LINHA:
            SentencaL();
        break;
        default: /*Epsilon*/ break;
    }
}

static int followSentencaL [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL,
                                 E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA,
                                 DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void SentencaL(){
    fprintf(stdout, "SentencaL\n");
    switch(tokenAtual){
        case SE:
            Se();
        break;
        case ENQUANTO:
            casar(ENQUANTO);
            casarOuPular(PARENTESE_ESQ, followSentencaL);
            Expr();
            casarOuPular(PARENTESE_DIR, followSentencaL);
            Sentenca();
        break;
        case ESCOLHA:
            casar(ESCOLHA);
            casarOuPular(PARENTESE_ESQ, followSentencaL);
            Expr();
            casarOuPular(PARENTESE_DIR, followSentencaL);
            casarOuPular(CHAVE_ESQ, followSentencaL);
            BlocoCaso();
            casarOuPular(CHAVE_DIR, followSentencaL);
        break;
        case DESVIA:
            casar(DESVIA);
            casarOuPular(PONTO_VIRGULA, followSentencaL);
        break;
        case IMPRIME:
            casar(IMPRIME);
            casarOuPular(PARENTESE_ESQ, followSentencaL);
            ListaExpr();
            casarOuPular(PARENTESE_DIR, followSentencaL);
            casarOuPular(PONTO_VIRGULA, followSentencaL);
        break;
        case LE_LINHA:
            casar(LE_LINHA);
            casarOuPular(PARENTESE_ESQ, followSentencaL);
            Expr();
            casarOuPular(PARENTESE_DIR, followSentencaL);
            casarOuPular(PONTO_VIRGULA, followSentencaL);
        break;
        case RETORNA:
            casar(RETORNA);
            Expr();
            casarOuPular(PONTO_VIRGULA, followSentencaL);
        break;
        case LANCA:
             casar(LANCA);
             casarOuPular(PONTO_VIRGULA, followSentencaL);
        break;
        case CHAVE_ESQ:
            casar(CHAVE_ESQ);
            ListaSentenca();
            casarOuPular(CHAVE_DIR, followSentencaL);
        break;
        case TENTA:
            casar(TENTA);
            Sentenca();
            casarOuPular(PEGA, followSentencaL);
            casarOuPular(PARENTESE_ESQ, followSentencaL);
            casarOuPular(TRES_PONTOS, followSentencaL);
            casarOuPular(PARENTESE_DIR, followSentencaL);
            Sentenca();
        break;
        default: /*ERRO*/ break;
    }
}

static int followSe [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL,
                          E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA,
                          DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void Se(){
    fprintf(stdout, "Se\n");
    switch(tokenAtual){
        case SE:
            casar(SE);
            casarOuPular(PARENTESE_ESQ, followSe);
            Expr();
            casarOuPular(PARENTESE_DIR, followSe);
            Sentenca();
            Senao();
        break;
        default: /*ERRO*/ break;
    }
}

static int followSenao [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL,
                             E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA,
                             DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void Senao(){
    fprintf(stdout, "Senao\n");
    switch(tokenAtual){
        case SENAO:
            casar(SENAO);
            Sentenca();
        break;
        default: /* Epsilon */ break;
    }
}

static int followBlocoCaso [] = {CHAVE_DIR, TOKEN_EOF};
void BlocoCaso(){
    fprintf(stdout, "BlocoCaso\n");
    switch(tokenAtual){
        case CASO:
            casar(CASO);
            if(tokenAtual == NUM_INTEIRO || tokenAtual == NUM_REAL) {
                casarOuPular(NUM_INTEIRO, followBlocoCaso);
            }
            casarOuPular(DOIS_PONTOS, followBlocoCaso);
            ListaSentenca();
            BlocoCaso();
        break;
        default: /* Epsilon */ break;
    }
}

static int followListaExpr [] = {PARENTESE_DIR, TOKEN_EOF};
void ListaExpr(){
    fprintf(stdout, "ListaExpr\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            Expr();
            ListaExprCont();
        break;
        default: /* Epsilon */ break;
    }
}


static int followListaExprCont [] = {PARENTESE_DIR, TOKEN_EOF};
void ListaExprCont(){
    fprintf(stdout, "ListaExprCont\n");
    switch(tokenAtual){
        case VIRGULA:
            casar(VIRGULA);
            Expr();
            ListaExprCont();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExpr [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void Expr() {
    fprintf(stdout, "Expr\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprOuBool();
            ExprAtrib();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprAtrib [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void ExprAtrib() {
    fprintf(stdout, "ExprAtrib\n");
    switch(tokenAtual){
        case ATRIBUICAO:
            casar(ATRIBUICAO);
            ExprOuBool();
            ExprAtrib();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprOuBool [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
void ExprOuBool(){
    fprintf(stdout, "ExprOuBool\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprEBool();
            ExprOuBoolL();
        break;
        default: /* Erro */ break;
    }
}

static int followExprOuBoolL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
void ExprOuBoolL(){
    fprintf(stdout, "ExprOuBoolL\n");
    switch(tokenAtual){
        case OU_CC:
            casar(OU_CC);
            ExprEBool();
            ExprOuBoolL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprEBool [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};
void ExprEBool(){
    fprintf(stdout, "ExprEBool\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprIgualdade();
            ExprEBoolL();
        break;
        default: /* Erro */ break;
    }
}

static int followExprEBoolL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};
void ExprEBoolL(){
    fprintf(stdout, "ExprEBoolL\n");
    switch(tokenAtual){
        case E:
            casar(E);
            ExprIgualdade();
            ExprEBoolL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprIgualdade [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, TOKEN_EOF};
void ExprIgualdade(){
    fprintf(stdout, "ExprIgualdade\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprRelacional();
            ExprIgualdadeL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprIgualdadeL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, TOKEN_EOF};
void ExprIgualdadeL(){
    fprintf(stdout, "ExprIgualdadeL\n");
    switch(tokenAtual){
        case COMPARACAO:
            casar(COMPARACAO);
            ExprRelacional();
            ExprIgualdadeL();
        break;
        case DIFERENTE:
            casar(DIFERENTE);
            ExprRelacional();
            ExprIgualdadeL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprRelacional [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                      DIFERENTE, TOKEN_EOF};
void ExprRelacional(){
    fprintf(stdout, "ExprRelacional\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprSoma();
            ExprRelacionalL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprRelacionalL []    = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                       DIFERENTE, TOKEN_EOF};
void ExprRelacionalL(){
    fprintf(stdout, "ExprRelacionalL\n");
    switch(tokenAtual){
        case MENOR:
            casar(MENOR);
            ExprSoma();
            ExprRelacionalL();
        break;
        case MENOR_IGUAL:
            casar(MENOR_IGUAL);
            ExprSoma();
            ExprRelacionalL();
        break;
        case MAIOR_IGUAL:
            casar(MAIOR_IGUAL);
            ExprSoma();
            ExprRelacionalL();
        break;
        case MAIOR:
            casar(MAIOR);
            ExprSoma();
            ExprRelacionalL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprSoma [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};
void ExprSoma(){
    fprintf(stdout, "ExprSoma\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprMultDivE();
            ExprSomaL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprSomaL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                 DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};
void ExprSomaL(){
    fprintf(stdout, "ExprSomaL\n");
    switch(tokenAtual){
        case ADICAO:
            casar(ADICAO);
            ExprMultDivE();
            ExprSomaL();
        break;
        case SUBTRACAO:
            casar(SUBTRACAO);
            ExprMultDivE();
            ExprSomaL();
        break;
        case OU:
            casar(OU);
            ExprMultDivE();
            ExprSomaL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprMultDivE [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                    DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, TOKEN_EOF};
void ExprMultDivE(){
    fprintf(stdout, "ExprMultDivE\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
            ExprUnaria();
            ExprMultDivEL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprMultDivEL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                     DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, TOKEN_EOF};
void ExprMultDivEL(){
    fprintf(stdout, "ExprMultDivEL\n");
    switch(tokenAtual){
        case ASTERISCO:
            casar(ASTERISCO);
            ExprUnaria();
            ExprMultDivEL();
        break;
        case DIVISAO:
            casar(DIVISAO);
            ExprUnaria();
            ExprMultDivEL();
        break;
        case PORCENTO:
            casar(PORCENTO);
            ExprUnaria();
            ExprMultDivEL();
        break;
        case E_COMERCIAL:
            casar(E_COMERCIAL);
            ExprUnaria();
            ExprMultDivEL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprUnaria [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                   DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                   E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprUnaria(){
    fprintf(stdout, "ExprUnaria\n");
    switch(tokenAtual){
        case NEGACAO:
            casar(NEGACAO);
            ExprAceCamp();
        break;
        case ADICAO:
            casar(ADICAO);
            ExprAceCamp();
        break;
        case SUBTRACAO:
            casar(SUBTRACAO);
            ExprAceCamp();
        break;
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII:
            ExprAceCamp();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprAceCamp [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                   DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                   E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprAceCamp(){
    fprintf(stdout, "ExprAceCamp\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII:
            ExprNovo();
            ExprAceCampL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprAceCampL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                    DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                    E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprAceCampL(){
    fprintf(stdout, "ExprAceCampL\n");
    switch(tokenAtual){
        case PONTEIRO:
            casar(PONTEIRO);
            ExprNovo();
            ExprAceCampL();
        break;
        case PONTO:
            casar(PONTO);
            ExprNovo();
            ExprAceCampL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followExprNovo [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};
void ExprNovo(){
    fprintf(stdout, "ExprNovo\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII:
            Primario();
            ExprNovoL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprNovoL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                 DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                 E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};
void ExprNovoL(){
    fprintf(stdout, "ExprNovoL\n");
    switch(tokenAtual){
        case COLCHETE_ESQ:
            casar(COLCHETE_ESQ);
            Expr();
            casarOuPular(COLCHETE_DIR, followExprNovoL);
            ExprNovoL();
        break;
        default: /* Epsilon */ break;
    }
}

static int followPrimario [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void Primario() {
    fprintf(stdout, "Primario\n");
    switch(tokenAtual){
        case ID:
            PrimarioID();
        break;
        case ASTERISCO:     case NUM_INTEIRO:   case NUM_REAL:
        case PARENTESE_ESQ: case LITERAL:       case E_COMERCIAL:
        case VERDADEIRO:    case FALSO:         case ESSE:
        case NOVO:          case ASCII:
            PrimarioL();
        break;
        default: /* ERRO */ break;
    }
}

static int followPrimarioL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                 DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                 E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioL(){
    fprintf(stdout, "PrimarioL\n");
    switch(tokenAtual){
        case NUM_INTEIRO:
            casar(NUM_INTEIRO);
        break;
        case NUM_REAL:
            casar(NUM_REAL);
        break;
        case LITERAL:
            casar(LITERAL);
        break;
        case ASCII:
            casar(ASCII);
        break;
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            Expr();
            casarOuPular(PARENTESE_DIR, followPrimarioL);
        break;
        case E_COMERCIAL:
            casar(E_COMERCIAL);
            Primario();
        break;
        case ASTERISCO:
            casar(ASTERISCO);
            Primario();
        break;
        case VERDADEIRO:
            casar(VERDADEIRO);
        break;
        case FALSO:
            casar(FALSO);
        break;
        case ESSE:
            casar(ESSE);
        break;
        case NOVO:
            casar(NOVO);
            casarOuPular(ID, followPrimarioL);
            casarOuPular(PARENTESE_ESQ, followPrimarioL);
            ListaExpr();
            casarOuPular(PARENTESE_DIR, followPrimarioL);
        break;
        default: /* ERRO */ break;
    }
}

static int followPrimarioID [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                  DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                  E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioID(){
    fprintf(stdout, "PrimarioID\n");
    switch(tokenAtual){
        case ID:
            casar(ID);
            PrimarioIDL();
        break;
        default: /* ERRO */ break;
    }
}

static int followPrimarioIDL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO,
                                   DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO, OU, ASTERISCO,
                                   E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioIDL(){
    fprintf(stdout, "PrimarioIDL\n");
    switch(tokenAtual){
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            ListaExpr();
            casarOuPular(PARENTESE_DIR, followPrimarioIDL);
        break;
        default: /* Epsilon */ break;
    }
}
