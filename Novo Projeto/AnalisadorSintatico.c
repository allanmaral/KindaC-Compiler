#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "ASA.h"

static int tokenAtual;

static NoPrograma   *listaPrograma = NULL;

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

const char *pegarTokenLiteral(int token) { return tokenLiteral[token]; }

typedef enum {
    EsperadosChaveOuDoisPontos = 0,
    EsperadosDefinicaoClassTipo,
    EsperadosInicializador,
    EsperadosDeclaracaoMembro,
    EsperadosIdentificador,
    EsperadosTipo,
    EsperadosSenteca,
    EsperadosExpressaoPrimaria,
    EsperadosTamanhoEnumerador
} Esperados;

static char esperadosLiteral[EsperadosTamanhoEnumerador][48] = {
    "CHAVE_ESQ\" ou \"DOIS_PONTOS", "DEFINICAO_TIPO\", \"CLASSE\" ou \"Tipo",   "Inicializador",
    "Declaracao de Membros",        "Identificador",                            "Tipo",
    "Sentenca",                     "Expressao Primaria"
};

void casar(int tokenEsperado){
    if(tokenAtual == tokenEsperado){
        if(tokenAtual == NUM_INTEIRO || tokenAtual == NUM_REAL || tokenEsperado == LITERAL ||
            tokenAtual == ASCII || tokenAtual == ID){
            fprintf(stdout, "CASOU: %s.%s\n",
                    tokenLiteral[tokenEsperado],
                    pegarLexema());
        } else{
              fprintf(stdout, "CASOU: %s\n", tokenLiteral[tokenEsperado]);
          }
    } else {
          fprintf(stdout, "NAO CASOU: LIDO: \"%s\" ESPERADO: \"%s\"\n", tokenLiteral[tokenAtual],
                  tokenLiteral[tokenEsperado]);
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
                sincronizado = 1;
                return;
            }
        } while(sinc[indice] != TOKEN_EOF);
        // Se chegar aqui, o erro ainda nao foi sincronizado
        tokenAtual = proximoToken();
    }
}

void casarOuPular(int token, int *sinc){
    if(tokenAtual == token) {
        casar(token);
    } else {
          saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual], tokenLiteral[token]);
          pular(sinc);
      }
}


void            ProgramaL();    	             void             ProgramaA(NoTipo *tipo, int ponteiro, NoId *id);
void            ProgramaB();                     NoDeclClasse    *DeclClasse();
NoDeclLocal    *DeclLocal();	                 NoDeclClasse    *DeclClasseL(NoId *idClasseDeclarada);
void            CorpoFunc(NoDeclFuncao *funcao); NoDeclLocal     *DeclLocalL(NoTipo *tipo, int ponteiro, NoId *id);
NoDeclVariavel *DeclVar();                       NoListaId       *ListaId();
NoListaId      *ListaIdCont();                   int              Ponteiro();
NoArranjo      *Arranjo();                       NoListaFormal   *ListaForma();
NoListaFormal  *ListaFormaCont();                NoTipo          *Tipo();
NoTipo         *TipoL();                         NoListaSentenca *ListaSentenca();
NoSentenca     *Sentenca();                      NoSentenca      *SentencaL();
NoSe           *Se();                            NoSenao         *Senao();
NoBlocoCaso    *BlocoCaso();                     NoListaExpr     *ListaExpr();
NoListaExpr    *ListaExprCont();                 NoExpr          *Expr();
NoExpr         *ExprAtrib(NoExpr *exprEsquerda); NoExpr          *ExprOuBool();
NoExpr         *ExprEBool();                     NoExpr          *ExprEBoolL(NoExpr *exprEsquerda);
NoExpr         *ExprIgualdade();                 NoExpr          *ExprIgualdadeL(NoExpr *exprEsquerda);
NoExpr         *ExprRelacional();                NoExpr          *ExprRelacionalL(NoExpr *exprEsquerda);
NoExpr         *ExprSoma();                      NoExpr          *ExprSomaL(NoExpr *exprEsquerda);
NoExpr         *ExprMultDivE();                  NoExpr          *ExprMultDivEL(NoExpr *exprEsquerda);
NoExpr         *ExprUnaria();                    NoExpr          *ExprAceCamp();
NoPrimario     *ExprNovo();                      NoPrimario      *ExprNovoL(NoPrimario *primario);
NoPrimario     *Primario();                      NoPrimario      *PrimarioID();
NoPrimario     *PrimarioIDL(NoId *id);           NoPrimario      *PrimarioL();
NoExpr         *ExprOuBoolL(NoExpr *exprEsquerda);
NoExpr         *ExprAceCampL(NoExpr *exprEsquerda);

NoPrograma *Programa(){
    tokenAtual = proximoToken();
    while(tokenAtual != TOKEN_EOF) ProgramaL();
    return listaPrograma;
}

static int sincPrograma [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, ESTRUTURA, CHAVE_ESQ,
                              PONTO_VIRGULA, PARENTESE_ESQ, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
static int firstPrograma [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
void ProgramaL(){
    fprintf(stdout, "ProgramaL\n");
    switch(tokenAtual){
        case DEFINICAO_TIPO: {
            casar(DEFINICAO_TIPO);
            casarOuPular(ESTRUTURA, sincPrograma);
            casarOuPular(CHAVE_ESQ, sincPrograma);
            NoTipo *tipo = Tipo();
            NoListaId *listaId = ListaId();
            casarOuPular(PONTO_VIRGULA, sincPrograma);
            NoDeclVariavel *variavel = new NoDeclVariavel(tipo, listaId, pegarLinha(), pegarColuna(), DeclVar());
            casarOuPular(CHAVE_DIR, sincPrograma);
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincPrograma);
            casarOuPular(PONTO_VIRGULA, sincPrograma);
            NoDeclTipo *declTipo = new NoDeclTipo(variavel, id, pegarLinha(), pegarColuna());
            if(listaPrograma){
                NoPrograma *ultimo = listaPrograma;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = declTipo;
            } else{
                  listaPrograma = declTipo;
              }
            ProgramaL();
        } break;
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID: {
            NoTipo *tipo = Tipo();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincPrograma);
            ProgramaA(tipo, ponteiro, id);
        } break;
        case CLASSE: {
            NoDeclClasse *classe = DeclClasse();
            classe->lista = NULL;
            if(listaPrograma){
                NoPrograma *ultimo = listaPrograma;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = classe;
            } else{
                  listaPrograma = classe;
              }
            ProgramaL();
        } break;
        case TOKEN_EOF:
            casar(TOKEN_EOF);
            return; // NULL
        break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosDefinicaoClassTipo]);
            pular(firstPrograma);
            return ProgramaL();
        break;
    }
}

static int sincProgramaAL [] = {PARENTESE_DIR, CHAVE_ESQ, TOKEN_EOF};
static int sincProgramaA [] = {CHAVE_ESQ, INTEIRO, REAL, BOLEANO, CARACTERE, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL,
                               PARENTESE_ESQ, NEGACAO, LITERAL, ASCII, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO,
                               ADICAO, SUBTRACAO, SE, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA,
                               TENTA, DEFINICAO_TIPO, CLASSE, TOKEN_EOF};
void ProgramaA(NoTipo *tipo, int ponteiro, NoId *id){
    fprintf(stdout, "ProgramaA\n");
    switch(tokenAtual){
        case PARENTESE_ESQ: {
            casar(PARENTESE_ESQ);
            NoListaFormal *listaFormal = ListaForma();
            if(tokenAtual == INTEIRO || tokenAtual == REAL || tokenAtual == CARACTERE || tokenAtual == ID ||
               tokenAtual == BOLEANO ) {
                saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                          tokenLiteral[VIRGULA]);
                pular(sincProgramaAL);
            }
            casarOuPular(PARENTESE_DIR, sincProgramaA);
            casarOuPular(CHAVE_ESQ, sincProgramaA);
            NoDeclFuncao *funcao = new NoDeclFuncao(tipo, ponteiro, id, listaFormal, NULL, NULL, NULL, pegarLinha(), pegarColuna());
            CorpoFunc(funcao);
            casarOuPular(CHAVE_DIR, sincProgramaA);
            if(listaPrograma){
                NoPrograma *ultimo = listaPrograma;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = funcao;
            } else{
                  listaPrograma = funcao;
              }
            ProgramaL();
        } break;
        case COLCHETE_ESQ:  case VIRGULA:       case PONTO_VIRGULA: {
            NoArranjo *arranjo = Arranjo();
            NoListaId *listaId = new NoListaId(ponteiro, id, arranjo, ListaIdCont(), pegarLinha(), pegarColuna());
            casarOuPular(PONTO_VIRGULA, sincProgramaA);
            NoDeclVariavel *variavel = new NoDeclVariavel(tipo, listaId, pegarLinha(), pegarColuna(), NULL);
            variavel->lista = NULL;
            if(listaPrograma){
                NoPrograma *ultimo = listaPrograma;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = variavel;
            } else{
                  listaPrograma = variavel;
              }
            ProgramaL();
        } break;
        default:
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosInicializador]);
            pular(sincProgramaA);
        break;
    }
}

static int sincDeclClasse [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, CHAVE_ESQ,
                                DOIS_PONTOS, TOKEN_EOF};
NoDeclClasse *DeclClasse(){
    fprintf(stdout, "DeclClasse\n");
    switch(tokenAtual){
        case CLASSE:{
            casar(CLASSE);
            NoId *idClasse = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincDeclClasse);
            return DeclClasseL(idClasse);
        } break;
    }
    return NULL;
}

static int sincDeclClasseL [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, CHAVE_ESQ,
                                 CHAVE_DIR, PONTO_VIRGULA, TOKEN_EOF};
NoDeclClasse *DeclClasseL(NoId *idClasseDeclarada){
    fprintf(stdout, "DeclClasseL\n");
    switch(tokenAtual){
        case CHAVE_ESQ:{
            casar(CHAVE_ESQ);
            NoDeclLocal *declLocal = DeclLocal();
            casarOuPular(CHAVE_DIR, sincDeclClasseL);
            casarOuPular(PONTO_VIRGULA, sincDeclClasseL);
            return new NoDeclClasse(idClasseDeclarada,NULL,declLocal, pegarLinha(), pegarColuna());
        } break;
        case DOIS_PONTOS:{
            casar(DOIS_PONTOS);
            NoId *idHeranca = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincDeclClasseL);
            casarOuPular(CHAVE_ESQ, sincDeclClasseL);
            NoDeclLocal *declLocal = DeclLocal();
            casarOuPular(CHAVE_DIR, sincDeclClasseL);
            casarOuPular(PONTO_VIRGULA, sincDeclClasseL);
            return new NoDeclClasse (idClasseDeclarada,idHeranca,declLocal, pegarLinha(), pegarColuna());
        } break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosChaveOuDoisPontos]);
            pular(sincDeclClasseL);
            return NULL;
        break;
    }
}

static int sincDeclLocal [] = {CHAVE_DIR, INTEIRO, REAL, BOLEANO, CARACTERE, ID, PUBLICO, PRIVADO, PARENTESE_ESQ,
                               COLCHETE_ESQ, VIRGULA, PONTO_VIRGULA, TOKEN_EOF};
NoDeclLocal *DeclLocal(){
    fprintf(stdout, "DeclLocal\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID:{
            NoTipo *tipo =  Tipo();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincDeclLocal);
            return DeclLocalL(tipo, ponteiro, id);
        } break;
        case PUBLICO:{
            casar(PUBLICO);
            casarOuPular(DOIS_PONTOS, sincDeclLocal);
            return new NoDeclLocalPublico(DeclLocal(), pegarLinha(), pegarColuna());
        } break;
        case PRIVADO:{
            casar(PRIVADO);
            casarOuPular(DOIS_PONTOS, sincDeclLocal);
            return new NoDeclLocalPrivado(DeclLocal(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int followDeclLocalL [] = {CHAVE_DIR, TOKEN_EOF};
static int sincDeclLocalL   [] = {CHAVE_DIR, CHAVE_ESQ, INTEIRO, REAL, BOLEANO, CARACTERE, ID, PUBLICO, PRIVADO,
                                  TOKEN_EOF};
static int firstCorpoFunc   [] = {ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, PARENTESE_ESQ, NEGACAO, LITERAL,
                                  E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, ASCII, CHAVE_ESQ,
                                  SE, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, INTEIRO,
                                  REAL, BOLEANO, CARACTERE, TOKEN_EOF };
NoDeclLocal *DeclLocalL(NoTipo *tipo, int ponteiro, NoId *id){
    fprintf(stdout, "DeclLocalL\n");
    switch(tokenAtual){
        case PARENTESE_ESQ:{
            casar(PARENTESE_ESQ);
            NoListaFormal *listaFormal = ListaForma();
            casarOuPular(PARENTESE_DIR, sincDeclLocalL);
            casarOuPular(CHAVE_ESQ, firstCorpoFunc);
            NoDeclFuncao *funcao = new NoDeclFuncao(tipo, ponteiro, id, listaFormal, NULL, NULL, NULL, pegarLinha(), pegarColuna());
            CorpoFunc(funcao);
            casarOuPular(CHAVE_DIR, sincDeclLocalL);
            return new NoDeclLocalFuncao(funcao, DeclLocal(), pegarLinha(), pegarColuna());
        } break;
        case COLCHETE_ESQ:  case VIRGULA:       case PONTO_VIRGULA:{
            NoArranjo *arranjo = Arranjo();
            NoListaId *listaIdCont = new NoListaId(ponteiro, id, arranjo, ListaIdCont(), pegarLinha(), pegarColuna());
            casarOuPular(PONTO_VIRGULA, sincDeclLocalL);
            NoDeclVariavel *variavel = new NoDeclVariavel(tipo, listaIdCont, pegarLinha(), pegarColuna(), NULL);
            return new NoDeclLocalVariavel(variavel, DeclLocal(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* ERRO */
            saidaErro(ErroSintaticoDepois, pegarLinha(), pegarColuna(),
                      esperadosLiteral[EsperadosDeclaracaoMembro], tokenLiteral[PONTO_VIRGULA]);
            pular(followDeclLocalL);
            return NULL;
        break;
    }
}

static int sincCorpoFunc   [] = { CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, PARENTESE_ESQ, NEGACAO, LITERAL,
                                  ASCII, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE,
                                  ENQUANTO, ESCOLHA, DESVIA, LE_LINHA, RETORNA, IMPRIME, LANCA, TENTA, INTEIRO,
                                  REAL, BOLEANO, CARACTERE, COLCHETE_ESQ, VIRGULA, CHAVE_DIR, TOKEN_EOF};
void CorpoFunc(NoDeclFuncao *funcao){
    fprintf(stdout, "CorpoFunc\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:{
            NoExpr *expressao = Expr();
            NoId *id = NULL;
            if(tokenAtual == ID){
                id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
                casar(ID);
            }
            NoListaId *listaid = ListaIdCont();
            NoArranjo *arranjo = Arranjo();
            casarOuPular(PONTO_VIRGULA, sincCorpoFunc);
            NoCorpoFuncao *corpo = new NoCorpoFuncao(id, listaid, expressao, arranjo, pegarLinha(), pegarColuna());
            if(funcao->corpoFunc){ // Insere no final da lista
                NoCorpoFuncao *ultimo = funcao->corpoFunc;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = corpo;
            } else{
                  funcao->corpoFunc = corpo;
              }
            CorpoFunc(funcao);
        } break;
        case CHAVE_ESQ:     case SE:            case ENQUANTO:
        case ESCOLHA:       case DESVIA:        case IMPRIME:
        case LE_LINHA:      case RETORNA:       case LANCA:{
        case TENTA:
            NoSentenca *sentenca = SentencaL();
            funcao->sentenca = new NoListaSentenca(sentenca, ListaSentenca(), pegarLinha(), pegarColuna());
        } break;
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:{
            NoTipo *tipo = TipoL();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincCorpoFunc);
            NoArranjo *arranjo = Arranjo();
            NoListaId *listaId = new NoListaId(ponteiro,id,arranjo,ListaIdCont(), pegarLinha(), pegarColuna());
            casarOuPular(PONTO_VIRGULA, sincCorpoFunc);
            NoDeclVariavel *variavel = new NoDeclVariavel(tipo, listaId, pegarLinha(), pegarColuna(), NULL);
            if(funcao->variaveis) { // Insere no final da lista
                NoPrograma *ultimo = funcao->variaveis;
                while(ultimo->lista) ultimo = ultimo->lista;
                ultimo->lista = variavel;
            } else{
                  funcao->variaveis = variavel;
              }
            CorpoFunc(funcao);
        } break;
        default: /* Epsilon */ break;
    }
}

static int sincDeclVar [] = {CHAVE_DIR, INTEIRO, REAL, BOLEANO, CARACTERE, ID, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
NoDeclVariavel *DeclVar(){
    fprintf(stdout, "DeclVar\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID: {
            NoTipo *tipo = Tipo();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincDeclVar);
            NoArranjo *arranjo = Arranjo();
            NoListaId *listaId = new NoListaId(ponteiro, id, arranjo, ListaIdCont(), pegarLinha(), pegarColuna());
            casarOuPular(PONTO_VIRGULA, sincDeclVar);
            return new NoDeclVariavel(tipo, listaId, pegarLinha(), pegarColuna(), DeclVar());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int sincListaId [] = {PONTO_VIRGULA, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
NoListaId *ListaId(){
    fprintf(stdout, "ListaId\n");
    switch(tokenAtual){
        case ID:
        case ASTERISCO: {
            int ponteriro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincListaId);
            NoArranjo *arranjo = Arranjo();
            return new NoListaId(ponteriro, id, arranjo, ListaIdCont(), pegarLinha(), pegarColuna());
        }
        break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosIdentificador]);
            pular(sincListaId);
            return NULL;
        break;
    }
}

static int followListaIdCont [] = {PONTO_VIRGULA, VIRGULA, COLCHETE_ESQ, TOKEN_EOF};
NoListaId *ListaIdCont(){
    fprintf(stdout, "ListaIdCont\n");
    switch(tokenAtual){
        case VIRGULA: {
            casar(VIRGULA);
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, followListaIdCont);
            NoArranjo *arranjo = Arranjo();
            return new NoListaId(ponteiro, id, arranjo, ListaIdCont(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

int Ponteiro(){
    fprintf(stdout, "Ponteiro\n");
    switch(tokenAtual){
        case ASTERISCO:
            casar(ASTERISCO);
            return 1;
        break;
        default:
            /* Epsilon */
            return 0;
        break;
    }
}

static int sincArranjo [] = {VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, COLCHETE_DIR, TOKEN_EOF};
NoArranjo *Arranjo(){
    fprintf(stdout, "Arranjo\n");
    switch(tokenAtual){
        case COLCHETE_ESQ: {
            casar(COLCHETE_ESQ);
            NoNum *num = NULL;
            if(tokenAtual == NUM_INTEIRO){
                casarOuPular(NUM_INTEIRO, sincArranjo);
                num = new NoNumInteiro(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            } else if(tokenAtual == NUM_REAL) { // NUM REAL AQUI É ERRO (SEMANTICO)
                       casarOuPular(NUM_REAL, sincArranjo);
                       num = new NoNumReal(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
                   }
            casarOuPular(COLCHETE_DIR, sincArranjo);
            return new NoArranjo(num, pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int sincListaForma [] = {PARENTESE_DIR, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
NoListaFormal *ListaForma(){
    fprintf(stdout, "ListaForma\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE:     case ID: {
            NoTipo *tipo = Tipo();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincListaForma);
            NoArranjo *arranjo = Arranjo();
            return new NoListaFormal(tipo, ponteiro, id, arranjo, ListaFormaCont(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int sincListaFormaCont [] = {PARENTESE_DIR, COLCHETE_ESQ, VIRGULA, TOKEN_EOF};
NoListaFormal *ListaFormaCont(){
    fprintf(stdout, "ListaFormaCont\n");
    switch(tokenAtual){
        case VIRGULA: {
            casar(VIRGULA);
            NoTipo *tipo = Tipo();
            int ponteiro = Ponteiro();
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, sincListaFormaCont);
            NoArranjo *arranjo = Arranjo();
            return new NoListaFormal(tipo, ponteiro, id, arranjo, ListaFormaCont(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int followTipo [] = {ID, ASTERISCO, TOKEN_EOF};
NoTipo *Tipo(){
    fprintf(stdout, "Tipo\n");
    switch(tokenAtual){
        case INTEIRO:       case REAL:          case BOLEANO:
        case CARACTERE: {
            return TipoL();
        } break;
        case ID: {
            NoTipo *id = new NoTipo(ID, pegarLinha(), pegarColuna(), pegarUltimoAtributo());
            casar(ID);
            return id;
        } break;
        default:
            /*ERRO*/
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosTipo]);
            pular(followTipo);
            return NULL;
        break;
    }
}

static int followTipoL [] = {ID, ASTERISCO, TOKEN_EOF};
NoTipo *TipoL(){
    fprintf(stdout, "TipoL\n");
    switch(tokenAtual){
        case INTEIRO: {
            casar(INTEIRO);
            return new NoTipo(INTEIRO, pegarLinha(), pegarColuna(), NULL);
        } break;
        case REAL: {
            casar(REAL);
            return new NoTipo(REAL, pegarLinha(), pegarColuna(), NULL);
        } break;
        case BOLEANO: {
            casar(BOLEANO);
            return new NoTipo(BOLEANO, pegarLinha(), pegarColuna(), NULL);
        } break;
        case CARACTERE: {
            casar(CARACTERE);
            return new NoTipo(CARACTERE, pegarLinha(), pegarColuna(), NULL);
        } break;
        default:
            /*ERRO*/
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosTipo]);
            pular(followTipoL);
            return NULL;
        break;
    }
}

NoListaSentenca *ListaSentenca(){
    fprintf(stdout, "ListaSentenca\n");
    switch(tokenAtual){
        case CHAVE_ESQ:     case ID:            case ASTERISCO:
        case NUM_INTEIRO:   case NUM_REAL:      case PARENTESE_ESQ:
        case LITERAL:       case E_COMERCIAL:
        case E:             case VERDADEIRO:    case FALSO:
        case ADICAO:        case SUBTRACAO:     case SE:
        case ENQUANTO:      case ESCOLHA:       case DESVIA:
        case RETORNA:       case LANCA:         case TENTA:
        case NEGACAO:       case NOVO:          case LE_LINHA:
        case ESSE:          case IMPRIME:       case ASCII: {
            NoSentenca *sentenca = Sentenca();
            return new NoListaSentenca(sentenca, ListaSentenca(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}


static int followSentenca [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO,
                                LITERAL, ASCII, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE,
                                SENAO, ENQUANTO, ESCOLHA, CASO, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA,
                                PEGA, TOKEN_EOF};
NoSentenca *Sentenca(){
    fprintf(stdout, "Sentenca\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case ASCII:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ADICAO:        case SUBTRACAO:
        case ESSE:          case NOVO:          case NEGACAO: {
            NoExpr  *expr = Expr();
            casarOuPular(PONTO_VIRGULA, followSentenca);
            return expr;
        } break;
        case CHAVE_ESQ:     case SE:            case ENQUANTO:
        case ESCOLHA:       case DESVIA:        case RETORNA:
        case LANCA:         case TENTA:         case IMPRIME:
        case LE_LINHA: {
            return SentencaL();
        } break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosSenteca]);
            pular(followSentenca);
            return NULL;
        break;
    }
}

static int sincSentencaL []   = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
                                 NEGACAO, LITERAL, ASCII, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
                                 SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, CASO, DESVIA, IMPRIME, LE_LINHA, RETORNA,
                                 LANCA, TENTA, PEGA, PONTO_VIRGULA, PARENTESE_DIR, TRES_PONTOS, TOKEN_EOF};
NoSentenca *SentencaL(){
    fprintf(stdout, "SentencaL\n");
    switch(tokenAtual){
        case SE: {
            return Se();
        } break;
        case ENQUANTO: {
            casar(ENQUANTO);
            casarOuPular(PARENTESE_ESQ, sincSentencaL);
            NoExpr *expr = Expr();
            casarOuPular(PARENTESE_DIR, sincSentencaL);
            return new NoEnquanto(expr, Sentenca(), pegarLinha(), pegarColuna());
        } break;
        case ESCOLHA: {
            casar(ESCOLHA);
            casarOuPular(PARENTESE_ESQ, sincSentencaL);
            NoExpr *expr = Expr();
            casarOuPular(PARENTESE_DIR, sincSentencaL);
            casarOuPular(CHAVE_ESQ, sincSentencaL);
            NoBlocoCaso *bloco = BlocoCaso();
            casarOuPular(CHAVE_DIR, sincSentencaL);
            return new NoEscolha(expr, bloco, pegarLinha(), pegarColuna());
        } break;
        case DESVIA: {
            casar(DESVIA);
            casarOuPular(PONTO_VIRGULA, sincSentencaL);
            return new NoDesvia();
        } break;
        case IMPRIME: {
            casar(IMPRIME);
            casarOuPular(PARENTESE_ESQ, sincSentencaL);
            NoListaExpr *lista = ListaExpr();
            casarOuPular(PARENTESE_DIR, sincSentencaL);
            casarOuPular(PONTO_VIRGULA, sincSentencaL);
            return new NoImprime(lista, pegarLinha(), pegarColuna());
        } break;
        case LE_LINHA: {
            casar(LE_LINHA);
            casarOuPular(PARENTESE_ESQ, sincSentencaL);
            NoExpr *expr = Expr();
            casarOuPular(PARENTESE_DIR, sincSentencaL);
            casarOuPular(PONTO_VIRGULA, sincSentencaL);
            return new NoLeLinha(expr, pegarLinha(), pegarColuna());
        } break;
        case RETORNA: {
            casar(RETORNA);
            NoExpr *expr = Expr();
            casarOuPular(PONTO_VIRGULA, sincSentencaL);
            return new NoRetorna(expr, pegarLinha(), pegarColuna());
        } break;
        case LANCA: {
             casar(LANCA);
             casarOuPular(PONTO_VIRGULA, sincSentencaL);
             return new NoLanca();
        } break;
        case CHAVE_ESQ: {
            casar(CHAVE_ESQ);
            NoListaSentenca *lista = ListaSentenca();
            casarOuPular(CHAVE_DIR, sincSentencaL);
            return new NoEscopo(lista, pegarLinha(), pegarColuna());
        } break;
        case TENTA: {
            casar(TENTA);
            NoSentenca *sentencaTry = Sentenca();
            casarOuPular(PEGA, sincSentencaL);
            casarOuPular(PARENTESE_ESQ, sincSentencaL);
            casarOuPular(TRES_PONTOS, sincSentencaL);
            casarOuPular(PARENTESE_DIR, sincSentencaL);
            return new NoTenta(sentencaTry, Sentenca(), pegarLinha(), pegarColuna());
        } break;
        default:
            /*ERRO*/
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosSenteca]);
            pular(sincSentencaL);
            return NULL;
        break;
    }
}

static int followSe [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO,
                          LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO,
                          ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
NoSe *Se(){
    fprintf(stdout, "Se\n");
    switch(tokenAtual){
        case SE: {
            casar(SE);
            casarOuPular(PARENTESE_ESQ, followSe);
            NoExpr  *expr = Expr();
            casarOuPular(PARENTESE_DIR, followSe);
            NoSentenca *sentenca = Sentenca();
            return new NoSe(expr, sentenca, Senao(), pegarLinha(), pegarColuna());
        } break;
        default:
            /*ERRO*/
            return NULL;
        break; /// Inalcançável
    }
}

NoSenao *Senao(){
    fprintf(stdout, "Senao\n");
    switch(tokenAtual){
        case SENAO: {
            casar(SENAO);
            return new NoSenao(Sentenca(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

static int sincBlocoCaso [] = {CHAVE_DIR, DOIS_PONTOS, CASO,  CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL,
                               PARENTESE_ESQ, CARACTERE, LITERAL, E_COMERCIAL, E, VERDADEIRO, FALSO, ADICAO,
                               SUBTRACAO, SE, ENQUANTO, ESCOLHA, DESVIA, RETORNA, LANCA, TENTA, NEGACAO, NOVO,
                               LE_LINHA, ESSE, IMPRIME, ASCII, TOKEN_EOF};
NoBlocoCaso *BlocoCaso(){
    fprintf(stdout, "BlocoCaso\n");
    switch(tokenAtual){
        case CASO: {
            casar(CASO);
            NoNum *num = NULL;
            if(tokenAtual == NUM_INTEIRO) {
                casarOuPular(NUM_INTEIRO, sincBlocoCaso);
                num = new NoNumInteiro(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            } else if(tokenAtual == NUM_REAL) {
                       casarOuPular(NUM_INTEIRO, sincBlocoCaso);
                       num = new NoNumReal(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
                   }
            casarOuPular(DOIS_PONTOS, sincBlocoCaso);
            NoListaSentenca *listaSentenca = ListaSentenca();
            return new NoBlocoCaso(num, listaSentenca, BlocoCaso(), pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return NULL;
        break;
    }
}

NoListaExpr *ListaExpr(){
    fprintf(stdout, "ListaExpr\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case E_COMERCIAL:
        case ASCII: {
            NoExpr *expr = Expr();
            return new NoListaExpr(expr, ListaExprCont(), pegarLinha(), pegarColuna());
        } break;
        default: return NULL; break;
    }
}


NoListaExpr *ListaExprCont(){
    fprintf(stdout, "ListaExprCont\n");
    switch(tokenAtual){
        case VIRGULA: {
            casar(VIRGULA);
            NoExpr *expr = Expr();
            return new NoListaExpr(expr, ListaExprCont(), pegarLinha(), pegarColuna());
        } break;
        default: return NULL; break;
    }
}

static int followExpr [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
NoExpr *Expr() {
    fprintf(stdout, "Expr\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
        case E_COMERCIAL:{
            NoExpr *exprOuBool = ExprOuBool();
            return ExprAtrib(exprOuBool);
        } break;
        default:
            /* ERRO */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExpr);
            return NULL;
        break;
    }
}

NoExpr  *ExprAtrib(NoExpr *exprEsquerda) {
    fprintf(stdout, "ExprAtrib\n");
    switch(tokenAtual){
        case ATRIBUICAO: {
            casar(ATRIBUICAO);
            NoExpr *exprDireita =  ExprOuBool();
            return ExprAtrib(new NoExprAtrib(exprEsquerda,exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprOuBool [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
NoExpr  *ExprOuBool(){
    fprintf(stdout, "ExprOuBool\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
        case E_COMERCIAL:{
            NoExpr *exprEBool = ExprEBool();
            return ExprOuBoolL(exprEBool);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprOuBool);
            return NULL;
        break;
    }
}

NoExpr  *ExprOuBoolL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprOuBoolL\n");
    switch(tokenAtual){
        case OU_CC: {
            casar(OU_CC);
            NoExpr *exprDireita =  ExprEBool();
            return ExprOuBoolL(new NoExprBinaria(OU_CC, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprEBool [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC,
                                 TOKEN_EOF};
NoExpr  *ExprEBool(){
    fprintf(stdout, "ExprEBool\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E:             case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
        case E_COMERCIAL:{
            NoExpr *exprIgualdade = ExprIgualdade();
           return ExprEBoolL(exprIgualdade);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprEBool);
            return NULL;
        break;
    }
}

NoExpr  *ExprEBoolL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprEBoolL\n");
    switch(tokenAtual){
        case E: {
            casar(E);
            NoExpr *exprDireita =  ExprIgualdade();
            return ExprEBoolL(new NoExprBinaria(E, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprIgualdade [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                     TOKEN_EOF};
NoExpr  *ExprIgualdade(){
    fprintf(stdout, "ExprIgualdade\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII: {
            NoExpr *exprRelacional = ExprRelacional();
            return ExprIgualdadeL(exprRelacional);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprIgualdade);
            return NULL;
        break;
    }
}

NoExpr  *ExprIgualdadeL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprIgualdadeL\n");
    switch(tokenAtual){
        case COMPARACAO: {
            casar(COMPARACAO);
            NoExpr *exprDireita = ExprRelacional();
            return ExprIgualdadeL(new NoExprBinaria(COMPARACAO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case DIFERENTE: {
            casar(DIFERENTE);
            NoExpr *exprDireita = ExprRelacional();
            return ExprIgualdadeL(new NoExprBinaria(DIFERENTE, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprRelacional [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                      COMPARACAO, DIFERENTE, TOKEN_EOF};
NoExpr  *ExprRelacional(){
    fprintf(stdout, "ExprRelacional\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII:
        {
            NoExpr *exprSoma=ExprSoma();
            return ExprRelacionalL(exprSoma);
        }break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprRelacional);
            return NULL;
        break;
    }
}

NoExpr  *ExprRelacionalL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprRelacionalL\n");
    switch(tokenAtual){
        case MENOR: {
            casar(MENOR);
            NoExpr *exprDireita = ExprSoma();
            return ExprRelacionalL(new NoExprBinaria(MENOR, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case MENOR_IGUAL: {
            casar(MENOR_IGUAL);
            NoExpr *exprDireita = ExprSoma();
            return ExprRelacionalL(new NoExprBinaria(MENOR_IGUAL, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case MAIOR_IGUAL: {
            casar(MAIOR_IGUAL);
            NoExpr *exprDireita = ExprSoma();
            return ExprRelacionalL(new NoExprBinaria(MAIOR_IGUAL, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case MAIOR: {
            casar(MAIOR);
            NoExpr *exprDireita = ExprSoma();
            return ExprRelacionalL(new NoExprBinaria(MAIOR, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprSoma [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};
NoExpr  *ExprSoma(){
    fprintf(stdout, "ExprSoma\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII: {
            NoExpr *exprMultDivE=ExprMultDivE();
            return ExprSomaL(exprMultDivE);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprSoma);
            return NULL;
        break;
    }
}

NoExpr  *ExprSomaL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprSomaL\n");
    switch(tokenAtual){
        case ADICAO: {
            casar(ADICAO);
            NoExpr *exprDireita = ExprMultDivE();
            return ExprSomaL(new NoExprBinaria(ADICAO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case SUBTRACAO: {
            casar(SUBTRACAO);
            NoExpr *exprDireita = ExprMultDivE();
            return ExprSomaL(new NoExprBinaria(SUBTRACAO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case OU: {
            casar(OU);
            NoExpr *exprDireita = ExprMultDivE();
            return ExprSomaL(new NoExprBinaria(OU, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default: return exprEsquerda; break;
    }
}

static int followExprMultDivE [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                    COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO,
                                    SUBTRACAO, OU, TOKEN_EOF};
NoExpr *ExprMultDivE(){
    fprintf(stdout, "ExprMultDivE\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:       case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:         case ESSE:          case NOVO:
        case ADICAO:        case SUBTRACAO:     case ASCII: {
            NoExpr *exprUnaria = ExprUnaria();
            return ExprMultDivEL(exprUnaria);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprMultDivE);
            return NULL;
        break;
    }
}

NoExpr *ExprMultDivEL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprMultDivEL\n");
    switch(tokenAtual){
        case ASTERISCO: {
            casar(ASTERISCO);
            NoExpr *exprDireita = ExprUnaria();
            return ExprMultDivEL(new NoExprBinaria(ASTERISCO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case DIVISAO: {
            casar(DIVISAO);
            NoExpr *exprDireita = ExprUnaria();
            return ExprMultDivEL(new NoExprBinaria(DIVISAO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case PORCENTO: {
            casar(PORCENTO);
            NoExpr *exprDireita = ExprUnaria();
            return ExprMultDivEL(new NoExprBinaria(PORCENTO, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        case E_COMERCIAL: {
            casar(E_COMERCIAL);
            NoExpr *exprDireita = ExprUnaria();
            return ExprMultDivEL(new NoExprBinaria(E_COMERCIAL, exprEsquerda, exprDireita, pegarLinha(), pegarColuna()));
        } break;
        default:
            /* Epsilon */
            return exprEsquerda;
        break;
    }
}

static int followExprUnaria [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                  COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                  OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
NoExpr *ExprUnaria(){
    fprintf(stdout, "ExprUnaria\n");
    switch(tokenAtual){
        case NEGACAO: {
            casar(NEGACAO);
            return new NoExprUnaria(NEGACAO, ExprAceCamp(), pegarLinha(), pegarColuna());
        } break;
        case ADICAO: {
            casar(ADICAO);
            return new NoExprUnaria(ADICAO, ExprAceCamp(), pegarLinha(), pegarColuna());
        } break;
        case SUBTRACAO: {
            casar(SUBTRACAO);
            return new NoExprUnaria(SUBTRACAO, ExprAceCamp(), pegarLinha(), pegarColuna());
        } break;
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII: {
            return ExprAceCamp();
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprUnaria);
            return NULL;
        break;
    }
}

static int followExprAceCamp [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO,
                                   SUBTRACAO, OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
NoExpr *ExprAceCamp(){
    fprintf(stdout, "ExprAceCamp\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII: {
            NoPrimario *exprNovo = ExprNovo();
            return ExprAceCampL(exprNovo);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprAceCamp);
            return NULL;
        break;
    }
}

NoExpr *ExprAceCampL(NoExpr *exprEsquerda){
    fprintf(stdout, "ExprAceCampL\n");
    switch(tokenAtual){
        case PONTEIRO: {
            casar(PONTEIRO);
            NoPrimario *exprDireita = ExprNovo();
            return ExprAceCampL(new NoExprAceCamp(exprEsquerda, exprDireita, PONTEIRO, pegarLinha(), pegarColuna()));
        } break;
        case PONTO: {
            casar(PONTO);
            NoPrimario *exprDireita = ExprNovo();
            return ExprAceCampL(new NoExprAceCamp(exprEsquerda, exprDireita, PONTO, pegarLinha(), pegarColuna()));
        } break;
        default:
            /* Epsilon */
            return exprEsquerda;
        break;
    }
}

static int followExprNovo [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};
NoPrimario *ExprNovo(){
    fprintf(stdout, "ExprNovo\n");
    switch(tokenAtual){
        case ID:            case ASTERISCO:     case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ: case LITERAL:
        case E_COMERCIAL:   case VERDADEIRO:    case FALSO:
        case ESSE:          case NOVO:          case ASCII: {
            NoPrimario *primario = Primario();
            return ExprNovoL(primario);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followExprNovo);
            return NULL;
        break;
    }
}

static int followExprNovoL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                 COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                 OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ,
                                 TOKEN_EOF};
NoPrimario *ExprNovoL(NoPrimario *primario){
    fprintf(stdout, "ExprNovoL\n");
    switch(tokenAtual){
        case COLCHETE_ESQ: {
            casar(COLCHETE_ESQ);
            NoExpr *expr = Expr();
            casarOuPular(COLCHETE_DIR, followExprNovoL);
            return ExprNovoL(new NoColchetes(primario, expr, pegarLinha(), pegarColuna()));
        } break;
        default:
            /* Epsilon */
            return primario;
        break;
    }
}

static int followPrimario [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ,
                                TOKEN_EOF};
NoPrimario *Primario() {
    fprintf(stdout, "Primario\n");
    switch(tokenAtual){
        case ID:
            return PrimarioID();
        break;
        case ASTERISCO:     case NUM_INTEIRO:   case NUM_REAL:
        case PARENTESE_ESQ: case LITERAL:       case E_COMERCIAL:
        case VERDADEIRO:    case FALSO:         case ESSE:
        case NOVO:          case ASCII:
            return PrimarioL();
        break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followPrimario);
            return NULL;
        break;
    }
}

static int followPrimarioL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                 COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                 OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ,
                                 PARENTESE_ESQ, TOKEN_EOF};
NoPrimario *PrimarioL(){
    fprintf(stdout, "PrimarioL\n");
    switch(tokenAtual){
        case NUM_INTEIRO: {
            casar(NUM_INTEIRO);
            return new NoNumInteiro(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
        } break;
        case NUM_REAL: {
            casar(NUM_REAL);
            return new NoNumReal(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
        } break;
        case LITERAL: {
            casar(LITERAL);
            return new NoLiteral(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
        } break;
        case ASCII: {
            casar(ASCII);
            return new NoAscii(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
        } break;
        case PARENTESE_ESQ: {
            casar(PARENTESE_ESQ);
            NoExpr *expr = Expr();
            casarOuPular(PARENTESE_DIR, followPrimarioL);
            return new NoParenteses(expr, pegarLinha(), pegarColuna());
        } break;
        case E_COMERCIAL: {
            casar(E_COMERCIAL);
            return new NoEndereco(Primario(), pegarLinha(), pegarColuna());
        } break;
        case ASTERISCO: {
            casar(ASTERISCO);
            return new NoConteudo(Primario(), pegarLinha(), pegarColuna());
        } break;
        case VERDADEIRO: {
            casar(VERDADEIRO);
            return new NoVerdadeiro();
        } break;
        case FALSO: {
            casar(FALSO);
            return new NoFalso();
        } break;
        case ESSE: {
            casar(ESSE);
            return new NoEsse();
        } break;
        case NOVO: {
            casar(NOVO);
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casarOuPular(ID, followPrimarioL);
            casarOuPular(PARENTESE_ESQ, followPrimarioL);
            NoListaExpr *listaExpr = ListaExpr();
            casarOuPular(PARENTESE_DIR, followPrimarioL);
            return new NoNovo(id, listaExpr, pegarLinha(), pegarColuna());
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followPrimarioL);
            return NULL;
        break;
    }
}

static int followPrimarioID [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                  COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
                                  OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ,
                                  TOKEN_EOF};
NoPrimario *PrimarioID(){
    fprintf(stdout, "PrimarioID\n");
    switch(tokenAtual){
        case ID: {
            NoId *id = new NoId(pegarUltimoAtributo(), pegarLinha(), pegarColuna());
            casar(ID);
            return PrimarioIDL(id);
        } break;
        default:
            /* Erro */
            saidaErro(ErroSintatico, pegarLinha(), pegarColuna(), tokenLiteral[tokenAtual],
                      esperadosLiteral[EsperadosExpressaoPrimaria]);
            pular(followPrimarioID);
            return NULL;
        break;
    }
}

static int followPrimarioIDL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
                                   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO,
                                   SUBTRACAO, OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO,
                                   COLCHETE_ESQ, TOKEN_EOF};
NoPrimario *PrimarioIDL(NoId *id){
    fprintf(stdout, "PrimarioIDL\n");
    switch(tokenAtual){
        case PARENTESE_ESQ: {
            casar(PARENTESE_ESQ);
            NoListaExpr *listaExpr = ListaExpr();
            casarOuPular(PARENTESE_DIR, followPrimarioIDL);
            return new NoChamadaFuncao(id, listaExpr, pegarLinha(), pegarColuna());
        } break;
        default:
            /* Epsilon */
            return id;
        break;
    }
}
