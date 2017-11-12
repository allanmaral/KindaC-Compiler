#include "RepresentacaoIntermadiaria.h"
#include "VisitanteRI.h"

#include <stdio.h>
#include <string.h>

Fragmento::Fragmento() : proximoFragmento(NULL) {}

Fragmento::~Fragmento(){};

Procedimento::Procedimento(Frame* frame, Stm* corpo) : frame(frame), corpo(corpo) {}

Procedimento::~Procedimento(){
    delete frame;
    delete corpo;
    delete proximoFragmento;
}

void Fragmento::aceita(VisitanteRI *vri){
    vri->visita(this);
}

Literal::Literal(char* literal) : literal(literal) {
    // CRIA UM NOVO ROTULO
}

Literal::~Literal(){
    delete literal;
    delete proximoFragmento;
}

void Literal::aceita(VisitanteRI* vri){
    vri->visita(this);
}

Variavel::Variavel(Atributo *tipo, int tamanho) : tipo(tipo), tamanho(tamanho) {}

Variavel::~Variavel(){}

void Variavel::aceita(VisitanteRI *vri){
    vri->visita(this);
}

int Temp::contador = 0;

Temp::Temp(){
    temp = new char[32];
    sprintf(temp, "temp$%d", contador++);
}

Temp::Temp(char *_temp) : temp(_temp) {
    temp = new char[strlen(_temp)+1];
    strcpy(this->temp, _temp);
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
    rotulo = new char[32];
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

ListaAcesso::ListaAcesso(AcessoLocal *acessoLocal,ListaAcesso *proximoAcesso)
    : acessoLocal(acessoLocal), proximoAcesso(proximoAcesso) {}

ListaAcesso::~ListaAcesso() {
    delete acessoLocal;
    delete proximoAcesso;
}

void ListaAcesso::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

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
    //TODO
}

AcessoLocal *FrameMIPS::insereLocal(bool escapa, int deslocamento) {
    //TODO
}

void FrameMIPS::aceita(VisitanteRI *vri) {
    vri->visita(this);
}

/*NoFrame::NoFrame(int deslocamento) : deslocamento(deslocamento) {
    exp = new MEM(new BINOP(OP_SUB, new TEMP(new Temp("$fp")), new CONST(deslocamento)));
}

NoFrame::~NoFrame() {
    delete exp;
}

void NoFrame::aceita(VisitanteRI *vri) {
    vri->visita(this);
}*/

