#include "AnalisadorSemantico.h"
#include "ASA.h"
#include "AnalisadorLexico.h"
#include "string.h"
#include "GerenciadorErro.h"

TabelaSimbolos *tabelavariaveisAtual = NULL;
TabelaSimbolos *tabelafuncoesAtual = NULL;
TabelaSimbolos *tabelaParametro = NULL;
bool publico = true;
bool verificandoClasse = false;
bool erro = false;
int retorno = 0;

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
    retorno = NUM_INTEIRO;
}
void AnalisadorSemantico::visita(NoNumReal* nr){
    retorno = NUM_REAL;
}
void AnalisadorSemantico::visita(NoArranjo* arr){
    if(arr->num){
        arr->num->aceita(this);
        if(retorno != NUM_INTEIRO){
            saidaErro(ErroSemanticoTamanhoArranjoReal, arr->linha, arr->coluna);
            erro = true;
        }
        retorno = 0;
    }
}
void AnalisadorSemantico::visita(NoListaExpr* le){

}
void AnalisadorSemantico::visita(NoListaFormal* lf){
    TabelaSimbolos *tabela = tabelavariaveisAtual;
    bool erroTipo = false;
    while(lf){
        if(lf->tipo->primitivo == ID){
            if(!obtemTabelaTipos()->busca(lf->tipo->entradaTabela->pegarLexema())){
                if(!obtemTabelaClasses()->busca(lf->tipo->entradaTabela->pegarLexema())){
                    saidaErro(ErroSemanticoTipoVariavel, lf->tipo->linha, lf->tipo->coluna,
                               lf->tipo->entradaTabela->pegarLexema());
                    erroTipo = false;
                }
            }
        }
        if(!tabela->busca(lf->id->entradaTabela->pegarLexema())){
            if(lf->arranjo){
                lf->arranjo->aceita(this);
            }
            if(!erro && !erroTipo){
                AtributoVariavel *atr = new AtributoVariavel();
                Tipo *tipo;
                if(lf->tipo->primitivo == ID){
                    tipo = new TipoId(lf->tipo->entradaTabela->pegarLexema(), ID);
                }else{
                    tipo = new Tipo(lf->tipo->primitivo);
                }
                atr->atribuirTipo(tipo);
                if(lf->arranjo){
                    if(lf->arranjo->num){
                        atr->atribuiArranjo(atoi(((NoNumInteiro*)lf->arranjo->num)->entradaTabela->pegarLexema()));
                    }else{
                        saidaErro(ErroSemanticoArranjoVazio,lf->arranjo->linha, lf->arranjo->coluna);
                    }
                }
                atr->atribuiPonteiro(lf->ponteiro);
                atr->atribuirLexema(lf->id->entradaTabela->pegarLexema());
                tabela->insere(lf->id->entradaTabela->pegarLexema(), atr);
            }
            erro = false;
        }
        else{
            saidaErro(ErroSemanticoConflitoDeDeclaracoes, lf->id->linha, lf->id->coluna,
                       lf->id->entradaTabela->pegarLexema());
        }
        lf = lf->lista;
    }
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
    TabelaSimbolos *tabela;
    if(!tabelafuncoesAtual){
        tabela = obtemTabelaFuncoes();
    }else{
        tabela = tabelafuncoesAtual;
    }
    if(decF->tipo->primitivo == ID){
        if(!obtemTabelaTipos()->busca(decF->tipo->entradaTabela->pegarLexema())){
            if(!obtemTabelaClasses()->busca(decF->tipo->entradaTabela->pegarLexema())){
                saidaErro(ErroSemanticoTipoVariavel, decF->tipo->linha, decF->tipo->coluna,
                       decF->tipo->entradaTabela->pegarLexema());
            }
        }
    }
    if(tabela->busca(decF->id->entradaTabela->pegarLexema())){
        saidaErro(ErroSemanticoRedefinicaoFuncao, decF->id->linha, decF->id->coluna, decF->id->entradaTabela->pegarLexema());
    }else{
        AtributoFuncao *atr;
        if(verificandoClasse){
            atr = new AtributoFuncaoClasse();
            ((AtributoFuncaoClasse*)atr)->atribuiPublico(publico);
        }else{
            atr = new AtributoFuncao();
        }
        atr->atribuirLexema(decF->id->entradaTabela->pegarLexema());
        atr->atribuirPonteiro(decF->ponteiro);
        tabela->insere(atr->pegarLexema(),atr);
        if(decF->parametros){
            tabelavariaveisAtual = atr->pegarParametros();
            decF->parametros->aceita(this);
            tabelavariaveisAtual = NULL;
        }
        if(decF->variaveis){
            tabelavariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametro = atr->pegarParametros();
            decF->variaveis->aceita(this);
            tabelavariaveisAtual = NULL;
            tabelaParametro = NULL;
        }
        if(decF->corpoFunc){
            tabelavariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametro = atr->pegarParametros();
            decF->corpoFunc->aceita(this);
            tabelavariaveisAtual = NULL;
            tabelaParametro = NULL;
        }
        if(decF->lista){
            decF->lista->aceita(this);
        }
    }

}
void AnalisadorSemantico::visita(NoListaId* lid){

}
void AnalisadorSemantico::visita(NoDeclVariavel* decV){
    bool erroTipo = false;
    TabelaSimbolos *tabela;
    if(!tabelavariaveisAtual){
        tabela = obtemTabelaVariaveis();
    }else{
        tabela = tabelavariaveisAtual;
    }
    if(decV->tipo->primitivo == ID){
        if(!obtemTabelaClasses()->busca(decV->tipo->entradaTabela->pegarLexema())){
            if(!obtemTabelaTipos()->busca(decV->tipo->entradaTabela->pegarLexema())){
                saidaErro(ErroSemanticoTipoVariavel, decV->linha, decV->coluna, decV->tipo->entradaTabela->pegarLexema());
                erroTipo = true;
            }
        }
    }
    NoListaId *aux = decV->variaveis;
    while(aux){
        if(tabela->busca(aux->id->entradaTabela->pegarLexema())){
            saidaErro(ErroSemanticoRedefinicaoVariavel, decV->linha, decV->coluna, aux->id->entradaTabela->pegarLexema());
        }else{
            if((tabelaParametro && !tabelaParametro->busca(aux->id->entradaTabela->pegarLexema()))
                || (tabelaParametro == NULL)){
                if(aux->arranjo){
                    erro = false;
                    aux->arranjo->aceita(this);
                }
                if(!erroTipo && !erro){
                    AtributoVariavel *atr;
                    if(verificandoClasse){
                        atr = new AtributoVariavelClasse();
                        ((AtributoVariavelClasse*)atr)->atribuiPublico(publico);
                    }else{
                        atr = new AtributoVariavel();
                    }
                    Tipo *tp;
                    if(decV->tipo->primitivo == ID){
                        tp = new TipoId(decV->tipo->entradaTabela->pegarLexema(), ID);
                    }else{
                        tp = new Tipo(decV->tipo->primitivo);
                    }
                    if(aux->arranjo){
                        if(aux->arranjo->num){
                            atr->atribuiArranjo(atoi(((NoNumInteiro*)aux->arranjo->num)->entradaTabela->pegarLexema()));
                        }else{
                            saidaErro(ErroSemanticoArranjoVazio,aux->arranjo->linha, aux->arranjo->coluna);
                        }
                    }
                    atr->atribuiPonteiro(aux->ponteiro);
                    atr->atribuirLexema(aux->id->entradaTabela->pegarLexema());
                    ((AtributoVariavel*)atr)->atribuirTipo(tp);
                    tabela->insere(atr->pegarLexema(), atr);
                }
            }else{
                saidaErro(ErroSemanticoVariavelIgualParametro, aux->linha, aux->coluna, aux->id->entradaTabela->pegarLexema());
            }
        }
        aux = aux->lista;
    }
    if(decV->lista){
        decV->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclTipo* decT){
    if(obtemTabelaClasses()->busca(decT->id->entradaTabela->pegarLexema()) ||
        obtemTabelaTipos()->busca(decT->id->entradaTabela->pegarLexema())){
        saidaErro(ErroSemanticoRedefinicaoTipo, decT->linha, decT->coluna, decT->id->entradaTabela->pegarLexema());
    }else{
        AtributoTipo *atr = new AtributoTipo();
        tabelavariaveisAtual = atr->pegaVariaveis();
        decT->campo->aceita(this);
        tabelavariaveisAtual = NULL;
        atr->atribuirLexema(decT->id->entradaTabela->pegarLexema());
        obtemTabelaTipos()->insere(decT->id->entradaTabela->pegarLexema(), atr);
    }
    if(decT->lista){
        decT->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclLocalFuncao* decLF){
    decLF->funcao->aceita(this);
    if(decLF->lista){
        decLF->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclLocalVariavel* decLV){
    decLV->variavel->aceita(this);
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
    if(cF->listaExpr){
        NoExprBinaria *bin = dynamic_cast<NoExprBinaria*>(cF->listaExpr->expressao);
        if(bin && bin->operador == ASTERISCO){
            NoId *tipo = (NoId*)bin->exprEsquerda;
            if(!obtemTabelaClasses()->busca(tipo->entradaTabela->pegarLexema())){
                if(!obtemTabelaTipos()->busca(tipo->entradaTabela->pegarLexema())){
                    saidaErro(ErroSemanticoTipoVariavel, tipo->linha, tipo->coluna, tipo->entradaTabela->pegarLexema());
                }
            }else{
                AtributoVariavel *atr = new AtributoVariavel();
                TipoId *tipoid = new TipoId(tipo->entradaTabela->pegarLexema(), ID);
                atr->atribuiPonteiro(true);
                atr->atribuirTipo(tipoid);
                NoId *variavel = dynamic_cast<NoId*>(bin->exprDireita);
                if(variavel){
                    if(!tabelavariaveisAtual->busca(variavel->entradaTabela->pegarLexema())){
                        if(!tabelaParametro->busca(variavel->entradaTabela->pegarLexema())){
                            atr->atribuirLexema(variavel->entradaTabela->pegarLexema());
                            tabelavariaveisAtual->insere(atr->pegarLexema(), atr);
                        }else{
                            saidaErro(ErroSemanticoRedefinicaoVariavel, variavel->linha, variavel->coluna, atr->pegarLexema());
                            delete atr;
                        }
                    }else{
                        saidaErro(ErroSemanticoRedefinicaoVariavel, variavel->linha, variavel->coluna, atr->pegarLexema());
                        delete atr;
                    }
                }else{
                    NoColchetes *arranjo = dynamic_cast<NoColchetes*>(bin->exprDireita);
                    if(arranjo){
                        NoId *id = dynamic_cast<NoId*>(arranjo->primario);
                        if(id && !tabelavariaveisAtual->busca(id->entradaTabela->pegarLexema())){
                            if(!tabelaParametro->busca(id->entradaTabela->pegarLexema())){
                                atr->atribuirLexema(id->entradaTabela->pegarLexema());
                                NoNumInteiro *inteiro = dynamic_cast<NoNumInteiro*>(arranjo->expressao);
                                if(inteiro){
                                    atr->atribuiArranjo(atoi(inteiro->entradaTabela->pegarLexema()));
                                    tabelavariaveisAtual->insere(atr->pegarLexema(), atr);
                                }else{
                                    saidaErro(ErroSemanticoTamanhoArranjoReal, arranjo->expressao->linha, arranjo->expressao->coluna);
                                    delete atr;
                                }
                            }else{
                                saidaErro(ErroSemanticoRedefinicaoVariavel, arranjo->expressao->linha, arranjo->expressao->coluna, atr->pegarLexema());
                                delete atr;
                            }
                        }else{
                            saidaErro(ErroSemanticoRedefinicaoVariavel, arranjo->expressao->linha, arranjo->expressao->coluna, atr->pegarLexema());
                            delete atr;
                        }
                    }
                }
            }
        }else{
            NoId *id = dynamic_cast<NoId*>(cF->listaExpr->expressao);
            if(id){
                if(!obtemTabelaClasses()->busca(id->entradaTabela->pegarLexema())){
                    if(!obtemTabelaTipos()->busca(id->entradaTabela->pegarLexema())){
                        saidaErro(ErroSemanticoTipoVariavel, id->linha, id->coluna, id->entradaTabela->pegarLexema());
                    }
                }else{

                }
            }
        }
    }

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
                saidaErro(ErroSemanticoClasseHerdadaMesma, decC->heranca->linha, decC->heranca->coluna);
            }else{
                saidaErro(ErroSemanticoClasseHerdadaNaoExiste, decC->heranca->linha, decC->heranca->linha);
            }
            erro = true;
        }
    }else{
         saidaErro(ErroSemanticoRedefinicaoClasse, decC->id->linha, decC->id->coluna, decC->id->entradaTabela->pegarLexema());
         erro = true;
    }
    atr = new AtributoClasse();
    verificandoClasse = true;
    tabelavariaveisAtual = atr->pegarVariaveis();
    tabelafuncoesAtual = atr->pegarFuncoes();
    decC->local->aceita(this);
    verificandoClasse = false;
    tabelavariaveisAtual = NULL;
    tabelafuncoesAtual = NULL;
    if(!erro){
        if(decC->heranca != NULL){
            her = new Atributo();
            her->atribuirLexema(decC->heranca->entradaTabela->pegarLexema());
            atr->atribuirHeranca(her);
        }
        atr->atribuirLexema(decC->id->entradaTabela->pegarLexema());
        classes->insere(decC->id->entradaTabela->pegarLexema(), atr);
    }else{
        delete atr;
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
