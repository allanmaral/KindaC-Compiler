#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"

class Visitante;

class NoDeclFuncao;
class NoDeclTipo;
class NoDeclVariavel;
class NoDeclClasse;
class NoCorpoFuncao;

class NoPrograma{
    public:
        virtual void aceita(Visitante *v) = 0;
        NoPrograma *lista;
        virtual ~NoPrograma() = 0;
};
class NoSentenca{
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
        NoId(Atributo *entradaTabela);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoLiteral:public NoPrimario{
    public:
        NoLiteral(Atributo *entradaTabela);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoAscii:public NoPrimario{
    public:
        NoAscii(Atributo *entradaTabela);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoParenteses:public NoPrimario{
    public:
        NoParenteses(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoColchetes:public NoPrimario{
    public:
        NoColchetes(NoPrimario *primario, NoExpr *expressao);
        void aceita(Visitante *v);
        NoPrimario *primario;
        NoExpr *expressao;
};
class NoConteudo:public NoPrimario{
    public:
        NoConteudo(NoPrimario *primario);
        void aceita(Visitante *v);
        NoPrimario *primario;
};
class NoEndereco:public NoPrimario{
    public:
        NoEndereco(NoPrimario *primario);
        void aceita(Visitante *v);
        NoPrimario *primario;
};
class NoNum:public NoPrimario{
    public:
        virtual void aceita(Visitante *v) = 0;
};
class NoNumInteiro:public NoNum{
    public:
        NoNumInteiro(Atributo *entradaTabela);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoNumReal:public NoNum{
    public:
        NoNumReal(Atributo *entradaTabela);
        void aceita(Visitante *v);
        Atributo *entradaTabela;
};
class NoArranjo{
    public:
        NoArranjo(NoNum *num);
        void aceita(Visitante *v);
        NoNum *num;
};
class NoListaExpr{
    public:
        NoListaExpr(NoExpr *expressao, NoListaExpr *lista);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoListaExpr *lista;
};
class NoTipo{
    public:
        NoTipo(int primitivo, Atributo *entradaTabela = NULL);
        void aceita(Visitante *v);
        int primitivo;
        Atributo *entradaTabela;
};
class NoListaFormal{
    public:
        NoListaFormal(NoTipo *tipo, bool ponteiro, NoId *id, NoArranjo *arranjo, NoListaFormal *lista);
        void aceita(Visitante *v);
        NoTipo *tipo;
        bool ponteiro;
        NoId *id;
        NoArranjo *arranjo;
        NoListaFormal *lista;
};
class NoListaSentenca{
    public:
        NoListaSentenca(NoSentenca *sentenca, NoListaSentenca *lista);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
        NoListaSentenca *lista;
};
class NoSenao:public NoSentenca{
    public:
        NoSenao(NoSentenca *sentenca);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
};
class NoSe:public NoSentenca{
    public:
        NoSe(NoExpr *expressao, NoSentenca *sentenca, NoSenao *senao);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoSentenca *sentenca;
        NoSenao *senao;
};
class NoEnquanto:public NoSentenca{
    public:
        NoEnquanto(NoExpr *expressao, NoSentenca *sentenca);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoSentenca *sentenca;
};
class NoBlocoCaso{
    public:
        NoBlocoCaso(NoNum *num, NoListaSentenca *listaSentenca, NoBlocoCaso *lista);
        void aceita(Visitante *v);
        NoNum *num;
        NoListaSentenca *listaSentenca;
        NoBlocoCaso *lista;
};
class NoEscolha:public NoSentenca{
    public:
        NoEscolha(NoExpr *expressao, NoBlocoCaso *blocoCaso);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoBlocoCaso *blocoCaso;
};
class NoDesvia:public NoSentenca{
    void aceita(Visitante *v);
};
class NoImprime:public NoSentenca{
    public:
        NoImprime(NoListaExpr *listaExpr);
        void aceita(Visitante *v);
        NoListaExpr *listaExpr;
};
class NoLeLinha:public NoSentenca{
    public:
        NoLeLinha(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoRetorna:public NoSentenca{
    public:
        NoRetorna(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoLanca:public NoSentenca{
    void aceita(Visitante *v);
};
class NoEscopo:public NoSentenca{
    public:
        NoEscopo(NoListaSentenca *lista);
        void aceita(Visitante *v);
        NoListaSentenca *lista;
};
class NoChamadaFuncao:public NoPrimario{
    public:
        NoChamadaFuncao(NoId *id, NoListaExpr *parametros);
        void aceita(Visitante *v);
        NoId *id;
        NoListaExpr *parametros;
};
class NoTenta:public NoSentenca{
    public:
        NoTenta(NoSentenca *sentencaTry, NoSentenca *sentencaCatch);
        void aceita(Visitante *v);
        NoSentenca *sentencaTry;
        NoSentenca *sentencaCatch;
};
class NoSentencaExpr:public NoSentenca{
    public:
        NoSentencaExpr(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoDeclFuncao:public NoPrograma{
    public:
        NoDeclFuncao(NoTipo* tipo, int ponteiro, NoId *id, NoListaFormal *parametros, NoDeclVariavel *variaveis,
                     NoListaSentenca *sentenca, NoDeclFuncao *lista);
        void aceita(Visitante *v);
        NoTipo* tipo;
        int ponteiro;
        NoId *id;
        NoListaFormal *parametros;
        NoDeclVariavel *variaveis;
        NoListaSentenca *sentenca;
        NoCorpoFuncao   *corpoFunc;
        TabelaSimbolos variaveisLocais;
};
class NoListaId{
    public:
        NoListaId(bool ponteiro, NoId* id, NoArranjo *arranjo, NoListaId *lista);
        void aceita(Visitante *v);
        NoId *id;
        bool ponteiro;
        NoArranjo *arranjo;
        NoListaId *lista;
};
class NoDeclVariavel:public NoPrograma{
    public:
        NoDeclVariavel(NoTipo* tipo, NoListaId *variaveis, NoDeclVariavel *lista = NULL);
        void aceita(Visitante *v);
        NoTipo *tipo;
        NoListaId *variaveis;
};
class NoDeclTipo:public NoPrograma{
    public:
        NoDeclTipo(NoDeclVariavel *campo, NoId* id, NoPrograma* lista = NULL);
        void aceita(Visitante *v);
        NoDeclVariavel *campo;
        NoId* id;
};
class NoDeclLocal{
    public:
        virtual void aceita(Visitante *v)=0;
};
class NoDeclLocalFuncao:public NoDeclLocal{
    public:
        NoDeclLocalFuncao(NoDeclFuncao *funcao, NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclFuncao *funcao;
        NoDeclLocal *lista;
};
class NoDeclLocalVariavel:public NoDeclLocal{
    public:
        NoDeclLocalVariavel(NoDeclVariavel *variavel, NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclVariavel *variavel;
        NoDeclLocal *lista;
};
class NoDeclLocalPublico:public NoDeclLocal{
    public:
        NoDeclLocalPublico(NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoDeclLocalPrivado:public NoDeclLocal{
    public:
        NoDeclLocalPrivado(NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoCorpoFuncao{
    public:
        NoCorpoFuncao(NoId *id, NoListaId *listaid, NoListaExpr *listaExpr, NoCorpoFuncao *lista = NULL);
        NoId *id;
        NoListaId *listaid;
        NoListaExpr *listaExpr;
        NoCorpoFuncao *lista;
        void aceita(Visitante* v);
};
class NoDeclClasse:public NoPrograma{
    public:
        NoDeclClasse(NoId *id, NoId *heranca, NoDeclLocal *local, NoDeclClasse *lista = NULL);
        void aceita(Visitante *v);
        NoId *id;
        NoId *heranca;
        NoDeclLocal *local;
};
class NoExprUnaria:public NoExpr{
    public:
        NoExprUnaria(int operador, NoExpr *expressao);
        void aceita(Visitante *v);
        int operador;
        NoExpr *expressao;
};
class NoExprBinaria:public NoExpr{
    public:
        NoExprBinaria(int operador, NoExpr *exprEsquerda, NoExpr *exprDireita);
        void aceita(Visitante *v);
        int operador;
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
};
class NoExprAtrib:public NoExpr{
    public:
        NoExprAtrib(NoExpr* exprEsquerda, NoExpr *exprDireita);
        void aceita(Visitante *v);
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
};
class NoExprAceCamp:public NoExpr{
    public:
        NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita, int terminal);
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
        NoNovo(NoId *id, NoListaExpr *listaExpr);
        void aceita(Visitante *v);
        NoId* id;
        NoListaExpr *listaExpr;
};
TabelaIdentificador* obtemTabelaIdentificador();
TabelaInteiro    * obtemTabelaInteiro();
TabelaLiteral  * obtemTabelaLiteral();
TabelaReal   * obtemTabelaReal();
TabelaSimbolos *obtemTabelaClasses();
TabelaSimbolos *obtemTabelaFuncoes();
TabelaSimbolos *obtemTabelaVariaveis();
TabelaSimbolos *obtemTabelaTipos();

#endif // ASA_H
