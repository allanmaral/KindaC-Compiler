#include "Gerador.h"
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
//Gerador::Gerador():arqAss(NULL),primeiroRegLivre(NULL){}

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
}
