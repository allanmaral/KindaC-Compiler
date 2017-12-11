#include "Gerador.h"
#include "AnalisadorLexico.h"
#include <string.h>
#define NUM_REGISTRADORES 16
#include "RepresentacaoIntermadiaria.h"
#define QUADRO_BASICO (19*4)
#define PALAVRA 32
typedef struct FilaRegistrador{
    Temp *reg;
    FilaRegistrador *proximo;
}FilaRegistrador;

static char registradores [16][3] = {
    "s1",
    "s2",
    "s3",
    "s4",
    "s5",
    "s6",
    "s7",
    "t1",
    "t2",
    "t3",
    "t4",
    "t5",
    "t6",
    "t7",
    "t8",
    "t9",
};
static bool registradorReservado(Temp *t){
    if(strcmp(t->obterString(),"$fp") && strcmp(t->obterString(),"$v0") &&  strcmp(t->obterString(),"$0") &&
        strcmp(t->obterString(),"$a0") &&  strcmp(t->obterString(),"$a1") &&  strcmp(t->obterString(),"$a2") &&
        strcmp(t->obterString(),"$a3") &&  strcmp(t->obterString(),"$sp")&&  strcmp(t->obterString(),"$r0")){
        return false;
    }else return true;
}
static bool registradorValido(Temp *t){
    for(int i=0;i<NUM_REGISTRADORES;i++){
        char aux[32];
        sprintf(aux,"$%s",registradores[i]);
        if(strcmp(t->obterString(),aux)==0){
            return true;
        }
    }
    return false;
}
void Gerador::liberaRetistrador(Temp* t){
    if(!registradorReservado(t)){
            //fprintf(stdout, "liberou: %s\n", t->obterString());///tambem tirar isso
            if(primeiroRegLivre){
                FilaRegistrador * liberado = new FilaRegistrador();
                liberado->reg = t;
                liberado->proximo = primeiroRegLivre;
                primeiroRegLivre = liberado;
            }else {
                primeiroRegLivre=new FilaRegistrador();
                primeiroRegLivre->proximo=NULL;
                primeiroRegLivre->reg=t;
             }
     }

}
Temp* Gerador::pegaRegistradorLivre(){
    if(primeiroRegLivre){
        //fprintf(stdout, "pegou: %s\n", primeiroRegLivre->reg->obterString());///tambem tirar isso
        Temp* t= primeiroRegLivre->reg;
        FilaRegistrador *prox = primeiroRegLivre->proximo;
        delete primeiroRegLivre;
        primeiroRegLivre = prox;
        return t;
    }else return NULL;
}
void Gerador::salvarTodosRegistradores(int offset){
    for(int i=0; i<NUM_REGISTRADORES; i++){
        fprintf(arqAss,"\tsw $%s,%d($sp)\n", registradores[i], offset);
        offset += 4;
    }
    fprintf(arqAss, "\tsw $fp,%d($sp)\n", offset);
    offset += 4;
    fprintf(arqAss, "\tsw $t0,%d($sp)\n", offset);
    offset += 4;
    fprintf(arqAss, "\tsw $ra,%d($sp)\n", offset);

}
void Gerador::recuperarTodosRegistradores(int offset){
    for(int i=0; i<NUM_REGISTRADORES; i++){
        fprintf(arqAss, "\tlw $%s,%d($sp)\n", registradores[i], offset);
        offset += 4;
    }
    fprintf(arqAss, "\tlw $fp,%d($sp)\n", offset);
    offset += 4;
    fprintf(arqAss, "\tlw $t0,%d($sp)\n", offset);
    offset += 4;
    fprintf(arqAss, "\tlw $ra,%d($sp)\n", offset);
}

Gerador::Gerador(FILE* arquivo) : arqAss(NULL), primeiroRegLivre(NULL){
    arqAss = arquivo;
    for(int i=0; i<NUM_REGISTRADORES; i++){
        liberaRetistrador(new Temp(registradores[i]));
    }
}
Gerador::~Gerador(){
    FilaRegistrador *aux;
    while(primeiroRegLivre!=NULL){
        aux=primeiroRegLivre->proximo;
        delete primeiroRegLivre;
        primeiroRegLivre=aux;

    }
    fclose(arqAss);
}
void Gerador::visita(Fragmento* f){
    f->aceita(this);
}
void Gerador::visita(Procedimento* p){
    fprintf(arqAss,"\n.text\n");
    p->frame->aceita(this);
    if(p->corpo)p->corpo->aceita(this);
    FrameMIPS *frame=dynamic_cast<FrameMIPS*>(p->frame);
    if(strcmp(frame->rotulo->rotulo,"main")){
        fprintf(arqAss,"%s_Epilogo:\n",frame->rotulo->obterString());
        int tamanhoParametros = frame->deslocamentoParametros;
        recuperarTodosRegistradores(tamanhoParametros);
        fprintf(arqAss,"\tj $ra \n\n\n");
        //recuperarTodosRegistradores(-tamanhoQuadro-NUM_REGISTRADORES-3*4);
        //fprintf(arqAss,"\taddi $sp, $fp, 0\n");
        //fprintf(arqAss,"\taddu $fp, $fp,%d\n",tamanhoQuadro+QUADRO_BASICO);
        //fprintf(arqAss,"\tj $ra \n\n\n",tamanhoQuadro+QUADRO_BASICO);
        if(p->proximoFragmento) p->proximoFragmento->aceita(this);
    } else { // Epilogo do main
        fprintf(arqAss,"%s_Epilogo:\n",frame->rotulo->obterString());
        int tamanhoQuadro = frame->deslocamentoVariaveisLocais;
        fprintf(arqAss,"\tlw $ra, %d($sp)\n", tamanhoQuadro);
        fprintf(arqAss,"\tlw $fp, %d($sp)\n", tamanhoQuadro+4);
        fprintf(arqAss,"\taddu $sp, $sp, %d\n",tamanhoQuadro+8);
        fprintf(arqAss,"\tj $ra \n\n\n");
    }

}
void Gerador::visita(Literal* l){
    fprintf(arqAss, ".rdata\n%s:\n\t.asciiz %s\n", l->rotulo->obterString(), l->literal);
    if(l->proximoFragmento) l->proximoFragmento->aceita(this);
}
void Gerador::visita(Variavel* v){
    fprintf(arqAss, ".data\n");
    fprintf(arqAss, "var_%s: ", v->rotulo->obterString());
    fprintf(arqAss, ".space %d\n", v->tamanho);
    if(v->proximoFragmento) v->proximoFragmento->aceita(this);
}

void Gerador::visita(FrameMIPS* quadroMIPS){
    int tamanhoQuadro = quadroMIPS->deslocamentoVariaveisLocais;
    int tamanhoParametros = quadroMIPS->deslocamentoParametros;
    //if(quadroMIPS->rotulo) quadroMIPS->rotulo->aceita(this);
    if(strcmp(quadroMIPS->rotulo->rotulo,"main") == 0){
        //caso seja o método main aloca somente o espaço das variáveis locais
        fprintf(arqAss,"main:\n");
        fprintf(arqAss,"\tsubu $sp, $sp, %d\n",tamanhoQuadro+8);
        fprintf(arqAss,"\tsw $ra, %d($sp)\n", tamanhoQuadro);
        fprintf(arqAss,"\tsw $fp, %d($sp)\n", tamanhoQuadro+4);
        fprintf(arqAss,"\taddu $fp, $sp, %d\n",tamanhoQuadro);
    }
    else{
        //armazena o deslocamento necessário para os argumentos das chamadas
        fprintf(arqAss,"%s_Prologo:\n",quadroMIPS->rotulo->obterString());
        salvarTodosRegistradores(tamanhoParametros);
        fprintf(arqAss,"\tmove $fp, $sp\n");
        if(tamanhoQuadro) fprintf(arqAss,"\tsubu $sp, $sp, %d\n", tamanhoQuadro);
        fprintf(arqAss,"%s:\n", quadroMIPS->rotulo->obterString());
        //salvarTodosRegistradores(-tamanhoQuadro-NUM_REGISTRADORES-3*4);
        //fprintf(arqAss,"\taddi $fp, $sp, 0\n");
        //fprintf(arqAss,"\tsubu $sp, $sp,%d\n", tamanhoQuadro + QUADRO_BASICO);
        //fprintf(arqAss,"\tj %s\n", quadroMIPS->rotulo->obterString());
        //fprintf(arqAss,"%s:\n", quadroMIPS->rotulo->obterString());
    }
}

Temp* Gerador::visita(ListaExp* lex){ return NULL; }
void Gerador::visita(EXP* e){
    TEMP *t = NULL;
    MEM *m = NULL;
    CALL *call = NULL;
    if(!(e->e && (m = dynamic_cast<MEM*>(e->e)))) {
        if(e->e && (call = dynamic_cast<CALL*>(e->e))){
            NAME *n;
            if(call->f && (n = dynamic_cast<NAME*>(call->f))){
                if(strcmp("printInt", n->n->obterString()) == 0){
                    ListaExp *aux = call->parametros;
                    Temp *reg = aux->exp->aceita(this);
                    fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                    fprintf(arqAss, "\tli $v0, 0x01\n");
                    fprintf(arqAss, "\tsyscall\n");
                    liberaRetistrador(reg);
                }
                else if(strcmp("printReal", n->n->obterString()) == 0){
                    ListaExp *aux = call->parametros;
                    Temp *reg =aux->exp->aceita(this);
                    fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                    fprintf(arqAss, "\tli $v0, 0x02\n");
                    fprintf(arqAss, "\tsyscall\n");
                    liberaRetistrador(reg);
                }
                else if(strcmp("printLiteral", n->n->obterString()) == 0){
                    ListaExp *aux = call->parametros;
                    Temp *reg = aux->exp->aceita(this);
                    fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                    fprintf(arqAss, "\tli $v0, 0x04\n");
                    fprintf(arqAss, "\tsyscall\n");
                    liberaRetistrador(reg);
                }
                else if(strcmp("printCaractere", n->n->obterString()) == 0) {
                    ListaExp *aux = call->parametros;
                    Temp *reg = aux->exp->aceita(this);
                    fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                    fprintf(arqAss, "\tli $v0, 0x0B\n");
                    fprintf(arqAss, "\tsyscall\n");
                    liberaRetistrador(reg);
                }
                else if(strcmp("readlnInt", n->n->obterString()) == 0){
                    ListaExp *aux = call->parametros;
                    Temp *reg = aux->exp->aceita(this);
                    fprintf(arqAss, "\tli $v0,0x05\n");
                    fprintf(arqAss, "\tsyscall\n");
                    fprintf(arqAss, "\tsw $v0, 0(%s)\n", reg->obterString());
                    liberaRetistrador(reg);
                }
                else if(strcmp("readlnReal", n->n->obterString()) == 0){
                    ListaExp *aux = call->parametros;
                    Temp *reg = aux->exp->aceita(this);
                    fprintf(arqAss, "\tli $v0,0x06\n");
                    fprintf(arqAss, "\tsyscall\n");
                    fprintf(arqAss, "\tsw $f0, 0(%s)\n", reg->obterString());
                    liberaRetistrador(reg);
                }else if(e->e)liberaRetistrador(e->e->aceita(this));
            }
        } else {
            if(e->e)liberaRetistrador(e->e->aceita(this));
        }
    }
}
Temp* Gerador::visita(ESEQ *e){ return NULL; }

Temp* Gerador::visita(CONST* c){
    Temp *t = pegaRegistradorLivre();
    fprintf(arqAss, "\tli %s, %d\n", t->obterString(), c->ci);
    return t;
}
Temp* Gerador::visita(CONSTF* c){
    Temp *t = pegaRegistradorLivre();
    fprintf(arqAss, "\tli %s, %d\n", t->obterString(), (int)c->cf);
    return t;
}
Temp* Gerador::visita(NAME* n){
    Temp *r = pegaRegistradorLivre();
    fprintf(arqAss, "\tla %s %s\n", r->obterString(), n->n->obterString());
    return r;
}
Temp* Gerador::visita(TEMP* t){
    if(!registradorReservado(t->t)){
        if(registradorValido(t->t)){
            return t->t;
        }else{
            Temp *tAux = pegaRegistradorLivre();
            fprintf(stdout,"Substituiu %s por %s\n",t->t->obterString(),tAux->obterString());///tem que tirar esse print depois
            *t->t=*tAux;
            free(tAux);
            return t->t;
        }
    }else return t->t;
}
Temp* Gerador::visita(BINOP* b){
     Temp *r = pegaRegistradorLivre();
    if(b->op == OP_ADD){
        CONST *c1, *c2;
        if(b->e1 && (c1 = dynamic_cast<CONST*>(b->e1))){
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss, "\taddi %s,%s,%d\n", r->obterString(), t2->obterString(), c1->ci);
            liberaRetistrador(t2);
        }else if(b->e2 && (c2 = dynamic_cast<CONST*>(b->e2))){
            Temp *t1 = b->e1->aceita(this);
            fprintf(arqAss,"\taddi %s,%s,%d\n", r->obterString(), t1->obterString(), c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1 = b->e1->aceita(this);
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss,"\tadd %s,%s,%s\n", r->obterString(), t1->obterString(), t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op == OP_MUL){
        CONST *c1, *c2;
        if(b->e1 && (c1 = dynamic_cast<CONST*>(b->e1))){
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss, "\tmul %s,%s,%d\n", r->obterString(), t2->obterString(), c1->ci);
            liberaRetistrador(t2);
        }else if(b->e2 && (c2 = dynamic_cast<CONST*>(b->e2))){
            Temp *t1 = b->e1->aceita(this);
            fprintf(arqAss, "\tmul %s,%s,%d\n", r->obterString(), t1->obterString(), c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1 = b->e1->aceita(this);
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss, "\tmul %s,%s,%s\n", r->obterString(), t1->obterString(), t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op == OP_DIV){
        CONST *c2;
        if(b->e2 && (c2 = dynamic_cast<CONST*>(b->e2))){
            Temp *t1 =b->e1->aceita(this);
            fprintf(arqAss,"\tdiv %s,%s,%d\n",r->obterString(),t1->obterString(),c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1 = b->e1->aceita(this);
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss,"\tdiv %s,%s,%s\n",r->obterString(),t1->obterString(),t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op==OP_SUB){
        CONST *c2;
        if(b->e2 && (c2 = dynamic_cast<CONST*>(b->e2))){
            Temp *t1 = b->e1->aceita(this);
            fprintf(arqAss, "\taddi %s,%s,%d\n", r->obterString(), t1->obterString(), -c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1 = b->e1->aceita(this);
            Temp *t2 = b->e2->aceita(this);
            fprintf(arqAss, "\tsub %s,%s,%s\n", r->obterString(), t1->obterString(), t2->obterString());
            liberaRetistrador(t1);
        }
    }
    return r;
}
Temp* Gerador::visita(MEM* m){
    Temp *r = pegaRegistradorLivre();
    BINOP *bop;
    if(m->e && (bop = dynamic_cast<BINOP*>(m->e)) && bop->op == OP_ADD){
        CONST *c1, *c2;
        if(bop->e1 && (c1 = dynamic_cast<CONST*>(bop->e1))){
            Temp *base = bop->e2->aceita(this);
            fprintf(arqAss, "\tlw %s, %d(%s)\n", r->obterString(), c1->ci, base->obterString());
            liberaRetistrador(base);
        }else if(bop->e2 && (c2 = dynamic_cast<CONST*>(bop->e2))){
            Temp* base = bop->e1->aceita(this);
            fprintf(arqAss, "\tlw %s, %d(%s)\n", r->obterString(), c2->ci, base->obterString());
            liberaRetistrador(base);
        }else{
            Temp* base = bop->aceita(this);
            fprintf(arqAss, "\tlw %s, 0(%s)\n", r->obterString(), base->obterString());
            liberaRetistrador(base);
        }

    }else{
        NAME *n;
        if(m->e && (n = dynamic_cast<NAME*>(m->e)))
            fprintf(arqAss, "\tlw %s, %s(%d)\n", r->obterString(), n->n->obterString(), 0);
        else{
			Temp* base =m->e->aceita(this);
            fprintf(arqAss, "\tlw %s, 0(%s)\n", r->obterString(), base->obterString());
            liberaRetistrador(base);
        }
    }
    return r;
}
Temp* Gerador::visita(CALL* call){
	NAME *n;
	Temp *r = pegaRegistradorLivre();
	if(call->f && (n = dynamic_cast<NAME*>(call->f))){
        if(strcmp("mfhi", n->n->obterString()) == 0){
            ListaExp *aux = call->parametros;
            Temp *reg = aux->exp->aceita(this);
            fprintf(arqAss, "\tmfhi %s\n",r->obterString());
            liberaRetistrador(reg);
			return r;
		}
		else{
		    ListaExp *l = NULL, *aux = call->parametros;
		    int i = 0;
		    while(aux){
                l = new ListaExp(aux->exp, l);
                aux = aux->proximoExp;
                i++;
		    }
		    aux = l;
		    int deslocamento = i*4;
		    fprintf(arqAss, "\t#Pre-Chamada\n\tsubu $sp, $sp, %d\n", deslocamento+QUADRO_BASICO);
		    i = 0;
		    while(aux){
                Temp *param  = aux->exp->aceita(this);
                if(i<4){
                    fprintf(arqAss,"\tmove $a%d, %s\n", i, param->obterString());
                }
                fprintf(arqAss,"\tsw %s, %d($sp)\n", param->obterString(), i*PALAVRA);
                liberaRetistrador(param);
                aux = aux->proximoExp;
                i++;
		    }
		    fprintf(arqAss, "\tjal %s_Prologo\n", n->n->obterString());
            fprintf(arqAss, "\tmove %s,$v0\n", r->obterString());
            fprintf(arqAss, "\t#Pos-Chamada\n\taddu $sp, $sp, %d\n", deslocamento+QUADRO_BASICO);
            return r;
		}
	}
	return r;
}
void Gerador::visita(ListaStm* lstm){

}
void Gerador::visita(MOVE* mov){
    MEM *m;
    CALL * call;
	TEMP *t = dynamic_cast<TEMP*>(mov->e1);
	if(mov->e1 && (m = dynamic_cast<MEM*>(mov->e1))){
        BINOP *bop;
        if(m->e && (bop = dynamic_cast<BINOP*>(m->e)) && bop->op == OP_ADD){
            CONST *const1;
            Temp *t1 = NULL;
            if(bop->e1 && (const1 = dynamic_cast<CONST*>(bop->e1)))
                t1 = bop->e2->aceita(this);
            else if(bop->e2 && (const1 = dynamic_cast<CONST*>(bop->e2)))
                t1 = bop->e1->aceita(this);
            if(const1 && t1){
				Temp *org = mov->e2->aceita(this);
                fprintf(arqAss, "\tsw %s, %d(%s)\n", org->obterString(), const1->ci, t1->obterString());
                liberaRetistrador(t1);
                liberaRetistrador(org);
            }else{
                Temp *org = mov->e2->aceita(this);
                Temp *dest= m->e->aceita(this);
                fprintf(arqAss, "\tsw %s, %d(%s)\n", org->obterString(), 0, dest->obterString());
                liberaRetistrador(org);
                liberaRetistrador(dest);
            }

        }else{
            NAME *name;
            Temp *org = mov->e2->aceita(this);
            if(m->e && (name = dynamic_cast<NAME*>(m->e)))
                fprintf(arqAss, "\tsw %s, %s(%d)\n", org->obterString(), name->n->obterString(), 0);
            else{
                Temp *r = m->e->aceita(this);
                fprintf(arqAss, "\tsw %s, %d(%s)\n", org->obterString(), 0, r->obterString());
                liberaRetistrador(r);
            }
            liberaRetistrador(org);
        }
	}else if(t){
        CONST *c;
        NAME *nome;
        if(mov->e2 && (c = dynamic_cast<CONST*>(mov->e2))){
            t->t= mov->e1->aceita(this);
            fprintf(arqAss, "\tli %s,%d\n", t->t->obterString(), c->ci);
        }
        else if(mov->e2 && (nome = dynamic_cast<NAME*>(mov->e2))){
              t->t= mov->e1->aceita(this);
              fprintf(arqAss, "\tla %s,%s\n", t->t->obterString(), nome->n->obterString());
        }
        else if(mov->e2 && (call = dynamic_cast<CALL*>(mov->e2))){
                NAME *n;
                if(call->f && (n = dynamic_cast<NAME*>(call->f))){
                    if(strcmp("printInt", n->n->obterString()) == 0){
                        ListaExp *aux = call->parametros;
                        Temp *reg = aux->exp->aceita(this);
                        fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                        fprintf(arqAss, "\tli $v0, 0x01\n");
                        fprintf(arqAss, "\tsyscall\n");
                        liberaRetistrador(reg);
                    }
                    else if(strcmp("printReal", n->n->obterString()) == 0){
                        ListaExp *aux = call->parametros;
                        Temp *reg =aux->exp->aceita(this);
                        fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                        fprintf(arqAss, "\tli $v0, 0x02\n");
                        fprintf(arqAss, "\tsyscall\n");
                        liberaRetistrador(reg);
                    }
                    else if(strcmp("printLiteral", n->n->obterString()) == 0){
                        ListaExp *aux = call->parametros;
                        Temp *reg = aux->exp->aceita(this);
                        fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                        fprintf(arqAss, "\tli $v0, 0x04\n");
                        fprintf(arqAss, "\tsyscall\n");
                        liberaRetistrador(reg);
                    }
                    else if(strcmp("printCaractere", n->n->obterString()) == 0) {
                        ListaExp *aux = call->parametros;
                        Temp *reg = aux->exp->aceita(this);
                        fprintf(arqAss, "\tmove $a0, %s\n", reg->obterString());
                        fprintf(arqAss, "\tli $v0, 0x0B\n");
                        fprintf(arqAss, "\tsyscall\n");
                        liberaRetistrador(reg);
                    }
                    else if(strcmp("readlnInt", n->n->obterString()) == 0){
                        ListaExp *aux = call->parametros;
                        Temp *reg = aux->exp->aceita(this);
                        fprintf(arqAss, "\tli $v0,0x05\n");
                        fprintf(arqAss, "\tsyscall\n");
                        fprintf(arqAss, "\tsw $v0, 0(%s)\n", reg->obterString());
                        liberaRetistrador(reg);
                    }
                    else if(strcmp("readlnReal", n->n->obterString()) == 0){
                        ListaExp *aux = call->parametros;
                        Temp *reg = aux->exp->aceita(this);
                        fprintf(arqAss, "\tli $v0,0x06\n");
                        fprintf(arqAss, "\tsyscall\n");
                        fprintf(arqAss, "\tsw $f0, 0(%s)\n", reg->obterString());
                        liberaRetistrador(reg);
                    }
                    else{
                        t->t= mov->e1->aceita(this);
                        Temp *aux = mov->e2->aceita(this);
                        fprintf(arqAss, "\tmove %s, %s\n", t->t->obterString(), aux->obterString());
                        liberaRetistrador(aux);
                    }
                }

        }else {
            t->t= mov->e1->aceita(this);
            Temp *aux = mov->e2->aceita(this);
            fprintf(arqAss, "\tmove %s,%s\n", t->t->obterString(), aux->obterString());
            liberaRetistrador(aux);
        }
	}
}
void Gerador::visita(JUMP* j){
    NAME *n;
    if(j->e && (n=dynamic_cast<NAME*>(j->e)))
        fprintf(arqAss, "\tj %s\n", n->n->obterString());
    else{
        Temp *t = j->e->aceita(this);
        fprintf(arqAss, "\tjr %s\n", t->obterString());
        liberaRetistrador(t);
    }
}
void Gerador::visita(CJUMP* cjp){
	char parte1[16], parte2[16];
	switch (cjp->op) {
		case OP_EQ:
			sprintf(parte1, "beq ");
			break;
		case OP_NEQ:
			sprintf(parte1, "bne ");
			break;
		case OP_GT:
			sprintf(parte1, "bgt ");
			break;
		case OP_GE:
			sprintf(parte1, "bge ");
			break;
		case OP_LT:
			sprintf(parte1, "blt ");
			break;
		case OP_LE:
			sprintf(parte1, "ble ");
			break;
	}
	/*CONST *c1, *c2;
	CONSTF *cf1, *cf2;
    if(cjp->e1 && ((c1 = dynamic_cast<CONST*>(cjp->e1)) || (cf1 = dynamic_cast<CONSTF*>(cjp->e1)))){
        Temp *t = cjp->e2->aceita(this);
        if(c1) sprintf(parte2, "%s, %d ", t->obterString(), c1->ci);
        liberaRetistrador(t);
	}
	else if(cjp->e2 && ((c2 = dynamic_cast<CONST*>(cjp->e2)) || (cf2 = dynamic_cast<CONSTF*>(cjp->e2)))){
        Temp *t = cjp->e1->aceita(this);
        if(c2) sprintf(parte2, "%s, %d ", t->obterString(), c2->ci);
        liberaRetistrador(t);
	}*/
	//else{

        Temp *t = cjp->e1->aceita(this);
        Temp *t2 = cjp->e2->aceita(this);
        sprintf(parte2, " %s, %s, ", t->obterString(), t2->obterString());
        liberaRetistrador(t);
        liberaRetistrador(t2);
	//}
	//fprintf(stdout,"%s\n",parte1);
    fprintf(arqAss, "\t%s%s%s\n", parte1, parte2, cjp->verdadeiro->obterString());
    fprintf(arqAss, "\tj %s\n", cjp->falso->obterString());
}
void Gerador::visita(SEQ* s){
    if(s->s1) s->s1->aceita(this);
    if(s->s2) s->s2->aceita(this);
}
void Gerador::visita(LABEL* l){
    fprintf(arqAss, "%s:\n", l->n->obterString());
}
