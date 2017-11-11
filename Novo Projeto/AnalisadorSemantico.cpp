#include "AnalisadorSemantico.h"
#include "ASA.h"
#include "AnalisadorLexico.h"
#include "string.h"
#include "GerenciadorErro.h"

TabelaSimbolos *tabelavariaveisAtual = NULL;
bool publico = true;

AnalisadorSemantico::AnalisadorSemantico(){}
AnalisadorSemantico::~AnalisadorSemantico(){}
void AnalisadorSemantico::visita(NoPrograma* prog){
    if(NoDeclClasse* decC = dynamic_cast<NoDeclClasse*>(prog)) { decC->aceita(this); }
    else if(NoDeclTipo* decT = dynamic_cast<NoDeclTipo*>(prog)) { decT->aceita(this); }
    else if(NoDeclVariavel* decV = dynamic_cast<NoDeclVariavel*>(prog)) { decV->aceita(this); }
    else if(NoDeclFuncao* decF = dynamic_cast<NoDeclFuncao*>(prog)) { decF->aceita(this); }
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
void AnalisadorSemantico::visita(NoSentencaExpr* senE){

}
void AnalisadorSemantico::visita(NoDeclFuncao* decF){

}
void AnalisadorSemantico::visita(NoListaId* lid){

}
void AnalisadorSemantico::visita(NoDeclVariavel* decV){
    bool erro = false;
    if(!tabelavariaveisAtual){
        tabelavariaveisAtual = new TabelaSimbolos();
    }
    if(!obtemTabelaClasses()->busca(decV->tipo->entradaTabela->pegarLexema())){
        if(!obtemTabelaTipos()->busca(decV->tipo->entradaTabela->pegarLexema())){
            ///erro semantico, tipo tal n foi declarado nesse escopo.
            erro = true;
        }
    }
    NoListaId *aux = decV->variaveis;
    while(!aux){
        if(tabelavariaveisAtual->busca(aux->id->entradaTabela->pegarLexema())){
            ///erro semantico, redefinicao de variavel;
        }else{

        }
        aux = aux->lista;
    }
    if(decV->lista){
        decV->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclTipo* decT){

}
void AnalisadorSemantico::visita(NoDeclLocalFuncao* decLF){

}
void AnalisadorSemantico::visita(NoDeclLocalVariavel* decLV){
    if(decLV->lista){
        decLV->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclLocalPublico* decLPub){
    publico = true;
    if(decLPub->lista){
        decLPub->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclLocalPrivado* decLpri){
    publico = false;
    if(decLpri->lista){
        decLpri->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoCorpoFuncao* cF){

}
void AnalisadorSemantico::visita(NoDeclClasse* decC){
    AtributoClasse *atr = NULL;
    Atributo *her = NULL;
    TabelaSimbolos *classes = obtemTabelaClasses();
    bool erro = false;
    if(classes->busca(decC->id->entradaTabela->pegarLexema()) == NULL){
        if(decC->heranca != NULL && classes->busca(decC->heranca->entradaTabela->pegarLexema()) == NULL){
            if(!strcmp(decC->heranca->entradaTabela->pegarLexema(),
                                               decC->id->entradaTabela->pegarLexema())){
                saidaErro(ErroSemanticoClasseHerdadaMesma, 0, 0);
            }else{
                saidaErro(ErroSemanticoClasseHerdadaNaoExiste, 0, 0);
            }
            erro = true;
        }
    }else{
         saidaErro(ErroSemanticoRedefinicaoClasse, 0, 0, decC->id->entradaTabela->pegarLexema());
         erro = true;
    }
    decC->local->aceita(this);
    if(!erro){
        atr = new AtributoClasse();
        if(decC->heranca != NULL){
            her = new Atributo();
            her->atribuirLexema(decC->heranca->entradaTabela->pegarLexema());
            atr->atribuirHeranca(her);
        }
        atr->atribuirLexema(decC->id->entradaTabela->pegarLexema());
        classes->insere(decC->id->entradaTabela->pegarLexema(), atr);
    }
    if(decC->lista != NULL){
        decC->lista->aceita(this);
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

