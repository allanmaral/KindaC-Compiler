#include "VisitanteRI.h"
#include "RepresentacaoIntermadiaria.h"

VisitanteTradutorASA::VisitanteTradutorASA(){
    this->fp = new Temp("$fp");
    this->sp = new Temp("$sp");
    this->primeiroFragmento=NULL;
    this->frameAtual=NULL;
}
VisitanteTradutorASA::~VisitanteTradutorASA(){
    delete fp;
    delete sp;
    delete primeiroFragmento;
    delete frameAtual;
}
void VisitanteTradutorASA::visita(NoPrograma  *prog){

}
Exp* VisitanteTradutorASA::visita(NoId                *id     ){}
Exp* VisitanteTradutorASA::visita(NoLiteral           *lit    ){}
Exp* VisitanteTradutorASA::visita(NoAscii             *asc    ){}
Exp* VisitanteTradutorASA::visita(NoParenteses        *pa     ){}
Exp* VisitanteTradutorASA::visita(NoConteudo          *con    ){}
Exp* VisitanteTradutorASA::visita(NoEndereco          *ende   ){}
Exp* VisitanteTradutorASA::visita(NoNumInteiro        *ni     ){}
Exp* VisitanteTradutorASA::visita(NoNumReal           *nr     ){}
Exp* VisitanteTradutorASA::visita(NoArranjo           *arr    ){}
ListaExp* VisitanteTradutorASA::visita(NoListaExpr         *le){}
ListaExp* VisitanteTradutorASA::visita(NoListaFormal       *lf){}
ListaStm* VisitanteTradutorASA::visita(NoListaSentenca     *ls){}
Stm* VisitanteTradutorASA::visita(NoSe                *se     ){}
Stm* VisitanteTradutorASA::visita(NoSenao             *sen    ){}
Stm* VisitanteTradutorASA::visita(NoEnquanto          *enq    ){}
Stm* VisitanteTradutorASA::visita(NoBlocoCaso         *bc     ){}
Stm* VisitanteTradutorASA::visita(NoDesvia            *des    ){}
Stm* VisitanteTradutorASA::visita(NoEscolha           *sw     ){}
Stm* VisitanteTradutorASA::visita(NoImprime           *imp    ){}
Stm* VisitanteTradutorASA::visita(NoLeLinha           *leL    ){}
Stm* VisitanteTradutorASA::visita(NoRetorna           *ret    ){}
Stm* VisitanteTradutorASA::visita(NoLanca             *lan    ){}
ListaStm* VisitanteTradutorASA::visita(NoEscopo       *esc    ){}
Exp* VisitanteTradutorASA::visita(NoChamadaFuncao     *cha    ){}
Stm* VisitanteTradutorASA::visita(NoTenta             *te     ){}
Exp* VisitanteTradutorASA::visita(NoSentencaExpr      *senE   ){}
void VisitanteTradutorASA::visita(NoDeclFuncao        *decF   ){}
ListaExp* VisitanteTradutorASA::visita(NoListaId      *lid    ){}
ListaAcesso* VisitanteTradutorASA::visita(NoDeclVariavel *decV ){}
void VisitanteTradutorASA::visita(NoDeclTipo          *decT   ){}
void VisitanteTradutorASA::visita(NoDeclLocalFuncao   *decLF  ){}
ListaAcesso* VisitanteTradutorASA::visita(NoDeclLocalVariavel *decLV  ){}
void VisitanteTradutorASA::visita(NoDeclLocalPublico   *decLPub){}
void VisitanteTradutorASA::visita(NoDeclLocalPrivado  *decLpri){}
ListaExp* VisitanteTradutorASA::visita(NoCorpoFuncao       *cF     ){}
void VisitanteTradutorASA::visita(NoDeclClasse        *decC   ){}
Exp* VisitanteTradutorASA::visita(NoExprUnaria    	*expU   ){}
Exp* VisitanteTradutorASA::visita(NoExprBinaria       *expB   ){}
Exp* VisitanteTradutorASA::visita(NoExprAtrib         *atr    ){}
Exp* VisitanteTradutorASA::visita(NoExprAceCamp       *expAC  ){}
Exp* VisitanteTradutorASA::visita(NoVerdadeiro        *tr     ){}
Exp* VisitanteTradutorASA::visita(NoFalso             *fa     ){}
Exp* VisitanteTradutorASA::visita(NoEsse              *th     ){}
Exp* VisitanteTradutorASA::visita(NoNovo              *n      ){}
void VisitanteTradutorASA::visita(NoTipo             *tp     ){}
Exp* VisitanteTradutorASA::visita(NoColchetes         *nc     ){}



VisitanteImpressaoRI::VisitanteImpressaoRI(){
    this->nivel=0;
}
void VisitanteImpressaoRI::imprimeNivel(){
    for(int i= 0;i<nivel;i++){
        fprintf(stdout,"  ");
    }
}
VisitanteImpressaoRI::~VisitanteImpressaoRI(){}
void VisitanteImpressaoRI::visita(Fragmento *f){
    if(f->proximoFragmento) f->proximoFragmento->aceita(this);
}
void VisitanteImpressaoRI::visita(Procedimento *p){
    fprintf(stdout,"FRAME:\n");
    if(p->frame) p->frame->aceita(this);
    fprintf(stdout,"CORPO:\n");
    if(p->corpo) p->corpo->aceita(this);
    if(p->proximoFragmento) p->proximoFragmento->aceita(this);
}
void VisitanteImpressaoRI::visita(Literal *l){
    if(l->rotulo) fprintf(stdout,"-LITERAL:%s : %s\n",l->rotulo->obterString(),l->literal);
    if(l->proximoFragmento) l->proximoFragmento->aceita(this);
}
void VisitanteImpressaoRI::visita(Variavel *var){
    nivel++;
    imprimeNivel();
    if(var->tipo) {

    }
    nivel++;
    imprimeNivel();
    if(var->tamanho) fprintf(stdout,"-TAM.%d\n",var->tamanho);
    nivel-=2;
    if(var->proximoFragmento) var->proximoFragmento->aceita(this);
}

void VisitanteImpressaoRI::visita(Temp *t){
    nivel++;
    imprimeNivel();
    if(t->temp) fprintf(stdout,"-TEMP.%s\n",t->temp);
    nivel--;
}
void VisitanteImpressaoRI::visita(ListaTemp *listaTemp){
    if(listaTemp->temp) listaTemp->temp->aceita(this);
    if(listaTemp->proximoTemp) listaTemp->proximoTemp->aceita(this);
}
void VisitanteImpressaoRI::visita(Rotulo *r){
    nivel++;
    imprimeNivel();
    fprintf(stdout, "Rotulo.%s\n", r->rotulo);
    nivel--;
}
void VisitanteImpressaoRI::visita(ListaRotulo *listaRotulo){
    if(listaRotulo->rotulo) listaRotulo->rotulo->aceita(this);
    if(listaRotulo->proximoRotulo) listaRotulo->proximoRotulo->aceita(this);
}
void VisitanteImpressaoRI::visita(ListaAcesso *listaAcesso){
    if(listaAcesso->acessoLocal) listaAcesso->acessoLocal->aceita(this);
    if(listaAcesso->proximoAcesso) listaAcesso->proximoAcesso->aceita(this);
}
void VisitanteImpressaoRI::visita(FrameMIPS *quadroMIPS){
    if(quadroMIPS->rotulo) fprintf(stdout,"Rotulo.%s\n",quadroMIPS->rotulo->rotulo);
    if(quadroMIPS->tempRetorno) fprintf(stdout,"Temp Retorno.%s\n",quadroMIPS->tempRetorno->temp);
    fprintf(stdout,"Deslocamento Parametros.%d\n",quadroMIPS->deslocamentoParametros);
    fprintf(stdout,"Deslocamento Locais.%d",quadroMIPS->deslocamentoVariaveisLocais);
    fprintf(stdout,"Lista de Acesso\n");
    if(quadroMIPS->variaveisLocais);
}
void VisitanteImpressaoRI::visita(NoRegistrador *nr){
    fprintf(stdout, "NoReg\n");
    nivel++;
    imprimeNivel();
    if(nr->temp) fprintf(stdout, "Temp.%s\n", nr->temp->temp);
    imprimeNivel();
    fprintf(stdout, "Codigo de Acesso\n");
    if(nr->exp) nr->codigoAcesso()->aceita(this);
    nivel--;
}

///Métodos visita para MAQUINA ABSTRATA
//Visita especializações de Exp
void VisitanteImpressaoRI::visita(ListaExp* lex){
    if(lex->exp) lex->exp->aceita(this);
    if(lex->proximoExp) lex->proximoExp->aceita(this);
}
void VisitanteImpressaoRI::visita(CONST *c){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-CONST.%d\n",c->ci);
    nivel--;
}
void VisitanteImpressaoRI::visita(CONSTF *c){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-CONSTF.%f\n",c->cf);
    nivel--;
}
void VisitanteImpressaoRI::visita(NAME *n){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-NAME\n");
    if(n->n) n->n->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(TEMP *temp){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-TEMP\n");
    if(temp->t) temp->t->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(BINOP *bop){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-BINOP.%d\n",bop->op);
    if(bop->e1) bop->e1->aceita(this);
    if(bop->e2) bop->e2->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(MEM *m){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-MEM\n");
    if(m->e) m->e->aceita(this);
    nivel--;

}
void VisitanteImpressaoRI::visita(CALL *ca){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-CALL\n");
    if(ca->f) ca->f->aceita(this);
    if(ca->parametros) ca->parametros->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(ESEQ *es){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-ESEQ\n");
    if(es->s) es->s->aceita(this);
    if(es->e) es->e->aceita(this);
    nivel--;

}
//Visita especializações de Stm
void VisitanteImpressaoRI::visita(ListaStm *lstm){
    if(lstm->stm) lstm->stm->aceita(this);
    if(lstm->proximoStm) lstm->proximoStm->aceita(this);
}
void VisitanteImpressaoRI::visita(MOVE *mo){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-MOVE\n");
    if(mo->e1) mo->e1->aceita(this);
    if(mo->e2) mo->e2->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(EXP *ex){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-EXP\n");
    if(ex->e) ex->e->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(JUMP *jp){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-JUMP\n");
    if(jp->e) jp->e->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(CJUMP *cjp){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-CJUMP.%d\n",cjp->op);
    if(cjp->e1) cjp->e1->aceita(this);
    if(cjp->e2) cjp->e2->aceita(this);
    if(cjp->verdadeiro) cjp->verdadeiro->aceita(this);
    if(cjp->falso) cjp->falso->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(SEQ *se){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-SEQ\n");
    if(se->s1) se->s1->aceita(this);
    if(se->s2) se->s2->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(LABEL *l){
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-LABEL\n");
    if(l->n) l->n->aceita(this);
    nivel--;
}

