#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"
class DeclFuncao;
class DeclTipo;
class DeclVariavel;
class DeclClasse;


class Programa{
    public:
        Programa(DeclClasse *listaClasse, DeclFuncao *listaFuncao, DeclTipo *listaTipo, DeclVariavel *listaVariavel);
        DeclClasse *listaClasse;
        DeclFuncao *listaFuncao;
        DeclTipo *listaTipo;
        DeclVariavel *listaVariavel;
};
class Id{};
class Expr{};
class Primario:public Expr{};
class Literal:public Primario{
    public:
        Literal(char *literal);
        ~Literal();
        char* literal;
};
class Ascii:public Primario{
    public:
        Ascii(char caractere);
        char caractere;
};
class Parenteses:public Primario{
    public:
        Parenteses(Expr expressao);
        Expr expressao;
};
class Conteudo:public Primario{
    public:
        Conteudo(Primario primario);
        Primario primario;
};
class Endereco:public Primario{
    public:
        Endereco(Primario primario);
        Primario primario;
};
class Num:public Primario{};
class NumInteiro:public Num{
    public:
        NumInteiro(int num);
        int num;
};
class NumReal:public Num{
    public:
        NumReal(float num);
        float num;
};
class Arranjo{
    public:
        Arranjo(NumInteiro num);
        NumInteiro num;
};
class ListaExpr{
    public:
        ListaExpr(Expr expressao, ListaExpr *lista);
        Expr expressao;
        ListaExpr *lista;
};
class ListaFormal{
    public:
        ListaFormal(int tipo, bool ponteiro, Id id, Arranjo *arranjo, ListaFormal *lista);
        int tipo;
        bool ponteiro;
        Id id;
        Arranjo *arranjo;
        ListaFormal *lista;
};
class Sentenca{};
class ListaSentenca{
    public:
        ListaSentenca(Sentenca sentenca, ListaSentenca *lista);
        Sentenca sentenca;
        ListaSentenca *lista;
};
class If:public Sentenca{
    public:
        If(Expr expressao, Sentenca sentenca);
        Expr expressao;
        Sentenca sentenca;
};
class Else:public Sentenca{
    public:
        Else(Sentenca sentenca);
        Sentenca sentenca;
};
class While:public Sentenca{
    public:
        While(Expr expressao, Sentenca sentenca);
        Expr expressao;
        Sentenca sentenca;
};
class BlocoCaso{
    public:
        BlocoCaso(Num num, ListaSentenca *listaSentenca, BlocoCaso *lista);
        Num num;
        ListaSentenca *listaSentenca;
        BlocoCaso *lista;
};
class Switch:public Sentenca{
    public:
        Switch(Expr expressao, BlocoCaso blocoCaso);
        Expr expressao;
        BlocoCaso blocoCaso;
};
class Break:public Sentenca{};
class Print:public Sentenca{
    public:
        Print(ListaExpr *listaExpr);
        ListaExpr *listaExpr;
};
class ReadLn:public Sentenca{
    public:
        ReadLn(Expr expressao);
        Expr expressao;
};
class Return:public Sentenca{
    public:
        Return(Expr expressao);
        Expr expressao;
};
class Throw:public Sentenca{};
class Escopo:public Sentenca{
    public:
        Escopo(ListaSentenca *lista);
        ListaSentenca *lista;
};
class ChamadaFuncao:public Sentenca{
    public:
        ChamadaFuncao(Id id, ListaExpr *parametros);
        Id id;
        ListaExpr *parametros;
};
class Try:public Sentenca{
    public:
        Try(Sentenca sentencaTry, Sentenca sentencaCatch);
        Sentenca sentencaTry;
        Sentenca sentencaCatch;
};
class SentencaExpr:public Sentenca{
    public:
        SentencaExpr(Expr expressao);
        Expr expressao;
};
class DeclFuncao{
    public:
        DeclFuncao(int tipo, Id id, ListaFormal *parametros, DeclVariavel *variaveis, ListaSentenca sentenca, DeclFuncao *lista);
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
        ListaId *lista;
        bool ponteiro;
        Arranjo *arranjo;
};
class DeclVariavel{
    public:
        DeclVariavel(int tipo, ListaId variaveis, DeclVariavel *lista);
        int tipo;
        ListaId variaveis;
        DeclVariavel *lista;
};
class DeclTipo{
    public:
        DeclTipo(DeclVariavel *campo);
        DeclVariavel *campo;
};
class DeclLocal{};
class DeclLocalFuncao:public DeclLocal{
    public:
        DeclLocalFuncao(DeclFuncao funcao, DeclLocal *lista);
        DeclFuncao funcao;
        DeclLocal *lista;
};
class DeclLocalVariavel:public DeclLocal{
    public:
        DeclLocalVariavel(DeclVariavel variavel, DeclLocal *lista);
        DeclVariavel variavel;
        DeclLocal *lista;
};
class DeclLocalPublic:public DeclLocal{
    public:
        DeclLocalPublic(DeclLocal *lista);
        DeclLocal *lista;
};
class DeclLocalPrivate:public DeclLocal{
    public:
        DeclLocalPrivate(DeclLocal *lista);
        DeclLocal *lista;
};
class DeclClasse{
    public:
        DeclClasse(Id id, Id *heranca, DeclLocal *lista);
        Id id;
        Id *heranca;
        DeclLocal *lista;
};
class ExprUnaria:public Expr{
    public:
        ExprUnaria(int operador, Expr expressao);
        int operador;
        Expr expressao;
};
class ExprBinaria:public Expr{
    public:
        ExprBinaria(int operador, Expr exprEsquerda, Expr exprDireita);
        int operador;
        Expr exprEsquerda;
        Expr exprDireita;
};
class ExprAtrib:public Expr{
    public:
        ExprAtrib(Expr exprEsquerda, Expr exprDireita);
        Expr exprEsquerda;
        Expr exprDireita;
};
class ExprAceCamp:public Expr{
    public:
        ExprAceCamp(Expr exprEsquerda, Expr exprDireita);
        Expr exprEsquerda;
        Expr exprDireita;
};
class True:public Primario{};
class False:public Primario{};
class This:public Primario{};
class New:public Primario{
    public:
        New(ListaExpr *listaExpr);
        ListaExpr *listaExpr;
};

TabelaIdentificador* obtemTabelaIdentificador();
TabelaInteiro    * obtemTabelaInteiro();
TabelaLiteral  * obtemTabelaLiteral();
TabelaReal   * obtemTabelaReal();

#endif // ASA_H
