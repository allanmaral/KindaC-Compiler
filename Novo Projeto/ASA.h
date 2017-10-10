#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"

class Visitante;

class DeclFuncao;
class DeclTipo;
class DeclVariavel;
class DeclClasse;


class NoPrograma{
    public:
        NoPrograma(DeclClasse *listaClasse, DeclFuncao *listaFuncao, DeclTipo *listaTipo, DeclVariavel *listaVariavel);
        void aceita(Visitante *v);
        DeclClasse *listaClasse;
        DeclFuncao *listaFuncao;
        DeclTipo *listaTipo;
        DeclVariavel *listaVariavel;
};
class Id{
public:
    char* literal;
    void aceita(Visitante *v);
};
class Expr{
public:
    virtual void aceita(Visitante *v) = 0;
};
class Primario:public Expr{
public:
   virtual void aceita(Visitante *v) = 0;
};
class Literal:public Primario{
    public:
        Literal(char *literal);
        void aceita(Visitante *v);
        ~Literal();
        char* literal;
};
class Ascii:public Primario{
    public:
        Ascii(char caractere);
        void aceita(Visitante *v);
        char caractere;
};
class Parenteses:public Primario{
    public:
        Parenteses(Expr *expressao);
        void aceita(Visitante *v);
        Expr *expressao;
};
class Conteudo:public Primario{
    public:
        Conteudo(Primario *primario);
        void aceita(Visitante *v);
        Primario *primario;
};
class Endereco:public Primario{
    public:
        Endereco(Primario *primario);
        void aceita(Visitante *v);
        Primario *primario;
};
class Num:public Primario{
public:
    virtual void aceita(Visitante *v) = 0;
};
class NumInteiro:public Num{
    public:
        NumInteiro(int num);
        void aceita(Visitante *v);
        int num;
};
class NumReal:public Num{
    public:
        NumReal(float num);
        void aceita(Visitante *v);
        float num;
};
class Arranjo{
    public:
        Arranjo(NumInteiro num);
        void aceita(Visitante *v);
        NumInteiro num;
};
class ListaExpr{
    public:
        ListaExpr(Expr *expressao, ListaExpr *lista);
        void aceita(Visitante *v);
        Expr *expressao;
        ListaExpr *lista;
};
class ListaFormal{
    public:
        ListaFormal(int tipo, bool ponteiro, Id id, Arranjo *arranjo, ListaFormal *lista);
        void aceita(Visitante *v);
        int tipo;
        bool ponteiro;
        Id id;
        Arranjo *arranjo;
        ListaFormal *lista;
};
class Sentenca{
public:
    virtual void aceita(Visitante *v) =0;
};
class ListaSentenca{
    public:
        ListaSentenca(Sentenca *sentenca, ListaSentenca *lista);
        void aceita(Visitante *v);
        Sentenca *sentenca;
        ListaSentenca *lista;
};
class If:public Sentenca{
    public:
        If(Expr *expressao, Sentenca *sentenca);
        void aceita(Visitante *v);
        Expr *expressao;
        Sentenca *sentenca;
};
class Else:public Sentenca{
    public:
        Else(Sentenca *sentenca);
        void aceita(Visitante *v);
        Sentenca *sentenca;
};
class While:public Sentenca{
    public:
        While(Expr *expressao, Sentenca *sentenca);
        void aceita(Visitante *v);
        Expr *expressao;
        Sentenca *sentenca;
};
class BlocoCaso{
    public:
        BlocoCaso(Num *num, ListaSentenca *listaSentenca, BlocoCaso *lista);
        void aceita(Visitante *v);
        Num *num;
        ListaSentenca *listaSentenca;
        BlocoCaso *lista;
};
class Switch:public Sentenca{
    public:
        Switch(Expr *expressao, BlocoCaso blocoCaso);
        void aceita(Visitante *v);
        Expr *expressao;
        BlocoCaso blocoCaso;
};
class Break:public Sentenca{
    void aceita(Visitante *v);
};
class Print:public Sentenca{
    public:
        Print(ListaExpr *listaExpr);
        void aceita(Visitante *v);
        ListaExpr *listaExpr;
};
class ReadLn:public Sentenca{
    public:
        ReadLn(Expr *expressao);
        void aceita(Visitante *v);
        Expr *expressao;
};
class Return:public Sentenca{
    public:
        Return(Expr *expressao);
        void aceita(Visitante *v);
        Expr *expressao;
};
class Throw:public Sentenca{
    void aceita(Visitante *v);
};
class Escopo:public Sentenca{
    public:
        Escopo(ListaSentenca *lista);
        void aceita(Visitante *v);
        ListaSentenca *lista;
};
class ChamadaFuncao:public Sentenca{
    public:
        ChamadaFuncao(Id id, ListaExpr *parametros);
        void aceita(Visitante *v);
        Id id;
        ListaExpr *parametros;
};
class Try:public Sentenca{
    public:
        Try(Sentenca *sentencaTry, Sentenca *sentencaCatch);
        void aceita(Visitante *v);
        Sentenca *sentencaTry;
        Sentenca *sentencaCatch;
};
class SentencaExpr:public Sentenca{
    public:
        SentencaExpr(Expr *expressao);
        void aceita(Visitante *v);
        Expr *expressao;
};
class DeclFuncao{
    public:
        DeclFuncao(int tipo, Id id, ListaFormal *parametros, DeclVariavel *variaveis, ListaSentenca sentenca, DeclFuncao *lista);
        void aceita(Visitante *v);
        int tipo;
        Id id;
        ListaFormal *parametros;
        DeclVariavel *variaveis;
        ListaSentenca sentenca;
        DeclFuncao *lista;
};
class ListaId{
    public:
        ListaId(ListaId *lista, bool ponteiro, Arranjo *arranjo);
        void aceita(Visitante *v);
        ListaId *lista;
        bool ponteiro;
        Arranjo *arranjo;
};
class DeclVariavel{
    public:
        DeclVariavel(int tipo, ListaId variaveis, DeclVariavel *lista);
        void aceita(Visitante *v);
        int tipo;
        ListaId variaveis;
        DeclVariavel *lista;
};
class DeclTipo{
    public:
        DeclTipo(DeclVariavel *campo);
        void aceita(Visitante *v);
        DeclVariavel *campo;
};
class DeclLocal{
public:
    virtual void aceita(Visitante *v)=0;
};
class DeclLocalFuncao:public DeclLocal{
    public:
        DeclLocalFuncao(DeclFuncao funcao, DeclLocal *lista);
        void aceita(Visitante *v);
        DeclFuncao funcao;
        DeclLocal *lista;
};
class DeclLocalVariavel:public DeclLocal{
    public:
        DeclLocalVariavel(DeclVariavel variavel, DeclLocal *lista);
        void aceita(Visitante *v);
        DeclVariavel variavel;
        DeclLocal *lista;
};
class DeclLocalPublic:public DeclLocal{
    public:
        DeclLocalPublic(DeclLocal *lista);
        void aceita(Visitante *v);
        DeclLocal *lista;
};
class DeclLocalPrivate:public DeclLocal{
    public:
        DeclLocalPrivate(DeclLocal *lista);
        void aceita(Visitante *v);
        DeclLocal *lista;
};
class DeclClasse{
    public:
        DeclClasse(Id id, Id *heranca, DeclLocal *lista);
        void aceita(Visitante *v);
        Id id;
        Id *heranca;
        DeclLocal *lista;
};
class ExprUnaria:public Expr{
    public:
        ExprUnaria(int operador, Expr *expressao);
        void aceita(Visitante *v);
        int operador;
        Expr *expressao;
};
class ExprBinaria:public Expr{
    public:
        ExprBinaria(int operador, Expr *exprEsquerda, Expr *exprDireita);
        void aceita(Visitante *v);
        int operador;
        Expr *exprEsquerda;
        Expr *exprDireita;
};
class ExprAtrib:public Expr{
    public:
        ExprAtrib(Expr* exprEsquerda, Expr *exprDireita);
        void aceita(Visitante *v);
        Expr *exprEsquerda;
        Expr *exprDireita;
};
class ExprAceCamp:public Expr{
    public:
        ExprAceCamp(Expr *exprEsquerda, Expr *exprDireita);
        void aceita(Visitante *v);
        Expr *exprEsquerda;
        Expr *exprDireita;
};
class True:public Primario{
    void aceita(Visitante *v);
};
class False:public Primario{
    void aceita(Visitante *v);
};
class This:public Primario{
    void aceita(Visitante *v);
};
class New:public Primario{
    public:
        New(ListaExpr *listaExpr);
        void aceita(Visitante *v);
        ListaExpr *listaExpr;
};

TabelaIdentificador* obtemTabelaIdentificador();
TabelaInteiro    * obtemTabelaInteiro();
TabelaLiteral  * obtemTabelaLiteral();
TabelaReal   * obtemTabelaReal();

#endif // ASA_H
