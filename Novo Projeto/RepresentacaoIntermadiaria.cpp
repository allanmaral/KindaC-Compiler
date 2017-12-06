#include "RepresentacaoIntermadiaria.h"
#include "VisitanteRI.h"

#include <stdio.h>
#include <string.h>

Fragmento::Fragmento() : proximoFragmento(NULL) {}

Fragmento::~Fragmento(){};

void Fragmento::InsereLista(Fragmento* frag) {
    Fragmento *ultimo = this;
    while(ultimo->proximoFragmento) ultimo = ultimo->proximoFragmento;
    ultimo->proximoFragmento = frag;
}

Procedimento::Procedimento(Frame* frame, Stm* corpo) : frame(frame), corpo(corpo) {}

Procedimento::~Procedimento(){
    delete frame;
    delete corpo;
    delete proximoFragmento;
}
void Procedimento::aceita(VisitanteRI *vri) {
    vri->visita(this);
}
void Fragmento::aceita(VisitanteRI *vri){
    vri->visita(this);
}
Literal::Literal(char* literal) : literal(literal) {
    rotulo = new Rotulo();
}

Literal::Literal(char *literal, Rotulo *rotulo) : literal(literal), rotulo(rotulo) { }

Literal::~Literal(){
    delete proximoFragmento;
    delete rotulo;
}
void Literal::aceita(VisitanteRI* vri){
    vri->visita(this);
}

Variavel::Variavel(Tipo *tipo, int tamanho, Rotulo *rotulo)
    : tipo(tipo), tamanho(tamanho), rotulo(rotulo) {}

Variavel::~Variavel(){}

void Variavel::aceita(VisitanteRI *vri){
    vri->visita(this);
}

int Temp::contador = 0;

Temp::Temp(){
    temp = new char[32];
    sprintf(temp, "$temp%d", contador++);
}
Temp::Temp(char *_temp) : temp(_temp) {
    this->temp = new char[strlen(_temp)+2];
    strcpy((this->temp)+1, _temp);
    this->temp[0] = '$';

}
Temp::~Temp(){
    delete temp;
}
const char* Temp::obterString() {
    return temp;
}
void Temp::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

ListaTemp::ListaTemp(Temp *temp, ListaTemp *proximoTemp) : temp(temp), proximoTemp(proximoTemp) {}

ListaTemp::~ListaTemp() {
    delete temp;
    delete proximoTemp;
}
void ListaTemp::aceita(VisitanteRI *vri){
    vri->visita(this);
}

int Rotulo::contador = 0;

Rotulo::Rotulo() {
    rotulo = new char[19]; // Tamanho maximo 8: "rotulo$" + 10: max int + 1: '\0'
    sprintf(rotulo, "rotulo$%d", contador++);
}
Rotulo::Rotulo(char *rotulo) {
    this->rotulo = new char[strlen(rotulo) + 1];
    strcpy(this->rotulo, rotulo);
}
Rotulo::~Rotulo() {
    delete rotulo;
}
const char* Rotulo::obterString() {
    return rotulo;
}
void Rotulo::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

ListaRotulo::ListaRotulo(Rotulo *rotulo,ListaRotulo *proximoRotulo)
    : rotulo(rotulo), proximoRotulo(proximoRotulo){}

ListaRotulo::~ListaRotulo() {
    delete rotulo;
    delete proximoRotulo;
}
void ListaRotulo::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

AcessoLocal::AcessoLocal() {};

AcessoLocal::~AcessoLocal() {};

ListaAcesso::ListaAcesso(AcessoLocal *acessoLocal,ListaAcesso *proximoAcesso)
    : acessoLocal(acessoLocal), proximoAcesso(proximoAcesso) {}

ListaAcesso::~ListaAcesso() {
    delete acessoLocal;
    delete proximoAcesso;
}
void ListaAcesso::aceita(VisitanteRI *vri) {
    vri->visita(this);
}
Frame::Frame(){}
Frame::~Frame(){}

FrameMIPS::FrameMIPS(Rotulo *rotulo, ListaAcesso *variaveisLocais, int desVarLocais, int desParametros)
                     : rotulo(rotulo), variaveisLocais(variaveisLocais), numeroParametros(0),
                       deslocamentoVariaveisLocais(desVarLocais), deslocamentoParametros(desParametros) {
    tempRetorno = new Temp();
}
FrameMIPS::~FrameMIPS() {
    delete rotulo;
    delete tempRetorno;
    delete variaveisLocais;
}
AcessoLocal *FrameMIPS::insereParametro(bool escapa, int deslocamento) {
    AcessoLocal* acesso = NULL;
    // Quatro primeiros parametros são colocados em registadores (se nao escaparem)
    if(numeroParametros <= 3 ) {
        if(escapa) acesso = new NoFrame(deslocamento);
        else acesso = new NoRegistrador(new Temp());
    } else {
        acesso = new NoFrame(deslocamento);
    }

    if(variaveisLocais) {
        ListaAcesso *t = variaveisLocais;
        while(t->proximoAcesso) t = t->proximoAcesso;
        t->proximoAcesso = new ListaAcesso(acesso, NULL);
    } else {
        variaveisLocais = new ListaAcesso(acesso, NULL);
    }
    numeroParametros++;
    return acesso;
}
AcessoLocal *FrameMIPS::insereLocal(bool escapa, int deslocamento) {
    AcessoLocal *acesso = NULL;
    if(escapa) acesso = new NoFrame(-deslocamento);
    else acesso = new NoRegistrador(new Temp());
    if(variaveisLocais) {
        ListaAcesso *t = variaveisLocais;
        while(t->proximoAcesso) t = t->proximoAcesso;
        t->proximoAcesso = new ListaAcesso(acesso, NULL);
    } else {
        variaveisLocais = new ListaAcesso(acesso, NULL);
    }
    return acesso;
}
void FrameMIPS::aceita(VisitanteRI *vri) {
    vri->visita(this);
}
NoFrame::NoFrame(int deslocamento) : deslocamento(deslocamento) {
    exp = new MEM(new BINOP(OP_ADD, new TEMP(new Temp((char*)"fp")), new CONST(deslocamento)));
}
NoFrame::~NoFrame() {
    delete exp;
}
Exp *NoFrame::codigoAcesso() {
    return exp;
}
void NoFrame::aceita(VisitanteRI *vri) {
    vri->visita(this);
}
NoRegistrador::NoRegistrador(Temp *temp) : temp(temp) {
    exp = new TEMP(temp);
}
NoRegistrador::~NoRegistrador() {
    delete temp;
    delete exp;
}
Exp *NoRegistrador::codigoAcesso() {
    return exp;
}
void NoRegistrador::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

///## MAQUINA ABSTRATA
///######################
Exp::~Exp() {}

ListaExp::ListaExp(Exp *exp, ListaExp *proximoExp) : exp(exp), proximoExp(proximoExp) { }

ListaExp::~ListaExp(){
    delete exp;
    delete proximoExp;
}
void ListaExp::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

CONST::CONST(int ci) : ci(ci) { }

CONST::~CONST() { }

void CONST::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

CONSTF::CONSTF(float cf) : cf(cf) { }

CONSTF::~CONSTF() { }

void CONSTF::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

NAME::NAME(Rotulo *n) : n(n) {}

NAME::~NAME() {}

void NAME::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

TEMP::TEMP(Temp *t) : t(t) { }

TEMP::~TEMP() { }

void TEMP::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

BINOP::BINOP(int op, Exp *e1, Exp *e2) : op(op), e1(e1), e2(e2) { }

BINOP::~BINOP() {
    delete e1;
    delete e2;
}
void BINOP::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

MEM::MEM(Exp *e) : e(e) {}

MEM::~MEM() {
    delete e;
}
void MEM::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

CALL::CALL(Exp *f, ListaExp *parametros) : f(f), parametros(parametros) { }

CALL::~CALL() {
    delete f;
    delete parametros;
}
void CALL::aceita(VisitanteRI *vri) {
    vri->visita(this);
}
ESEQ::ESEQ(Stm *sentenca, Exp *exp){
    this->s=sentenca;
    this->e=exp;
}
ESEQ::~ESEQ(){
    delete s;
    delete e;
}
void ESEQ::aceita(VisitanteRI *vri){
    vri->visita(this);
}

Stm::~Stm() {}

ListaStm::ListaStm(Stm *stm, ListaStm *proximoStm){
    this->stm=stm;
    this->proximoStm=proximoStm;
}
ListaStm::~ListaStm(){
    delete stm;
    delete proximoStm;
}
void ListaStm::aceita(VisitanteRI *vri){
    vri->visita(this);
}
MOVE::MOVE(Exp *e1, Exp *e2){
    this->e1=e1;
    this->e2=e2;
}
MOVE::~MOVE(){
    delete e1;
    delete e2;
}
void MOVE::aceita(VisitanteRI *vri){
    vri->visita(this);
}
EXP::EXP(Exp *e){
    this->e=e;
}
EXP::~EXP(){
    delete e;
}
void EXP::aceita(VisitanteRI *vri){
    vri->visita(this);
}
JUMP::JUMP(Exp *e){
    this->e=e;
}
JUMP::~JUMP(){
    delete e;
}
void JUMP::aceita(VisitanteRI *vri){
    vri->visita(this);
}
CJUMP::CJUMP(int op, Exp *e1, Exp *e2, Rotulo *verdadeiro, Rotulo *falso){
    this->op=op;
    this->e1=e1;
    this->e2=e2;
    this->verdadeiro=verdadeiro;
    this->falso=falso;
}
CJUMP::~CJUMP(){
    delete e1;
    delete e2;
    delete verdadeiro;
    delete falso;
}
void CJUMP::aceita(VisitanteRI *vri){
    vri->visita(this);
}
SEQ::SEQ(Stm *s1, Stm *s2){
    this->s1=s1;
    this->s2=s2;
}
SEQ::~SEQ(){
    delete s1;
    delete s2;
}
void SEQ::aceita(VisitanteRI *vri){
    vri->visita(this);
}
LABEL::LABEL(Rotulo *n){
    this->n=n;
}
LABEL::~LABEL(){
    delete n;
}
void LABEL::aceita(VisitanteRI *vri){
    vri->visita(this);
}
