#include <stdio.h>
#include <stdlib.h>
#include "ASA.h"
#include "Visitante.h"
#include "AnalisadorSintatico.h"

void VisitanteImpressao::calculaNivel(){
	for(int i=0; i<nivel; i++){
        fprintf(stdout, "   ");
    }
}
VisitanteImpressao::VisitanteImpressao(){
    nivel=0;
}
void VisitanteImpressao::visita(NoPrograma *prog){
    fprintf(stdout, "\n\n-PROGRAMA\n");
    if(NoDeclClasse* decC = dynamic_cast<NoDeclClasse*>(prog)) { decC->aceita(this); }
    else if(NoDeclTipo* decT = dynamic_cast<NoDeclTipo*>(prog)) { decT->aceita(this); }
    else if(NoDeclVariavel* decV = dynamic_cast<NoDeclVariavel*>(prog)) { decV->aceita(this); }
    else if(NoDeclFuncao* decF = dynamic_cast<NoDeclFuncao*>(prog)) { decF->aceita(this); }
}
void VisitanteImpressao::visita(NoId *id ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ID.%s\n", id->entradaTabela->pegarLexema());
	nivel--;
}
void VisitanteImpressao::visita(NoLiteral *lit){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-LITERAL.%s\n", lit->entradaTabela->pegarLexema());
	nivel--;
}
void VisitanteImpressao::visita(NoAscii *asc){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ASCII.%s\n", asc->entradaTabela->pegarLexema());
	nivel--;
}
void VisitanteImpressao::visita(NoParenteses *pa){
	if(pa->expressao) pa->expressao->aceita(this);
}
void VisitanteImpressao::visita(NoConteudo *con){
	nivel++;
	calculaNivel();
	if(con->primario)con->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoEndereco *ende){
    nivel++;
	calculaNivel();
	if(ende->primario)ende->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoNumInteiro *ni){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_INTEIRO.%s\n", ni->entradaTabela->pegarLexema());
	nivel--;
}
void VisitanteImpressao::visita(NoNumReal *nr){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_REAL.%s\n", nr->entradaTabela->pegarLexema());
	nivel--;
}
void VisitanteImpressao::visita(NoArranjo *arr){
    if(!arr) return;
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ARRANJO\n");
    if(arr->num) arr->num->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoListaExpr *le){
    if(le->expressao)le->expressao->aceita(this);
    if(le->lista)le->lista->aceita(this);
}
void VisitanteImpressao::visita(NoListaFormal *lf){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-LISTA_FORMAL\n");
    if(lf->tipo) lf->tipo->aceita(this);
    if(lf->ponteiro) { nivel++; calculaNivel(); fprintf(stdout, "-PONTEIRO\n"); nivel--; }
    if(lf->id) lf->id->aceita(this);
    if(lf->arranjo) lf->arranjo->aceita(this);
    nivel--;
    if(lf->lista) lf->lista->aceita(this);
}
void VisitanteImpressao::visita(NoListaSentenca *ls){
    if(ls->sentenca) ls->sentenca->aceita(this);
    if(ls->lista) ls->lista->aceita(this);
}
void VisitanteImpressao::visita(NoSe *se){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SE\n");
	if(se->expressao) se->expressao->aceita(this);
	if(se->sentenca) se->sentenca->aceita(this);
	nivel--;
	if(se->senao) se->senao->aceita(this);
}
void VisitanteImpressao::visita(NoSenao *sen){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SENAO\n");
	if(sen->sentenca) sen->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoEnquanto *enq){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ENQUANTO\n");
	if(enq->expressao) enq->expressao->aceita(this);
	if(enq->sentenca) enq->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoBlocoCaso *bc){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CASO\n");
	if(bc->num) bc->num->aceita(this);
	if(bc->listaSentenca) bc->listaSentenca->aceita(this);
	if(bc->lista) bc->lista->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoDesvia *des){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DESVIA\n");
    nivel--;
}
void VisitanteImpressao::visita(NoEscolha *sw){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ESCOLHA\n");
	if(sw->expressao) sw->expressao->aceita(this);
	sw->blocoCaso->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoImprime *imp){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-IMPRIME\n");
	if(imp->listaExpr) imp->listaExpr->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoLeLinha *leL){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-LE_LINHA\n");
	if(leL->expressao) leL->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoRetorna *ret){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-RETORNA\n");
	if(ret->expressao) ret->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoLanca *lan){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-LANCA\n");
    nivel--;
}
void VisitanteImpressao::visita(NoEscopo *esc){
    if(esc->lista) esc->lista->aceita(this);
}
void VisitanteImpressao::visita(NoChamadaFuncao *cha){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CHAMADA\n");
	cha->id->aceita(this);
	if(cha->parametros) cha->parametros->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoTenta *te ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-TENTA\n");
	if(te->sentencaTry) te->sentencaTry->aceita(this);
	if(te->sentencaCatch){
        calculaNivel();
        fprintf(stdout, "-PEGA\n");
        te->sentencaCatch->aceita(this);
	}
	nivel--;
}
void VisitanteImpressao::visita(NoSentencaExpr *senE){
    if(senE->expressao) senE->aceita(this);
}
void VisitanteImpressao::visita(NoDeclFuncao *decF){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_FUNCAO\n");
    if(decF->tipo) decF->tipo->aceita(this);
    if(decF->ponteiro) { nivel++; calculaNivel(); fprintf(stdout, "-PONTEIRO\n"); nivel--; }
    if(decF->id) decF->id->aceita(this);
    if(decF->parametros) decF->parametros->aceita(this);
    if(decF->variaveis) decF->variaveis->aceita(this);
    if(decF->corpoFunc) decF->corpoFunc->aceita(this);
    if(decF->sentenca) decF->sentenca->aceita(this);
    nivel--;
    if(decF->lista) decF->lista->aceita(this);
}
void VisitanteImpressao::visita(NoListaId *lid ){
    if(!lid) return;
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ID_LIST\n");
    if(lid->ponteiro){
        nivel++;
        calculaNivel();
        fprintf(stdout, "-PONTEIRO\n");
        nivel--;
    }
    lid->id->aceita(this);
    if(lid->arranjo) lid->arranjo->aceita(this);
    nivel--;
    if(lid->lista) lid->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclVariavel *decV){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_VARIAVEL\n");
    if(decV->tipo)decV->tipo->aceita(this);
    if(decV->variaveis)decV->variaveis->aceita(this);
    nivel--;
    if(decV->lista) decV->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclTipo *decT){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_TIPO\n");
    if(decT->id) decT->id->aceita(this);
    if(decT->campo) decT->campo->aceita(this);
    nivel--;
    if(decT->lista) decT->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclLocalFuncao *decLF){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_FUNCAO_LOC\n");
    decLF->funcao->aceita(this);
    nivel--;
    if(decLF->lista) decLF->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclLocalVariavel *decLV){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_VARIAVEL_LOC\n");
    decLV->variavel->aceita(this);
    nivel--;
    if(decLV->lista) decLV->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclLocalPublico *decLPub){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PUBLIC\n");
    nivel--;
    if(decLPub->lista) decLPub->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclLocalPrivado *decLPri){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PRIVATE\n");
    nivel--;
    if(decLPri->lista) decLPri->lista->aceita(this);
}
void VisitanteImpressao::visita(NoCorpoFuncao *cF){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-CORPO_FUNCAO\n");
    if(cF->listaExpr) cF->listaExpr->aceita(this);
    nivel--;
    if(cF->lista) cF->lista->aceita(this);
}
void VisitanteImpressao::visita(NoDeclClasse *decC ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DEC_CLASSE\n");
    if(decC->id)  decC->id->aceita(this);
    if(decC->heranca){
         nivel++;
         calculaNivel();
         fprintf(stdout, "-HERANCA\n");
         decC->heranca->aceita(this);
         nivel--;
    }
    if(decC->local) decC->local->aceita(this);
    nivel--;
    if(decC->lista) decC->lista->aceita(this);
}
void VisitanteImpressao::visita(NoExprUnaria *expU){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_UNARIA.%s\n", pegarTokenLiteral(expU->operador));
    if(expU->expressao) expU->expressao->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprBinaria *expB){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_BINARIA.%s\n", pegarTokenLiteral(expB->operador));
    if(expB->exprEsquerda) expB->exprEsquerda->aceita(this);
    if(expB->exprDireita) expB->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprAtrib *atr){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ATRIBUICAO\n");
    if(atr->exprEsquerda) atr->exprEsquerda->aceita(this);
    if(atr->exprDireita) atr->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprAceCamp *expAC){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_ACE_CAMPO\n");
    if(expAC->exprEsquerda) expAC->exprEsquerda->aceita(this);
    if(expAC->exprDireita) expAC->exprDireita->aceita(this);
    nivel--;
}
 void VisitanteImpressao::visita(NoVerdadeiro *tr){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VERDADEIRO\n");
    nivel--;
 }
 void VisitanteImpressao::visita(NoFalso *fa){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-FALSO\n");
    nivel--;
 }

 void VisitanteImpressao::visita(NoEsse *th){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ESSE\n");
    nivel--;
 }
void VisitanteImpressao::visita(NoNovo *n){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-NOVO\n");
    if(n->id) n->id->aceita(this);
    if(n->listaExpr) n->listaExpr->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoTipo *tp){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-TIPO\n");
    nivel++;
    calculaNivel();
    if(tp->entradaTabela) { fprintf(stdout, "-ID.%s\n", tp->entradaTabela->pegarLexema()); }
    else { fprintf(stdout, "-%s\n", pegarTokenLiteral(tp->primitivo)); }
    nivel-=2;
}
void VisitanteImpressao::visita(NoColchetes *nc){
    //TUDO
    nivel++;
    calculaNivel();
    fprintf(stdout, "-INDICE\n");
    if(nc->primario) nc->primario->aceita(this);
    if(nc->expressao) nc->expressao->aceita(this);
    nivel--;
}
