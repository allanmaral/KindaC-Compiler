#include "VisitanteRI.h"
#include "RepresentacaoIntermadiaria.h"
typedef struct FilaRegistrador;

class Gerador: public VisitanteRI{
    private:
        FilaRegistrador* primeiroRegLivre;
        void liberaRetistrador(Temp *t);
        Temp* pegaRegistradorLivre();
        FILE *arqAss;
        void salvarTodosRegistradores(int offset);
        void recuperarTodosRegistradores(int offset);
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
          void visita(CONST *c);
          void visita(CONSTF *cf);
          void visita(NAME *n);
          void visita(TEMP *t);
          void visita(BINOP *bop);
          void visita(MEM *m);
          void visita(CALL *ca);
          void visita(ESEQ *es);
          //Visita especializa��es de Stm
          void visita(ListaStm *lstm);
          void visita(MOVE *mo);
          void visita(EXP *ex);
          void visita(JUMP *jp);
          void visita(CJUMP *cjp);
          void visita(SEQ *se);
          void visita(LABEL *l);
};
