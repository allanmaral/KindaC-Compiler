#include "ASA.h"
#include "Visitante.h"
#include <string.h>
static TabelaIdentificador tabelaID;
static TabelaInteiro tabelaInteiro;
static TabelaLiteral tabelaLiteral;
static TabelaReal tabelaReal;

NoPrograma::NoPrograma(DeclClasse *listaClasse, DeclFuncao *listaFuncao, DeclTipo *listaTipo, DeclVariavel *listaVariavel){
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
NoParenteses::NoParenteses(Expr *expressao){
    this->expressao = expressao;
}
void NoParenteses::aceita(Visitante *v){
    v->visita(this);
}
NoConteudo::NoConteudo(Primario *primario){
    this->primario = primario;
}
void NoConteudo::aceita(Visitante *v){
    v->visita(this);
}
NoEndereco::NoEndereco(Primario *primario){
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
NoArranjo::NoArranjo(NumInteiro num):num(num){
    this->num = num;
}
void NoArranjo::aceita(Visitante *v){
    v->visita(this);
}
NoListaExpr::NoListaExpr(Expr *expressao, ListaExpr *lista){
    this->expressao = expressao;
    this->lista = lista;
}
void NoListaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoListaFormal::NoListaFormal(int tipo, bool ponteiro, Id id, Arranjo *arranjo, ListaFormal *lista){
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void NoListaFormal::aceita(Visitante *v){
    v->visita(this);
}
NoListaSentenca::NoListaSentenca(Sentenca *sentenca, ListaSentenca *lista){
    this->sentenca = sentenca;
    this->lista = lista;
}
void NoListaSentenca::aceita(Visitante *v){
    v->visita(this);
}
NoIf::NoIf(Expr *expressao, Sentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoIf::aceita(Visitante *v){
    v->visita(this);
}
NoElse::NoElse(Sentenca *sentenca){
    this->sentenca = sentenca;
}
void NoElse::aceita(Visitante *v){
    v->visita(this);
}
NoWhile::NoWhile(Expr *expressao, Sentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoWhile::aceita(Visitante *v){
    v->visita(this);
}
NoBlocoCaso::NoBlocoCaso(Num *num, ListaSentenca *listaSentenca, BlocoCaso *lista){
    this->num = num;
    this->listaSentenca = listaSentenca;
    this->lista = lista;
}
void NoBlocoCaso::aceita(Visitante *v){
    v->visita(this);
}
NoSwitch::NoSwitch(Expr *expressao, BlocoCaso blocoCaso):blocoCaso(blocoCaso){
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
void NoSwitch::aceita(Visitante *v){
    v->visita(this);
}
NoPrint::NoPrint(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void NoPrint::aceita(Visitante *v){
    v->visita(this);
}
NoReadLn::NoReadLn(Expr *expressao){
    this->expressao = expressao;
}
void NoReadLn::aceita(Visitante *v){
    v->visita(this);
}
NoReturn::NoReturn(Expr *expressao){
    this->expressao = expressao;
}
void NoReturn::aceita(Visitante *v){
    v->visita(this);
}
NoEscopo::NoEscopo(ListaSentenca *lista){
    this->lista = lista;
}
void NoEscopo::aceita(Visitante *v){
    v->visita(this);
}
NoChamadaFuncao::NoChamadaFuncao(Id id, ListaExpr *parametros){
    this->id = id;
    this->parametros = parametros;
}
void NoChamadaFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoTry::NoTry(Sentenca *sentencaTry, Sentenca *sentencaCatch){
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
void NoTry::aceita(Visitante *v){
    v->visita(this);
}
NoSentencaExpr::NoSentencaExpr(Expr *expressao){
    this->expressao = expressao;
}
void NoSentencaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoDeclFuncao::NoDeclFuncao(int tipo, Id id, ListaFormal *parametros, DeclVariavel *variaveis, ListaSentenca sentenca, DeclFuncao *lista):sentenca(sentenca){
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
NoListaId::NoListaId(ListaId *lista, bool ponteiro, Arranjo *arranjo){
    this->lista = lista;
    this->ponteiro = ponteiro;
    this->arranjo = arranjo;
}
void NoListaId::aceita(Visitante *v){
    v->visita(this);
}
NoDeclVariavel::NoDeclVariavel(int tipo, ListaId variaveis, DeclVariavel *lista):variaveis(variaveis){
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
void NoDeclVariavel::aceita(Visitante *v){
    v->visita(this);
}
NoDeclTipo::NoDeclTipo(DeclVariavel *campo){
    this->campo = campo;
}
void NoDeclTipo::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalFuncao::NoDeclLocalFuncao(DeclFuncao funcao, DeclLocal *lista):funcao(funcao){
    this->funcao = funcao;
    this->lista = lista;
}
void NoDeclLocalFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalVariavel::NoDeclLocalVariavel(DeclVariavel variavel, DeclLocal *lista):variavel(variavel){
    this->variavel = variavel;
    this->lista = lista;
}
void NoDeclLocalVariavel::aceita(Visitante *v){
    v->visita(this);
}

NoDeclLocalPublic::NoDeclLocalPublic(DeclLocal *lista){
    this->lista = lista;
}
void NoDeclLocalPublic::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalPrivate::NoDeclLocalPrivate(DeclLocal *lista){
    this->lista = lista;
}
void NoDeclLocalPrivate::aceita(Visitante *v){
    v->visita(this);
}

NoDeclClasse::NoDeclClasse(Id id, Id *heranca, DeclLocal *lista){
    this->id = id;
    this->heranca = heranca;
    this->lista = lista;
}
void NoDeclClasse::aceita(Visitante *v){
    v->visita(this);
}
NoExprUnaria::NoExprUnaria(int operador, Expr *expressao){
    this->operador = operador;
    this->expressao = expressao;
}
void NoExprUnaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprBinaria::NoExprBinaria(int operador, Expr *exprEsquerda, Expr *exprDireita){
    this->operador = operador;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprBinaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprAtrib::NoExprAtrib(Expr *exprEsquerda, Expr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprAtrib::aceita(Visitante *v){
    v->visita(this);
}
NoExprAceCamp::NoExprAceCamp(Expr *exprEsquerda, Expr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprAceCamp::aceita(Visitante *v){
    v->visita(this);
}
NoNew::NoNew(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void NoNew::aceita(Visitante *v){
    v->visita(this);
}
TabelaIdentificador* obtemTabelaIdentificador(){return &tabelaID;};
TabelaLiteral* obtemTabelaLiteral(){return &tabelaLiteral;};
TabelaInteiro* obtemTabelaInteiro(){return &tabelaInteiro;};
TabelaReal*    obtemTabelaReal(){return &tabelaReal;};
