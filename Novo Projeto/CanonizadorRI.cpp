#include "CanonizadorRI.h"
#include "RepresentacaoIntermadiaria.h"
Exp *expAtual = NULL;
Stm *stmAtual = NULL;
Exp *expAnterior = NULL;
Stm *stmAnterior = NULL;
bool alterado = false;

CanonizadorRI::CanonizadorRI():VisitanteRI(){

}
CanonizadorRI::~CanonizadorRI(){

}
void CanonizadorRI::visita(ListaExp* lex){
    if(lex->exp){
        expAnterior = lex;
        stmAnterior = NULL;
        lex->exp->aceita(this);
        lex->exp = expAtual;
    }
    if(lex->proximoExp){
        lex->proximoExp->aceita(this);
    }
}
void CanonizadorRI::visita(CONST* c){
    expAtual = c;
}
void CanonizadorRI::visita(CONSTF* cf){
    expAtual = cf;
}
void CanonizadorRI::visita(NAME* n){
    expAtual = n;
}
void CanonizadorRI::visita(TEMP* t){
    expAtual = t;
}
void CanonizadorRI::visita(BINOP* bop){
    ESEQ *exp;
    expAnterior = bop;
    stmAnterior = NULL;
    if(bop->e1){
        bop->e1->aceita(this);
        bop->e1 = expAtual;
    }
    if(bop->e2){
        bop->e2->aceita(this);
        bop->e2 = expAtual;
    }

    if(bop->e1 && (exp = dynamic_cast<ESEQ*>(bop->e1))){
        alterado = true;
        Exp *e1 = exp->e;
        exp->e = bop;
        bop->e1 = e1;
        expAtual = exp;
    }else{
        if(bop->e2 && (exp = dynamic_cast<ESEQ*>(bop->e2))){
            alterado = true;
            Temp *t = new Temp();
            TEMP *t1 = new TEMP(t);
            TEMP *t2 = new TEMP(t);
            Exp *e1 = bop->e1;
            MOVE *m = new MOVE(t2,e1);
            ESEQ *eseq = new ESEQ(m,exp);
            bop->e1 = t1;
            bop->e2 = exp->e;
            exp->e = bop;
            eseq->aceita(this);
        }else{
            expAtual = bop;
        }
    }
}
void CanonizadorRI::visita(MEM* m){
    expAnterior = m;
    stmAnterior = NULL;
    if(m->e){
        m->e->aceita(this);
        m->e = expAtual;
    }
    ESEQ* eseq;
    if(m->e && (eseq = dynamic_cast<ESEQ*>(m->e))){
        alterado = true;
        m->e = eseq->e;
        expAtual = new ESEQ(eseq->s, m);
        eseq->e = NULL;
        eseq->s = NULL;
        delete eseq;
    }else{
        expAtual = m;
    }
}
void CanonizadorRI::visita(CALL* ca){
    MOVE *mo;
    TEMP *tmp;
    if(!expAnterior){
        if((mo = dynamic_cast<MOVE*>(stmAnterior))){
            if(mo->e1 && (tmp = dynamic_cast<TEMP*>(mo->e1))){
                expAtual = ca;
                return;
            }
        }
        alterado = true;
        Temp *t = new Temp();
        TEMP *t1 = new TEMP(t);
        TEMP *t2 = new TEMP(t);
        MOVE *mo = new MOVE(t1,ca);
        ESEQ *eseq = new ESEQ(mo,t2);
        expAtual = eseq;
    }else{
        expAtual = ca;
    }
}
void CanonizadorRI::visita(ESEQ* es){
    ESEQ *exp;
    expAnterior = es;
    stmAnterior = NULL;
    if(es->e){
        es->e->aceita(this);
        es->e = expAtual;
    }
    if(es->s){
        es->s->aceita(this);
        es->s = stmAtual;
    }
    if(es->e && (exp = dynamic_cast<ESEQ*>(es->e))){
        alterado = true;
        SEQ *novo_seq;
        Stm *s1 = es->s;
        Stm *s2 = exp->s;
        novo_seq = new SEQ(s1,s2);
        es->s = novo_seq;
        es->e = exp->e;
        exp->e = NULL;
        exp->s = NULL;
        delete exp;
    }
    expAtual = es;
}
void CanonizadorRI::visita(ListaStm* lstm){
    if(lstm->stm){
        lstm->stm->aceita(this);
        lstm->stm = stmAtual;
    }if(lstm->proximoStm){
        lstm->proximoStm->aceita(this);
    }
    stmAtual = lstm;
}
void CanonizadorRI::visita(MOVE* mo){
    ESEQ *exp;
    stmAnterior = mo;
    expAnterior = NULL;
    if(mo->e1){
        mo->e1->aceita(this);
        mo->e1 = expAtual;
    }
    if(mo->e2){
        mo->e2->aceita(this);
        mo->e2 = expAtual;
    }
    if(mo->e1 && (exp = dynamic_cast<ESEQ*>(mo->e1))){
        alterado = true;
        Stm *s = exp->s;
        Exp *e1 = exp->e;
        mo->e1 = e1;
        SEQ *seq = new SEQ(s,mo);
        exp->e = NULL;
        exp->s = NULL;
        delete exp;
        stmAtual = seq;
    }else{
        stmAtual = mo;
    }
}
void CanonizadorRI::visita(EXP* ex){
    ESEQ *eseq;
    if(ex->e){
        stmAnterior = ex;
        expAnterior = NULL;
        ex->e->aceita(this);
        ex->e = expAtual;
        if(expAtual && (eseq = dynamic_cast<ESEQ*>(expAtual))){
            stmAtual = new SEQ(eseq->s, new EXP(eseq->e));
            return;
        }
    }
    stmAtual = ex;
}
void CanonizadorRI::visita(JUMP* jp){
    ESEQ* eseq;
    stmAnterior = jp;
    expAnterior = NULL;
    if(jp->e){
        jp->e->aceita(this);
        jp->e = expAtual;
    }
    if(jp->e && (eseq = dynamic_cast<ESEQ*>(jp->e))){
        alterado = true;
        jp->e = eseq->e;
        stmAtual = new SEQ(eseq->s, jp);
        eseq->e = NULL;
        eseq->s = NULL;
        delete eseq;
    }else{
        stmAtual = jp;
    }
}
void CanonizadorRI::visita(CJUMP* cjp){
    stmAnterior = cjp;
    expAnterior = NULL;
    if(cjp->e1){
        cjp->e1->aceita(this);
        cjp->e1 = expAtual;
    }
    if(cjp->e2){
        cjp->e2->aceita(this);
        cjp->e2 = expAtual;
    }
    ESEQ* eseq;
    if(cjp->e1 && (eseq = dynamic_cast<ESEQ*>(cjp->e1))){
        alterado = true;
        cjp->e1 = eseq->e;
        stmAtual = new SEQ(eseq->s,cjp);
    }else{
        if(cjp->e2 && (eseq = dynamic_cast<ESEQ*>(cjp->e2))){
            alterado = true;
            Temp* t = new Temp();
            Exp *e = cjp->e1;
            cjp->e1 = new TEMP(t);
            cjp->e2 = eseq->e;
            stmAtual = new SEQ(new MOVE(new TEMP(t), e), new SEQ(eseq->s, cjp));
            eseq->e = NULL;
            eseq->s = NULL;
            delete eseq;
        }else{
            stmAtual = cjp;
        }
    }
}
void CanonizadorRI::visita(SEQ* se){
    stmAnterior = se;
    expAnterior = NULL;
    SEQ *stm;
    if(se->s1){
        se->s1->aceita(this);
        se->s1 = stmAtual;
    }
    if(se->s2){
        se->s2->aceita(this);
        se->s2 = stmAtual;
    }
    if(se->s1 && (stm = dynamic_cast<SEQ*>(se->s1))){
        alterado = true;
        Stm *s1 = stm->s1;
        Stm *s2 = stm->s2;
        Stm *s3 = se->s2;
        se->s1 = s1;
        se->s2 = stm;
        stm->s1 = s2;
        stm->s2 = s3;
    }
    stmAtual = se;
}
void CanonizadorRI::visita(LABEL* l){
    stmAtual = l;
}
void CanonizadorRI::visita(Fragmento* f){
    f->aceita(this);
}
void CanonizadorRI::visita(Procedimento* p){
    if(p->corpo){
        do{
            alterado = false;
            p->corpo->aceita(this);
        }while(alterado);
        p->corpo = stmAtual;
    }
    if(p->proximoFragmento){
        p->proximoFragmento->aceita(this);
    }
}
void CanonizadorRI::visita(Literal* l){
    if(l->proximoFragmento){
        l->proximoFragmento->aceita(this);
    }
}
void CanonizadorRI::visita(Variavel* var){
    if(var->proximoFragmento){
        var->proximoFragmento->aceita(this);
    }
}
void CanonizadorRI::visita(Temp* t){}
void CanonizadorRI::visita(ListaTemp* listaTemp){}
void CanonizadorRI::visita(Rotulo* r){}
void CanonizadorRI::visita(ListaRotulo* listaRotulo){}
void CanonizadorRI::visita(ListaAcesso* listaAcesso){}
void CanonizadorRI::visita(FrameMIPS* quadroMIPS){}

void CanonizadorRI::visita(NoFrame* nq){
    if(nq->exp){
        nq->exp->aceita(this);
        nq->exp = expAtual;
    }
}
void CanonizadorRI::visita(NoRegistrador* nr){
    if(nr->exp){
        nr->exp->aceita(this);
        nr->exp = expAtual;
    }
}
