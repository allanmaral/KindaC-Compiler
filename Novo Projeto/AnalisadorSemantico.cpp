#include "AnalisadorSemantico.h"
#include "ASA.h"

AnalisadorSemantico::AnalisadorSemantico(){}
AnalisadorSemantico::~AnalisadorSemantico(){}
void AnalisadorSemantico::visita(NoPrograma* prog){
    prog->listaClasse->aceita(this);
}
void AnalisadorSemantico::visita(NoId* id){

}
void AnalisadorSemantico::visita(NoLiteral* lit){

}
void AnalisadorSemantico::visita(NoAscii* asc){

}
void AnalisadorSemantico::visita(NoParenteses* pa){

}
void AnalisadorSemantico::visita(NoConteudo* con){

}
void AnalisadorSemantico::visita(NoEndereco* ende){

}
void AnalisadorSemantico::visita(NoNumInteiro* ni){

}
void AnalisadorSemantico::visita(NoNumReal* nr){

}
void AnalisadorSemantico::visita(NoArranjo* arr){

}
void AnalisadorSemantico::visita(NoListaExpr* le){

}
void AnalisadorSemantico::visita(NoListaFormal* lf){

}
void AnalisadorSemantico::visita(NoListaSentenca* ls){

}
void AnalisadorSemantico::visita(NoSe* se){

}
void AnalisadorSemantico::visita(NoSenao* sen){

}
void AnalisadorSemantico::visita(NoEnquanto* enq){

}
void AnalisadorSemantico::visita(NoBlocoCaso* bc){

}
void AnalisadorSemantico::visita(NoDesvia* des){

}
void AnalisadorSemantico::visita(NoEscolha* sw){

}
void AnalisadorSemantico::visita(NoImprime* imp){

}
void AnalisadorSemantico::visita(NoLeLinha* leL){

}
void AnalisadorSemantico::visita(NoRetorna* ret){

}
void AnalisadorSemantico::visita(NoLanca* lan){

}
void AnalisadorSemantico::visita(NoEscopo* esc){

}
void AnalisadorSemantico::visita(NoChamadaFuncao* cha){

}
void AnalisadorSemantico::visita(NoTenta* te){

}
void AnalisadorSemantico::visita(NoSentencaExpr* senE)
{

}
void AnalisadorSemantico::visita(NoDeclFuncao* decF){

}
void AnalisadorSemantico::visita(NoListaId* lid){

}
void AnalisadorSemantico::visita(NoDeclVariavel* decV){

}
void AnalisadorSemantico::visita(NoDeclTipo* decT){

}
void AnalisadorSemantico::visita(NoDeclLocalFuncao* decLF){

}
void AnalisadorSemantico::visita(NoDeclLocalVariavel* decLV){

}
void AnalisadorSemantico::visita(NoDeclLocalPublic* decLPub){

}
void AnalisadorSemantico::visita(NoDeclLocalPrivate* decLpri){

}
void AnalisadorSemantico::visita(NoCorpoFuncao* cF){

}
void AnalisadorSemantico::visita(NoDeclClasse* decC){
    AtributoClasse *atr = NULL;
    while(decC != NULL){
        tabelaClasses.insere(decC->id->entradaTabela->pegarLexema(), atr);
    }
}
void AnalisadorSemantico::visita(NoExprUnaria* expU){

}
void AnalisadorSemantico::visita(NoExprBinaria* expB){

}
void AnalisadorSemantico::visita(NoExprAtrib* atr){

}
void AnalisadorSemantico::visita(NoExprAceCamp* expAC){

}
void AnalisadorSemantico::visita(NoVerdadeiro* tr){

}
void AnalisadorSemantico::visita(NoFalso* fa){

}
void AnalisadorSemantico::visita(NoEsse* th){

}
void AnalisadorSemantico::visita(NoNovo* n){

}
void AnalisadorSemantico::visita(NoTipo* tp){

}
void AnalisadorSemantico::visita(NoColchetes* nc){

}

