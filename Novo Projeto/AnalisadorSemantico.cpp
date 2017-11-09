#include "AnalisadorSemantico.h"
#include "ASA.h"
#include "AnalisadorLexico.h"

Atributo *atual = NULL;

AnalisadorSemantico::AnalisadorSemantico(){}
AnalisadorSemantico::~AnalisadorSemantico(){}
void AnalisadorSemantico::visita(NoPrograma* prog){
    prog->listaClasse->aceita(this);
    prog->listaTipo->aceita(this);
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
    AtributoVariavel *atr = NULL;
    atual = new AtributoTipo();
    TabelaSimbolos *classes = obtemTabelaClasses();
    TabelaSimbolos *tipos = obtemTabelaTipos();
    NoListaId *ids = NULL;
    bool ok = false;
    while(decV != NULL){
        if(decV->tipo->primitivo == ID){
            if(!classes->busca(decV->tipo->entradaTabela->pegarLexema())){
                if(!tipos->busca(decV->tipo->entradaTabela->pegarLexema())){
                    ///Erro semantico,tipo "ID" não foi declarado
                    ok = false;
                }
            }
        }
        ids = decV->variaveis;
        while(ids != NULL){
            if(((AtributoTipo*)atual)->buscaVariavel(ids->id->entradaTabela->pegarLexema())){
                ///Erro semantico, redefinicao da variavel "ID"
                ok = false;
            }else{
                ///adiciona variavel na tabela de simbolos do atual
            }
            ids = ids->lista;
        }
        decV = decV->lista;
    }
    if(!ok){
        delete atual;
    }
}
void AnalisadorSemantico::visita(NoDeclTipo* decT){
    while(decT != NULL){
        if(obtemTabelaTipos()->busca(decT->id->entradaTabela->pegarLexema()) != NULL){
            ///erro semantico, redefinicao de tipo
        }
        else{
            decT->campo->aceita(this);
            if(atual){
                atual->atribuirLexema(decT->id->entradaTabela->pegarLexema());
                obtemTabelaTipos()->insere(atual->pegarLexema(), atual);
            }
        }
        decT = decT->lista;
    }
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
    Atributo *her = NULL;
    TabelaSimbolos *classes = obtemTabelaClasses();
    bool ok = true;
    while(decC != NULL){
        if(classes->busca(decC->id->entradaTabela->pegarLexema()) != NULL){
            ///erro semantico, redefinicao de classe
            ok = false;
        }
        if(decC->heranca != NULL && classes->busca(decC->heranca->entradaTabela->pegarLexema()) == NULL){
            ///erro semantico, classe herdada nao encontrada
            ok = false;
        }
        //decC->local->aceita(this);
        if(ok){
            atr = new AtributoClasse();
            if(decC->heranca != NULL){
                her = new Atributo();
                her->atribuirLexema(decC->heranca->entradaTabela->pegarLexema());
                atr->atribuirHeranca(her);
            }
            atr->atribuirLexema(decC->id->entradaTabela->pegarLexema());
            classes->insere(decC->id->entradaTabela->pegarLexema(), atr);
        }
        ok = true;
        decC = decC->lista;
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

