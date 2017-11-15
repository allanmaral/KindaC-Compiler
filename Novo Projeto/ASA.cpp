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

NoPrograma::~NoPrograma(){

}
void NoId::aceita(Visitante *v){
    v->visita(this);
}
NoId::NoId(Atributo *entradaTabela, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->entradaTabela = entradaTabela;
}
NoLiteral::NoLiteral(Atributo *entradaTabela, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->entradaTabela = entradaTabela;
}
void NoLiteral::aceita(Visitante *v){
    v->visita(this);
}
NoAscii::NoAscii(Atributo *entradaTabela, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->entradaTabela = entradaTabela;
}
void NoAscii::aceita(Visitante *v){
    v->visita(this);
}
NoParenteses::NoParenteses(NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
}
void NoParenteses::aceita(Visitante *v){
    v->visita(this);
}
NoConteudo::NoConteudo(NoPrimario *primario, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->primario = primario;
}
void NoConteudo::aceita(Visitante *v){
    v->visita(this);
}
NoEndereco::NoEndereco(NoPrimario *primario, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->primario = primario;
}
void NoEndereco::aceita(Visitante *v){
    v->visita(this);
}
NoNumInteiro::NoNumInteiro(Atributo *entradaTabela, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->entradaTabela = entradaTabela;
}
void NoNumInteiro::aceita(Visitante *v){
    v->visita(this);
}
NoNumReal::NoNumReal(Atributo *entradaTabela, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->entradaTabela = entradaTabela;
}
void NoNumReal::aceita(Visitante *v){
    v->visita(this);
}
NoArranjo::NoArranjo(NoNum *num, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->num = num;
}
void NoArranjo::aceita(Visitante *v){
    v->visita(this);
}
NoListaExpr::NoListaExpr(NoExpr *expressao, NoListaExpr *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
    this->lista = lista;
}
void NoListaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoListaFormal::NoListaFormal(NoTipo *tipo, bool ponteiro, NoId *id, NoArranjo *arranjo, NoListaFormal *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->tipo = tipo;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void NoListaFormal::aceita(Visitante *v){
    v->visita(this);
}
NoListaSentenca::NoListaSentenca(NoSentenca *sentenca, NoListaSentenca *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->sentenca = sentenca;
    this->lista = lista;
}
void NoListaSentenca::aceita(Visitante *v){
    v->visita(this);
}
NoSe::NoSe(NoExpr *expressao, NoSentenca *sentenca, NoSenao *senao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
    this->sentenca = sentenca;
    this->senao = senao;
}
void NoSe::aceita(Visitante *v){
    v->visita(this);
}
NoSenao::NoSenao(NoSentenca *sentenca, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->sentenca = sentenca;
}
void NoSenao::aceita(Visitante *v){
    v->visita(this);
}
NoEnquanto::NoEnquanto(NoExpr *expressao, NoSentenca *sentenca, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
    this->sentenca = sentenca;
}
void NoEnquanto::aceita(Visitante *v){
    v->visita(this);
}
NoBlocoCaso::NoBlocoCaso(NoNum *num, NoListaSentenca *listaSentenca, NoBlocoCaso *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->num = num;
    this->listaSentenca = listaSentenca;
    this->lista = lista;
}
void NoBlocoCaso::aceita(Visitante *v){
    v->visita(this);
}
NoEscolha::NoEscolha(NoExpr *expressao, NoBlocoCaso *blocoCaso, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
    this->blocoCaso = blocoCaso;
}
void NoEscolha::aceita(Visitante *v){
    v->visita(this);
}
void NoDesvia::aceita(Visitante *v){
    v->visita(this);
}
NoImprime::NoImprime(NoListaExpr *listaExpr, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->listaExpr = listaExpr;
}
void NoImprime::aceita(Visitante *v){
    v->visita(this);
}
NoLeLinha::NoLeLinha(NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
}
void NoLeLinha::aceita(Visitante *v){
    v->visita(this);
}
NoRetorna::NoRetorna(NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
}
void NoRetorna::aceita(Visitante *v){
    v->visita(this);
}
void NoLanca::aceita(Visitante *v){
    v->visita(this);
}
NoEscopo::NoEscopo(NoListaSentenca *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->lista = lista;
}
void NoEscopo::aceita(Visitante *v){
    v->visita(this);
}
NoChamadaFuncao::NoChamadaFuncao(NoId *id, NoListaExpr *parametros, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->id = id;
    this->parametros = parametros;
}
void NoChamadaFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoTenta::NoTenta(NoSentenca *sentencaTry, NoSentenca *sentencaCatch, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->sentencaTry = sentencaTry;
    this->sentencaCatch = sentencaCatch;
}
void NoTenta::aceita(Visitante *v){
    v->visita(this);
}
NoSentencaExpr::NoSentencaExpr(NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->expressao = expressao;
}
void NoSentencaExpr::aceita(Visitante *v){
    v->visita(this);
}
NoDeclFuncao::NoDeclFuncao(NoTipo* tipo, bool ponteiro, NoId *id, NoListaFormal *parametros,
                           NoDeclVariavel *variaveis, NoListaSentenca *sentenca, NoDeclFuncao *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
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
NoListaId::NoListaId(bool ponteiro, NoId* id, NoArranjo *arranjo, NoListaId *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->ponteiro = ponteiro;
    this->id = id;
    this->arranjo = arranjo;
    this->lista = lista;
}
void NoListaId::aceita(Visitante *v){
    v->visita(this);
}
NoDeclVariavel::NoDeclVariavel(NoTipo *tipo, NoListaId *variaveis, int linha, int coluna, NoDeclVariavel *lista){
    this->linha = linha;
    this->coluna = coluna;
    this->tipo = tipo;
    this->variaveis = variaveis;
    this->lista = lista;
}
void NoDeclVariavel::aceita(Visitante *v){
    v->visita(this);
}
NoDeclTipo::NoDeclTipo(NoDeclVariavel *campo, NoId *id, int linha, int coluna, NoPrograma *lista){
    this->linha = linha;
    this->coluna = coluna;
    this->campo = campo;
    this->id = id;
    this->lista = lista;
}
void NoDeclTipo::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalFuncao::NoDeclLocalFuncao(NoDeclFuncao *funcao, NoDeclLocal *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->funcao = funcao;
    this->lista = lista;
}
void NoDeclLocalFuncao::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalVariavel::NoDeclLocalVariavel(NoDeclVariavel *variavel, NoDeclLocal *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->variavel = variavel;
    this->lista = lista;
}
void NoDeclLocalVariavel::aceita(Visitante *v){
    v->visita(this);
}

NoDeclLocalPublico::NoDeclLocalPublico(NoDeclLocal *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->lista = lista;
}
void NoDeclLocalPublico::aceita(Visitante *v){
    v->visita(this);
}
NoDeclLocalPrivado::NoDeclLocalPrivado(NoDeclLocal *lista, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->lista = lista;
}
void NoDeclLocalPrivado::aceita(Visitante *v){
    v->visita(this);
}
NoCorpoFuncao::NoCorpoFuncao(NoId *id, NoListaId *listaid, NoListaExpr *listaExpr, int linha, int coluna, NoCorpoFuncao *lista){
    this->linha = linha;
    this->coluna = coluna;
    this->listaExpr = listaExpr;
    this->lista = lista;
    this->id = id;
    this->listaid = listaid;
}
void NoCorpoFuncao::aceita(Visitante* v){
    v->visita(this);
}
NoDeclClasse::NoDeclClasse(NoId *id, NoId *heranca, NoDeclLocal *local, int linha, int coluna, NoDeclClasse *lista){
    this->linha = linha;
    this->coluna = coluna;
    this->id = id;
    this->heranca = heranca;
    this->local = local;
    this->lista = lista;
}
void NoDeclClasse::aceita(Visitante *v){
    v->visita(this);
}
NoExprUnaria::NoExprUnaria(int operador, NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->operador = operador;
    this->expressao = expressao;
}
void NoExprUnaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprBinaria::NoExprBinaria(int operador, NoExpr *exprEsquerda, NoExpr *exprDireita, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->operador = operador;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprBinaria::aceita(Visitante *v){
    v->visita(this);
}
NoExprAtrib::NoExprAtrib(NoExpr *exprEsquerda, NoExpr *exprDireita, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
}
void NoExprAtrib::aceita(Visitante *v){
    v->visita(this);
}
NoExprAceCamp::NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita, int terminal, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
    this->exprEsquerda = exprEsquerda;
    this->exprDireita = exprDireita;
    this->terminal = terminal;
}
void NoExprAceCamp::aceita(Visitante *v){
    v->visita(this);
}
NoNovo::NoNovo(NoId* id, NoListaExpr *listaExpr, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
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
NoTipo::NoTipo(int primitivo, int linha, int coluna, Atributo *entradaTabela){
    this->linha = linha;
    this->coluna = coluna;
    this->primitivo = primitivo;
    this->entradaTabela = entradaTabela;
}
void NoTipo::aceita(Visitante *v){
    v->visita(this);
}
NoColchetes::NoColchetes(NoPrimario *primario, NoExpr *expressao, int linha, int coluna){
    this->linha = linha;
    this->coluna = coluna;
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
TabelaSimbolos* obtemTabelaClasses(){
    return &tabelaClasses;
}
TabelaSimbolos* obtemTabelaFuncoes(){
    return &tabelaFuncoes;
}
TabelaSimbolos* obtemTabelaVariaveis(){
    return &tabelaVariaveis;
}
TabelaSimbolos* obtemTabelaTipos(){
    return &tabelaTipos;
}
