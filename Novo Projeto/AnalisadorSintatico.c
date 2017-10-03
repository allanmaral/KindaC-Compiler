#include "AnalisadorLexico.h"

static int tokenAtual;

void casar(int token){
    // Faz alguma coisa aquim
    tokenAtual = proximoToken();
}

void pular(int* sinc){
    int sincronizado = 0;
    int indice = 0;
    // Enquanto ainda não tiver sido sincronizado, verifica se o token atual pertence ao sinc
    while(!sincronizado) {
        // Percorre a lista de sync
        do {
            if(tokenAtual == sinc[indice]) {
                sincronizado = 1;
                return;
            }
            indice++;
        } while(sinc[indice] != TOKEN_EOF);
        // Se chegar aqui, o erro ainda não foi sincronizado
        tokenAtual = proximoToken();
    }
}

void casarOuPular(int token, int* sinc){
    if(tokenAtual == token) {
        casar(token);
    } else {
          /// LANCA ERRO AQUI
          pular(sinc);
      }
}

void Programa();
void ProgramaA();
void ProgramaB();
void DeclClasse();
void DeclClasseL();
void DeclLocal();
void DeclLocalL();
void DeclLocalLL();
void DeclVar();
void ListaId();
void ListaIdCont();
void Ponteiro();
void Arranjo();
void ListaForma();
void ListaFormaCont();
void Tipo();
void TipoL();
void ListaSentenca();
void Sentenca();
void SentencaL();
void Se();
void Senao();
void BlocoCaso();
void ListaExpr();
void ListaExprCont();
void Expr();
void ExprAtrib();
void ExprOuBool();
void ExprOuBoolL();
void ExprEBool();
void ExprEBoolL();
void ExprIgualdade();
void ExprIgualdadeL();
void ExprRelacional();
void ExprRelacionalL();
void ExprSoma();
void ExprSomaL();
void ExprMultDivE();
void ExprMultDivEL();
void ExprUnaria();
void ExprAceCamp();
void ExprAceCampL();
void ExprNovo();
void ExprNovoL();
void Primario();
void PrimarioID();
void PrimarioIDL();
void PrimarioL();



static int followPrograma [] = {TOKEN_EOF};
void Programa(){
	switch(tokenAtual){
		case DEFINICAO_TIPO:
			casar(DEFINICAO_TIPO);
			casarOuPular(ESTRUTURA, followPrograma);
			casarOuPular(COLCHETE_ESQ, followPrograma);
			Tipo();
			ListaId();
			casarOuPular(PONTO_VIRGULA, followPrograma);
			DeclVar();
			casarOuPular(COLCHETE_DIR, followPrograma);
			casarOuPular(ID, followPrograma);
			casarOuPular(VIRGULA, followPrograma);
			Programa();
		break;
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			Tipo();
			Ponteiro();
			casarOuPular(ID, followPrograma);
			ProgramaA();
		break;
		case CLASSE:
			DeclClasse();
			Programa();
		break;
	}
}

static int followProgramaA [] = {TOKEN_EOF};
void ProgramaA(){
	switch(tokenAtual){
		case PARENTESE_ESQ:
			casar(PARENTESE_ESQ);
			ListaForma();
			casarOuPular(PARENTESE_DIR, followProgramaA);
			casarOuPular(CHAVE_ESQ, followProgramaA);
			DeclLocalLL();
			casarOuPular(CHAVE_DIR, followProgramaA);
			Programa();
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
		case COLCHETE_ESQ:
			Arranjo();
			ListaIdCont();
			casarOuPular(PONTO_VIRGULA, followProgramaA);
			ProgramaB();
		break;
	}
}

static int followProgramaB [] = {TOKEN_EOF};
void ProgramaB(){
	switch(tokenAtual){
		case DEFINICAO_TIPO: case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE: case CLASSE:
			Programa();
		break;
		default: /* Epsilon */ break;
	}
}

static int followDeclClasse [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
void DeclClasse(){
	switch(tokenAtual){
		case CLASSE:
			casar(CLASSE);
			casarOuPular(ID, followDeclClasse);
			DeclClasseL();
		break;
		default: /* ERRO */ break;
	}
}

static int followDeclClasseL [] = {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
void DeclClasseL(){
	switch(tokenAtual){
		case CHAVE_ESQ:
			casar(CHAVE_ESQ);
			DeclLocal();
			casarOuPular(CHAVE_DIR, followDeclClasseL);
			casarOuPular(PONTO_VIRGULA, followDeclClasseL);
		break;
		case DOIS_PONTOS:
			casar(DOIS_PONTOS);
			casarOuPular(ID, followDeclClasseL);
			casarOuPular(CHAVE_ESQ, followDeclClasseL);
			DeclLocal();
			casarOuPular(CHAVE_DIR, followDeclClasseL);
			casarOuPular(PONTO_VIRGULA, followDeclClasseL);
		break;
		default: /* ERRO */ break;
	}
}

static int followDeclLocal [] = {CHAVE_DIR, TOKEN_EOF};
void DeclLocal(){
	switch(tokenAtual){
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			Tipo();
			Ponteiro();
			casarOuPular(ID, followDeclLocal);
			DeclLocalL();
		break;
		case PUBLICO:
			casar(PUBLICO);
			casarOuPular(DOIS_PONTOS, followDeclLocal);
		break;
		case PRIVADO:
			casar(PRIVADO);
			casarOuPular(DOIS_PONTOS, followDeclLocal);
		break;
		default: /* ERRO */ break;
	}
}

static int followDeclLocalL [] = {CHAVE_DIR, TOKEN_EOF};
void DeclLocalL(){
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
		case VIRGULA:
			ListaIdCont();
			casarOuPular(PONTO_VIRGULA, followDeclLocalL);
			DeclLocal();
		break;
		case PONTO_VIRGULA:
			casar(PONTO_VIRGULA);
			DeclLocal();
		break;
		case COLCHETE_ESQ:
			Arranjo();
			ListaIdCont();
			casarOuPular(PONTO_VIRGULA, followDeclLocalL);
			DeclLocal();
		break;
		default: /* ERRO */ break;
	}
}

static int followDeclLocalLL [] = {CHAVE_DIR, TOKEN_EOF};
void DeclLocalLL(){
	switch(tokenAtual){
		case ID:        case NUM_INTEIRO:   case NUM_REAL:
        case ASTERISCO: case PARENTESE_ESQ: case NEGACAO:
        case LITERAL:   case E_COMERCIAL:   case VERDADEIRO:
        case FALSO:     case ESSE:          case NOVO:
        case ADICAO:    case SUBTRACAO:
			Expr();
			ListaIdCont();
			casarOuPular(PONTO_VIRGULA, followDeclLocalLL);
			ListaSentenca();
		break;
		case CHAVE_ESQ: case SE:            case ENQUANTO:
        case ESCOLHA:   case DESVIA:        case IMPRIME:
        case LE_LINHA:  case RETORNA:       case LANCA:
        case TENTA:
			SentencaL();
			ListaSentenca();
		break;
		case INTEIRO:   case REAL:          case BOLEANO:
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
	switch(tokenAtual){
		case INTEIRO: case REAL: case BOLEANO: case CARACTERE: case ID:
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
	switch(tokenAtual){
		case VIRGULA:
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
	switch(tokenAtual){
		case ASTERISCO:
			casar(ASTERISCO);
		break;
		default: /* Epsilon */ break;
	}
}

static int followArranjo [] = {VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void Arranjo(){
	switch(tokenAtual){
		case CHAVE_ESQ:
			casar(CHAVE_ESQ);
			casarOuPular(NUM_INTEIRO, followArranjo);
			//casarOuPular(NUM_REAL, followArranjo);
			casarOuPular(CHAVE_DIR, followArranjo);
		break;
		default: /* Epsilon */ break;
	}
}

static int followListaForma [] = {PARENTESE_DIR, TOKEN_EOF};
void ListaForma(){
	switch(tokenAtual){
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			Tipo();
			Ponteiro();
			casarOuPular(ID, followListaForma);
			Arranjo();
			ListaFormaCont();
		break;
		default: /* Epsilon */ break;
	}
}
static int followListaFormaCont []	= {PARENTESE_DIR, TOKEN_EOF};
void ListaFormaCont(){
	switch(tokenAtual){
		case VIRGULA:
			Tipo();
			Ponteiro();
			casarOuPular(ID,followListaFormaCont);
			Arranjo();
			ListaFormaCont();
		break;
		default: /* Epsilion*/ break;
	}
}

static int followTipo [] = {ID, ASTERISCO, TOKEN_EOF};
void Tipo(){
	switch(tokenAtual){
		case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			TipoL();
		case ID: casarOuPular(ID,followTipo);
		break;
		default: /*ERRO*/ break;
	}
}

static int followTipoL [] = {ID, ASTERISCO, TOKEN_EOF};
void TipoL(){
	switch(tokenAtual){
		case INTEIRO: casar(INTEIRO);	  break;
		case REAL: casar(REAL); 	 	  break;
		case BOLEANO: casar(BOLEANO);	  break;
		case CARACTERE: casar(CARACTERE); break;
		default: /*ERRO*/ 				  break;
	}
}

static int followListaSentenca [] = {CHAVE_DIR, CASO, TOKEN_EOF};
void ListaSentenca(){
	switch(tokenAtual){
		case CHAVE_ESQ: case ID: case ASTERISCO: case NUM_INTEIRO: case NUM_REAL: case PARENTESE_ESQ: case NEGACAO:
		case CARACTERE: case LITERAL: case E_COMERCIAL: case E: case VERDADEIRO: case FALSO: case ESSE:  case NOVO:
		case ADICAO: case SUBTRACAO: case SE: case ENQUANTO: case ESCOLHA: case DESVIA: case IMPRIME: case LE_LINHA:
		case RETORNA: case LANCA: case TENTA:
			Sentenca();
			ListaSentenca();
		break;
		default: /* Epsilon */ break;
	}
}


static int followSentenca [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void Sentenca(){
	switch(tokenAtual){
		case ID: case ASTERISCO: case NUM_INTEIRO: case NUM_REAL: case PARENTESE_ESQ: case NEGACAO:
		case CARACTERE: case LITERAL: case E_COMERCIAL: case VERDADEIRO: case FALSO: case ESSE:  case NOVO:
		case ADICAO: case SUBTRACAO:
			Expr();
			casarOuPular(PONTO_VIRGULA,followSentenca);
		break;
		case CHAVE_ESQ: case SE: case ENQUANTO: case ESCOLHA: case DESVIA: case IMPRIME: case LE_LINHA:
		case RETORNA: case LANCA: case TENTA:
			SentencaL();
		break;
		default: /*Epsilon*/ break;
	}
}

static int followSentencaL [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void SentencaL(){
	switch(tokenAtual){
		case CHAVE_ESQ:
			ListaSentenca();
			casarOuPular(CHAVE_DIR,followSentencaL);
		break;
		case SE:
			Se();
		break;
		case ENQUANTO:
			casar(ENQUANTO);
			casarOuPular(PARENTESE_ESQ,followSentencaL);
			Expr();
			casarOuPular(PARENTESE_DIR,followSentencaL);
			Sentenca();
		break;
		case ESCOLHA:
			casar(ESCOLHA);
			casarOuPular(PARENTESE_ESQ,followSentencaL);
			Expr();
			casarOuPular(PARENTESE_DIR,followSentencaL);
			casarOuPular(CHAVE_ESQ,followSentencaL);
			BlocoCaso();
			casarOuPular(CHAVE_DIR,followSentencaL);
		break;
		case DESVIA:
			casar(DESVIA);
		break;
		case IMPRIME:
			casar(IMPRIME);
			casarOuPular(PARENTESE_ESQ,followSentencaL);
			ListaExpr();
			casarOuPular(PARENTESE_DIR,followSentencaL);
			casarOuPular(PONTO_VIRGULA,followSentencaL);
		break;
		case LE_LINHA:
			casar(LE_LINHA);
			casarOuPular(PARENTESE_ESQ,followSentencaL);
			Expr();
			casarOuPular(PARENTESE_DIR,followSentencaL);
			casarOuPular(PONTO_VIRGULA,followSentencaL);
		break;
		case RETORNA:
			casar(RETORNA);
			Expr();
		break;
		case LANCA:
			 casar(LANCA);
			 casarOuPular(PONTO_VIRGULA,followSentencaL);
		break;
		case TENTA:
			casar(TENTA);
			Sentenca();
			casarOuPular(PEGA,followSentencaL);
			casarOuPular(PARENTESE_DIR,followSentencaL);
			ListaExpr();
			casarOuPular(PARENTESE_ESQ,followSentencaL);
			Sentenca();
		break;
		default: /*ERRO*/ break;
	}
}

static int followSe [] = {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ, NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO, SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA, LANCA, TENTA, PEGA, TOKEN_EOF};
void Se(){
	switch(tokenAtual){
		case SE:
			casar(SE);
			casarOuPular(PARENTESE_ESQ,followSe);
			Expr();
			casarOuPular(PARENTESE_ESQ,followSe);
			Sentenca();
			Senao();
		break;
		default: /*ERRO*/ break;
	}
}

static int followSenao []			= {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
	NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
	SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA,
	LANCA, TENTA, PEGA, TOKEN_EOF};
void Senao(){
	switch(tokenAtual){
		case SENAO:
			casar(SENAO);
			Sentenca();
		break;
		default: /* epsilon */ break;
	}
}

static int followBlocoCaso []		= {CHAVE_DIR, TOKEN_EOF};
void BlocoCaso(){
	switch(tokenAtual){
		case CASO:
			casar(CASO);
			if(tokenAtual == NUM_INTEIRO || tokenAtual == NUM_REAL) {
				casarOuPular(NUM_INTEIRO, followBlocoCaso);
			}
			if(tokenAtual == DOIS_PONTOS) {
				casarOuPular(DOIS_PONTOS, followBlocoCaso);
			}
			ListaSentenca();
			BlocoCaso();
		break;
		default: /* epsilon */ break;
	}
}



static int followListaExpr []		= {PARENTESE_DIR, TOKEN_EOF};
void ListaExpr(){
	switch(tokenAtual) {
		case ID:        case ASTERISCO:     case NUM_INTEIRO:
		case NUM_REAL:  case PARENTESE_ESQ: case NEGACAO:
		case LITERAL:   case E:             case VERDADEIRO:
		case FALSO:     case ESSE:          case NOVO:
		case ADICAO:    case SUBTRACAO:
			Expr();
			ListaExprCont();
		break;
		default: /* epsilon */ break;
	}
}


static int followListaExprCont []	= {PARENTESE_DIR, TOKEN_EOF};
void ListaExprCont(){
	switch(tokenAtual) {
		case VIRGULA:
			casar(VIRGULA);
			ListaExprCont();
		break;
		default: /* epsilon */ break;
	}
}

static int followExpr []			= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void Expr() {
	switch(tokenAtual) {
		case ID:        case ASTERISCO:     case NUM_INTEIRO:
		case NUM_REAL:  case PARENTESE_ESQ: case NEGACAO:
		case LITERAL:   case E:             case VERDADEIRO:
		case FALSO:     case ESSE:          case NOVO:
		case ADICAO:    case SUBTRACAO:
			ExprOuBool();
			ExprAtrib();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprAtrib []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
void ExprAtrib() {
	switch(tokenAtual) {
		case ATRIBUICAO:
			casar(ATRIBUICAO);
			ExprOuBool();
			ExprAtrib();
		break;
		default: /* epsilon */ break;
	}
}

static int followExprOuBool []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
void ExprOuBool(){
	switch(tokenAtual) {
		case ID:        case ASTERISCO:     case NUM_INTEIRO:
		case NUM_REAL:  case PARENTESE_ESQ: case NEGACAO:
		case LITERAL:   case E:             case VERDADEIRO:
		case FALSO:     case ESSE:          case NOVO:
		case ADICAO:    case SUBTRACAO:
			ExprEBool();
			ExprOuBoolL();
		break;
		default: /* Erro */ break;
	}
}

static int followExprOuBoolL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
void ExprOuBoolL(){
	switch(tokenAtual){
		case OU_CC:
			casar(OU_CC);
			ExprEBool();
			ExprOuBoolL();
		break;
		default: /* epsilon */ break;
	}
}

static int followExprEBool []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};
void ExprEBool(){
	switch(tokenAtual) {
		case ID:        case ASTERISCO:     case NUM_INTEIRO:
		case NUM_REAL:  case PARENTESE_ESQ: case NEGACAO:
		case LITERAL:   case E:             case VERDADEIRO:
		case FALSO:     case ESSE:          case NOVO:
		case ADICAO:    case SUBTRACAO:
			ExprIgualdade();
			ExprEBoolL();
		break;
		default: /* Erro */ break;
	}
}

static int followExprEBoolL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};
void ExprEBoolL(){
	switch(tokenAtual){
		case E:
			ExprIgualdade();
			ExprEBoolL();
		break;
		default: /* epsilon */ break;
	}
}

static int followExprIgualdade [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, TOKEN_EOF};
void ExprIgualdade(){
	switch(tokenAtual){
		case ID:            case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ:     case NEGACAO:
        case LITERAL:       case E_COMERCIAL:       case VERDADEIRO:
        case FALSO:         case ESSE:              case NOVO:
        case ADICAO:        case SUBTRACAO:
			ExprRelacional();
			ExprIgualdadeL();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprIgualdadeL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, TOKEN_EOF};
void ExprIgualdadeL(){
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

static int followExprRelacional [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO, DIFERENTE, TOKEN_EOF};
void ExprRelacional(){
	switch(tokenAtual){
		case ID:            case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:      case PARENTESE_ESQ:     case NEGACAO:
        case LITERAL:       case E_COMERCIAL:       case VERDADEIRO:
        case FALSO:         case ESSE:              case NOVO:
        case ADICAO:        case SUBTRACAO:
			ExprSoma();
			ExprRelacionalL();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprRelacionalL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO, DIFERENTE, TOKEN_EOF};
void ExprRelacionalL(){
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
		case MAIOR:
			casar(MAIOR);
			ExprSoma();
			ExprRelacionalL();
		break;
		case MAIOR_IGUAL:
			casar(MAIOR_IGUAL);
			ExprSoma();
			ExprRelacionalL();
		break;
		default: /* Epsilon */ break;
	}
}

static int followExprSoma [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};
void ExprSoma(){
	switch(tokenAtual){
		case ID:        case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:  case PARENTESE_ESQ:     case NEGACAO:
        case LITERAL:   case E_COMERCIAL:       case VERDADEIRO:
        case FALSO:     case ESSE:              case NOVO:
        case ADICAO:    case SUBTRACAO:
			ExprMultDivE();
			ExprSomaL();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprSomaL [] = {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E, COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};
void ExprSomaL(){
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

static int followExprMultDivE []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, TOKEN_EOF};
void ExprMultDivE(){
    switch(tokenAtual){
		case ID:        case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:  case PARENTESE_ESQ:     case NEGACAO:
        case LITERAL:   case E_COMERCIAL:       case VERDADEIRO:
        case FALSO:     case ESSE:              case NOVO:
        case ADICAO:    case SUBTRACAO:
			ExprUnaria();
			ExprMultDivEL();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprMultDivEL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, TOKEN_EOF};
void ExprMultDivEL(){
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
        default: /* epsilon */ break;
    }
}

static int followExprUnaria []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprUnaria(){
    switch(tokenAtual){
        case ADICAO:
            casar(ADICAO);
            ExprAceCamp();
        break;
        case SUBTRACAO:
            casar(SUBTRACAO);
            ExprAceCamp();
        break;
        case NEGACAO:
            casar(NEGACAO);
            ExprAceCamp();
        break;
		case ID:                case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:          case PARENTESE_ESQ:     case LITERAL:
        case E_COMERCIAL:       case VERDADEIRO:        case FALSO:
        case ESSE:              case NOVO:
			ExprAceCamp();
		break;
		default: /* ERRO */ break;
	}
}

static int followExprAceCamp []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprAceCamp(){
    switch(tokenAtual){
        case ID:                case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:          case PARENTESE_ESQ:     case LITERAL:
        case E_COMERCIAL:       case VERDADEIRO:        case FALSO:
        case ESSE:              case NOVO:
            ExprNovo();
            ExprAceCampL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprAceCampL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};
void ExprAceCampL(){
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
        default: /* epsilon */ break;
    }
}

static int followExprNovo []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};
void ExprNovo(){
    switch(tokenAtual){
        case ID:                case ASTERISCO:         case NUM_INTEIRO:
        case NUM_REAL:          case PARENTESE_ESQ:     case LITERAL:
        case E_COMERCIAL:       case VERDADEIRO:        case FALSO:
        case ESSE:              case NOVO:
            Primario();
            ExprNovoL();
        break;
        default: /* ERRO */ break;
    }
}

static int followExprNovoL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};
void ExprNovoL(){
    switch(tokenAtual){
        case COLCHETE_ESQ:
            casar(COLCHETE_ESQ);
            Expr();
            casarOuPular(COLCHETE_DIR, followExprNovoL);
            ExprNovoL();
        break;
        default: /* epsilon */ break;
    }
}

static int followPrimario []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void Primario() {
    switch(tokenAtual){
        case ID:
            PrimarioID();
        case ASTERISCO:         case NUM_INTEIRO:       case NUM_REAL:
        case PARENTESE_ESQ:     case LITERAL:           case E_COMERCIAL:
        case VERDADEIRO:        case FALSO:             case ESSE:
        case NOVO:
            PrimarioL();
        break;
        default: /* ERRO */ break;
    }
}

static int followPrimarioL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioL(){
    switch(tokenAtual){
        case ASTERISCO:
            casar(ASTERISCO);
            Primario();
        break;
        case NUM_INTEIRO:
            casar(NUM_INTEIRO);
        break;
        case NUM_REAL:
            casar(NUM_REAL);
        break;
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            Expr();
            casarOuPular(PARENTESE_DIR, followPrimarioL);
        break;
        case LITERAL:
            casar(LITERAL);
        break;
        case E_COMERCIAL:
            casar(E_COMERCIAL);
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

static int followPrimarioID []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioID(){
    switch(tokenAtual){
        case ID:
            casar(ID);
            PrimarioIDL();
        break;
        default: /* ERRO */ break;
    }
}

static int followPrimarioIDL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};
void PrimarioIDL(){
    switch(tokenAtual) {
        case PARENTESE_ESQ:
            casar(PARENTESE_ESQ);
            ListaExpr();
            casarOuPular(PARENTESE_DIR, followPrimarioIDL);
        break;
        default: /* epsilon */ break;
    }
}
