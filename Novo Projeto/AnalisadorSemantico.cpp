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
bool verificandoAcesso = false;
bool verificandoParametros = false;
bool encontrou = false;
bool erro = false;
bool verificandoCorpo = false;
bool ponteiro = false;
bool declVariavel = false;
int retorno = 0;
Atributo *valorRetorno = NULL;
Atributo *funcaoChamada = NULL;
int arranjo = 0;
Atributo *tipo = NULL;
AtributoClasse *tamanhoClasse = NULL;
AtributoTipo *tamanhoTipo = NULL;
NoDeclFuncao *funcAtual = NULL;
Atributo *arranjoEntrada = NULL;
NoListaSentenca *listaSentencaTemp = NULL;

AnalisadorSemantico::AnalisadorSemantico(){}
AnalisadorSemantico::~AnalisadorSemantico(){}
void AnalisadorSemantico::visita(NoPrograma* prog){
    if(NoDeclClasse* decC = dynamic_cast<NoDeclClasse*>(prog)) { decC->aceita(this); }
    else if(NoDeclTipo* decT = dynamic_cast<NoDeclTipo*>(prog)) { decT->aceita(this); }
    else if(NoDeclVariavel* decV = dynamic_cast<NoDeclVariavel*>(prog)) { decV->aceita(this); }
    else if(NoDeclFuncao* decF = dynamic_cast<NoDeclFuncao*>(prog)) { decF->aceita(this); }
}
void AnalisadorSemantico::visita(NoId* id){
    fprintf(stdout, "ID: %s\n", id->entradaTabela->pegarLexema());
    Atributo *atr = NULL;
    if(!(atr = tabelaParametrosAtual->busca(id->entradaTabela->pegarLexema()))){
        if(!(atr = tabelaVariaveisAtual->busca(id->entradaTabela->pegarLexema()))){
            if(!(atr = obtemTabelaVariaveis()->busca(id->entradaTabela->pegarLexema()))){
                retorno = ID;
                valorRetorno = id->entradaTabela;
                if(verificandoCorpo){
                    tipo = valorRetorno;
                } else tipo = 0;
                encontrou = false;
                return;
            }
        }
    }
    encontrou = true;
    retorno = ((AtributoVariavel*)atr)->pegarTipo()->pegaTipo();
    ponteiro = ((AtributoVariavel*)atr)->pegarPonteiro();
    id->tipo = ((AtributoVariavel*)atr)->pegarTipo();
    if(retorno == CARACTERE &&
            (((AtributoVariavel*)atr)->pegarPonteiro() || ((AtributoVariavel*)atr)->pegarArranjo())){
        retorno = LITERAL;
    }
    if(retorno == ID && !verificandoAcesso){
        Atributo *entradaTabela = obtemTabelaClasses()->busca(
                                                ((TipoId*)((AtributoVariavel*)atr)->pegarTipo())->pegarLexema());
        if(!entradaTabela){
            entradaTabela = obtemTabelaTipos()->busca(
                                                ((TipoId*)((AtributoVariavel*)atr)->pegarTipo())->pegarLexema());
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
    lit->tipo = new Tipo(LITERAL);
}
void AnalisadorSemantico::visita(NoAscii* asc){
    retorno = ASCII;
    asc->tipo = new Tipo(ASCII);
}
void AnalisadorSemantico::visita(NoParenteses* pa){
    if(pa->expressao) {
        pa->expressao->aceita(this);
        pa->tipo = pa->expressao->tipo;
    }
}
void AnalisadorSemantico::visita(NoConteudo* con){
    if(con->primario) {
        con->primario->aceita(this);
        con->tipo = con->primario->tipo;
    }
}
void AnalisadorSemantico::visita(NoEndereco* ende){
    if(ende->primario){
        ende->primario->aceita(this);
        ende->tipo = ende->primario->tipo;
    }
    if(retorno == ID){
        if(!tipo){
            ((AtributoVariavel*)valorRetorno)->atribuirEscapa(true);
        }
        ponteiro = true;
    }else{
        ponteiro = false;
    }
}
void AnalisadorSemantico::visita(NoNumInteiro* ni){
    retorno = NUM_INTEIRO;
    valorRetorno = ni->entradaTabela;
    ni->tipo = new Tipo(NUM_INTEIRO);
}
void AnalisadorSemantico::visita(NoNumReal* nr){
    retorno = NUM_REAL;
    nr->tipo = new Tipo(NUM_REAL);
}
void AnalisadorSemantico::visita(NoArranjo* arr){
    if(arr->num){
        arr->num->aceita(this);
        if(retorno != NUM_INTEIRO){
            saidaErro(ErroSemanticoTamanhoArranjoReal, arr->linha, arr->coluna);
            erro = true;
        }
        arranjoEntrada = valorRetorno;
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
    Atributo *atrT = NULL;
    Atributo *atrC = NULL;
    bool erroTipo = false;
    while(lf){
        if(lf->tipo->primitivo == ID){
            if(!(atrT = obtemTabelaTipos()->busca(lf->tipo->entradaTabela->pegarLexema()))){
                if(!(atrC = obtemTabelaClasses()->busca(lf->tipo->entradaTabela->pegarLexema()))){
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
                if(lf->ponteiro){
                    atr->atribuirEscapa(true);
                }
                if(atrT){
                    atr->atribuiTamanho(((AtributoTipo*)atrT)->pegarTamBytes());
                }else if(atrC){
                    atr->atribuiTamanho(((AtributoClasse*)atrC)->pegarTamBytes());
                }
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
    if(se->expressao){
        se->expressao->aceita(this);
        if(retorno == ID || retorno == REAL || retorno == LITERAL){
            saidaErro(ErroSemanticoExprContr, se->expressao->linha, se->expressao->coluna);
        }
    }
    if(se->sentenca){
        se->sentenca->aceita(this);
    }
    if(se->senao){
        se->senao->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoSenao* sen){
    if(sen->sentenca){
        sen->sentenca->aceita(this);
    }
}
void AnalisadorSemantico::visita(NoEnquanto* enq){
    if(enq->expressao){
        enq->expressao->aceita(this);
        if(retorno == ID || retorno == REAL || retorno == LITERAL){
            saidaErro(ErroSemanticoExprContr, enq->expressao->linha, enq->expressao->coluna);
        }
    }
}
void AnalisadorSemantico::visita(NoBlocoCaso* bc){
    if(bc->listaSentenca) bc->listaSentenca->aceita(this);
    if(bc->lista) bc->lista->aceita(this);
}
void AnalisadorSemantico::visita(NoDesvia* des){
    retorno = DESVIA;
}
void AnalisadorSemantico::visita(NoEscolha* sw){
    if(sw->expressao){
        sw->expressao->aceita(this);
        if(retorno == ID || retorno == LITERAL){
            saidaErro(ErroSemanticoExprContr, sw->expressao->linha, sw->expressao->coluna);
        }
    }
    if(sw->blocoCaso)sw->blocoCaso->aceita(this);
}
void AnalisadorSemantico::visita(NoImprime* imp){
    if(imp->listaExpr) imp->listaExpr->aceita(this);
}
void AnalisadorSemantico::visita(NoLeLinha* leL){
    if(leL->expressao) leL->expressao->aceita(this);
}
void AnalisadorSemantico::visita(NoRetorna* ret){
    if(ret->expressao) ret->expressao->aceita(this);
}
void AnalisadorSemantico::visita(NoLanca* lan){
}
void AnalisadorSemantico::visita(NoEscopo* esc){
    if(esc->lista) esc->lista->aceita(this);
}
void AnalisadorSemantico::visita(NoChamadaFuncao* cha){
    if(cha->id){
        Atributo *aux = NULL;
        cha->id->aceita(this);
        aux = valorRetorno;
        if(cha->parametros) cha->parametros->aceita(this);
        valorRetorno = aux;
        AtributoFuncao* func = ((AtributoFuncao*) obtemTabelaFuncoes()->busca(aux->pegarLexema()));
        if(func) cha->tipo = func->pegarRetorno();
    }
}
void AnalisadorSemantico::visita(NoTenta* te){
    if(te->sentencaTry) te->sentencaTry->aceita(this);
    if(te->sentencaCatch) te->sentencaCatch->aceita(this);
}
void AnalisadorSemantico::visita(NoSentencaExpr* senE){
    if(senE->expressao)senE->expressao->aceita(this);
}
void AnalisadorSemantico::visita(NoDeclFuncao* decF){
    funcAtual = decF;
    TabelaSimbolos *tabela;
    TabelaSimbolos *tabelaVariaveisAux = tabelaVariaveisAtual;
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
        saidaErro(ErroSemanticoRedefinicaoFuncao, decF->id->linha, decF->id->coluna,
                                                    decF->id->entradaTabela->pegarLexema());
    }else{
        AtributoFuncao *atr;
        if(verificandoClasse){
            atr = new AtributoFuncaoClasse();
            ((AtributoFuncaoClasse*)atr)->atribuiPublico(publico);
        }else{
            atr = new AtributoFuncao();
        }
        decF->atr = atr;

        if(decF->tipo->primitivo == ID){
            atr->adicionarRetorno(new TipoId(decF->tipo->entradaTabela->pegarLexema(), ID));
        }
        else
            atr->adicionarRetorno(new Tipo(decF->tipo->primitivo));

        atr->atribuirLexema(decF->id->entradaTabela->pegarLexema());
        atr->atribuirPonteiro(decF->ponteiro);
        tabela->insere(atr->pegarLexema(),atr);
        if(decF->parametros){
            tabelaVariaveisAtual = atr->pegarParametros();
            decF->parametros->aceita(this);
        }
        if(decF->variaveis){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->variaveis->aceita(this);
            tabelaParametrosAtual = NULL;
        }
        listaSentencaTemp = NULL;
        if(decF->corpoFunc){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->corpoFunc->aceita(this);
            if(listaSentencaTemp) {
                NoListaSentenca* t = listaSentencaTemp;
                while(t->lista) { t = t->lista; }
                t->lista = decF->sentenca;
                decF->sentenca = listaSentencaTemp;
            }
            tabelaParametrosAtual = NULL;
        }
        if(decF->sentenca){
            tabelaVariaveisAtual = atr->pegarVariaveisLocais();
            tabelaParametrosAtual = atr->pegarParametros();
            decF->sentenca->aceita(this);
            tabelaParametrosAtual = NULL;
        }
        tabelaVariaveisAtual = tabelaVariaveisAux;
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
                    TipoId *tp = new TipoId(tipo->pegarLexema(), ID);
                    atr->atribuirTipo(tp);
                    atr->atribuirLexema(lid->id->entradaTabela->pegarLexema());
                    atr->atribuiArranjo(arranjo);
                    atr->atribuiPonteiro(lid->ponteiro);
                    tabelaVariaveisAtual->insere(atr->pegarLexema(), atr);
                }
            }
        }else{
            saidaErro(ErroSemanticoRedefinicaoVariavel, lid->id->linha, lid->id->coluna,
                                                lid->id->entradaTabela->pegarLexema());
            if(lid->arranjo){
                lid->arranjo->aceita(this);
            }
        }
    }else{
        saidaErro(ErroSemanticoVariavelIgualParametro, lid->id->linha, lid->id->coluna,
                                                lid->id->entradaTabela->pegarLexema());
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
    Atributo *atrC = NULL;
    Atributo *atrT = NULL;
    TabelaSimbolos *tabela;
    if(!tabelaVariaveisAtual){
        tabela = obtemTabelaVariaveis();
    }else{
        tabela = tabelaVariaveisAtual;
    }
    if(decV->tipo->primitivo == ID){
        if(!(atrC = obtemTabelaClasses()->busca(decV->tipo->entradaTabela->pegarLexema()))){
            if(!(atrT = obtemTabelaTipos()->busca(decV->tipo->entradaTabela->pegarLexema()))){
                saidaErro(ErroSemanticoTipoVariavel, decV->linha, decV->coluna,
                                                decV->tipo->entradaTabela->pegarLexema());
                erroTipo = true;
            }
        }
    }
    NoListaId *aux = decV->variaveis;
    while(aux){
        if(tabela->busca(aux->id->entradaTabela->pegarLexema())){
            saidaErro(ErroSemanticoRedefinicaoVariavel, decV->linha, decV->coluna,
                                                aux->id->entradaTabela->pegarLexema());
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
                    if(aux->ponteiro){
                        atr->atribuirEscapa(true);
                    }
                    if(atrT){
                        atr->atribuiTamanho(((AtributoTipo*)atrT)->pegarTamBytes());
                    }else if(atrC){
                        atr->atribuiTamanho(((AtributoClasse*)atrC)->pegarTamBytes());
                    }
                    if(tamanhoClasse){
                        tamanhoClasse->adicionarTamanho(atr->pegarTamanho());
                    }
                    if(tamanhoTipo){
                        atr->atribuirDeslocamento(tamanhoTipo->pegarTamBytes());
                        tamanhoTipo->adicionarTamanho(atr->pegarTamanho());
                    }
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
        tamanhoTipo = atr;
        decT->campo->aceita(this);
        tamanhoTipo = NULL;
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
    declVariavel = false;
    if(cF->expressao) { tipo = 0; verificandoCorpo = true; cF->expressao->aceita(this); }
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
                        int tamanho = 4;
                        if(AtributoTipo* __atr = (AtributoTipo*)obtemTabelaTipos()->busca(tipo->pegarLexema())){
                            tamanho = __atr->pegarTamBytes();
                        } else if(AtributoClasse* __atr = (AtributoClasse*)obtemTabelaClasses()->busca(tipo->pegarLexema())) {
                            tamanho = __atr->pegarTamBytes();
                        }
                        atr->atribuirTipo(tp);
                        atr->atribuiTamanho(tamanho);
                        atr->atribuirLexema(cF->id->entradaTabela->pegarLexema());
                        atr->atribuiArranjo(arranjo);
                        atr->atribuiPonteiro(false);
                        tabelaVariaveisAtual->insere(atr->pegarLexema(), atr);
                        NoListaId * lsId = new NoListaId(true, new NoId(cF->id->entradaTabela, cF->linha, cF->coluna),
                                                         (atr->pegarArranjo() > 0) ? new NoArranjo(new NoNumInteiro(arranjoEntrada,
                                                                                                                    cF->linha,
                                                                                                                    cF->coluna),
                                                                                                   cF->linha, cF->coluna) : NULL,
                                                         NULL, cF->linha, cF->coluna);
                        NoDeclVariavel *dclVar = new NoDeclVariavel(new NoTipo(ID, cF->linha, cF->coluna, tipo), lsId, cF->linha, cF->coluna, funcAtual->variaveis);
                        funcAtual->variaveis = dclVar;
                        declVariavel = true;
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
    if(!declVariavel) {
        NoListaSentenca* temp = listaSentencaTemp;
        if(temp){
            while(temp->lista) { temp = temp->lista; }
            temp->lista = new NoListaSentenca(cF->expressao, NULL, cF->linha, cF->coluna);
        } else {
            listaSentencaTemp = new NoListaSentenca(cF->expressao, NULL, cF->linha, cF->coluna);
        }
        cF->expressao = NULL;
    }
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
         saidaErro(ErroSemanticoRedefinicaoClasse, decC->id->linha, decC->id->coluna,
                                            decC->id->entradaTabela->pegarLexema());
         erro = true;
    }
    atr = new AtributoClasse();
    verificandoClasse = true;
    tabelaVariaveisAtual = atr->pegarVariaveis();
    tabelaFuncoesAtual = atr->pegarFuncoes();
    tamanhoClasse = atr;
    if(decC->local) decC->local->aceita(this);
    tamanhoClasse = NULL;
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
        expU->tipo = expU->expressao->tipo;
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
Tipo *precedenciaTipo(Tipo *a, Tipo *b) {
    if(!a|| !b) { return NULL; }
    int _a = a->pegaTipo(), _b = b->pegaTipo();
    if(_b == ID || _a == ASCII || (_a == NUM_INTEIRO && _b == NUM_REAL))
        return b;
    else
        return a;
}

void AnalisadorSemantico::visita(NoExprBinaria* expB){
    if(verificandoCorpo){
        verificandoCorpo = false;
        if(expB->exprEsquerda){
            expB->exprEsquerda->aceita(this);
            if(retorno == ID){
                if(obtemTabelaTipos()->busca(valorRetorno->pegarLexema()) ||
                    obtemTabelaClasses()->busca(valorRetorno->pegarLexema())){
                    Atributo *tipoRetorno = valorRetorno;
                    if(expB->exprDireita){
                        verificandoCorpo = true;
                        expB->exprDireita->aceita(this);
                        verificandoCorpo = false;
                        if(valorRetorno && !tabelaVariaveisAtual->busca(valorRetorno->pegarLexema())){
                            tipo = tipoRetorno;
                            if(!tabelaParametrosAtual->busca(valorRetorno->pegarLexema())){
                                AtributoVariavel *atr = new AtributoVariavel();
                                TipoId *tp = new TipoId(tipo->pegarLexema(), ID);
                                if(retorno == NUM_INTEIRO && arranjo > 0){
                                    atr->atribuiArranjo(arranjo);
                                }
                                atr->atribuiPonteiro(true);
                                atr->atribuiTamanho(4);
                                atr->atribuirTipo(tp);
                                atr->atribuirLexema(valorRetorno->pegarLexema());
                                tabelaVariaveisAtual->insere(atr->pegarLexema(),atr);
                                NoListaId * lsId = new NoListaId(true, new NoId(valorRetorno, expB->linha, expB->coluna),
                                                                 (atr->pegarArranjo() > 0) ? new NoArranjo(new NoNumInteiro(arranjoEntrada,
                                                                                                                            expB->linha, expB->coluna),
                                                                                                           expB->linha, expB->coluna) : NULL ,
                                                                 NULL, expB->linha, expB->coluna);
                                NoDeclVariavel *dclVar = new NoDeclVariavel(new NoTipo(ID, expB->linha, expB->coluna, tipo), lsId, expB->linha, expB->coluna, funcAtual->variaveis);
                                funcAtual->variaveis = dclVar;
                                declVariavel = true;
                            }else{
                                saidaErro(ErroSemanticoRedefinicaoVariavel, expB->exprEsquerda->linha,
                                          expB->exprEsquerda->coluna, tipo->pegarLexema());
                            }
                        }else if(valorRetorno){
                            saidaErro(ErroSemanticoRedefinicaoVariavel, expB->exprEsquerda->linha,
                                      expB->exprEsquerda->coluna, valorRetorno->pegarLexema());
                        }
                    }
                }else{
                    if(!tabelaVariaveisAtual->busca(valorRetorno->pegarLexema())){
                        if(!tabelaParametrosAtual->busca(valorRetorno->pegarLexema())){
                            saidaErro(ErroSemanticoTipoVariavel, expB->exprEsquerda->linha,
                                      expB->exprEsquerda->coluna, valorRetorno->pegarLexema());

                            retorno = 0;
                            valorRetorno = NULL;
                            tipo = NULL;
                            return;
                        }
                    }
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
            /*bool erro = false;
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
            }*/
        }
        else{
            saidaErro(ErroSemanticoTipoOperacaoInvalida, expB->linha, expB->coluna);
        }
        /*if(expB->exprEsquerda && expB->exprDireita) {
            expB->tipo = precedenciaTipo(expB->exprEsquerda, expB->exprDireita)
        }*/

        if(expB->exprDireita && expB->exprEsquerda) {
            expB->tipo = precedenciaTipo(expB->exprDireita->tipo, expB->exprEsquerda->tipo);
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
        erro = false;
        atr->exprEsquerda->aceita(this);
        tipoEsq = retorno;
        idEsq = valorRetorno;
        atr->tipo = atr->exprEsquerda->tipo;
    }
    if(tipo && tipoEsq == ID && tipoDir == ID && !erro){
        char *lex1 = ((TipoId*)((AtributoVariavel*)idEsq)->pegarTipo()->pegaTipo())->pegarLexema();
        char *lex2 = ((TipoId*)((AtributoVariavel*)idDir)->pegarTipo()->pegaTipo())->pegarLexema();
        if(!strcmp(lex1, lex2)){
            saidaErro(ErroSemanticoTipoAtribuicaoInvalido, atr->linha, atr->coluna, lex1, lex2);
        }
        else if(((AtributoVariavel*)idEsq)->pegarPonteiro() ^ ((AtributoVariavel*)idDir)->pegarPonteiro()){
                 saidaErro(ErroSemanticoExpressaoInvalidaPonteiro, atr->linha, atr->coluna);
             }
    }
    else{
        if(erro){
            erro = false;
            saidaErro(ErroSemanticoFuncaoAtribuicaoInvalido, atr->linha, atr->coluna);
        }
        else if(tipoEsq != tipoDir){
            switch(tipoEsq){
                case ID:
                case LITERAL:
                    saidaErro(ErroSemanticoTipoAtribuicaoInvalido, atr->linha, atr->coluna,
                      (char*) pegarTokenLiteral(tipoEsq), (char*) pegarTokenLiteral(tipoDir));
                break;
                case INTEIRO:
                case REAL:
                case BOLEANO:
                case CARACTERE:
                    if(tipoDir == LITERAL || tipoDir == ID){
                        saidaErro(ErroSemanticoTipoAtribuicaoInvalido, atr->linha, atr->coluna,
                      (char*) pegarTokenLiteral(tipoEsq), (char*) pegarTokenLiteral(tipoDir));
                    }
                break;
            }
        }
    }
}
void AnalisadorSemantico::visita(NoExprAceCamp* expAC){
    int tipoEsq = 0, tipoDir = 0;
    Atributo *idDir = NULL, *idEsq = NULL;
    if(expAC->exprDireita){
        verificandoAcesso = true;
        expAC->exprDireita->aceita(this);
        verificandoAcesso = false;
        tipoDir = retorno;
        idDir = valorRetorno;
    }
    if(expAC->exprEsquerda){
        verificandoAcesso = true;
        expAC->exprEsquerda->aceita(this);
        verificandoAcesso = false;
        tipoEsq = retorno;
        idEsq = valorRetorno;
    }
    if(encontrou && idEsq && tipoEsq == ID){
        Atributo *atr = NULL;
        if(idDir) expAC->id_direita = idDir->pegarLexema();
        if((atr = obtemTabelaClasses()->busca(
                                    ((TipoId*)((AtributoVariavel*)idEsq)->pegarTipo())->pegarLexema()))){
            Atributo *atrFunc = NULL;
            if((atrFunc = ((AtributoClasse*)atr)->buscaFuncao(idDir->pegarLexema()))){
                if(!((AtributoFuncaoClasse*)atrFunc)->pegaPublico()){
                    saidaErro(ErroSemanticoAcessoACampoPrivado, expAC->linha, expAC->coluna);
                }
                else if(ponteiro && expAC->terminal == PONTO)
                    saidaErro(ErroSemanticoAcessoPonteiro, expAC->exprEsquerda->linha,expAC->exprEsquerda->coluna);
                else if(!ponteiro && expAC->terminal == PONTEIRO)
                    saidaErro(ErroSemanticoAcessoPonto, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
                else{
                    erro = true;
                    retorno = ((AtributoFuncao*)atrFunc)->pegarRetorno()->pegaTipo();
                    expAC->tipo = ((AtributoFuncao*)atrFunc)->pegarRetorno();
                    fprintf(stdout, "RETORNO: %s", (char*) pegarTokenLiteral(retorno));
                    if(retorno == CARACTERE &&
                            (((AtributoFuncao*)atrFunc)->pegarPonteiro())){
                        retorno = LITERAL;
                        expAC->tipo = new Tipo(LITERAL);
                    } else if(retorno == ID) {
                               if(!(valorRetorno = obtemTabelaClasses()->busca(((TipoId*)expAC->tipo)->pegarLexema()))) {
                                   valorRetorno = obtemTabelaTipos()->busca(((TipoId*)expAC->tipo)->pegarLexema());
                               }
                           }
                }
            }
            else if((atrFunc = ((AtributoClasse*)atr)->buscaVariavel(idDir->pegarLexema()))){
                if(!((AtributoVariavelClasse*)atrFunc)->pegaPublico()){
                    saidaErro(ErroSemanticoAcessoACampoPrivado, expAC->linha, expAC->coluna);
                }
                else if(ponteiro && expAC->terminal == PONTO)
                    saidaErro(ErroSemanticoAcessoPonteiro, expAC->exprEsquerda->linha,expAC->exprEsquerda->coluna);
                else if(!ponteiro && expAC->terminal == PONTEIRO)
                    saidaErro(ErroSemanticoAcessoPonto, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
                else{
                    retorno = ((AtributoVariavel*)atrFunc)->pegarTipo()->pegaTipo();
                    expAC->tipo = ((AtributoVariavel*)atrFunc)->pegarTipo();
                    fprintf(stdout, "RETORNO: %s", (char*) pegarTokenLiteral(retorno));
                    if(retorno == CARACTERE &&
                            (((AtributoVariavel*)atrFunc)->pegarPonteiro() ||
                             ((AtributoVariavel*)atrFunc)->pegarArranjo())    ){
                        retorno = LITERAL;
                        expAC->tipo = new Tipo(LITERAL);
                    } else if(retorno == ID) {
                               if(!(valorRetorno = obtemTabelaClasses()->busca(((TipoId*)expAC->tipo)->pegarLexema()))) {
                                   valorRetorno = obtemTabelaTipos()->busca(((TipoId*)expAC->tipo)->pegarLexema());
                               }
                           }
                }
            }
            else saidaErro(ErroSemanticoCampoNaoExiste, expAC->linha, expAC->coluna, idDir->pegarLexema());
        }
        else if((atr = obtemTabelaTipos()->busca(
                                    ((TipoId*)((AtributoVariavel*)idEsq)->pegarTipo())->pegarLexema()))){
            Atributo *atrVar = NULL;
            if((atrVar = ((AtributoTipo*)atr)->buscaVariavel(idDir->pegarLexema()))){
                retorno = ((AtributoVariavel*)atrVar)->pegarTipo()->pegaTipo();
                expAC->tipo = ((AtributoVariavel*)atrVar)->pegarTipo();
                if((retorno == CARACTERE &&
                        (((AtributoVariavel*)atrVar)->pegarPonteiro() ||
                         ((AtributoVariavel*)atrVar)->pegarArranjo())    )){
                    retorno = LITERAL;
                    expAC->tipo = new Tipo(LITERAL);
                } else if(retorno == ID) {
                           if(!(valorRetorno = obtemTabelaClasses()->busca(((TipoId*)expAC->tipo)->pegarLexema()))) {
                               valorRetorno = obtemTabelaTipos()->busca(((TipoId*)expAC->tipo)->pegarLexema());
                           }
                       }
            }
            else if(ponteiro && expAC->terminal == PONTO)
                saidaErro(ErroSemanticoAcessoPonteiro, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
            else if(!ponteiro && expAC->terminal == PONTEIRO)
                saidaErro(ErroSemanticoAcessoPonto, expAC->exprEsquerda->linha, expAC->exprEsquerda->coluna);
            else saidaErro(ErroSemanticoCampoNaoExiste, expAC->linha, expAC->coluna, idDir->pegarLexema());
        }
        else saidaErro(ErroSemanticoAcessoNaoExiste, expAC->exprEsquerda->linha,
                      expAC->exprEsquerda->coluna,
                      ((TipoId*)((AtributoVariavel*)idEsq)->pegarTipo())->pegarLexema());
    }
    else saidaErro(ErroSemanticoNaoPossuiAcesso, expAC->linha, expAC->coluna);
}
void AnalisadorSemantico::visita(NoVerdadeiro* tr){
    retorno = BOLEANO;
    tr->tipo = new Tipo(BOLEANO);
}
void AnalisadorSemantico::visita(NoFalso* fa){
    retorno = BOLEANO;
    fa->tipo = new Tipo(BOLEANO);
}
void AnalisadorSemantico::visita(NoEsse* th){
    if(!verificandoClasse){
        saidaErro(ErroSemanticoEsse, th->linha, th->coluna);
    }
    retorno = ESSE;
}
void AnalisadorSemantico::visita(NoNovo* n){
    if(n->id){
        n->id->aceita(this);
        if(!obtemTabelaClasses()->busca(valorRetorno->pegarLexema())){
            if(!obtemTabelaTipos()->busca(valorRetorno->pegarLexema())){
                saidaErro(ErroSemanticoTipoVariavel, n->id->linha, n->id->coluna);
            }
        }
    }
}
void AnalisadorSemantico::visita(NoTipo* tp){}
void AnalisadorSemantico::visita(NoColchetes* nc){
    if(verificandoCorpo){
        if(nc->expressao){
            nc->expressao->aceita(this);
            if(retorno == NUM_INTEIRO){
                arranjo = atoi(valorRetorno->pegarLexema());
                arranjoEntrada = valorRetorno;
                if(nc->primario){
                    nc->primario->aceita(this);
                    if(retorno != ID){
                        //saidaErro(ErroSemanticoTamanhoArranjoReal, nc->linha, nc->coluna);
                    }
                }
            }else{
                retorno = 0;
                valorRetorno = NULL;
                //saidaErro(ErroSemanticoTamanhoArranjoReal, nc->linha, nc->coluna);
            }
        }
    }else {
        if(nc->expressao) nc->expressao->aceita(this);
        if(nc->primario) {
            nc->primario->aceita(this);
            nc->tipo = nc->primario->tipo;
        }
    }
    nc->tipo = nc->primario->tipo;
}
