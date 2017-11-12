#ifndef VISITANTERI_H
#define VISITANTERI_H
#include "RepresentacaoIntermadiaria.h"
#include "ASA.h"
class VisitanteRI{
      public:
          virtual ~VisitanteRI() { };
          virtual void visita(Fragmento *f)             = 0;
          virtual void visita(Procedimento *p)          = 0;
          virtual void visita(Literal *l)               = 0;
          virtual void visita(Variavel *var)            = 0;

          virtual void visita(Temp *t)                  = 0;
          virtual void visita(ListaTemp *listaTemp)     = 0;
          virtual void visita(Rotulo *r)                = 0;
          virtual void visita(ListaRotulo *listaRotulo) = 0;
          virtual void visita(ListaAcesso *listaAcesso) = 0;
          virtual void visita(QuadroMIPS *quadroMIPS)   = 0;
          virtual void visita(NoQuadro *nq)            = 0;
          virtual void visita(NoRegistrador *nr)        = 0;

          ///Métodos visita para MAQUINA ABSTRATA
          //Visita especializações de Exp
          virtual void visita(CONST *c)        = 0;
          virtual void visita(CONSTF *cf)      = 0;
          virtual void visita(NAME *n)         = 0;
          virtual void visita(TEMP *t)         = 0;
          virtual void visita(BINOP *bop)      = 0;
          virtual void visita(MEM *m)          = 0;
          virtual void visita(CALL *ca)        = 0;
          virtual void visita(ESEQ *es)        = 0;
          //Visita especializações de Stm
          virtual void visita(MOVE *mo)        = 0;
          virtual void visita(EXP *ex)         = 0;
          virtual void visita(JUMP *jp)        = 0;
          virtual void visita(CJUMP *cjp)      = 0;
          virtual void visita(SEQ *se)         = 0;
          virtual void visita(LABEL *l)        = 0;
};
class VisitanteImpressaoRI: public VisitanteRI{
    public:
          VisitanteImpressaoRI(){};
          ~VisitanteImpressaoRI(){};
          void visita(Fragmento *f);
          void visita(Procedimento *p);
          void visita(Literal *l);
          void visita(Variavel *var);

          void visita(Temp *t);
          void visita(ListaTemp *listaTemp);
          void visita(Rotulo *r);
          void visita(ListaRotulo *listaRotulo);
          void visita(ListaAcesso *listaAcesso);
          void visita(QuadroMIPS *quadroMIPS);
          void visita(NoQuadro *nq);
          void visita(NoRegistrador *nr);

          ///Métodos visita para MAQUINA ABSTRATA
          //Visita especializações de Exp
          void visita(CONST *c);
          void visita(CONSTF *cf);
          void visita(NAME *n);
          void visita(TEMP *t);
          void visita(BINOP *bop);
          void visita(MEM *m);
          void visita(CALL *ca);
          void visita(ESEQ *es);
          //Visita especializações de Stm
          void visita(MOVE *mo);
          void visita(EXP *ex);
          void visita(JUMP *jp);
          void visita(CJUMP *cjp);
          void visita(SEQ *se);
          void visita(LABEL *l);
};

class VisitanteTradutorASA{///incompleto
    public:
        Temp *sp;
        Temp *fp;
        Fragmento *fInicial;
        //Frame *frameAtual;

    public:
		virtual ~VisitanteTradutorASA(){};
		virtual void visita(NoPrograma          *prog   ) = 0;
		virtual Exp* visita(NoId                *id     ) = 0;
		virtual Exp* visita(NoLiteral           *lit    ) = 0;
		virtual Exp* visita(NoAscii             *asc    ) = 0;
		virtual Exp* visita(NoParenteses        *pa     ) = 0;
		virtual Exp* visita(NoConteudo          *con    ) = 0;
		virtual Exp* visita(NoEndereco          *ende   ) = 0;
		virtual Exp* visita(NoNumInteiro        *ni     ) = 0;
		virtual Exp* visita(NoNumReal           *nr     ) = 0;
		virtual Exp* visita(NoArranjo           *arr    ) = 0;
		virtual ListaExp* visita(NoListaExpr         *le     ) = 0;
		virtual ListaExp* visita(NoListaFormal       *lf     ) = 0;
		virtual ListaStm* visita(NoListaSentenca     *ls     ) = 0;
		virtual Stm* visita(NoSe                *se     ) = 0;
		virtual Stm* visita(NoSenao             *sen    ) = 0;
		virtual Stm* visita(NoEnquanto          *enq    ) = 0;
		virtual Stm* visita(NoBlocoCaso         *bc     ) = 0;
		virtual Stm* visita(NoDesvia            *des    ) = 0;
		virtual Stm* visita(NoEscolha           *sw     ) = 0;
		virtual Stm* visita(NoImprime           *imp    ) = 0;
		virtual Stm* visita(NoLeLinha           *leL    ) = 0;
		virtual Stm* visita(NoRetorna           *ret    ) = 0;
		virtual Stm* visita(NoLanca             *lan    ) = 0;
		virtual ListaStm* visita(NoEscopo            *esc    ) = 0;
		virtual Exp* visita(NoChamadaFuncao     *cha    ) = 0;
		virtual Stm* visita(NoTenta             *te     ) = 0;
		virtual Exp* visita(NoSentencaExpr      *senE   ) = 0;
		virtual void visita(NoDeclFuncao        *decF   ) = 0;
		virtual ListaExp* visita(NoListaId           *lid    ) = 0;
		virtual ListaAcesso* visita(NoDeclVariavel      *decV   ) = 0;
		virtual void visita(NoDeclTipo          *decT   ) = 0;
		virtual void visita(NoDeclLocalFuncao   *decLF  ) = 0;
		virtual ListaAcesso* visita(NoDeclLocalVariavel *decLV  ) = 0;
		virtual void visita(NoDeclLocalPublico   *decLPub) = 0;
		virtual void visita(NoDeclLocalPrivado  *decLpri) = 0;
		virtual ListaExp* visita(NoCorpoFuncao       *cF     ) = 0;
		virtual void visita(NoDeclClasse        *decC   ) = 0;
		virtual Exp* visita(NoExprUnaria    	*expU   ) = 0;
		virtual Exp* visita(NoExprBinaria       *expB   ) = 0;
		virtual Exp* visita(NoExprAtrib         *atr    ) = 0;
		virtual Exp* visita(NoExprAceCamp       *expAC  ) = 0;
        virtual Exp* visita(NoVerdadeiro        *tr     ) = 0;
        virtual Exp* visita(NoFalso             *fa     ) = 0;
        virtual Exp* visita(NoEsse              *th     ) = 0;
		virtual Exp* visita(NoNovo              *n      ) = 0;
		virtual void visita(NoTipo              *tp     ) = 0;
		virtual Exp* visita(NoColchetes         *nc     ) = 0;
};
#endif // VISITANTERI_H
