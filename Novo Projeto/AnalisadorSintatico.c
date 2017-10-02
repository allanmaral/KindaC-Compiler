
static int intfollowPrograma []		= {TOKEN_EOF};
static int followProgramaA [] 		= {TOKEN_EOF};
static int followProgramaB []		= {TOKEN_EOF};

static int followDeclClasse []		= {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};
static int followDeclClasseL []		= {DEFINICAO_TIPO, INTEIRO, REAL, BOLEANO, CARACTERE, ID, CLASSE, TOKEN_EOF};

static int followDeclLocal []		= {CHAVE_DIR, TOKEN_EOF};
static int followDeclLocalL []		= {CHAVE_DIR, TOKEN_EOF};
static int followDeclLocalLL []		= {CHAVE_DIR, TOKEN_EOF};

static int followListaId []			= {PONTO_VIRGULA, TOKEN_EOF};
static int followListaIdCont []		= {PONTO_VIRGULA, TOKEN_EOF};

static int followPonteiro []		= {ID, TOKEN_EOF};

static int followArranjo []			= {VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};

static int followListaForma []		= {PARENTESE_DIR, TOKEN_EOF};
static int followListaFormaCont []	= {PARENTESE_DIR, TOKEN_EOF};

static int followTipo []			= {ID, ASTERISCO, TOKEN_EOF};
static int followTipoL []			= {ID, ASTERISCO, TOKEN_EOF};

static int followListaSentenca []	= {CHAVE_DIR, CASO, TOKEN_EOF};

static int followSentenca []		= {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
									   NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
									   SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA,
									   LANCA, TENTA, PEGA, TOKEN_EOF};

static int followSentencaL []		= {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
									   NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
									   SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA,
									   LANCA, TENTA, PEGA, TOKEN_EOF};

static int followSe []				= {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
									   NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
									   SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA,
									   LANCA, TENTA, PEGA, TOKEN_EOF};

static int followSenao []			= {CHAVE_ESQ, ID, ASTERISCO, NUM_INTEIRO, NUM_REAL, CHAVE_DIR, PARENTESE_ESQ,
									   NEGACAO, LITERAL, E_COMERCIAL, VERDADEIRO, FALSO, ESSE, NOVO, ADICAO,
									   SUBTRACAO, SE, SENAO, ENQUANTO, ESCOLHA, DESVIA, IMPRIME, LE_LINHA, RETORNA,
									   LANCA, TENTA, PEGA, TOKEN_EOF};

static int followBlocoCaso []		= {CHAVE_DIR, TOKEN_EOF};

static int followListaExpr []		= {PARENTESE_DIR, TOKEN_EOF};
static int followListaExprCont []	= {PARENTESE_DIR, TOKEN_EOF};

static int followExpr []			= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};
static int followExprAtrib []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, TOKEN_EOF};

static int followExprOuBool []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};
static int followExprOuBoolL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, TOKEN_EOF};

static int followExprEBool []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};
static int followExprEBoolL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, TOKEN_EOF};

static int followExprIgualdade []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   TOKEN_EOF};

static int followExprIgualdadeL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   TOKEN_EOF};

static int followExprRelacional []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, TOKEN_EOF};

static int followExprRelacionalL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, TOKEN_EOF};

static int followExprSoma []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};

static int followExprSomaL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, TOKEN_EOF};

static int followExprMultDivE []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, TOKEN_EOF};

static int followExprMultDivEL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, TOKEN_EOF};

static int followExprUnaria []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};

static int followExprAceCamp []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};

static int followExprAceCampL []	= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, TOKEN_EOF};

static int followExprNovo []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};

static int followExprNovoL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, TOKEN_EOF};

static int followPrimario []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};

static int followPrimarioL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};

static int followPrimarioID []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};

static int followPrimarioIDL []		= {COLCHETE_DIR, VIRGULA, PONTO_VIRGULA, PARENTESE_DIR, ATRIBUICAO, OU_CC, E,
									   COMPARACAO, DIFERENTE, MENOR, MENOR_IGUAL, MAIOR_IGUAL, MAIOR, ADICAO, SUBTRACAO,
									   OU, ASTERISCO, E_COMERCIAL, DIVISAO, PORCENTO, PONTEIRO, PONTO, COLCHETE_ESQ, TOKEN_EOF};


static int tokenAtual;

void match(int token){
	tokenAtual = proximoToken();
}

void Programa(){
	switch(tokenAtual){
		case DEFINICAO_TIPO:
			match(tokenAtual);
			if(tokenAtual == ESTRUTURA) { match(tokenAtual); }
			if(tokenAtual == COLCHETE_ESQ) { match(tokenAtual); }
			Tipo();
			ListaId();
			if(tokenAtual == PONTO_VIRGULA) { match(tokenAtual); }
			DeclVar();
			if(tokenAtual == COLCHETE_DIR) { match(tokenAtual); }
			if(tokenAtual == ID) { match(tokenAtual); }
			if(tokenAtual == VIRGULA) { match(tokenAtual); }
			Programa();
		break;
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			Tipo();
			Ponteiro();
			if(tokenAtual == ID) { match(tokenAtual); }
			ProgramaA;
		break;
		case CLASSE:
			DeclClasse();
			Programa();
		break;
	}
}

void ProgramaA(){
	switch(tokenAtual){
		case PARENTESE_ESQ:
			match(tokenAtual);
			ListaForma();
			if(tokenAtual == PARENTESE_DIR) { match(tokenAtual); }
			if(tokenAtual == CHAVE_ESQ) { match(tokenAtual); }
			DeclLocalLL();
			if(tokenAtual == CHAVE_DIR) { match(tokenAtual); }
			Programa();
		break;
		case COLCHETE_ESQ:
			Arranjo();
			ListaIdCont();
			if(tokenAtual == PONTO_VIRGULA) { match(tokenAtual); }
			ProgramaB();
		break;
	}
}

void ProgramaB(){
	switch(tokenAtual){
		case DEFINICAO_TIPO:
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
		case CLASSE:
			Programa();
		break;
		default: /* Epsilon */ break;
	}
}

void DeclClasse(){
	switch(tokenAtual){
		case CLASSE:
			match(tokenAtual);
			if(tokenAtual == ID) { match(tokenAtual); }
			DeclClasseL();
		break;
		default: /* ERRO */ break;
	}
}

void DeclClasseL(){
	switch(tokenAtual){
		case CHAVE_ESQ:
			match(tokenAtual);
			DeclLocal();
			if(tokenAtual == CHAVE_DIR) { match(tokenAtual); }
			if(tokenAtual == PONTO_VIRGULA) { match(tokenAtual); }
		break;
		case DOIS_PONTOS:
			match(tokenAtual);
			if(tokenAtual == ID) { match(tokenAtual); }
			if(tokenAtual == CHAVE_ESQ) { match(tokenAtual); }
			DeclLocal();
			if(tokenAtual == CHAVE_DIR) { match(tokenAtual); }
			if(tokenAtual == PONTO_VIRGULA) { match(tokenAtual); }
		break;
		default: /* ERRO */ break;
	}
}

void DeclLocal(){
	switch(tokenAtual){
		case ID: case INTEIRO: case REAL: case BOLEANO: case CARACTERE:
			Tipo();
			Ponteiro();
			if(tokenAtual == ID) { match(tokenAtual); }
			DeclLocalL();
		break;
		case PUBLICO:
			match(tokenAtual);
			if(tokenAtual == DOIS_PONTOS) { match(tokenAtual); }
		break;
		case PRIVADO:
			match(tokenAtual);
			if(tokenAtual == DOIS_PONTOS) { match(tokenAtual); }
		break;
		default: /* ERRO */ break;
	}
}

void DeclLocalL(){
	switch(tokenAtual){
		case PARENTESE_ESQ:
			match(tokenAtual);
			ListaForma();
			if(tokenAtual == PARENTESE_DIR) { match(tokenAtual); }
			if(tokenAtual == CHAVE_ESQ) { match(tokenAtual); }
			DeclLocalLL();
			if(tokenAtual == CHAVE_DIR) { match(tokenAtual); }
			DeclLocal();
		break;
		case COLCHETE_ESQ:
			Arranjo();
			ListaIdCont();
			if(tokenAtual == PONTO_VIRGULA) { match(tokenAtual); }
			DeclLocal();
		break;
		default: /* ERRO */ break;
	}
}
