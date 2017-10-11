#include "ASA.h"
#include "Visitante.h"
#include "AnalisadorLexico.h"
#include <string.h>

static TabelaIdentificador tabelaID;
static TabelaInteiro tabelaInteiro;
static TabelaLiteral tabelaLiteral;
static TabelaReal tabelaReal;

NoPrograma::NoPrograma(NoDeclClasse *listaClasse, NoDeclFuncao *listaFuncao, NoDeclTipo *listaTipo, NoDeclVariavel *listaVariavel){
    this->listaClasse = listaClasse;
    this->listaFuncao = listaFuncao;
    this->listaTipo = listaTipo;
    this->listaVariavel = listaVariavel;
}
void NoId::aceita(Visitante *v){
    v->visita(this);
}
void NoPrograma::aceita(Visitante *v){
    v->visita(this);
}
NoLiteral::NoLiteral(char *literal){
    this->literal = new char[strlen(literal)+1];
    strcpy(this->literal, literal);
}
NoLiteral::~NoLiteral(){
    delete []literal;
}
void NoLiteral::aceita(Visitante *v){
    v->visita(this);
}
NoAscii::NoAscii(char caractere){
    this->caractere = caractere;
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
NoNumInteiro::NoNumInteiro(int num){
    this->num = num;
}
void NoNumInteiro::aceita(Visitante *v){
    v->visita(this);
}
NoNumReal::NoNumReal(float num){
    this->num = num;
}
void NoNumReal::aceita(Visitante *v){
    v->visita(this);
}
NoArranjo::NoArranjo(NoNumInteiro *num){
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
NoListaFormal::NoListaFormal(int tipo, bool ponteiro, NoId *id, NoArranjo *arranjo, NoListaFormal *lista){
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
NoIf::NoIf(NoExpr *expressao, NoSentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoIf::aceita(Visitante *v){
    v->visita(this);
}
NoElse::NoElse(NoSentenca *sentenca){
    this->sentenca = sentenca;
}
void NoElse::aceita(Visitante *v){
    v->visita(this);
}
NoWhile::NoWhile(NoExpr *expressao, NoSentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoWhile::aceita(Visitante *v){
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
NoSwitch::NoSwitch(NoExpr *expressao, NoBlocoCaso *blocoCaso):blocoCaso(blocoCaso){
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
void NoSwitch::aceita(Visitante *v){
    v->visita(this);
}
NoPrint::NoPrint(NoListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void NoPrint::aceita(Visitante *v){
    v->visita(this);
}
NoReadLn::NoReadLn(NoExpr *expressao){
    this->expressao = expressao;
}
void NoReadLn::aceita(Visitante *v){
    v->visita(this);
}
NoReturn::NoReturn(NoExpr *expressao){
    this->expressao = expressao;
}
void NoReturn::aceita(Visitante *v){
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
NoTry::NoTry(NoSentenca *sentencaTry, NoSentenca *sentencaCatch){
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
void NoTry::aceita(Visitante *v){
    v->visita(this);
}
NoSentencaExpr::NoSentencaExpr(NoExpr *expressao){
    this->expressao = expressao;
}
void NoSentencaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoDeclFuncao::NoDeclFuncao(int tipo, NoId *id, NoListaFormal *parametros, NoDeclVariavel *variaveis, NoListaSentenca *sentenca, NoDeclFuncao *lista){
    this->tipo = tipo;
    this->id = id;
    this->parametros = parametros;
    this->variaveis = variaveis;
    this->sentenca = sentenca;
    this->lista = lista;
}
void NoDeclFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoListaId::NoListaId(NoListaId *lista, bool ponteiro, NoArranjo *arranjo){
    this->lista = lista;
    this->ponteiro = ponteiro;
    this->arranjo = arranjo;
}
void NoListaId::aceita(Visitante *v){
    v->visita(this);
}
NoDeclVariavel::NoDeclVariavel(int tipo, NoListaId *variaveis, NoDeclVariavel *lista){
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
void NoDeclVariavel::aceita(Visitante *v){
    v->visita(this);
}
NoDeclTipo::NoDeclTipo(NoDeclVariavel *campo){
    this->campo = campo;
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

NoDeclClasse::NoDeclClasse(NoId *id, NoId *heranca, NoDeclLocal *lista){
    this->id = id;
    this->heranca = heranca;
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
NoExprAceCamp::NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprAceCamp::aceita(Visitante *v){
    v->visita(this);
}
NoNew::NoNew(NoListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void NoNew::aceita(Visitante *v){
    v->visita(this);
}
NoTipo::NoTipo(int primitivo):primitivo(primitivo), atributo(NULL){
    if(primitivo == ID){ atributo = pegarUltimoAtributo(); }
}
void NoTipo::aceita(Visitante *v){
    v->visita(this);
}

TabelaIdentificador* obtemTabelaIdentificador(){return &tabelaID;};
TabelaLiteral* obtemTabelaLiteral(){return &tabelaLiteral;};
TabelaInteiro* obtemTabelaInteiro(){return &tabelaInteiro;};
TabelaReal*    obtemTabelaReal(){return &tabelaReal;};
