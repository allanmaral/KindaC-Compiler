#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"

class Visitante;

class NoDeclFuncao;
class NoDeclTipo;
class NoDeclVariavel;
class NoDeclClasse;


class NoPrograma{
    public:
        NoPrograma(NoDeclClasse *listaClasse, NoDeclFuncao *listaFuncao, NoDeclTipo *listaTipo, NoDeclVariavel *listaVariavel);
        void aceita(Visitante *v);
        NoDeclClasse *listaClasse;
        NoDeclFuncao *listaFuncao;
        NoDeclTipo *listaTipo;
        NoDeclVariavel *listaVariavel;
};
class NoExpr{
public:
    virtual void aceita(Visitante *v) = 0;
};
class NoPrimario:public NoExpr{
public:
   virtual void aceita(Visitante *v) = 0;
};
class NoId:public NoPrimario{
public:
    char* literal;
    void aceita(Visitante *v);
};
class NoLiteral:public NoPrimario{
    public:
        NoLiteral(char *literal);
        void aceita(Visitante *v);
        ~NoLiteral();
        char* literal;
};
class NoAscii:public NoPrimario{
    public:
        NoAscii(char caractere);
        void aceita(Visitante *v);
        char caractere;
};
class NoParenteses:public NoPrimario{
    public:
        NoParenteses(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoConteudo:public NoPrimario{
    public:
        NoConteudo(Primario *primario);
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
        NoNumInteiro(int num);
        void aceita(Visitante *v);
        int num;
};
class NoNumReal:public NoNum{
    public:
        NoNumReal(float num);
        void aceita(Visitante *v);
        float num;
};
class NoArranjo{
    public:
        NoArranjo(NoNumInteiro num);
        void aceita(Visitante *v);
        NumInteiro num;
};
class NoListaExpr{
    public:
        NoListaExpr(NoExpr *expressao, NoListaExpr *lista);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoListaExpr *lista;
};
class NoListaFormal{
    public:
        NoListaFormal(int tipo, bool ponteiro, NoId id, NoArranjo *arranjo, NoListaFormal *lista);
        void aceita(Visitante *v);
        int tipo;
        bool ponteiro;
        NoId id;
        NoArranjo *arranjo;
        NoListaFormal *lista;
};
class NoSentenca{
public:
    virtual void aceita(Visitante *v) =0;
};
class NoListaSentenca{
    public:
        NoListaSentenca(NoSentenca *sentenca, NoListaSentenca *lista);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
        NoListaSentenca *lista;
};
class NoIf:public NoSentenca{
    public:
        NoIf(NoExpr *expressao, NoSentenca *sentenca);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoSentenca *sentenca;
};
class NoElse:public NoSentenca{
    public:
        NoElse(NoSentenca *sentenca);
        void aceita(Visitante *v);
        NoSentenca *sentenca;
};
class NoWhile:public NoSentenca{
    public:
        NoWhile(NoExpr *expressao, NoSentenca *sentenca);
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
class NoSwitch:public NoSentenca{
    public:
        NoSwitch(NoExpr *expressao, NoBlocoCaso blocoCaso);
        void aceita(Visitante *v);
        NoExpr *expressao;
        NoBlocoCaso blocoCaso;
};
class NoBreak:public NoSentenca{
    void aceita(Visitante *v);
};
class NoPrint:public NoSentenca{
    public:
        NoPrint(NoListaExpr *listaExpr);
        void aceita(Visitante *v);
        NoListaExpr *listaExpr;
};
class NoReadLn:public NoSentenca{
    public:
        NoReadLn(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoReturn:public NoSentenca{
    public:
        NoReturn(NoExpr *expressao);
        void aceita(Visitante *v);
        NoExpr *expressao;
};
class NoThrow:public NoSentenca{
    void aceita(NoVisitante *v);
};
class NoEscopo:public NoSentenca{
    public:
        NoEscopo(NoListaSentenca *lista);
        void aceita(Visitante *v);
        NoListaSentenca *lista;
};
class NoChamadaFuncao:public NoSentenca{
    public:
        NoChamadaFuncao(NoId id, NoListaExpr *parametros);
        void aceita(Visitante *v);
        NoId id;
        NoListaExpr *parametros;
};
class NoTry:public NoSentenca{
    public:
        NoTry(NoSentenca *sentencaTry, NoSentenca *sentencaCatch);
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
class NoDeclFuncao{
    public:
        NoDeclFuncao(int tipo, NoId id, NoListaFormal *parametros, NoDeclVariavel *variaveis, NoListaSentenca sentenca, NoDeclFuncao *lista);
        void aceita(Visitante *v);
        int tipo;
        NoId id;
        NoListaFormal *parametros;
        NoDeclVariavel *variaveis;
        NoListaSentenca sentenca;
        NoDeclFuncao *lista;
};
class NoListaId{
    public:
        NoListaId(NoListaId *lista, bool ponteiro, NoArranjo *arranjo);
        void aceita(Visitante *v);
        NoListaId *lista;
        bool ponteiro;
        NoArranjo *arranjo;
};
class NoDeclVariavel{
    public:
        NoDeclVariavel(int tipo, NoListaId variaveis, NoDeclVariavel *lista);
        void aceita(Visitante *v);
        int tipo;
        NoListaId variaveis;
        NoDeclVariavel *lista;
};
class NoDeclTipo{
    public:
        NoDeclTipo(NoDeclVariavel *campo);
        void aceita(Visitante *v);
        NoDeclVariavel *campo;
};
class NoDeclLocal{
    public:
        virtual void aceita(Visitante *v)=0;
};
class NoDeclLocalFuncao:public NoDeclLocal{
    public:
        NoDeclLocalFuncao(NoDeclFuncao funcao, NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclFuncao funcao;
        NoDeclLocal *lista;
};
class NoDeclLocalVariavel:public NoDeclLocal{
    public:
        NoDeclLocalVariavel(NoDeclVariavel variavel, NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclVariavel variavel;
        NoDeclLocal *lista;
};
class NoDeclLocalPublic:public NoDeclLocal{
    public:
        NoDeclLocalPublic(NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoDeclLocalPrivate:public NoDeclLocal{
    public:
        NoDeclLocalPrivate(NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoDeclLocal *lista;
};
class NoDeclClasse{
    public:
        NoDeclClasse(NoId id, NoId *heranca, NoDeclLocal *lista);
        void aceita(Visitante *v);
        NoId id;
        NoId *heranca;
        NoDeclLocal *lista;
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
class NoExprAceCamp:public EExpr{
    public:
        NoExprAceCamp(NoExpr *exprEsquerda, NoExpr *exprDireita);
        void aceita(Visitante *v);
        NoExpr *exprEsquerda;
        NoExpr *exprDireita;
};
class NoTrue:public NoPrimario{
    void aceita(Visitante *v);
};
class NoFalse:public NoPrimario{
    void aceita(Visitante *v);
};
class NoThis:public NoPrimario{
    void aceita(Visitante *v);
};
class NoNew:public NoPrimario{
    public:
        New(NoListaExpr *listaExpr);
        void aceita(Visitante *v);
        NoListaExpr *listaExpr;
};

TabelaIdentificador* obtemTabelaIdentificador();
TabelaInteiro    * obtemTabelaInteiro();
TabelaLiteral  * obtemTabelaLiteral();
TabelaReal   * obtemTabelaReal();

#endif // ASA_H
