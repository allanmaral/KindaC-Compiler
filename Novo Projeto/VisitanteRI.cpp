#include "VisitanteRI.h"
#include "RepresentacaoIntermadiaria.h"
#include "AnalisadorLexico.h"
#include <string.h>
VisitanteTradutor::VisitanteTradutor()
    : ultimaStm(NULL), ultimaExp(NULL), classeAtual(NULL), funcaoAtual(NULL),
      ultimoFim(NULL), frame(NULL), listaFragmento(NULL), resultadoEscolha(NULL),
      contLiteral(0), contLaco(0), contCaso(0), contEscolha(0) {}

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
    char* rot = RotuloNome("Literal", contLiteral++);
    Rotulo  *r = new Rotulo(rot);
    Literal *l = new Literal(lit->entradaTabela->pegarLexema(), r);
    ultimaExp  = new NAME(r);
    delete rot;
    // Insere na lista de fragmentos
    if(listaFragmento) listaFragmento->InsereLista(l);
    else listaFragmento = l;
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
void VisitanteTradutor::visita(NoListaExpr         *le     ) {
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
void VisitanteTradutor::visita(NoListaSentenca     *ls     ) {
    Stm *st1 = NULL, *st2 = NULL;
    if(ls->sentenca) {
        ls->sentenca->aceita(this);
        st1 = ultimaStm;
    }
    if(ls->lista) {
        ls->lista->aceita(this);
        st2 = ultimaStm;
        ultimaStm = new SEQ(st1, st2);
    }
}
void VisitanteTradutor::visita(NoSe                *se     ) {
    char *rEntao = RotuloNome("EntaoSe", ++contLaco);
    char *rFimSe = RotuloNome("FimSe",     contLaco);
    Rotulo *entao = new Rotulo(rEntao);
    Rotulo *fimSe = new Rotulo(rFimSe);
    Rotulo *rUltimoFim = ultimoFim; // Empilha ultimo fim
    ultimoFim = fimSe;
    delete rEntao;
    delete rFimSe;
    se->expressao->aceita(this);
    Exp *e1 = ultimaExp;
    se->sentenca->aceita(this);
    Stm *s1 = ultimaStm;
    if(se->senao){
        char* rSenao = RotuloNome("SeNao", contLaco);
        Rotulo *senao = new Rotulo(rSenao);
        delete rSenao;
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
    ultimoFim = rUltimoFim; // Desempilha ultimo fim
}
void VisitanteTradutor::visita(NoSenao             *sen    ) {
    if(sen->sentenca) sen->sentenca->aceita(this);
}
void VisitanteTradutor::visita(NoEnquanto          *enq    ) {
	char *rTeste = RotuloNome("TesteEnquanto", ++contLaco);
	char *rInicio = RotuloNome("InicioEnquanto", contLaco);
	char *rFim = RotuloNome("FimEnquanto", contLaco);
	Rotulo *w = new Rotulo(rTeste);
	Rotulo *inicio= new Rotulo(rInicio);
	Rotulo *fim= new Rotulo(rFim);
	delete rTeste, delete rInicio, delete rFim;
	Rotulo *rUltimoFim = ultimoFim; // Empilha o ultimo fim na pilha
	ultimoFim = fim;
	if(enq->expressao) enq->expressao->aceita(this);
	Exp *e=ultimaExp;
	if(enq->sentenca) enq->sentenca->aceita(this);
	Stm *s=ultimaStm;
	ultimaStm=new SEQ(new LABEL(w),
					  new SEQ(new CJUMP(OP_NEQ,e,new CONST(0),inicio,fim),
						      new SEQ(new LABEL(inicio),
                                      new SEQ(s, new SEQ(new JUMP(new NAME(w)), new LABEL(fim))))));
    ultimoFim = rUltimoFim; // Desempilha o ultimo fim
}
void VisitanteTradutor::visita(NoBlocoCaso         *bc     ) {
    char *rCaso = RotuloNome("EntaoCaso", ++contCaso);
    Rotulo *entao = new Rotulo(rCaso);
    delete rCaso;
    bc->num->aceita(this);
    Exp *e1 = ultimaExp;
    bc->listaSentenca->aceita(this);
    Stm *s1 = ultimaStm;
    if(bc->lista){
        char* rSenao = RotuloNome("SeNaoCaso", contCaso);
        Rotulo *senao = new Rotulo(rSenao);
        delete rSenao;
        bc->lista->aceita(this);
        Stm *s2 = ultimaStm;
        ultimaStm = new SEQ(new CJUMP(OP_EQ,new TEMP(resultadoEscolha),e1,entao,senao),
                            new SEQ(new LABEL(entao),
                                    new SEQ(new SEQ(s1,new JUMP(new NAME(ultimoFim))),
                                            new SEQ(new LABEL(senao),
                                                    s2))));
    } else{
          ultimaStm = new SEQ(new CJUMP(OP_EQ,new TEMP(resultadoEscolha),e1,entao,ultimoFim),
                              new SEQ(new LABEL(entao),new SEQ(s1,new LABEL(ultimoFim))));
      }
}
void VisitanteTradutor::visita(NoDesvia            *des    ) {
    ultimaStm = new JUMP(new NAME(ultimoFim));
}
void VisitanteTradutor::visita(NoEscolha           *sw     ) {
    if(sw->expressao) sw->expressao->aceita(this);
    resultadoEscolha = new Temp();
    Stm *resultado = new MOVE(new TEMP(resultadoEscolha), ultimaExp);
    contCaso = 0;
    char *rFim = RotuloNome("FimEscolha", ++contEscolha);
	Rotulo *fim= new Rotulo(rFim);
	Rotulo *tFim = ultimoFim;
	ultimoFim = fim;
    if(sw->blocoCaso) sw->blocoCaso->aceita(this);
    ultimaStm = new SEQ(resultado, ultimaStm);
    ultimoFim = tFim;
}
void VisitanteTradutor::visita(NoImprime           *imp    ) {
    imp->listaExpr->aceita(this);
    ultimaStm = new EXP(new CALL(new NAME(new Rotulo((char*)"imprime")), static_cast<ListaExp*>(ultimaExp)));
}
void VisitanteTradutor::visita(NoLeLinha           *leL    ) {
    leL->expressao->aceita(this);
    ultimaStm = new EXP(new CALL(new NAME(new Rotulo((char*)"le_linha")), new ListaExp(ultimaExp, NULL)));
}
void VisitanteTradutor::visita(NoRetorna           *ret    ) {
    // Cria um rotulo para o epilogo da função
    Exp* e1 = NULL;
    if(ret->expressao) {
        ret->expressao->aceita(this);
        e1 = ultimaExp;
    } else {
        e1 = new CONST(0);
    }
    char* rotuloReg = RotuloNome("Retorno", 0);
    char* rotulo = RotuloNome("Epilogo", 0);
    ultimaStm = new SEQ(new MOVE(new TEMP(new Temp(rotuloReg)), e1),
                        new JUMP(new NAME(new Rotulo(rotulo))));
    delete rotuloReg;
    delete rotulo;
}

void VisitanteTradutor::visita(NoEscopo            *esc    ) {
    esc->lista->aceita(this);
}
void VisitanteTradutor::visita(NoChamadaFuncao     *cha    ) {
    cha->parametros->aceita(this);
    /// Descobre rotulo da função
    char* rotulo = RotuloCF(NULL, NULL, cha->id->entradaTabela->pegarLexema(),0);
    ListaExp* listaParametros = static_cast<ListaExp*>(ultimaExp);
    ultimaExp = new CALL(new NAME(new Rotulo(rotulo)), listaParametros);
    delete rotulo;
}
void VisitanteTradutor::visita(NoSentencaExpr      *senE   ) {
    if(senE->expressao) senE->expressao->aceita(this);
    ultimaStm = new EXP(ultimaExp);
}
void VisitanteTradutor::visita(NoDeclFuncao        *decF   ) {
    char *rotulo = RotuloNome(decF->id->entradaTabela->pegarLexema(), 0); // REVER NOME DEPOIS
    FrameMIPS *novoFrame = new FrameMIPS(new Rotulo(rotulo), NULL, 0, 0);
    novoFrame->atr = decF->atr;
    frame = novoFrame;
    funcaoAtual = decF;
    // Visita a lista de parametros
    if(decF->parametros){
        decF->parametros->aceita(this);
    }
    // Visita as declarações locais
    if(decF->variaveis){
        decF->variaveis->aceita(this);
    }
    // Visita os stmts
    decF->sentenca->aceita(this);
    Procedimento *procedimento = new Procedimento(novoFrame, ultimaStm);
    if(listaFragmento) listaFragmento->InsereLista(procedimento);
    else listaFragmento = procedimento;

    frame = NULL;
    funcaoAtual = NULL;
    if(decF->lista) decF->lista->aceita(this);
}
void VisitanteTradutor::visita(NoListaFormal       *lf     ) {
    // Adiciona paramantros ao frame
   if(lf){
        AtributoVariavel* var = (AtributoVariavel*) funcaoAtual->atr->buscaParametro(lf->id->entradaTabela->pegarLexema());
        if(var){
            var->atribuiAcesso(frame->insereParametro(false/*var->escapa*/,10/*var->tamanho*/));
        }
        if(lf->lista) lf->lista->aceita(this);
   }
}
void VisitanteTradutor::visita(NoListaId           *lid    ) {}
void VisitanteTradutor::visita(NoDeclVariavel      *decV   ) {
    NoListaId *listaId = decV->variaveis;
    while(listaId) {
        Atributo *atr;
        if(frame) atr = frame->atr->buscaVariavel(listaId->id->entradaTabela->pegarLexema());
        else atr = obtemTabelaVariaveis()->busca(listaId->id->entradaTabela->pegarLexema());
        AtributoVariavel *var = static_cast<AtributoVariavel*>(atr);

        int tamanho = 4; //var->pegarTamanho();
        bool escapa = false; //var->pegarEscapa();

        if(frame) {
            frame->deslocamentoVariaveisLocais += tamanho;
            AcessoLocal* acesso = frame->insereLocal(escapa, frame->deslocamentoVariaveisLocais);
            /// Atribui o acesso local à tabela de simbolos
            AtributoVariavel *var =
                 static_cast<AtributoVariavel*>(frame->atr->busca(listaId->id->entradaTabela->pegarLexema()));
                 static_cast<AtributoVariavel*>(frame->atr->busca(listaId->id->entradaTabela->pegarLexema()));
            var->atribuiAcesso(acesso);
        } else {
            Rotulo *rotulo = new Rotulo(listaId->id->entradaTabela->pegarLexema());
            Variavel *variavel = new Variavel(var->pegarTipo(), tamanho, rotulo);
            /// PRECISA SALVAR NA TABELA DE ESIMBOLOS
            if(listaFragmento) listaFragmento->InsereLista(variavel);
            else  listaFragmento = variavel;
        }

        listaId = listaId->lista;
    }
}
void VisitanteTradutor::visita(NoDeclTipo          *decT   ) {}

void VisitanteTradutor::visita(NoExprUnaria    	   *expU   ) {
    expU->expressao->aceita(this);
    Exp *e1=ultimaExp;
	switch(expU->operador){
        case NEGACAO:{
            Temp *r = new Temp();
            Rotulo *nV = new Rotulo();
            Rotulo *nF = new Rotulo();
            Rotulo *fim = new Rotulo();
            ultimaExp = new ESEQ(new SEQ(new CJUMP(OP_EQ,e1,new CONST(1),nV,nF),
                                         new SEQ(new LABEL(nV),
                                                 new SEQ(new SEQ(new MOVE(new TEMP(r), new CONST(0)),
                                                                 new JUMP(new NAME(fim))),
                                                         new SEQ(new LABEL(nF),
                                                                 new SEQ(new MOVE(new TEMP(r), new CONST(1)),
                                                                         new LABEL(fim)))))),
                                 new TEMP(r));
            }break;
        case ADICAO:
            ultimaExp = new BINOP(OP_ADD,e1,new CONST(0));
            break;
        case SUBTRACAO:
            ultimaExp = new BINOP(OP_SUB,e1,new CONST(0));
            break;
    }
}
void VisitanteTradutor::visita(NoExprBinaria       *expB   ) {
    expB->exprEsquerda->aceita(this);
    Exp *e1=ultimaExp;
    expB->exprDireita->aceita(this);
    Exp *e2=ultimaExp;
	 switch(expB->operador){
        case MENOR: case MENOR_IGUAL: case MAIOR: case MAIOR_IGUAL:{
            int opRelacional = 0;
            if(expB->operador==MENOR){
              opRelacional = OP_LT;
            }else if(expB->operador==MENOR_IGUAL){
                     opRelacional = OP_LE;
                   }else if(expB->operador==MAIOR){
                            opRelacional = OP_GT;
                          }else if(expB->operador==MAIOR_IGUAL){
                                   opRelacional = OP_GE;
                                 }
            Rotulo *l1 =  new Rotulo();
			Rotulo *l2 =  new Rotulo();
			Temp *r = new Temp();
			ultimaExp = new ESEQ(new SEQ(new MOVE(new TEMP(r),new CONST(1)),
                            new SEQ(new CJUMP(opRelacional,e1,e2,l1,l2),
                                new SEQ(new LABEL(l2),
                                    new SEQ(new MOVE(new TEMP(r),new CONST(0)),new LABEL(l1))))),new TEMP(r));
            }break;
        case ATRIBUICAO:
            break;
        case E:{
			Rotulo *l1 =  new Rotulo();
			Rotulo *l2 =  new Rotulo();
			Rotulo *l3 =  new Rotulo();
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
			Temp *r = new Temp();
			ultimaExp = new ESEQ(new SEQ(new MOVE(new TEMP(r),e1),
							new SEQ(new CJUMP(OP_NEQ,e2,new CONST(0),l1,l2),
								new SEQ(new LABEL(l1),
									new SEQ(new MOVE(new TEMP(r),new CONST(1)),new LABEL(l2))))),new TEMP(r));
			}break;
        case OU_CC:
            break;
        case ADICAO:
            ultimaExp = new BINOP(OP_ADD,e1,e2);
            break;
        case SUBTRACAO:
            ultimaExp = new BINOP(OP_SUB,e1,e2);
            break;
        case ASTERISCO:
            ultimaExp = new BINOP(OP_MUL,e1,e2);
            break;
        case DIVISAO:
            ultimaExp = new BINOP(OP_DIV,e1,e2);
            break;
        case PORCENTO:{
            Temp *r= new Temp();
            //ultimaExp = new ESEQ(new EXP(new BINOP(OP_DIV,e1,e2)),new MOVE(new TEMP(r),new CALL(new NAME(new Rotulo("mfhi")),new ListaExp(new TEMP(r),NULL))));
            ultimaExp = new ESEQ(new SEQ(new EXP(new BINOP(OP_DIV,e1,e2)),
                            new EXP(new CALL(new NAME(new Rotulo((char*)"mfhi")),new ListaExp(new TEMP(r),NULL)))),new TEMP(r));
        }break;
    }
}
void VisitanteTradutor::visita(NoExprAtrib         *atr    ) {
    atr->exprEsquerda->aceita(this);
    Exp *e1=ultimaExp;
    atr->exprDireita->aceita(this);
    Exp *e2=ultimaExp;
    ultimaStm = new MOVE(e1,e2);
}
void VisitanteTradutor::visita(NoExprAceCamp       *expAC  ) {///Precisa do ofsset da classe + do frame atual

}
void VisitanteTradutor::visita(NoVerdadeiro        *tr     ) {
    ultimaExp = new CONST(1);
}
void VisitanteTradutor::visita(NoFalso             *fa     ) {
    ultimaExp = new CONST(0);
}
void VisitanteTradutor::visita(NoEsse              *th     ) {
    ultimaExp = new MEM(new TEMP(new Temp((char*)"fp")));
}
void VisitanteTradutor::visita(NoNovo              *n      ) {
    ultimaExp = new CONST(0);
    /*Temp* t = new Temp();
    char* nome = n->id->entradaTabela->pegarLexema();
    if(n->listaExpr) n->listaExpr->aceita(this);
    int tamanho = 4;
    Rotulo *rotulo;
    if(n->id) {
        AtributoClasse *atr = static_cast<AtributoClasse*>(
                                                 obtemTabelaClasses()->busca(n->id->entradaTabela->pegarLexema()));
        /// REVER TAMANHO CLASSE
        //tamanho = atr->pegarTamanho();
        char *r = RotuloCF(nome, NULL, nome, 0);
        rotulo = new Rotulo(r);
        delete r;
    }
    ultimaExp = new ESEQ(new MOVE(new TEMP(t),
                                  new CALL(new NAME(new Rotulo((char*)"malloc")),
                                           new ListaExp(new CONST(tamanho), NULL))),
                         new ESEQ(new EXP(new CALL(new NAME(rotulo),
                                                   new ListaExp(new TEMP(t), static_cast<ListaExp*>(ultimaExp)))),
                                  new TEMP(t)));*/
}
void VisitanteTradutor::visita(NoTipo              *tp     ) {}
void VisitanteTradutor::visita(NoColchetes         *nc     ) {
    int tamanhoTipo ;
    Exp *base, *offset;
    if(nc->primario) {
        nc->primario->aceita(this);
        base = ultimaExp;
        /// Descobre o tamanho
    }
    if(nc->expressao) {
        nc->expressao->aceita(this);
        offset = new BINOP(OP_MUL, new CONST(tamanhoTipo), ultimaExp);
    }
    ultimaExp = new BINOP(OP_ADD, base, offset);
}

void VisitanteTradutor::visita(NoArranjo           *arr    ) {}
void VisitanteTradutor::visita(NoLanca             *lan    ) {}
void VisitanteTradutor::visita(NoTenta             *te     ) {}
void VisitanteTradutor::visita(NoDeclLocalFuncao   *decLF  ) {}
void VisitanteTradutor::visita(NoDeclLocalVariavel *decLV  ) {}
void VisitanteTradutor::visita(NoDeclLocalPublico  *decLPub) {}
void VisitanteTradutor::visita(NoDeclLocalPrivado  *decLPri) {}
void VisitanteTradutor::visita(NoCorpoFuncao       *cF     ) {}
void VisitanteTradutor::visita(NoDeclClasse        *decC   ) {}

/// Cria um rotulo para o literal usando função e classe que ele pertence
char* VisitanteTradutor::RotuloNome(const char *nome, int cont) {
    char *rotulo = NULL, *t1 = NULL, *t2 = NULL;
    int tamanho = strlen(nome) + 14; //10: max int, 3: '_', 1: char com '\0';
    if(classeAtual) {
        t1 = classeAtual->id->entradaTabela->pegarLexema();
        tamanho += strlen(t1);
    }
    if(funcaoAtual) {
        if(t1) t2 = funcaoAtual->id->entradaTabela->pegarLexema(), tamanho += strlen(t2);
        else   t1 = funcaoAtual->id->entradaTabela->pegarLexema(), tamanho += strlen(t1);
    }
    rotulo = new char[tamanho];
    if(t2) sprintf(rotulo, "%s_%s_%s_%d", t1, t2, nome, cont);
    else if(t1) sprintf(rotulo, "%s_%s_%d", t1, nome, cont);
         else   sprintf(rotulo, "%s_%d", nome, cont);
    return rotulo;
}

char* VisitanteTradutor::RotuloCF(char* classe, char* func, char* nome, int cont)
{
    char *rotulo = NULL, *t1 = NULL, *t2 = NULL;
    int tamanho = strlen(nome) + 14; //10: max int, 3: '_', 1: char com '\0';
    if(classe) {
        t1 = classe;
        tamanho += strlen(t1);
    }
    if(func) {
        if(t1) t2 = func, tamanho += strlen(t2);
        else   t1 = func, tamanho += strlen(t1);
    }
    rotulo = new char[tamanho];
    if(t2) sprintf(rotulo, "%s_%s_%s_%d", t1, t2, nome, cont);
    else if(t1) sprintf(rotulo, "%s_%s_%d", t1, nome, cont);
         else   sprintf(rotulo, "%s_%d", nome, cont);
    return rotulo;
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
void VisitanteImpressaoRI::visita(Variavel *var){///Terminar
    nivel++;
    imprimeNivel();
    fprintf(stdout,"-VAR\n");
    //AtributoVariavel* atr=static_cast<AtributoVariavel*>(var->tipo);
    //atr->pegarAcesso()->aceita(this);
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
void VisitanteImpressaoRI::visita(AcessoLocal *ace){
    nivel++;
    ace->codigoAcesso()->aceita(this);
    nivel--;
}
void VisitanteImpressaoRI::visita(FrameMIPS *quadroMIPS){///Verificar
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
    fprintf(stdout,"-BINOP.%d\n",bop->op);/// Arrumar impressão do literal do operador
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
    fprintf(stdout,"-CJUMP.%d\n",cjp->op);/// Arrumar impressão do literal do operador
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
void VisitanteImpressaoRI::visita(NoFrame* nq){}

