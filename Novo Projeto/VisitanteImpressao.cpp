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
void VisitanteImpressao::visita(NoPrograma *prog){
	fprintf(stdout,"\n\n-PROGRAMA\n");
	if(prog->listaClasse) prog->listaClasse->aceita(this);
	if(prog->listaFuncao) prog->listaFuncao->aceita(this);
	if(prog->listaTipo)   prog->listaTipo->aceita(this);
	if(prog->listaVariavel) prog->listaVariavel->aceita(this);
}
void VisitanteImpressao::visita(NoId       *id ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ID\n");
	///pegar o valor do id
	nivel--;

}
void VisitanteImpressao::visita(NoLiteral  *lit ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-LITERAL\n");
	///pegar o valor do literal
	nivel--;

}
void VisitanteImpressao::visita(NoAscii    *asc ){
	nivel++;
	calculaNivel();
	fprintf(stdout, "-ASCII\n");
	///pegar o valor do ascii
	nivel--;
}
void VisitanteImpressao::visita(NoParenteses *pa){
	nivel++;
	calculaNivel();
	if(pa->expressao)pa->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoConteudo  *con){
	nivel++;
	calculaNivel();
	if(con->primario)con->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoEndereco  *ende ){
    nivel++;
	calculaNivel();
	if(ende->primario)ende->primario->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoNumInteiro *ni){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_INTEIRO\n");
	///pegar o numero inteiro
	nivel--;
}
void VisitanteImpressao::visita(NoNumReal   *nr ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-NUM_REAL\n");
	///pegar o numero real
	nivel--;
}
void VisitanteImpressao::visita(NoArranjo   *arr){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ARRANJO\n");
    arr->num.aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoListaExpr *le ){
    if(le->expressao)le->expressao->aceita(this);
    if(le->lista)le->lista->aceita(this);
}
void VisitanteImpressao::visita(NoListaFormal *lf){
    if(lf->arranjo) lf->arranjo->aceita(this);
    if(lf->lista) lf->lista->aceita(this);
}
void VisitanteImpressao::visita(NoListaSentenca *ls ){
    if(ls->sentenca) ls->sentenca->aceita(this);
    if(ls->lista) ls->lista->aceita(this);
}
void VisitanteImpressao::visita(NoIf            *se ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SE\n");
	if(se->expressao)se->expressao->aceita(this);
	if(se->sentenca)se->sentenca->aceita(this);
	nivel--;

}
void VisitanteImpressao::visita(NoElse          *sen){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-SENAO\n");
	if(sen->sentenca)sen->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoWhile         *enq){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ENQUANTO\n");
	if(enq->expressao) enq->expressao->aceita(this);
	if(enq->sentenca) enq->sentenca->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoBlocoCaso     *bc ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CASE\n");
	if(bc->listaSentenca) bc->listaSentenca->aceita(this);
	if(bc->lista) bc->lista->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoBreak         *des){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-DESVIA\n");
    nivel--;
}
void VisitanteImpressao::visita(NoSwitch        *sw ){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-ESCOLHA\n");
	if(sw->expressao) sw->expressao->aceita(this);
	sw->blocoCaso.aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoPrint         *imp){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-IMPRIME\n");
	if(imp->listaExpr) imp->listaExpr->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoReadLn        *leL){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-LE_LINHA\n");
	if(leL->expressao) leL->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoReturn        *ret){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-RETORNA\n");
	if(ret->expressao) ret->expressao->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoEscopo        *esc){
    if(esc->lista) esc->lista->aceita(this);
}
void VisitanteImpressao::visita(NoChamadaFuncao *cha){
    nivel++;
	calculaNivel();
	fprintf(stdout, "-CHAMADA\n");
	cha->id.aceita(this);
	if(cha->parametros) cha->parametros->aceita(this);
	nivel--;
}
void VisitanteImpressao::visita(NoTry           *te ){
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
void VisitanteImpressao::visita(NoSentencaExpr  *senE){
    if(senE->expressao) senE->aceita(this);
}
void VisitanteImpressao::visita(NoDeclFuncao    *decF){
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
void VisitanteImpressao::visita(NoListaId       *lid ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ID_LIST\n");
    if(lid->arranjo) lid->arranjo->aceita(this);
    if(lid->lista) lid->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclVariavel  *decV){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VAR_DEC\n");
    decV->variaveis.aceita(this);
    if(decV->lista) decV->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclTipo           *decT){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-TIPO_DEC\n");
    if(decT->campo) decT->campo->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclLocalFuncao  *decLF   ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-FUC_LOC_DEC\n");
    decLF->funcao.aceita(this);
    if(decLF->lista) decLF->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclLocalVariavel *decLV  ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VAR_LOC_DEC\n");
    decLV->variavel.aceita(this);
    if(decLV->lista) decLV->lista->aceita(this);
    nivel--;

}
void VisitanteImpressao::visita(NoDeclLocalPublic   *decLPub){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PUB_LOC_DEC\n");
    if(decLPub->lista) decLPub->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclLocalPrivate  *decLPri){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-PRI_LOC_DEC\n");
    if(decLPri->lista) decLPri->lista->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoDeclClasse        *decC ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-CLASSE_DEC\n");
    decC->id.aceita(this);
    if(decC->heranca){
         nivel++;
         calculaNivel();
         fprintf(stdout, "-HERANCA\n");
         decC->heranca->aceita(this);
         nivel--;
    }
    if(decC->lista) decC->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprUnaria    	  *expU ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_UNARIA\n");
    if(expU->expressao) expU->expressao->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprBinaria       *expB ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_BINARIA\n");
    if(expB->exprEsquerda) expB->exprEsquerda->aceita(this);
    if(expB->exprDireita) expB->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprAtrib         *atr  ){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ATRIB\n");
    if(atr->exprEsquerda) atr->exprEsquerda->aceita(this);
    if(atr->exprDireita) atr->exprDireita->aceita(this);
    nivel--;
}
void VisitanteImpressao::visita(NoExprAceCamp       *expAC){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-EXPR_ACC\n");
    if(expAC->exprEsquerda) expAC->exprEsquerda->aceita(this);
    if(expAC->exprDireita) expAC->exprDireita->aceita(this);
    nivel--;
}
 void VisitanteImpressao::visita(NoTrue              *tr){
    nivel++;
    calculaNivel();
    fprintf(stdout, "-VERDADEIRO\n");
    nivel--;
 }
 void VisitanteImpressao::visita(NoFalse             *fa) {
    nivel++;
    calculaNivel();
    fprintf(stdout, "-FALSO\n");
    nivel--;
 }

 void VisitanteImpressao::visita(NoThis              *th) {
    nivel++;
    calculaNivel();
    fprintf(stdout, "-ESSE\n");
    nivel--;
 }
void VisitanteImpressao::visita(NoNew               *n    ){
     nivel++;
    calculaNivel();
    fprintf(stdout, "-NOVO\n");
    if(n->listaExpr) n->listaExpr->aceita(this);
    nivel--;
}
