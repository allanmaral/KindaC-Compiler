#ifndef CANONIZADORRI_H
#define CANONIZADORRI_H
#include "VisitanteRI.h"

class CanonizadorRI:VisitanteRI{
    public:
        CanonizadorRI();
        virtual void visita(Fragmento *f);
        virtual void visita(Procedimento *p);
        virtual void visita(Literal *l);
        virtual void visita(Variavel *var);
        virtual void visita(Temp *t);
        virtual void visita(ListaTemp *listaTemp);
        virtual void visita(Rotulo *r);
        virtual void visita(ListaRotulo *listaRotulo);
        virtual void visita(ListaAcesso *listaAcesso);
        virtual void visita(FrameMIPS *quadroMIPS);
        virtual void visita(NoFrame *nq);
        virtual void visita(NoRegistrador *nr);

        virtual void visita(ListaExp *lex);
        virtual void visita(CONST *c);
        virtual void visita(CONSTF *cf);
        virtual void visita(NAME *n);
        virtual void visita(TEMP *t);
        virtual void visita(BINOP *bop);
        virtual void visita(MEM *m);
        virtual void visita(CALL *ca);
        virtual void visita(ESEQ *es);
        virtual void visita(ListaStm *lstm);
        virtual void visita(MOVE *mo);
        virtual void visita(EXP *ex);
        virtual void visita(JUMP *jp);
        virtual void visita(CJUMP *cjp);
        virtual void visita(SEQ *se);
        virtual void visita(LABEL *l);
        ~CanonizadorRI();
    private:
};

#endif // CANONIZADORRI_H
