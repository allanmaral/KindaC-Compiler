#ifndef ASA_H
#define ASA_H
#include "TabelaSimbolos.h"
class DeclFuncao;
class DeclTipo;
class DeclVariavel;
class DeclClasse;


class Programa{
    public:
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
        char* literal;
};
class ASCII:public Primario{
    public:
        char caractere;
};
class Parenteses:public Primario{
    public:
        Expr expressao;
};
class Conteudo:public Primario{
    public:
        Primario primario;
};
class Entereco:public Primario{
    public:
        Primario primario;
};
class Num:public Primario{};
class NumInteiro:public Num{
    public:
        int num;
};
class NumReal:public Num{
    public:
        float num;
};
class Arranjo{
    NumInteiro num;
};
class ListaExpr{
    public:
        Expr expressao;
        ListaExpr *lista;
};
class ListaFormal{
    public:
        int tipo;
        bool ponteiro;
        Id id;
        Arranjo *arranjo;
        ListaFormal *lista;
};
class Sentenca{};
class ListaSentenca{
    public:
        Sentenca sentenca;
        ListaSentenca *lista;
};
class If:public Sentenca{
    public:
        Expr expressao;
        Sentenca sentenca;
};
class Else:public Sentenca{
    public:
        Sentenca sentenca;
};
class While:public Sentenca{
    public:
        Expr expressao;
        Sentenca sentenca;
};
class BlocoCaso{
    public:
        Num num;
        ListaSentenca *listaSentenca;
        BlocoCaso *lista;
};
class Switch:public Sentenca{
    public:
        Expr expressao;
        BlocoCaso blocoCaso;
};
class Break:public Sentenca{};
class Print:public Sentenca{
    public:
        ListaExpr *listaExpr;
};
class ReadLn:public Sentenca{
    public:
        Expr expressao;
};
class Return:public Sentenca{
    public:
        Expr expressao;
};
class Throw:public Sentenca{};
class Escopo:public Sentenca{
    public:
        ListaSentenca *lista;
};
class ChamadaFuncao:public Sentenca{
    public:
        Id id;
        ListaExpr *parametros;
};
class Try:public Sentenca{
    public:
        Sentenca sentencaTry;
        Sentenca sentencaCatch;
};
class SentencaExpr:public Sentenca{
    public:
        Expr expressao;
};
class DeclFuncao{
    public:
        int tipo;
        Id id;
        ListaFormal *parametros;
        DeclVariavel *variaveis;
        ListaSentenca sentenca;
        DeclFuncao *funcao;
};
class ListaId{
    public:
        ListaId *listaId;
        bool ponteiro;
        Arranjo *arranjo;
};
class DeclVariavel{
    public:
        int tipo;
        ListaId variaveis;
        DeclVariavel *listaVariaveis;
};
class DeclTipo{
    public:
        DeclVariavel *campo;
};
class DeclLocal{};
class DeclLocalFuncao:public DeclLocal{
    public:
        DeclFuncao funcao;
        DeclLocal *lista;
};
class DeclLocalVariavel:public DeclLocal{
    public:
        DeclVariavel variavel;
        DeclLocal *lista;
};
class DeclLocalPublic:public DeclLocal{
    public:
        DeclLocal *lista;
};
class DeclLocalPrivate:public DeclLocal{
    public:
        DeclLocal *lista;
};
class DeclClasse{
    public:
        Id id;
        Id *heranca;
        DeclLocal lista;
};
class ExprUnaria:public Expr{
    public:
        int operador;
        Expr expressao;
};
class ExprBinaria:public Expr{
    public:
        int operador;
        Expr exprEsquerda;
        Expr exprDireita;
};
class ExprAtrib:public Expr{
    public:
        Expr exprEsquerda;
        Expr exprDireita;
};
class ExprAceCamp:public Expr{
    public:
        Expr exprEsquerda;
        Expr exprDireita;
};
class True:public Primario{};
class False:public Primario{};
class This:public Primario{};
class New:public Primario{
    public:
        ListaExpr *listaExpr;
};

TabelaIdentificador* obtemTabelaIdentificador();
TabelaInteiro    * obtemTabelaInteiro();
TabelaLiteral  * obtemTabelaLiteral();
TabelaReal   * obtemTabelaReal();

#endif // ASA_H
