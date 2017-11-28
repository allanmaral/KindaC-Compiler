#include "AnalisadorSemantico.h"
#include "AnalisadorSintatico.h"
#include "ASA.h"
#include "AnalisadorLexico.h"
#include "string.h"
#include "GerenciadorErro.h"

TabelaSimbolos *tabelaVariaveisAtual = NULL;
TabelaSimbolos *tabelaFuncoesAtual = NULL;
TabelaSimbolos *tabelaParametrosAtual = NULL;
bool publico = true;
bool verificandoClasse = false;
bool erro = false;
int retorno = 0;
Atributo *valorRetorno = NULL;
int verificandoCorpo = false;
int arranjo = 0;
Atributo *tipo = NULL;

AnalisadorSemantico::AnalisadorSemantico(){}
AnalisadorSemantico::~AnalisadorSemantico(){}
void AnalisadorSemantico::visita(NoPrograma* prog){
    if(NoDeclClasse* decC = dynamic_cast<NoDeclClasse*>(prog)) { decC->aceita(this); }
    else if(NoDeclTipo* decT = dynamic_cast<NoDeclTipo*>(prog)) { decT->aceita(this); }
    else if(NoDeclVariavel* decV = dynamic_cast<NoDeclVariavel*>(prog)) { decV->aceita(this); }
    else if(NoDeclFuncao* decF = dynamic_cast<NoDeclFuncao*>(prog)) { decF->aceita(this); }
}
void AnalisadorSemantico::visita(NoId* id){
    Atributo *atr = NULL;
    if(!(atr = tabelaParametrosAtual->busca(id->entradaTabela->pegarLexema()))){
        if(!(atr = tabelaVariaveisAtual->busca(id->entradaTabela->pegarLexema()))){
            if(!(atr = obtemTabelaVariaveis()->busca(id->entradaTabela->pegarLexema()))){
                retorno = ID;
                valorRetorno = id->entradaTabela;
                if(verificandoCorpo){
                    tipo = valorRetorno;
                }
                return;
            }
        }
    }
    retorno = ((AtributoVariavel*)atr)->pegarTipo()->pegaTipo();
    if(retorno == ID){
        Atributo *entradaTabela = obtemTabelaClasses()->busca(((TipoId*)((AtributoVariavel*)atr)->pegarTipo())->pegarLexema());
        if(!entradaTabela){
            entradaTabela = obtemTabelaTipos()->busca(((TipoId*)((AtributoVariavel*)atr)->pegarTipo())->pegarLexema());
        }else{
            tipo = NULL;
        }
        valorRetorno = entradaTabela;
    }else{
        valorRetorno = atr;
    }
}
void AnalisadorSemantico::visita(NoLiteral* lit){
    retorno = LITERAL;
}
void AnalisadorSemantico::visita(NoAscii* asc){
    retorno = ASCII;
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
    if(le->expressao){
        le->expressao->aceita(this);
    }
    if(le->lista){
        le->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoListaFormal* lf){
    TabelaSimbolos *tabela = tabelaVariaveisAtual;
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
    if(ls->sentenca) ls->sentenca->aceita(this);
    if(ls->lista) ls->lista->aceita(this);
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
    if(!tabelaFuncoesAtual){
        tabela = obtemTabelaFuncoes();
    }else{
        tabela = tabelaFuncoesAtual;
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
        decF->atr = atr;

        if(decF->tipo->primitivo == ID)
            atr->adicionarRetorno(new TipoId(decF->tipo->entradaTabela->pegarLexema(), ID));
        else
            atr->adicionarRetorno(new Tipo(decF->tipo->primitivo));

        atr->atribuirLexema(decF->id->entradaTabela->pegarLexema());
        atr->atribuirPonteiro(decF->ponteiro);
        tabela->insere(atr->pegarLexema(),atr);
        if(decF->parametros){
            tabelaVariaveisAtual = atr->pegarParametros();
            decF->parametros->aceita(this);
            tabelaVariaveisAtual = NULL;
        }
        if(decF->variaveis){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->variaveis->aceita(this);
            tabelaVariaveisAtual = NULL;
            tabelaParametrosAtual = NULL;
        }
        if(decF->corpoFunc){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->corpoFunc->aceita(this);
            tabelaVariaveisAtual = NULL;
            tabelaParametrosAtual = NULL;
        }
        if(decF->sentenca){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->sentenca->aceita(this);
            tabelaVariaveisAtual = NULL;
            tabelaParametrosAtual = NULL;
        }
        if(decF->lista){
            decF->lista->aceita(this);
        }
    }
}
void AnalisadorSemantico::visita(NoListaId* lid){
    if(!tabelaParametrosAtual->busca(lid->id->entradaTabela->pegarLexema())){
        if(!tabelaVariaveisAtual->busca(lid->id->entradaTabela->pegarLexema())){
            if(tipo){
                if(lid->arranjo){
                    lid->arranjo->aceita(this);
                }
                if(!erro){
                    AtributoVariavel *atr = new AtributoVariavel();
                    TipoId *tp = new TipoId(tipo->pegarLexema(),ID);
                    atr->atribuirTipo(tp);
                    atr->atribuirLexema(lid->id->entradaTabela->pegarLexema());
                    atr->atribuiArranjo(arranjo);
                    atr->atribuiPonteiro(lid->ponteiro);
                    tabelaVariaveisAtual->insere(atr->pegarLexema(), atr);
                }
            }
        }else{
            saidaErro(ErroSemanticoRedefinicaoVariavel,lid->id->linha, lid->id->coluna, lid->id->entradaTabela->pegarLexema());
            if(lid->arranjo){
                lid->arranjo->aceita(this);
            }
        }
    }else{
        saidaErro(ErroSemanticoVariavelIgualParametro,lid->id->linha, lid->id->coluna, lid->id->entradaTabela->pegarLexema());
        if(lid->arranjo){
            lid->arranjo->aceita(this);
        }
    }
    if(lid->lista){
        lid->lista->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoDeclVariavel* decV){
    bool erroTipo = false;
    TabelaSimbolos *tabela;
    if(!tabelaVariaveisAtual){
        tabela = obtemTabelaVariaveis();
    }else{
        tabela = tabelaVariaveisAtual;
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
            if((tabelaParametrosAtual && !tabelaParametrosAtual->busca(aux->id->entradaTabela->pegarLexema()))
                || (tabelaParametrosAtual == NULL)){
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
                            atr->atribuiArranjo(atoi(((NoNumInteiro*)aux->arranjo->num)->
                                                     entradaTabela->pegarLexema()));
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
                saidaErro(ErroSemanticoVariavelIgualParametro, aux->linha, aux->coluna,
                          aux->id->entradaTabela->pegarLexema());
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
        tabelaVariaveisAtual = atr->pegaVariaveis();
        decT->campo->aceita(this);
        tabelaVariaveisAtual = NULL;
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
    if(cF->expressao) {verificandoCorpo = true; cF->expressao->aceita(this);}
    if(tipo && cF->expressao && valorRetorno){
        if(!obtemTabelaClasses()->busca(valorRetorno->pegarLexema())){
            if(!obtemTabelaTipos()->busca(valorRetorno->pegarLexema())){
                saidaErro(ErroSemanticoTipoVariavel, cF->expressao->linha,
                            cF->expressao->coluna, valorRetorno->pegarLexema());
                erro = true;
            }
        }
    }
    if(cF->id){
        if(!tabelaParametrosAtual->busca(cF->id->entradaTabela->pegarLexema())){
            if(!tabelaVariaveisAtual->busca(cF->id->entradaTabela->pegarLexema())){
                if(tipo){
                    if(cF->arranjo){
                        cF->arranjo->aceita(this);
                    }
                    if(!erro){
                        AtributoVariavel *atr = new AtributoVariavel();
                        TipoId *tp = new TipoId(tipo->pegarLexema(),ID);
                        atr->atribuirTipo(tp);
                        atr->atribuirLexema(cF->id->entradaTabela->pegarLexema());
                        atr->atribuiArranjo(arranjo);
                        atr->atribuiPonteiro(false);
                        tabelaVariaveisAtual->insere(atr->pegarLexema(), atr);
                    }
                }
            }else{
                saidaErro(ErroSemanticoRedefinicaoVariavel,cF->id->linha, cF->id->coluna,
                          cF->id->entradaTabela->pegarLexema());
            }
        }else{
            saidaErro(ErroSemanticoVariavelIgualParametro,cF->id->linha, cF->id->coluna,
                      cF->id->entradaTabela->pegarLexema());
        }
    }
    if(cF->listaid) cF->listaid->aceita(this);
    erro = false;
    tipo = NULL;
    if(cF->lista) cF->lista->aceita(this);
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
    tabelaVariaveisAtual = atr->pegarVariaveis();
    tabelaFuncoesAtual = atr->pegarFuncoes();
    if(decC->local) decC->local->aceita(this);
    verificandoClasse = false;
    tabelaVariaveisAtual = NULL;
    tabelaFuncoesAtual = NULL;
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
    if(expU->expressao){
        expU->expressao->aceita(this);
        if(retorno != 0){
            if(retorno != ID && retorno != LITERAL){
                if(((AtributoVariavel*)valorRetorno)->pegarPonteiro()){
                    saidaErro(ErroSemanticoExpressaoInvalidaPonteiro, expU->linha, expU->coluna);
                }
                else if(((AtributoVariavel*)valorRetorno)->pegarArranjo()){
                         saidaErro(ErroSemanticoExpressaoInvalidaArranjo, expU->linha, expU->coluna);
                     }
            }
            else if(retorno == LITERAL || retorno == ID){
                     saidaErro(ErroSemanticoTipoOperacaoInvalida, expU->linha, expU->coluna);
                 }
                 else if(expU->operador == NEGACAO){
                          retorno = BOLEANO;
                      }
        }
    }
}
void AnalisadorSemantico::visita(NoExprBinaria* expB){
    if(verificandoCorpo){
        verificandoCorpo = false;
        if(expB->exprEsquerda){
            expB->exprEsquerda->aceita(this);
            if(retorno == ID){
                if(obtemTabelaTipos()->busca(valorRetorno->pegarLexema()) ||
                    obtemTabelaClasses()->busca(valorRetorno->pegarLexema())){
                    if(expB->exprDireita){
                        verificandoCorpo = true;
                        expB->exprDireita->aceita(this);
                        verificandoCorpo = false;
                        if(valorRetorno && !tabelaVariaveisAtual->busca(valorRetorno->pegarLexema())){
                            tipo = valorRetorno;
                            if(!tabelaParametrosAtual->busca(valorRetorno->pegarLexema())){
                                AtributoVariavel *atr = new AtributoVariavel();
                                TipoId *tp = new TipoId(tipo->pegarLexema(),ID);
                                if(retorno == NUM_INTEIRO && arranjo > 0){
                                    atr->atribuiArranjo(arranjo);
                                }
                                atr->atribuiPonteiro(true);
                                atr->atribuirTipo(tp);
                                atr->atribuirLexema(valorRetorno->pegarLexema());
                                tabelaVariaveisAtual->insere(atr->pegarLexema(),atr);
                            }else{
                                saidaErro(ErroSemanticoRedefinicaoVariavel, expB->exprEsquerda->linha,
                                          expB->exprEsquerda->coluna, tipo->pegarLexema());
                            }
                        }else if(valorRetorno){
                            saidaErro(ErroSemanticoRedefinicaoVariavel, expB->exprEsquerda->linha,
                                      expB->exprEsquerda->coluna, tipo->pegarLexema());
                        }
                    }
                }else{
                    saidaErro(ErroSemanticoTipoVariavel, expB->exprEsquerda->linha,
                                      expB->exprEsquerda->coluna, valorRetorno->pegarLexema());

                    retorno = 0;
                    valorRetorno = NULL;
                    tipo = NULL;
                    return;
                    expB->aceita(this);
                }
            }
        }
        retorno = 0;
        valorRetorno = NULL;
    }
    else{
        int tipoDir = 0, tipoEsq = 0;
        Atributo *idDir = NULL, *idEsq = NULL;
        if(expB->exprDireita){
            expB->exprDireita->aceita(this);
            if(!tipo){
                tipoDir = retorno;
                idDir = valorRetorno;
            }else{
                idDir = NULL;
                tipoDir = 0;
            }
        }
        if(expB->exprEsquerda){
            expB->exprEsquerda->aceita(this);
            if(!tipo){
                tipoEsq = retorno;
                idEsq = valorRetorno;
            }else{
                idEsq = NULL;
                tipoEsq = 0;
            }
        }
        if(tipoDir != ID && tipoEsq != ID && tipoDir != LITERAL && tipoEsq != LITERAL){
            bool erro = false;
            if(idDir){
                if(((AtributoVariavel*)idDir)->pegarPonteiro()){
                    saidaErro(ErroSemanticoExpressaoInvalidaPonteiro, expB->linha, expB->coluna);
                    erro = true;
                }
                else if(((AtributoVariavel*)idDir)->pegarArranjo()){
                         saidaErro(ErroSemanticoExpressaoInvalidaArranjo, expB->linha, expB->coluna);
                         erro = true;
                     }
            }
            if(idEsq){
                if(!erro && ((AtributoVariavel*)idEsq)->pegarPonteiro()){
                    saidaErro(ErroSemanticoExpressaoInvalidaPonteiro, expB->linha, expB->coluna);
                }
                else if(!erro && ((AtributoVariavel*)idEsq)->pegarArranjo()){
                         saidaErro(ErroSemanticoExpressaoInvalidaArranjo, expB->linha, expB->coluna);
                     }
            }
        }
        else{
            saidaErro(ErroSemanticoTipoOperacaoInvalida, expB->linha, expB->coluna);
        }
    }
}
void AnalisadorSemantico::visita(NoExprAtrib* atr){
    int tipoDir = 0, tipoEsq = 0;
    Atributo *idDir = NULL, *idEsq = NULL;
    if(atr->exprDireita){
        atr->exprDireita->aceita(this);
        tipoDir = retorno;
        idDir = valorRetorno;
    }
    if(atr->exprEsquerda){
        atr->exprEsquerda->aceita(this);
        tipoEsq = retorno;
        idEsq = valorRetorno;
    }
    if(tipoEsq == ID && tipoDir == ID){
        char *lex1 = ((TipoId*)((AtributoVariavel*)idEsq)->pegarTipo()->pegaTipo())->pegarLexema();
        char *lex2 = ((TipoId*)((AtributoVariavel*)idDir)->pegarTipo()->pegaTipo())->pegarLexema();
        if(!strcmp(lex1, lex2)){
            saidaErro(ErroSemanticoTipoAtribuicaoInvalido, atr->linha, atr->coluna, lex1, lex2);
        }
        else if(((AtributoVariavel*)idEsq)->pegarPonteiro() ^ ((AtributoVariavel*)idDir)->pegarPonteiro()){
                 saidaErro(ErroSemanticoExpressaoInvalidaPonteiro, atr->linha, atr->coluna);
             }
    }
    else if(tipoEsq != tipoDir && tipoEsq != 0 && tipoDir != 0 &&
           ((tipoEsq != REAL || tipoDir != INTEIRO) && (tipoEsq != INTEIRO || tipoDir != REAL))){
        saidaErro(ErroSemanticoTipoAtribuicaoInvalido, atr->linha, atr->coluna,
                  (char*) pegarTokenLiteral(tipoEsq), (char*) pegarTokenLiteral(tipoDir));
    }
}
void AnalisadorSemantico::visita(NoExprAceCamp* expAC){
    int tipoDir = 0;
    int tipoEsq = 0;
    Atributo *idDir = NULL, *idEsq = NULL;
    if(expAC->exprDireita){
        expAC->exprDireita->aceita(this);
        tipoDir = retorno;
        idDir = valorRetorno;
    }
    if(expAC->exprEsquerda){
        expAC->exprEsquerda->aceita(this);
        tipoEsq = retorno;
        idEsq = valorRetorno;
    }
    fprintf(stdout, "\n\n\n%d", retorno);
    if(idEsq && tipoEsq == ID){
        if((expAC->terminal == PONTEIRO &&   ((AtributoVariavel*)idEsq)->pegarPonteiro()) ||
           (expAC->terminal == PONTO    && !(((AtributoVariavel*)idEsq)->pegarPonteiro()))    ){
            Atributo *atr = NULL;
            if((atr = obtemTabelaClasses()->busca(idEsq->pegarLexema()))){
                Atributo *atrFunc = NULL;
                if((atrFunc = ((AtributoClasse*)atr)->buscaFuncao(idDir->pegarLexema()))){
                    if(!((AtributoVariavelClasse*)atrFunc)->pegaPublico()){
                        saidaErro(ErroSemanticoAcessoACampoPrivado, expAC->linha, expAC->coluna);
                    }
                    else{
                        retorno = ((AtributoFuncao*)atrFunc)->pegarRetorno()->pegaTipo();
                    }
                }
                else if((atrFunc = ((AtributoClasse*)atr)->buscaVariavel(idDir->pegarLexema()))){
                    if(!((AtributoVariavelClasse*)atrFunc)->pegaPublico()){
                        saidaErro(ErroSemanticoAcessoACampoPrivado, expAC->linha, expAC->coluna);
                    }
                    else{
                        retorno = ((AtributoVariavel*)atrFunc)->pegarTipo()->pegaTipo();
                    }
                }
                else saidaErro(ErroSemanticoAcessoNaoExiste, expAC->linha, expAC->coluna);
            }
            else if((atr = obtemTabelaTipos()->busca(idEsq->pegarLexema()))){
                Atributo *atrVar = NULL;
                if((atrVar = ((AtributoTipo*)atr)->buscaVariavel(idDir->pegarLexema()))){
                    retorno = ((AtributoVariavel*)atrVar)->pegarTipo()->pegaTipo();
                }
                else{
                    saidaErro(ErroSemanticoAcessoNaoExiste, expAC->linha, expAC->coluna);
                }
            }
            else{
                saidaErro(ErroSemanticoAcessoNaoExiste, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
            }
        }
        else{
            saidaErro(ErroSemanticoAcessoNaoExiste, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
        }
    }
    fprintf(stdout, "\n%d\n", retorno);
}
void AnalisadorSemantico::visita(NoVerdadeiro* tr){
    retorno = VERDADEIRO;
}
void AnalisadorSemantico::visita(NoFalso* fa){
    retorno = FALSO;
}
void AnalisadorSemantico::visita(NoEsse* th){

}
void AnalisadorSemantico::visita(NoNovo* n){

}
void AnalisadorSemantico::visita(NoTipo* tp){

}
void AnalisadorSemantico::visita(NoColchetes* nc){
    if(verificandoCorpo){
        if(nc->expressao){
            nc->expressao->aceita(this);
            if(retorno == NUM_INTEIRO){
                arranjo = atoi(valorRetorno->pegarLexema());
                if(nc->primario){
                    nc->primario->aceita(this);
                    if(retorno != ID){
                        saidaErro(ErroSemanticoTamanhoArranjoReal, nc->linha, nc->coluna);
                    }
                }
            }else{
                retorno = 0;
                valorRetorno = NULL;
                saidaErro(ErroSemanticoTamanhoArranjoReal, nc->linha, nc->coluna);
            }
        }
    }
}
