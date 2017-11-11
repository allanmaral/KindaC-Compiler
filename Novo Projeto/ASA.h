#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"

class Visitante;

class NoDeclFuncao;
class NoDeclTipo;
class NoDeclVariavel;
class NoDeclClasse;
class NoCorpoFuncao;

class NoErro{
    public:
        int linha;
        int coluna;
};
class NoPrograma:public NoErro{
    public:
        virtual void aceita(Visitante *v) = 0;
        NoPrograma *lista;
        virtual ~NoPrograma() = 0;
};
class NoSentenca:public NoErro{
    public:
        virtual void aceita(Visitante *v) = 0;
};
class NoExpr:public NoSentenca{
    public:
        virtual void aceita(Visitante *v) = 0;
};
class NoPrimario:public NoExpr{
    public:
       virtual void aceita(Visitante *v) = 0;
};
class NoId:public NoPrimario{
    public:
        NoId(Atributo *entradaTabela, int linha, int coluna);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoLiteral:public NoPrimario{
    public:
        NoLiteral(Atributo *entradaTabela,  int linha, int coluna);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoAscii:public NoPrimario{
    public:
        NoAscii(Atributo *entradaTabela, int linha, int coluna);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoParenteses:public NoPrimario{
    public:
        NoParenteses(NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoColchetes:public NoPrimario{
    public:
        NoColchetes(NoPrimario *primario, NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        NoPrimario *primario;
        NoExpr *expressao;
};
class NoConteudo:public NoPrimario{
    public:
        NoConteudo(NoPrimario *primario, int linha, int coluna);
        void aceita(Visitante *v);
        NoPrimario *primario;
};
class NoEndereco:public NoPrimario{
    public:
        NoEndereco(NoPrimario *primario, int linha, int coluna);
        void aceita(Visitante *v);
        NoPrimario *primario;
};
class NoNum:public NoPrimario{
    public:
        virtual void aceita(Visitante *v) = 0;
};
class NoNumInteiro:public NoNum{
    public:
        NoNumInteiro(Atributo *entradaTabela, int linha, int coluna);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoNumReal:public NoNum{
    public:
        NoNumReal(Atributo *entradaTabela, int linha, int coluna);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoArranjo:public NoErro{
    public:
        NoArranjo(NoNum *num, int linha, int coluna);
        void aceita(Visitante *v);
        NoNum *num;
};
class NoListaExpr:public NoErro{
    public:
        NoListaExpr(NoExpr *expressao, NoListaExpr *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoListaExpr *lista;
};
class NoTipo:public NoErro{
    public:
        NoTipo(int primitivo, int linha, int coluna, Atributo *entradaTabela = NULL);
        void aceita(Visitante *v);
        int primitivo;
        Atributo *entradaTabela;
};
class NoListaFormal:public NoErro{
    public:
        NoListaFormal(NoTipo *tipo, bool ponteiro, NoId *id, NoArranjo *arranjo, NoListaFormal *lista,
                      int linha, int coluna);
        void aceita(Visitante *v);
        NoTipo *tipo;
        bool ponteiro;
        NoId *id;
        NoArranjo *arranjo;
        NoListaFormal *lista;
};
class NoListaSentenca:public NoErro{
    public:
        NoListaSentenca(NoSentenca *sentenca, NoListaSentenca *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
        NoListaSentenca *lista;
};
class NoSenao:public NoSentenca{
    public:
        NoSenao(NoSentenca *sentenca, int linha, int coluna);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
};
class NoSe:public NoSentenca{
    public:
        NoSe(NoExpr *expressao, NoSentenca *sentenca, NoSenao *senao, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoSentenca *sentenca;
        NoSenao *senao;
};
class NoEnquanto:public NoSentenca{
    public:
        NoEnquanto(NoExpr *expressao, NoSentenca *sentenca, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoSentenca *sentenca;
};
class NoBlocoCaso:public NoErro{
    public:
        NoBlocoCaso(NoNum *num, NoListaSentenca *listaSentenca, NoBlocoCaso *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoNum *num;
        NoListaSentenca *listaSentenca;
        NoBlocoCaso *lista;
};
class NoEscolha:public NoSentenca{
    public:
        NoEscolha(NoExpr *expressao, NoBlocoCaso *blocoCaso, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoBlocoCaso *blocoCaso;
};
class NoDesvia:public NoSentenca{
    void aceita(Visitante *v);
};
class NoImprime:public NoSentenca{
    public:
        NoImprime(NoListaExpr *listaExpr, int linha, int coluna);
        void aceita(Visitante *v);
        NoListaExpr *listaExpr;
};
class NoLeLinha:public NoSentenca{
    public:
        NoLeLinha(NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoRetorna:public NoSentenca{
    public:
        NoRetorna(NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoLanca:public NoSentenca{
    void aceita(Visitante *v);
};
class NoEscopo:public NoSentenca{
    public:
        NoEscopo(NoListaSentenca *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoListaSentenca *lista;
};
class NoChamadaFuncao:public NoPrimario{
    public:
        NoChamadaFuncao(NoId *id, NoListaExpr *parametros, int linha, int coluna);
        void aceita(Visitante *v);
        NoId *id;
        NoListaExpr *parametros;
};
class NoTenta:public NoSentenca{
    public:
        NoTenta(NoSentenca *sentencaTry, NoSentenca *sentencaCatch, int linha, int coluna);
        void aceita(Visitante *v);
        NoSentenca *sentencaTry;
        NoSentenca *sentencaCatch;
};
class NoSentencaExpr:public NoSentenca{
    public:
        NoSentencaExpr(NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoDeclFuncao:public NoPrograma{
    public:
        NoDeclFuncao(NoTipo* tipo, int ponteiro, NoId *id, NoListaFormal *parametros, NoDeclVariavel *variaveis,
                     NoListaSentenca *sentenca, NoDeclFuncao *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoTipo* tipo;
        int ponteiro;
        NoId *id;
        NoListaFormal *parametros;
        NoDeclVariavel *variaveis;
        NoListaSentenca *sentenca;
        NoCorpoFuncao *corpoFunc;
        TabelaSimbolos variaveisLocais;
};
class NoListaId:public NoErro{
    public:
        NoListaId(bool ponteiro, NoId* id, NoArranjo *arranjo, NoListaId *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoId *id;
        bool ponteiro;
        NoArranjo *arranjo;
        NoListaId *lista;
};
class NoDeclVariavel:public NoPrograma{
    public:
        NoDeclVariavel(NoTipo* tipo, NoListaId *variaveis, int linha, int coluna, NoDeclVariavel *lista = NULL);
        void aceita(Visitante *v);
        NoTipo *tipo;
        NoListaId *variaveis;
};
class NoDeclTipo:public NoPrograma{
    public:
        NoDeclTipo(NoDeclVariavel *campo, NoId* id, int linha, int coluna, NoPrograma* lista = NULL);
        void aceita(Visitante *v);
        NoDeclVariavel *campo;
        NoId* id;
};
class NoDeclLocal:public NoErro{
    public:
        virtual void aceita(Visitante *v)=0;
};
class NoDeclLocalFuncao:public NoDeclLocal{
    public:
        NoDeclLocalFuncao(NoDeclFuncao *funcao, NoDeclLocal *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoDeclFuncao *funcao;
        NoDeclLocal *lista;
};
class NoDeclLocalVariavel:public NoDeclLocal{
    public:
        NoDeclLocalVariavel(NoDeclVariavel *variavel, NoDeclLocal *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoDeclVariavel *variavel;
        NoDeclLocal *lista;
};
class NoDeclLocalPublico:public NoDeclLocal{
    public:
        NoDeclLocalPublico(NoDeclLocal *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoDeclLocalPrivado:public NoDeclLocal{
    public:
        NoDeclLocalPrivado(NoDeclLocal *lista, int linha, int coluna);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoCorpoFuncao:public NoErro{
    public:
        NoCorpoFuncao(NoId *id, NoListaId *listaid, NoListaExpr *listaExpr, int linha, int coluna,
                      NoCorpoFuncao *lista = NULL);
        NoId *id;
        NoListaId *listaid;
        NoListaExpr *listaExpr;
        NoCorpoFuncao *lista;
        void aceita(Visitante* v);
};
class NoDeclClasse:public NoPrograma{
    public:
        NoDeclClasse(NoId *id, NoId *heranca, NoDeclLocal *local, int linha, int coluna,
                     NoDeclClasse *lista = NULL);
        void aceita(Visitante *v);
        NoId *id;
        NoId *heranca;
        NoDeclLocal *local;
};
class NoExprUnaria:public NoExpr{
    public:
        NoExprUnaria(int operador, NoExpr *expressao, int linha, int coluna);
        void aceita(Visitante *v);
        int operador;
        NoExpr *expressao;
};
class NoExprBinaria:public NoExpr{
    public:
        NoExprBinaria(int operador, NoExpr *exprEsquerda, NoExpr *exprDireita, int linha, int coluna);
        void aceita(Visitante *v);
        int operador;
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
};
class NoExprAtrib:public NoExpr{
    public:
        NoExprAtrib(NoExpr* exprEsquerda, NoExpr *exprDireita, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
};
class NoExprAceCamp:public NoExpr{
    public:
        NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita, int terminal, int linha, int coluna);
        void aceita(Visitante *v);
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
        int terminal;
};
class NoVerdadeiro:public NoPrimario{
    void aceita(Visitante *v);
};
class NoFalso:public NoPrimario{
    void aceita(Visitante *v);
};
class NoEsse:public NoPrimario{
    void aceita(Visitante *v);
};
class NoNovo:public NoPrimario{
    public:
        NoNovo(NoId *id, NoListaExpr *listaExpr, int linha, int coluna);
        void aceita(Visitante *v);
        NoId* id;
        NoListaExpr *listaExpr;
};
TabelaIdentificador *obtemTabelaIdentificador();
TabelaInteiro       *obtemTabelaInteiro();
TabelaLiteral       *obtemTabelaLiteral();
TabelaReal          *obtemTabelaReal();
TabelaSimbolos      *obtemTabelaClasses();
TabelaSimbolos      *obtemTabelaFuncoes();
TabelaSimbolos      *obtemTabelaVariaveis();
TabelaSimbolos      *obtemTabelaTipos();

#endif // ASA_H
