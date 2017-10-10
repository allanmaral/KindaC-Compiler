#include "ASA.h"
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
Literal::Literal(char *literal){
    strcpy(this->literal, literal);
}
Literal::~Literal(){
    delete []literal;
}
Ascii::Ascii(char caractere){
    this->caractere = caractere;
}
Parenteses::Parenteses(Expr expressao){
    this->expressao = expressao;
}
Conteudo::Conteudo(Primario primario){
    this->primario = primario;
}
Endereco::Endereco(Primario primario){
    this->primario = primario;
}
NumInteiro::NumInteiro(int num){
    this->num = num;
}
NumReal::NumReal(float num){
    this->num = num;
}
Arranjo::Arranjo(NumInteiro num):num(num){
    this->num = num;
}
ListaExpr::ListaExpr(Expr expressao, ListaExpr *lista){
    this->expressao = expressao;
    this->lista = lista;
}
ListaFormal::ListaFormal(int tipo, bool ponteiro, Id id, Arranjo *arranjo, ListaFormal *lista){
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
ListaSentenca::ListaSentenca(Sentenca sentenca, ListaSentenca *lista){
    this->sentenca = sentenca;
    this->lista = lista;
}
If::If(Expr expressao, Sentenca sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
Else::Else(Sentenca sentenca){
    this->sentenca = sentenca;
}
While::While(Expr expressao, Sentenca sentenca){
    this->expressao = expressao;
    this->sentenca = sentenca;
}
BlocoCaso::BlocoCaso(Num num, ListaSentenca *listaSentenca, BlocoCaso *lista){
    this->num = num;
    this->listaSentenca = listaSentenca;
    this->lista = lista;
}
Switch::Switch(Expr expressao, BlocoCaso blocoCaso):blocoCaso(blocoCaso){
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
Print::Print(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
ReadLn::ReadLn(Expr expressao){
    this->expressao = expressao;
}
Return::Return(Expr expressao){
    this->expressao = expressao;
}
Escopo::Escopo(ListaSentenca *lista){
    this->lista = lista;
}
ChamadaFuncao::ChamadaFuncao(Id id, ListaExpr *parametros){
    this->id = id;
    this->parametros = parametros;
}
Try::Try(Sentenca sentencaTry, Sentenca sentencaCatch){
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
SentencaExpr::SentencaExpr(Expr expressao){
    this->expressao = expressao;
}
DeclFuncao::DeclFuncao(int tipo, Id id, ListaFormal *parametros, DeclVariavel *variaveis, ListaSentenca sentenca, DeclFuncao *lista):sentenca(sentenca){
    this->tipo = tipo;
    this->id = id;
    this->parametros = parametros;
    this->variaveis = variaveis;
    this->sentenca = sentenca;
    this->lista = lista;
}
ListaId::ListaId(ListaId *lista, bool ponteiro, Arranjo *arranjo){
    this->lista = lista;
    this->ponteiro = ponteiro;
    this->arranjo = arranjo;
}
DeclVariavel::DeclVariavel(int tipo, ListaId variaveis, DeclVariavel *lista):variaveis(variaveis){
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
DeclTipo::DeclTipo(DeclVariavel *campo){
    this->campo = campo;
}
DeclLocalFuncao::DeclLocalFuncao(DeclFuncao funcao, DeclLocal *lista):funcao(funcao){
    this->funcao = funcao;
    this->lista = lista;
}
DeclLocalVariavel::DeclLocalVariavel(DeclVariavel variavel, DeclLocal *lista):variavel(variavel){
    this->variavel = variavel;
    this->lista = lista;
}
DeclLocalPublic::DeclLocalPublic(DeclLocal *lista){
    this->lista = lista;
}
DeclLocalPrivate::DeclLocalPrivate(DeclLocal *lista){
    this->lista = lista;
}
DeclClasse::DeclClasse(Id id, Id *heranca, DeclLocal *lista){
    this->id = id;
    this->heranca = heranca;
    this->lista = lista;
}
ExprUnaria::ExprUnaria(int operador, Expr expressao){
    this->operador = operador;
    this->expressao = expressao;
}
ExprBinaria::ExprBinaria(int operador, Expr exprEsquerda, Expr exprDireita){
    this->operador = operador;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
ExprAtrib::ExprAtrib(Expr exprEsquerda, Expr exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
ExprAceCamp::ExprAceCamp(Expr exprEsquerda, Expr exprDireita){
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
New::New(ListaExpr *listaExpr){
    this->listaExpr = listaExpr;
}
TabelaIdentificador* obtemTabelaIdentificador(){return &tabelaID;};
TabelaLiteral* obtemTabelaLiteral(){return &tabelaLiteral;};
TabelaInteiro* obtemTabelaInteiro(){return &tabelaInteiro;};
TabelaReal*    obtemTabelaReal(){return &tabelaReal;};
