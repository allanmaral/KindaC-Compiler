#include "ASA.h"
#include "Visitante.h"
#include <string.h>

static TabelaIdentificador tabelaID;
static TabelaInteiro tabelaInteiro;
static TabelaLiteral tabelaLiteral;
static TabelaReal tabelaReal;
static TabelaSimbolos tabelaClasses;
static TabelaSimbolos tabelaFuncoes;
static TabelaSimbolos tabelaVariaveis;
static TabelaSimbolos tabelaTipos;

NoPrograma::NoPrograma(NoDeclClasse *listaClasse, NoDeclFuncao *listaFuncao, NoDeclTipo *listaTipo,
                       NoDeclVariavel *listaVariavel){
    this->listaClasse = listaClasse;
    this->listaFuncao = listaFuncao;
    this->listaTipo = listaTipo;
    this->listaVariavel = listaVariavel;
}
void NoId::aceita(Visitante *v){
    v->visita(this);
}
NoId::NoId(Atributo *entradaTabela){
    this->entradaTabela = entradaTabela;
}
void NoPrograma::aceita(Visitante *v){
    v->visita(this);
}
NoLiteral::NoLiteral(Atributo *entradaTabela){
    this->entradaTabela = entradaTabela;
}
void NoLiteral::aceita(Visitante *v){
    v->visita(this);
}
NoAscii::NoAscii(Atributo *entradaTabela){
    this->entradaTabela = entradaTabela;
}
void NoAscii::aceita(Visitante *v){
    v->visita(this);
}
NoParenteses::NoParenteses(NoExpr *expressao){
    this->expressao = expressao;
}
void NoParenteses::aceita(Visitante *v){
    v->visita(this);
}
NoConteudo::NoConteudo(NoPrimario *primario){
    this->primario = primario;
}
void NoConteudo::aceita(Visitante *v){
    v->visita(this);
}
NoEndereco::NoEndereco(NoPrimario *primario){
    this->primario = primario;
}
void NoEndereco::aceita(Visitante *v){
    v->visita(this);
}
NoNumInteiro::NoNumInteiro(Atributo *entradaTabela){
    this->entradaTabela = entradaTabela;
}
void NoNumInteiro::aceita(Visitante *v){
    v->visita(this);
}
NoNumReal::NoNumReal(Atributo *entradaTabela){
    this->entradaTabela = entradaTabela;
}
void NoNumReal::aceita(Visitante *v){
    v->visita(this);
}
NoArranjo::NoArranjo(NoNum *num){
    this->num = num;
}
void NoArranjo::aceita(Visitante *v){
    v->visita(this);
}
NoListaExpr::NoListaExpr(NoExpr *expressao, NoListaExpr *lista){
    this->expressao = expressao;
    this->lista = lista;
}
void NoListaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoListaFormal::NoListaFormal(NoTipo *tipo, bool ponteiro, NoId *id, NoArranjo *arranjo, NoListaFormal *lista){
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void NoListaFormal::aceita(Visitante *v){
    v->visita(this);
}
NoListaSentenca::NoListaSentenca(NoSentenca *sentenca, NoListaSentenca *lista){
    this->sentenca = sentenca;
    this->lista = lista;
}
void NoListaSentenca::aceita(Visitante *v){
    v->visita(this);
}
NoSe::NoSe(NoExpr *expressao, NoSentenca *sentenca, NoSenao *senao){
    this->expressao = expressao;
    this->sentenca = sentenca;
    this->senao = senao;
}
void NoSe::aceita(Visitante *v){
    v->visita(this);
}
NoSenao::NoSenao(NoSentenca *sentenca){
    this->sentenca = sentenca;
}
void NoSenao::aceita(Visitante *v){
    v->visita(this);
}
NoEnquanto::NoEnquanto(NoExpr *expressao, NoSentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoEnquanto::aceita(Visitante *v){
    v->visita(this);
}
NoBlocoCaso::NoBlocoCaso(NoNum *num, NoListaSentenca *listaSentenca, NoBlocoCaso *lista){
    this->num = num;
    this->listaSentenca = listaSentenca;
    this->lista = lista;
}
void NoBlocoCaso::aceita(Visitante *v){
    v->visita(this);
}
NoEscolha::NoEscolha(NoExpr *expressao, NoBlocoCaso *blocoCaso){
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
void NoEscolha::aceita(Visitante *v){
    v->visita(this);
}
void NoDesvia::aceita(Visitante *v){
    v->visita(this);
}
NoImprime::NoImprime(NoListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void NoImprime::aceita(Visitante *v){
    v->visita(this);
}
NoLeLinha::NoLeLinha(NoExpr *expressao){
    this->expressao = expressao;
}
void NoLeLinha::aceita(Visitante *v){
    v->visita(this);
}
NoRetorna::NoRetorna(NoExpr *expressao){
    this->expressao = expressao;
}
void NoRetorna::aceita(Visitante *v){
    v->visita(this);
}
void NoLanca::aceita(Visitante *v){
    v->visita(this);
}
NoEscopo::NoEscopo(NoListaSentenca *lista){
    this->lista = lista;
}
void NoEscopo::aceita(Visitante *v){
    v->visita(this);
}
NoChamadaFuncao::NoChamadaFuncao(NoId *id, NoListaExpr *parametros){
    this->id = id;
    this->parametros = parametros;
}
void NoChamadaFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoTenta::NoTenta(NoSentenca *sentencaTry, NoSentenca *sentencaCatch){
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
void NoTenta::aceita(Visitante *v){
    v->visita(this);
}
NoSentencaExpr::NoSentencaExpr(NoExpr *expressao){
    this->expressao = expressao;
}
void NoSentencaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoDeclFuncao::NoDeclFuncao(NoTipo* tipo, int ponteiro, NoId *id, NoListaFormal *parametros,
                           NoDeclVariavel *variaveis, NoListaSentenca *sentenca, NoDeclFuncao *lista){
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->parametros = parametros;
    this->variaveis = variaveis;
    this->sentenca = sentenca;
    this->corpoFunc = NULL;
    this->lista = lista;
}
void NoDeclFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoListaId::NoListaId(bool ponteiro, NoId* id, NoArranjo *arranjo, NoListaId *lista){
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void NoListaId::aceita(Visitante *v){
    v->visita(this);
}
NoDeclVariavel::NoDeclVariavel(NoTipo *tipo, NoListaId *variaveis, NoDeclVariavel *lista){
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
void NoDeclVariavel::aceita(Visitante *v){
    v->visita(this);
}
NoDeclTipo::NoDeclTipo(NoDeclVariavel *campo, NoId *id, NoDeclTipo *lista){
    this->campo = campo;
    this->id = id;
    this->lista = lista;
}
void NoDeclTipo::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalFuncao::NoDeclLocalFuncao(NoDeclFuncao *funcao, NoDeclLocal *lista){
    this->funcao = funcao;
    this->lista = lista;
}
void NoDeclLocalFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalVariavel::NoDeclLocalVariavel(NoDeclVariavel *variavel, NoDeclLocal *lista){
    this->variavel = variavel;
    this->lista = lista;
}
void NoDeclLocalVariavel::aceita(Visitante *v){
    v->visita(this);
}

NoDeclLocalPublic::NoDeclLocalPublic(NoDeclLocal *lista){
    this->lista = lista;
}
void NoDeclLocalPublic::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalPrivate::NoDeclLocalPrivate(NoDeclLocal *lista){
    this->lista = lista;
}
void NoDeclLocalPrivate::aceita(Visitante *v){
    v->visita(this);
}
NoCorpoFuncao::NoCorpoFuncao(NoListaExpr *listaExpr, NoCorpoFuncao *lista){
    this->listaExpr = listaExpr;
    this->lista = lista;
}
void NoCorpoFuncao::aceita(Visitante* v){
    v->visita(this);
}
NoDeclClasse::NoDeclClasse(NoId *id, NoId *heranca, NoDeclLocal *local, NoDeclClasse *lista){
    this->id = id;
    this->heranca = heranca;
    this->local = local;
    this->lista = lista;
}
void NoDeclClasse::aceita(Visitante *v){
    v->visita(this);
}
NoExprUnaria::NoExprUnaria(int operador, NoExpr *expressao){
    this->operador = operador;
    this->expressao = expressao;
}
void NoExprUnaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprBinaria::NoExprBinaria(int operador, NoExpr *exprEsquerda, NoExpr *exprDireita){
    this->operador = operador;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprBinaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprAtrib::NoExprAtrib(NoExpr *exprEsquerda, NoExpr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprAtrib::aceita(Visitante *v){
    v->visita(this);
}
NoExprAceCamp::NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita, int terminal){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
    this->terminal = terminal;
}
void NoExprAceCamp::aceita(Visitante *v){
    v->visita(this);
}
NoNovo::NoNovo(NoId* id, NoListaExpr *listaExpr){
    this->id = id;
    this->listaExpr = listaExpr;
}
void NoNovo::aceita(Visitante *v){
    v->visita(this);
}
void NoEsse::aceita(Visitante *v){
    v->visita(this);
}
void NoVerdadeiro::aceita(Visitante *v){
    v->visita(this);
}
void NoFalso::aceita(Visitante *v){
    v->visita(this);
}
NoTipo::NoTipo(int primitivo, Atributo *entradaTabela){
    this->primitivo = primitivo;
    this->entradaTabela = entradaTabela;
}
void NoTipo::aceita(Visitante *v){
    v->visita(this);
}
NoColchetes::NoColchetes(NoPrimario *primario, NoExpr *expressao){
    this->primario = primario;
    this->expressao = expressao;
}
void NoColchetes::aceita(Visitante *v){
    v->visita(this);
}
TabelaIdentificador* obtemTabelaIdentificador(){return &tabelaID;};
TabelaLiteral* obtemTabelaLiteral(){return &tabelaLiteral;};
TabelaInteiro* obtemTabelaInteiro(){return &tabelaInteiro;};
TabelaReal*    obtemTabelaReal(){return &tabelaReal;};
