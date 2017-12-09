#ifndef GERADOR_H
#define GERADOR_H
#include <stdio.h>


class Tipo;
class Atributo;
class AtributoFuncao;

class VisitanteRI;

class Fragmento;
class Procedimento;
class Literal;
class Variavel;

///## Frame
///######################
class Temp;
class ListaTemp;
class Rotulo;
class ListaRotulo;

class AcessoLocal;
class ListaAcesso;

class Frame;
class FrameMIPS;

class NoFrame;
class NoRegistrador;


///## MAQUINA ABSTRATA
///######################
/// Classes abstratas
class Exp;
class Stm;

/// Especializações de Exp
class ListaExp;
class CONST;
class CONSTF;
class NAME;
class TEMP;
class BINOP;
class MEM;
class CALL;
class ESEQ;

/// Especializações de Stm
class ListaStm;
class MOVE;
class EXP;
class JUMP;
class CJUMP;
class SEQ;
class LABEL;

struct FilaRegistrador;
class Gerador {
    private:
        FILE *arqAss;
        FilaRegistrador* primeiroRegLivre;
        void liberaRetistrador(Temp *t);
        Temp* pegaRegistradorLivre();
        void salvarTodosRegistradores(int offset);
        void recuperarTodosRegistradores(int offset);
    public:
          Gerador(char *nomeArquivo);
          ~Gerador();
          void visita(Fragmento *f);
          void visita(Procedimento *p);
          void visita(Literal *l);
          void visita(Variavel *var);
          void visita(FrameMIPS *quadroMIPS);

          ///Metodos visita para MAQUINA ABSTRATA
          //Visita especializa��es de Exp
          Temp* visita(ListaExp* lex);
          void visita(Exp *e);
          Temp* visita(CONST *c);
          Temp* visita(CONSTF *cf);
          Temp* visita(NAME *n);
          Temp* visita(TEMP *t);
          Temp* visita(BINOP *bop);
          Temp* visita(MEM *m);
          Temp* visita(CALL *ca);
          Temp* visita(ESEQ *e);
          //Visita especializa��es de Stm
          void visita(ListaStm *lstm);
          void visita(MOVE *mo);
          void visita(EXP *ex);
          void visita(JUMP *jp);
          void visita(CJUMP *cjp);
          void visita(SEQ *se);
          void visita(LABEL *l);
};
#endif
