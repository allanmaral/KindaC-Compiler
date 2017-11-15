#include "VisitanteRI.h"
#include "RepresentacaoIntermadiaria.h"
#include "AnalisadorLexico.h"
VisitanteTradutor::VisitanteTradutor() : ultimaStm(NULL), ultimaExp(NULL), classeAtual(NULL), funcaoAtual(NULL) {}
VisitanteTradutor::~VisitanteTradutor() {}

// Agora é abstrato, não deve entrar aqui
void VisitanteTradutor::visita(NoPrograma          *prog   ) {
    if(prog->lista) prog->lista->aceita(this);
}
void VisitanteTradutor::visita(NoId                *id     ) {
    /// PEGAR DESLOCAMENTO
    ultimaExp = new CONST(0);
}
void VisitanteTradutor::visita(NoLiteral           *lit    ) {
    /// GERAR ROTULO
    Rotulo  *r = new Rotulo();
    Literal *l = new Literal(lit->entradaTabela->pegarLexema(), r);
    ultimaExp  = new NAME(r);
}
void VisitanteTradutor::visita(NoAscii             *asc    ) {
    ultimaExp = new CONST((int)asc->entradaTabela->pegarLexema()[0]);
}
void VisitanteTradutor::visita(NoParenteses        *pa     ) {
    if(pa->expressao) pa->expressao->aceita(this);
}
void VisitanteTradutor::visita(NoConteudo          *con    ) {
    if(con->primario) con->primario->aceita(this);
    ultimaExp = new MEM(ultimaExp);
}
void VisitanteTradutor::visita(NoEndereco          *ende   ) {
    /// REVER
    if(ende->primario) ende->primario->aceita(this);
    // Remove o acesso a memoria da expressão filha, pegando, assim, o endereço
    if(MEM *mem = dynamic_cast<MEM*>(ultimaExp)) {
        ultimaExp = mem->e;
    }
}
void VisitanteTradutor::visita(NoNumInteiro        *ni     ) {
    ultimaExp = new CONST(atoi(ni->entradaTabela->pegarLexema()));
}
void VisitanteTradutor::visita(NoNumReal           *nr     ) {
    ultimaExp = new CONSTF(atof(nr->entradaTabela->pegarLexema()));
}
void VisitanteTradutor::visita(NoArranjo           *arr    ) {
    /// REVER DEVERIA RETORNAR UM TAMANHO EM BYTES, OU NEM SER VISITADO
}
void VisitanteTradutor::visita(NoListaExpr         *le     ) {
    /// LISTA DE EXP OU CONJUTO DE ESEC?
    Exp      *e1 = NULL;
    ListaExp *e2 = NULL;
    if(le->expressao) {
        le->expressao->aceita(this);
        e1 = ultimaExp;
    }
    if(le->lista) {
        le->lista->aceita(this);
        e2 = static_cast<ListaExp*>(ultimaExp);
    }
    ultimaExp = new ListaExp(e1, e2);
}
void VisitanteTradutor::visita(NoListaFormal       *lf     ) {
    // Adiciona paramantros ao frame
}
void VisitanteTradutor::visita(NoListaSentenca     *ls     ) {
    Stm *st1 = NULL, *st2 = NULL;
    if(ls->sentenca) {
        ls->sentenca->aceita(this);
        st1 = ultimaStm;
    }
    if(ls->lista) {
        ls->lista->aceita(this);
        st2 = ultimaStm;
    }
    ultimaStm = new SEQ(st1, st2);
}
void VisitanteTradutor::visita(NoSe                *se     ) {
    Rotulo *entao = new Rotulo();
    Rotulo *fimSe = new Rotulo();
    Rotulo *senao = new Rotulo();
    se->expressao->aceita(this);
    Exp *e1 = ultimaExp;
    se->sentenca->aceita(this);
    Stm *s1 = ultimaStm;
    if(se->senao){
        se->senao->aceita(this);
        Stm *s2 = ultimaStm;
        ultimaStm = new SEQ(new CJUMP(OP_NEQ,e1,new CONST(0),entao,senao),
                          new SEQ(new LABEL(entao),
                            new SEQ(new SEQ(s1,new JUMP(new NAME(fimSe))),
                                     new SEQ(new LABEL(senao),
                                        new SEQ(s2,new LABEL(fimSe))))));


    } else{
          ultimaStm = new SEQ(new CJUMP(OP_NEQ,e1,new CONST(0),entao,fimSe),
                          new SEQ(new LABEL(entao),new SEQ(s1,new LABEL(fimSe))));
      }

    //Stm *s2 = new SEQ(new LABEL(entaoSe), new SEQ())

    //ultimaStm = new SEQ(new CJUMP());
}
void VisitanteTradutor::visita(NoSenao             *sen    ) {}
void VisitanteTradutor::visita(NoEnquanto          *enq    ) {
	if(enq->expressao) enq->expressao->aceita(this);
	Exp *e=ultimaExp;
	if(enq->sentenca) enq->sentenca->aceita(this);
	Stm *s=ultimaStm;
	Rotulo *w = new Rotulo();
	Rotulo *inicio= new Rotulo();
	Rotulo *fim= new Rotulo();
	ultimaStm=new SEQ(new LABEL(w),
					new SEQ(new CJUMP(OP_NEQ,e,new CONST(0),inicio,fim),
						new SEQ(new LABEL(inicio),new SEQ(s,
								new SEQ(new JUMP(new NAME(w)),new LABEL(fim))))));
}
void VisitanteTradutor::visita(NoBlocoCaso         *bc     ) {}
void VisitanteTradutor::visita(NoDesvia            *des    ) {}
void VisitanteTradutor::visita(NoEscolha           *sw     ) {}
void VisitanteTradutor::visita(NoImprime           *imp    ) {}
void VisitanteTradutor::visita(NoLeLinha           *leL    ) {}
void VisitanteTradutor::visita(NoRetorna           *ret    ) {}
void VisitanteTradutor::visita(NoLanca             *lan    ) {}
void VisitanteTradutor::visita(NoEscopo            *esc    ) {}
void VisitanteTradutor::visita(NoChamadaFuncao     *cha    ) {}
void VisitanteTradutor::visita(NoTenta             *te     ) {}
void VisitanteTradutor::visita(NoSentencaExpr      *senE   ) {}
void VisitanteTradutor::visita(NoDeclFuncao        *decF   ) {}
void VisitanteTradutor::visita(NoListaId           *lid    ) {}
void VisitanteTradutor::visita(NoDeclVariavel      *decV   ) {}
void VisitanteTradutor::visita(NoDeclTipo          *decT   ) {}
void VisitanteTradutor::visita(NoDeclLocalFuncao   *decLF  ) {}
void VisitanteTradutor::visita(NoDeclLocalVariavel *decLV  ) {}
void VisitanteTradutor::visita(NoDeclLocalPublico  *decLPub) {}
void VisitanteTradutor::visita(NoDeclLocalPrivado  *decLPri) {}
void VisitanteTradutor::visita(NoCorpoFuncao       *cF     ) {}
void VisitanteTradutor::visita(NoDeclClasse        *decC   ) {}
void VisitanteTradutor::visita(NoExprUnaria    	   *expU   ) {
	switch(expU->operador){
        case NEGACAO:
            break;
        case ADICAO:
            break;
        case SUBTRACAO:
            break;
    }
}
void VisitanteTradutor::visita(NoExprBinaria       *expB   ) {
	 switch(expB->operador){
        case MENOR:
            break;
        case MENOR_IGUAL:
            break;
        case MAIOR:
            break;
        case MAIOR_IGUAL:
            break;
        case ATRIBUICAO:
            break;
        case E:{
			Rotulo *l1 =  new Rotulo();
			Rotulo *l2 =  new Rotulo();
			Rotulo *l3 =  new Rotulo();
			expB->exprEsquerda->aceita(this);
			Exp *e1=ultimaExp;
			expB->exprDireita->aceita(this);
			Exp *e2=ultimaExp;
			Temp *t = new Temp();
			ultimaExp = new ESEQ(new SEQ(new MOVE(new TEMP(t),new CONST(0)),
							new SEQ(new CJUMP(OP_NEQ,e1,new CONST(0),l1,l2),
							  new SEQ(new LABEL(l1),new SEQ(new CJUMP(OP_NEQ,e2,new CONST(0),l3,l2),
								new SEQ(new LABEL(l3),new SEQ(new MOVE(new TEMP(t),new CONST(1)),new LABEL(l2))))))),new TEMP(t));
			 }break;
        case E_COMERCIAL:
            break;
        case OU:{
        	Rotulo *l1 =  new Rotulo();
			Rotulo *l2 =  new Rotulo();
			expB->exprEsquerda->aceita(this);
			Exp *e1=ultimaExp;
			expB->exprDireita->aceita(this);
			Exp *e2=ultimaExp;
			Temp *r = new Temp();
			ultimaExp = new ESEQ(new SEQ(new MOVE(new TEMP(r),e1),
							new SEQ(new CJUMP(OP_NEQ,e2,new CONST(0),l1,l2),
								new SEQ(new LABEL(l1),
									new SEQ(new MOVE(new TEMP(r),new CONST(1)),new LABEL(l2))))),new TEMP(r));

			}break;
        case OU_CC:
            break;
        case ADICAO:
            break;
        case SUBTRACAO:
            break;
        case ASTERISCO:
            break;
        case DIVISAO:
            break;
        case PORCENTO:
            break;
    }
}
void VisitanteTradutor::visita(NoExprAtrib         *atr    ) {}
void VisitanteTradutor::visita(NoExprAceCamp       *expAC  ) {}
void VisitanteTradutor::visita(NoVerdadeiro        *tr     ) {
    ultimaExp = new CONST(1);
}
void VisitanteTradutor::visita(NoFalso             *fa     ) {
    ultimaExp = new CONST(0);
}
void VisitanteTradutor::visita(NoEsse              *th     ) {

}
void VisitanteTradutor::visita(NoNovo              *n      ) {}
void VisitanteTradutor::visita(NoTipo              *tp     ) {}
void VisitanteTradutor::visita(NoColchetes         *nc     ) {
    int tamanhoTipo;
    Exp *base, *offset;
    if(nc->primario) {
        nc->primario->aceita(this);
        base = ultimaExp;
        // Descobre o tamanho
    }
    if(nc->expressao) {
        nc->expressao->aceita(this);
        offset = new BINOP(OP_MUL, new CONST(tamanhoTipo), ultimaExp);
    }
    ultimaExp = new BINOP(OP_ADD, base, offset);
}




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

