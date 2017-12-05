#include "RepresentacaoIntermadiaria.h"
#include <stdio.h>
typedef struct FilaRegistrador;

class Gerador{
    private:
        FilaRegistrador* primeiroRegLivre;
        void liberaRetistrador(Temp *t);
        Temp* pegaRegistradorLivre();
        FILE *arqAss;
        void salvarTodosRegistradores(int offset);
        void recuperarTodosRegistradores(int offset);
        Temp *r0;
    public:
          Gerador();
          ~Gerador();
          void visita(Fragmento *f);
          void visita(Procedimento *p);
          void visita(Literal *l);
          void visita(Variavel *var);
          void inicializa(char *nomeArquivo);

          void visita(Temp *t);
          void visita(ListaTemp *listaTemp);
          void visita(Rotulo *r);
          void visita(ListaRotulo *listaRotulo);
          void visita(ListaAcesso *listaAcesso);
          void visita(AcessoLocal *ac);
          void visita(FrameMIPS *quadroMIPS);
          void visita(NoRegistrador *nr);
          void visita(NoFrame *nq);

          ///Metodos visita para MAQUINA ABSTRATA
          //Visita especializa��es de Exp
          void visita(ListaExp* lex);
          void visita(Exp *e);
          Temp* visita(CONST *c);
          Temp* visita(CONSTF *cf);
          Temp* visita(NAME *n);
          Temp* visita(TEMP *t);
          Temp* visita(BINOP *bop);
          Temp* visita(MEM *m);
          Temp* visita(CALL *ca);
          //Visita especializa��es de Stm
          void visita(ListaStm *lstm);
          void visita(MOVE *mo);
          void visita(EXP *ex);
          void visita(JUMP *jp);
          void visita(CJUMP *cjp);
          void visita(SEQ *se);
          void visita(LABEL *l);
};
