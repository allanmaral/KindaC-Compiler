#include <stdio.h>
#include <stdlib.h>
#include "ASA.h"
#include "Visitante.h"
#include "VisitanteImpressao.h"

VisitanteImpressao::VisitanteImpressao(){
	nivel=0;
}
void VisitanteImpressao::calculaNivel(){
	for(int i=0;i<nivel;i++){
        fprintf(stdout, "   ");
    }
}
void VisitanteImpressao::visita(Programa *prog){
	fprintf(stdout,"\n\n-PROGRAMA\n");
	/*if(prog->listaClasse) prog->listaClasse->aceita(this);
	if(prog->listaFuncao) prog->listaFuncao->aceita(this);
	if(prog->listaTipo)   prog->listaTipo->aceita(this);
	if(prog->listaVariavel) prog->listaVariavel->aceita(this);*/
}
void VisitanteImpressao::visita(Id       *id ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ID\n");
	///pegar o valor do id
	nivel--;

}
void VisitanteImpressao::visita(Literal  *lit ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-LITERAL\n");
	///pegar o valor do literal
	nivel--;

}
void VisitanteImpressao::visita(Ascii    *asc ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ASCII\n");
	///pegar o valor do ascii
	nivel--;
}
void VisitanteImpressao::visita(Parenteses *pa){
	nivel++;
	calculaNivel();
	if(pa->expressao)pa->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Conteudo  *con){
	nivel++;
	calculaNivel();
	if(con->primario)con->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Endereco  *ende ){
    nivel++;
	calculaNivel();
	if(ende->primario)ende->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NumInteiro *ni){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_INTEIRO\n");
	///pegar o numero inteiro
	nivel--;
}
void VisitanteImpressao::visita(NumReal   *nr ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_REAL\n");
	///pegar o numero real
	nivel--;
}
void VisitanteImpressao::visita(Arranjo   *arr){
    arr->num.aceita(this);
}
void VisitanteImpressao::visita(ListaExpr *le ){
    if(le->expressao)le->expressao->aceita(this);
    if(le->lista)le->lista->aceita(this);
}
void VisitanteImpressao::visita(ListaFormal *lf){
    if(lf->arranjo) lf->arranjo->aceita(this);
    if(lf->lista) lf->lista->aceita(this);
}
void VisitanteImpressao::visita(ListaSentenca *ls ){
    if(ls->sentenca) ls->sentenca->aceita(this);
    if(ls->lista) ls->lista->aceita(this);
}
void VisitanteImpressao::visita(If            *se ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SE\n");
	if(se->expressao)se->expressao->aceita(this);
	if(se->sentenca)se->sentenca->aceita(this);
	nivel--;

}
void VisitanteImpressao::visita(Else          *sen){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SENAO\n");
	if(sen->sentenca)sen->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(While         *enq){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ENQUANTO\n");
	if(enq->expressao) enq->expressao->aceita(this);
	if(enq->sentenca) enq->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(BlocoCaso     *bc ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CASE\n");
	if(bc->listaSentenca) bc->listaSentenca->aceita(this);
	if(bc->lista) bc->lista->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Break         *des){
    //des->aceita(this);
}
void VisitanteImpressao::visita(Switch        *sw ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ESCOLHA\n");
	if(sw->expressao) sw->expressao->aceita(this);
	sw->blocoCaso.aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Print         *imp){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-IMPRIME\n");
	if(imp->listaExpr) imp->listaExpr->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(ReadLn        *leL){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-LE_LINHA\n");
	if(leL->expressao) leL->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Return        *ret){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-RETORNA\n");
	if(ret->expressao) ret->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Escopo        *esc){
    if(esc->lista) esc->lista->aceita(this);
}
void VisitanteImpressao::visita(ChamadaFuncao *cha){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CHAMADA\n");
	cha->id.aceita(this);
	if(cha->parametros) cha->parametros->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(Try           *te ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-TENTA\n");
	if(te->sentencaTry) te->sentencaTry->aceita(this);
	if(te->sentencaCatch) {
        nivel++;
        calculaNivel();
        fprintf(stdout, "-PEGA\n");
        te->sentencaCatch->aceita(this);
        nivel--;
	}
	nivel--;
}
void VisitanteImpressao::visita(SentencaExpr  *senE){
    if(senE->expressao) senE->aceita(this);
}
void VisitanteImpressao::visita(DeclFuncao    *decF){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-FUNC_DEC\n");
    decF->id.aceita(this);
    if(decF->parametros) decF->parametros->aceita(this);
    if(decF->variaveis) decF->variaveis->aceita(this);
    decF->sentenca.aceita(this);
    if(decF->lista) decF->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(ListaId       *lid ){
    ///arrumar
}
void VisitanteImpressao::visita(DeclVariavel  *decV){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VAR_DEC\n");
    decV->variaveis.aceita(this);
    if(decV->lista) decV->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(DeclTipo           *decT){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-TIPO_DEC\n");
    if(decT->campo) decT->campo->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(DeclLocalFuncao  *decLF   ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-FUC_LOC_DEC\n");
    decLF->funcao.aceita(this);
    if(decLF->lista) decLF->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(DeclLocalVariavel *decLV  ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VAR_LOC_DEC\n");
    decLV->variavel.aceita(this);
    if(decLV->lista) decLV->lista->aceita(this);
    nivel--;

}
void VisitanteImpressao::visita(DeclLocalPublic   *decLPub){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PUB_LOC_DEC\n");
    if(decLPub->lista) decLPub->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(DeclLocalPrivate  *decLPri){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PRI_LOC_DEC\n");
    if(decLPri->lista) decLPri->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(DeclClasse        *decC ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-CLASSE_DEC\n");
    decC->id.aceita(this);
    if(decC->heranca){
         nivel++;
         calculaNivel();
         fprintf(stdout, "-HERANCA\n");
         decC->heranca->aceita(this);
    }
    if(decC->lista) decC->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(ExprUnaria    	  *expU ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_UNARIA\n");
    if(expU->expressao) expU->expressao->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(ExprBinaria       *expB ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_BINARIA\n");
    if(expB->exprEsquerda) expB->exprEsquerda->aceita(this);
    if(expB->exprDireita) expB->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(ExprAtrib         *atr  ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-ATRIB\n");
    if(atr->exprEsquerda) atr->exprEsquerda->aceita(this);
    if(atr->exprDireita) atr->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(ExprAceCamp       *expAC){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_ACC\n");
    if(expAC->exprEsquerda) expAC->exprEsquerda->aceita(this);
    if(expAC->exprDireita) expAC->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(New               *n    ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-NOVO\n");
    if(n->listaExpr) n->listaExpr->aceita(this);
    nivel--;
}
