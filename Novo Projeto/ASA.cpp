#include "ASA.h"
#include "Visitante.h"
#include <string.h>
static TabelaIdentificador tabelaID;
static TabelaInteiro tabelaInteiro;
static TabelaLiteral tabelaLiteral;
static TabelaReal tabelaReal;

Programa::Programa(DeclClasse *listaClasse, DeclFuncao *listaFuncao, DeclTipo *listaTipo, DeclVariavel *listaVariavel){
    this->listaClasse = listaClasse;
    this->listaFuncao = listaFuncao;
    this->listaTipo = listaTipo;
    this->listaVariavel = listaVariavel;
}
void Id::aceita(Visitante *v){
    v->visita(this);
}
void Programa::aceita(Visitante *v){
    v->visita(this);
}
Literal::Literal(char *literal){
    strcpy(this->literal, literal);
}
Literal::~Literal(){
    delete []literal;
}
void Literal::aceita(Visitante *v){
    v->visita(this);
}
Ascii::Ascii(char caractere){
    this->caractere = caractere;
}
void Ascii::aceita(Visitante *v){
    v->visita(this);
}
Parenteses::Parenteses(Expr *expressao){
    this->expressao = expressao;
}
void Parenteses::aceita(Visitante *v){
    v->visita(this);
}
Conteudo::Conteudo(Primario *primario){
    this->primario = primario;
}
void Conteudo::aceita(Visitante *v){
    v->visita(this);
}
Endereco::Endereco(Primario *primario){
    this->primario = primario;
}
void Endereco::aceita(Visitante *v){
    v->visita(this);
}
NumInteiro::NumInteiro(int num){
    this->num = num;
}
void NumInteiro::aceita(Visitante *v){
    v->visita(this);
}
NumReal::NumReal(float num){
    this->num = num;
}
void NumReal::aceita(Visitante *v){
    v->visita(this);
}
Arranjo::Arranjo(NumInteiro num):num(num){
    this->num = num;
}
void Arranjo::aceita(Visitante *v){
    v->visita(this);
}
ListaExpr::ListaExpr(Expr *expressao, ListaExpr *lista){
    this->expressao = expressao;
    this->lista = lista;
}
void ListaExpr::aceita(Visitante *v){
    v->visita(this);
}
ListaFormal::ListaFormal(int tipo, bool ponteiro, Id id, Arranjo *arranjo, ListaFormal *lista){
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void ListaFormal::aceita(Visitante *v){
    v->visita(this);
}
ListaSentenca::ListaSentenca(Sentenca *sentenca, ListaSentenca *lista){
    this->sentenca = sentenca;
    this->lista = lista;
}
void ListaSentenca::aceita(Visitante *v){
    v->visita(this);
}
If::If(Expr *expressao, Sentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void If::aceita(Visitante *v){
    v->visita(this);
}
Else::Else(Sentenca *sentenca){
    this->sentenca = sentenca;
}
void Else::aceita(Visitante *v){
    v->visita(this);
}
While::While(Expr *expressao, Sentenca *sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void While::aceita(Visitante *v){
    v->visita(this);
}
BlocoCaso::BlocoCaso(Num *num, ListaSentenca *listaSentenca, BlocoCaso *lista){
    this->num = num;
    this->listaSentenca = listaSentenca;
    this->lista = lista;
}
void BlocoCaso::aceita(Visitante *v){
    v->visita(this);
}
Switch::Switch(Expr *expressao, BlocoCaso blocoCaso):blocoCaso(blocoCaso){
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
void Switch::aceita(Visitante *v){
    v->visita(this);
}
Print::Print(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void Print::aceita(Visitante *v){
    v->visita(this);
}
ReadLn::ReadLn(Expr *expressao){
    this->expressao = expressao;
}
void ReadLn::aceita(Visitante *v){
    v->visita(this);
}
Return::Return(Expr *expressao){
    this->expressao = expressao;
}
void Return::aceita(Visitante *v){
    v->visita(this);
}
Escopo::Escopo(ListaSentenca *lista){
    this->lista = lista;
}
void Escopo::aceita(Visitante *v){
    v->visita(this);
}
ChamadaFuncao::ChamadaFuncao(Id id, ListaExpr *parametros){
    this->id = id;
    this->parametros = parametros;
}
void ChamadaFuncao::aceita(Visitante *v){
    v->visita(this);
}
Try::Try(Sentenca *sentencaTry, Sentenca *sentencaCatch){
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
void Try::aceita(Visitante *v){
    v->visita(this);
}
SentencaExpr::SentencaExpr(Expr *expressao){
    this->expressao = expressao;
}
void SentencaExpr::aceita(Visitante *v){
    v->visita(this);
}
DeclFuncao::DeclFuncao(int tipo, Id id, ListaFormal *parametros, DeclVariavel *variaveis, ListaSentenca sentenca, DeclFuncao *lista):sentenca(sentenca){
    this->tipo = tipo;
    this->id = id;
    this->parametros = parametros;
    this->variaveis = variaveis;
    this->sentenca = sentenca;
    this->lista = lista;
}
void DeclFuncao::aceita(Visitante *v){
    v->visita(this);
}
ListaId::ListaId(ListaId *lista, bool ponteiro, Arranjo *arranjo){
    this->lista = lista;
    this->ponteiro = ponteiro;
    this->arranjo = arranjo;
}
void ListaId::aceita(Visitante *v){
    v->visita(this);
}
DeclVariavel::DeclVariavel(int tipo, ListaId variaveis, DeclVariavel *lista):variaveis(variaveis){
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
void DeclVariavel::aceita(Visitante *v){
    v->visita(this);
}
DeclTipo::DeclTipo(DeclVariavel *campo){
    this->campo = campo;
}
void DeclTipo::aceita(Visitante *v){
    v->visita(this);
}
DeclLocalFuncao::DeclLocalFuncao(DeclFuncao funcao, DeclLocal *lista):funcao(funcao){
    this->funcao = funcao;
    this->lista = lista;
}
void DeclLocalFuncao::aceita(Visitante *v){
    v->visita(this);
}
DeclLocalVariavel::DeclLocalVariavel(DeclVariavel variavel, DeclLocal *lista):variavel(variavel){
    this->variavel = variavel;
    this->lista = lista;
}
void DeclLocalVariavel::aceita(Visitante *v){
    v->visita(this);
}

DeclLocalPublic::DeclLocalPublic(DeclLocal *lista){
    this->lista = lista;
}
void DeclLocalPublic::aceita(Visitante *v){
    v->visita(this);
}
DeclLocalPrivate::DeclLocalPrivate(DeclLocal *lista){
    this->lista = lista;
}
void DeclLocalPrivate::aceita(Visitante *v){
    v->visita(this);
}

DeclClasse::DeclClasse(Id id, Id *heranca, DeclLocal *lista){
    this->id = id;
    this->heranca = heranca;
    this->lista = lista;
}
void DeclClasse::aceita(Visitante *v){
    v->visita(this);
}
ExprUnaria::ExprUnaria(int operador, Expr *expressao){
    this->operador = operador;
    this->expressao = expressao;
}
void ExprUnaria::aceita(Visitante *v){
    v->visita(this);
}
ExprBinaria::ExprBinaria(int operador, Expr *exprEsquerda, Expr *exprDireita){
    this->operador = operador;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void ExprBinaria::aceita(Visitante *v){
    v->visita(this);
}
ExprAtrib::ExprAtrib(Expr *exprEsquerda, Expr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void ExprAtrib::aceita(Visitante *v){
    v->visita(this);
}
ExprAceCamp::ExprAceCamp(Expr *exprEsquerda, Expr *exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void ExprAceCamp::aceita(Visitante *v){
    v->visita(this);
}
New::New(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
void New::aceita(Visitante *v){
    v->visita(this);
}
TabelaIdentificador* obtemTabelaIdentificador(){return &tabelaID;};
TabelaLiteral* obtemTabelaLiteral(){return &tabelaLiteral;};
TabelaInteiro* obtemTabelaInteiro(){return &tabelaInteiro;};
TabelaReal*    obtemTabelaReal(){return &tabelaReal;};
