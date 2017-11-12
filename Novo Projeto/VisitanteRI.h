#ifndef VISITANTERI_H
#define VISITANTERI_H
#include "RepresentacaoIntermadiaria.h"
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
          virtual void visita(FrameMIPS *quadroMIPS)   = 0;
          virtual void visita(NoFrame *nq)            = 0;
          virtual void visita(NoRegistrador *nr)        = 0;

          ///Métodos visita para MAQUINA ABSTRATA
          //Visita especializações de Exp
          virtual void visita(ListaExp *lex)   = 0;
          virtual void visita(CONST *c)        = 0;
          virtual void visita(CONSTF *cf)      = 0;
          virtual void visita(NAME *n)         = 0;
          virtual void visita(TEMP *t)         = 0;
          virtual void visita(BINOP *bop)      = 0;
          virtual void visita(MEM *m)          = 0;
          virtual void visita(CALL *ca)        = 0;
          virtual void visita(ESEQ *es)        = 0;
          //Visita especializações de Stm
          virtual void visita(ListaStm *lstm)  = 0;
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
          void visita(FrameMIPS *quadroMIPS);
          void visita(NoFrame *nq);
          void visita(NoRegistrador *nr);

          ///Métodos visita para MAQUINA ABSTRATA
          //Visita especializações de Exp
          void visita(ListaExp* lex);
          void visita(CONST *c);
          void visita(CONSTF *cf);
          void visita(NAME *n);
          void visita(TEMP *t);
          void visita(BINOP *bop);
          void visita(MEM *m);
          void visita(CALL *ca);
          void visita(ESEQ *es);
          //Visita especializações de Stm
          void visita(ListaStm *lstm);
          void visita(MOVE *mo);
          void visita(EXP *ex);
          void visita(JUMP *jp);
          void visita(CJUMP *cjp);
          void visita(SEQ *se);
          void visita(LABEL *l);
};
#endif // VISITANTERI_H
