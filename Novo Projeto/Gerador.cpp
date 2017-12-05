#include "Gerador.h"
#include <string.h>
#define NUM_REGISTRADORES 16

typedef struct FilaRegistrador{
    Temp *reg;
    FilaRegistrador *proximo;
}FilaRegistrador;

static char registradores [16][4]{
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$t8",
    "$t9",
};
Gerador::Gerador():arqAss(NULL),primeiroRegLivre(NULL),r0(new Temp("$r0")){}

void Gerador::liberaRetistrador(Temp *t){
    FilaRegistrador * liberado = new FilaRegistrador();
    liberado->reg=t;
    liberado->proximo=primeiroRegLivre;
    primeiroRegLivre=liberado;
};
Temp* Gerador::pegaRegistradorLivre(){
    if(primeiroRegLivre){
        Temp* t= primeiroRegLivre->reg;
        FilaRegistrador *prox= primeiroRegLivre->proximo;
        delete primeiroRegLivre;
        primeiroRegLivre=prox;
        return t;
    }else return NULL;
};

void Gerador::inicializa(char *nomeArquivo){
    arqAss = fopen(nomeArquivo,"w+");
    primeiroRegLivre = new FilaRegistrador();
    for(int i=0; i<NUM_REGISTRADORES;i++){
        liberaRetistrador(new Temp(registradores[i]));
    }
}

void Gerador::salvarTodosRegistradores(int offset){
    for(int i=0;i<NUM_REGISTRADORES;i++){
        fprintf(arqAss,"sw %s,%d($sp)\n",registradores[i],offset);
        offset+=4;
    }
    fprintf(arqAss,"sw $fp,%d($sp)\n",offset);
    offset+=4;
    fprintf(arqAss,"sw $t0,%d($sp)\n",offset);
    offset+=4;
    fprintf(arqAss,"sw $ra,%d($sp)\n",offset);

};
void Gerador::recuperarTodosRegistradores(int offset){
    for(int i=0;i<NUM_REGISTRADORES;i++){
        fprintf(arqAss,"lw %s,%d($sp)\n",registradores[i],offset);
        offset+=4;
    }
    fprintf(arqAss,"lw $fp,%d($sp)\n",offset);
    offset+=4;
    fprintf(arqAss,"lw $t0,%d($sp)\n",offset);
    offset+=4;
    fprintf(arqAss,"lw $ra,%d($sp)\n",offset);
};

void Gerador::visita(Literal* l){
    fprintf(arqAss, ".rdata\nLiteral_%d:\n.asciiz %s\n", l->rotulo, l->literal);
};
void Gerador::visita(Variavel* v){
    fprintf(arqAss, ".data\n");
    fprintf(arqAss,"var_%s: ",v->rotulo);
    fprintf(arqAss,".space %d\n",v->tamanho);
}
Temp* Gerador::visita(TEMP* t){
    return t->t;
};

Temp* Gerador::visita(CONST* c){
    if(c->ci==0){
        return r0;
    }else{
        Temp *t=pegaRegistradorLivre();
        fprintf(arqAss,"li %s, %d\n",t->obterString(),c->ci);
        return t;
    }
}
Temp* Gerador::visita(CONSTF* c){
	if(c->cf==0.0){
        return r0;
    }else{
        Temp *t=pegaRegistradorLivre();
        fprintf(arqAss,"li %s, %d\n",t->obterString(),(int)c->cf);
        return t;
    }
}
Temp* Gerador::visita(NAME* n){
    Temp * r=pegaRegistradorLivre();
    fprintf(arqAss,"la %s %s\n",r->obterString(),n->n);
    return r;
}
void Gerador::visita(JUMP* j){
    NAME *n=dynamic_cast<NAME*>(j->e);
    if(n)
        fprintf(arqAss,"b %s\n",n->n->obterString());
    else{
        Temp *t;//=j->e->aceita(this); colocar o aceita nos bagulhete
        fprintf(arqAss,"jr %s\n",t->obterString());
        liberaRetistrador(t);
    }
}
void Gerador::visita(LABEL* l){
    fprintf(arqAss, "%s:\n", l->n->obterString());
}
void Gerador::visita(Exp* e){
    //liberaRetistrador(e->e->aceita(this));
}
void Gerador::visita(SEQ* s){
	//s->s1->aceita(this);
    //s->s2->aceita(this);
}
Temp* Gerador::visita(BINOP* b){
     Temp *r=pegaRegistradorLivre();
    if(b->op==OP_ADD){
         CONST *c1= dynamic_cast<CONST*>(b->e1),*c2= dynamic_cast<CONST*>(b->e2);;
        if(c1){
            Temp *t2;//=b->e2->accept(this);
            fprintf(arqAss,"addi %s,%s,%d\n",r->obterString(),t2->obterString(),c1->ci);
            liberaRetistrador(t2);
        }else if(c2){
            Temp *t1;//=b->e1->aceita(this);
            fprintf(arqAss,"addi %s,%s,%d\n",r->obterString(),t1->obterString(),c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1;//=b->e1->aceita(this);
            Temp *t2;//=b->e2->aceita(this);
            fprintf(arqAss,"add %s,%s,%s\n",r->obterString(),t1->obterString(),t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op==OP_MUL){
         CONST *c1= dynamic_cast<CONST*>(b->e1),*c2= dynamic_cast<CONST*>(b->e2);;
        if(c1){
            Temp *t2;//=b->e2->aceita(this);
            fprintf(arqAss,"mul %s,%s,%d\n",r->obterString(),t2->obterString(),c1->ci);
            liberaRetistrador(t2);
        }else if(c2){
            Temp *t1;//=b->e1->accept(this);
            fprintf(arqAss,"mul %s,%s,%d\n",r->obterString(),t1->obterString(),c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1;//=b->e1->aceita(this);
            Temp *t2;//=b->e2->aceita(this);
            fprintf(arqAss,"mul %s,%s,%s\n",r->obterString(),t1->obterString(),t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op==OP_DIV){
        CONST *c2= dynamic_cast<CONST*>(b->e2);;
        if(c2){
            Temp *t1;//=b->e1->aceita(this);
            fprintf(arqAss,"div %s,%s,%d\n",r->obterString(),t1->obterString(),c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1;//=b->e1->aceita(this);
            Temp *t2;//=b->e2->aceita(this);
            fprintf(arqAss,"div %s,%s,%s\n",r->obterString(),t1->obterString(),t2->obterString());
            liberaRetistrador(t1);
            liberaRetistrador(t2);
        }
    }
    if(b->op==OP_SUB){
        CONST *c2= dynamic_cast<CONST*>(b->e2);;
        if(c2){
            Temp *t1;//=b->e1->aceita(this);
            fprintf(arqAss,"addi %s,%s,%d\n",r->obterString(),t1->obterString(),-c2->ci);
            liberaRetistrador(t1);
        }else{
            Temp *t1;//=b->e1->aceita(this);
            Temp *t2;//=b->e2->aceita(this);
            fprintf(arqAss,"sub %s,%s,%s\n",r->obterString(),t1->obterString(),t2->obterString());
            liberaRetistrador(t1);
        }
    }
    return r;
}
Temp* Gerador::visita(MEM* m){
    Temp *r=pegaRegistradorLivre();
    BINOP *bop=dynamic_cast<BINOP*>(m->e);
    if(bop && bop->op==OP_ADD){
        CONST *c1=dynamic_cast<CONST*>(bop->e1);
        CONST *c2=dynamic_cast<CONST*>(bop->e2);
        if(c1){
            Temp *base;//=bop->e2->aceita(this);
            fprintf(arqAss, "lw %s, %d(%s)\n",r->obterString(),c1->ci,base->obterString());
            liberaRetistrador(base);

        }else if(c2){
            Temp* base;//=bop->e1->aceita(this);
            fprintf(arqAss, "lw %s, %d(%s)\n",r->obterString(),c2->ci,base->obterString());
            liberaRetistrador(base);
        }else{
            Temp* base;//=bop->aceita(this);
            fprintf(arqAss, "lw %s, 0(%s)\n",r->obterString(),base->obterString());
            liberaRetistrador(base);
        }

    }else{
        NAME *n=dynamic_cast<NAME*>(m->e);
        if(n){
            fprintf(arqAss, "lw %s, %s(%s)\n",r->obterString(),n->n->obterString(),r0->obterString());
        }else {
			Temp* base;//=m->e->aceita(this);
            fprintf(arqAss, "lw %s, 0(%s)\n",r->obterString(),base->obterString());
            liberaRetistrador(base);
        }
    }
    return r;
}
Temp* Gerador::visita(CALL* call){
	NAME *n = dynamic_cast<NAME*>(call->f);
	Temp *r=pegaRegistradorLivre();
	if (n) {
		if (strcmp("printInt", n->n->rotulo)==0) {
			ListaExp *aux=call->parametros;
            Temp *reg;//=aux->e->aceita(this);
            fprintf(arqAss, "move $a0,%s\n",reg->obterString());
            fprintf(arqAss, "li $v0,0x01\n");
            fprintf(arqAss, "syscall\n");
            liberaRetistrador(reg);
            return r;
		}
		else if (strcmp("printReal", n->n->obterString())==0) {
			ListaExp *aux=call->parametros;
            Temp *reg;//=aux->e->aceita(this);
            fprintf(arqAss, "move $a0,%s\n",reg->obterString());
            fprintf(arqAss, "li $v0,0x02\n");
            fprintf(arqAss, "syscall\n");
            liberaRetistrador(reg);
			return r;
		}
		else if (strcmp("printLiteral", n->n->obterString())==0) {
			ListaExp *aux=call->parametros;
            Temp *reg;//=aux->e->aceita(this);
            fprintf(arqAss, "move $a0,%s\n",reg->obterString());
            fprintf(arqAss, "li $v0,0x04\n");
            fprintf(arqAss, "syscall\n");
            liberaRetistrador(reg);
			return r;
		}
		else if (strcmp("readlnInt", n->n->obterString())==0) {
            fprintf(arqAss, "li $v0,0x05\n");
            fprintf(arqAss, "syscall\n");
            fprintf(arqAss, "move %s,$v0\n",r->obterString());
			return r;
		}
		else if (strcmp("readlnFloat", n->n->obterString())==0) {
            fprintf(arqAss, "li $v0,0x06\n");
            fprintf(arqAss, "syscall\n");
            fprintf(arqAss, "move %s,$f0\n",r->obterString());
			return r;
		}
		else{
		    ListaExp *l=NULL,*aux=call->parametros;
		    while(aux){
                l=new ListaExp(aux->exp,l);
                aux=aux->proximoExp;
		    }
		    aux=l;
		    int i=0;
		    while(aux){
                Temp *param;//=aux->e->aceita(this);
                if(i<4){
                    fprintf(arqAss,"move $a%d, %s\n",i,param->obterString());
                }
                fprintf(arqAss,"sw %s, %d($sp)\n",param->obterString(),i*4);
                liberaRetistrador(param);
                aux=aux->proximoExp;
                i++;
		    }
		    fprintf(arqAss, "jal %s\n",n->n->obterString());
            fprintf(arqAss, "move %s,$v0\n",r->obterString());
            return r;
		}
	}

	return r;
}
void Gerador::visita(MOVE* mov){
    MEM *m = dynamic_cast<MEM*>(mov->e2);
	TEMP *t =dynamic_cast<TEMP*>(mov->e2);
	if(m){
        BINOP *bop=dynamic_cast<BINOP*>(m->e);
        if(bop && bop->op==OP_ADD){
            CONST *const1=dynamic_cast<CONST*>(bop->e1);
            Temp * t1=NULL;
            if(const1){
                t1;//=bop->e2->aceita(this);
            }else{
                const1=dynamic_cast<CONST*>(bop->e2);
                if(const1)
                    t1;//=bop->e1->aceita(this);
            }
            if(const1 && t1){
				Temp *org;//=mov->e1->aceita(this);
                fprintf(arqAss, "sw %s, %d(%s)\n",org->obterString(),const1->ci,t1->obterString());
                liberaRetistrador(t1);
                liberaRetistrador(org);
            }else{
                Temp *org;//=mov->e1->aceita(this);
                Temp *dest;//=m->e->aceita(this);
                fprintf(arqAss, "sw %s, %d(%s)\n",org->obterString(),0,dest->obterString());
                liberaRetistrador(org);
                liberaRetistrador(dest);
            }

        }else{
            Temp *org;//=mov->e1->aceita(this);
            NAME *name=dynamic_cast<NAME*>(m->e);
            if(name){
                fprintf(arqAss, "sw %s, %s(%s)\n",org->obterString(),name->n->obterString(),r0->obterString());
            }else{
                Temp *r;//=m->e->accept(this);
                fprintf(arqAss, "sw %s, %d(%s)\n",org->obterString(),0,r->obterString());
                liberaRetistrador(r);
            }
            liberaRetistrador(org);

        }
	}else if(t){
        CONST *c=dynamic_cast<CONST*>(mov->e1);
        NAME *nome=dynamic_cast<NAME*>(mov->e1);
        if(c){
            fprintf(arqAss,"li %s,%d\n",t->t->obterString(),c->ci);
        }else if(nome){
            fprintf(arqAss,"la %s,%s\n",t->t->obterString(),nome->n->obterString());
        }else{
            Temp *aux;//=mov->e1->aceita(this);
            fprintf(arqAss,"move %s,%s\n",t->t->obterString(),aux->obterString());
        }
	}

}

