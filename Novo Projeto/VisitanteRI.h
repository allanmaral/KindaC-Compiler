#ifndef VISITANTERI_H
#define VISITANTERI_H
#include "RepresentacaoIntermadiaria.h"
#include "Visitante.h"

class VisitanteRI{
      public:
          virtual ~VisitanteRI(){}
          virtual void visita(Fragmento *f)             = 0;
          virtual void visita(Procedimento *p)          = 0;
          virtual void visita(Literal *l)               = 0;
          virtual void visita(Variavel *var)            = 0;

          virtual void visita(Temp *t)                  = 0;
          virtual void visita(ListaTemp *listaTemp)     = 0;
          virtual void visita(Rotulo *r)                = 0;
          virtual void visita(ListaRotulo *listaRotulo) = 0;
          virtual void visita(ListaAcesso *listaAcesso) = 0;
          virtual void visita(FrameMIPS *quadroMIPS)    = 0;
          virtual void visita(NoFrame *nq)              = 0;
          virtual void visita(NoRegistrador *nr)        = 0;

          ///M�todos visita para MAQUINA ABSTRATA
          //Visita especializa��es de Exp
          virtual void visita(ListaExp *lex)   = 0;
          virtual void visita(CONST *c)        = 0;
          virtual void visita(CONSTF *cf)      = 0;
          virtual void visita(NAME *n)         = 0;
          virtual void visita(TEMP *t)         = 0;
          virtual void visita(BINOP *bop)      = 0;
          virtual void visita(MEM *m)          = 0;
          virtual void visita(CALL *ca)        = 0;
          virtual void visita(ESEQ *es)        = 0;
          //Visita especializa��es de Stm
          virtual void visita(ListaStm *lstm)  = 0;
          virtual void visita(MOVE *mo)        = 0;
          virtual void visita(EXP *ex)         = 0;
          virtual void visita(JUMP *jp)        = 0;
          virtual void visita(CJUMP *cjp)      = 0;
          virtual void visita(SEQ *se)         = 0;
          virtual void visita(LABEL *l)        = 0;
};
class VisitanteImpressaoRI: public VisitanteRI{
    private:
        int nivel;
        void imprimeNivel();
    public:
          VisitanteImpressaoRI();
          ~VisitanteImpressaoRI();
          void visita(Fragmento *f);
          void visita(Procedimento *p);
          void visita(Literal *l);
          void visita(Variavel *var);

          void visita(Temp *t);
          void visita(ListaTemp *listaTemp);
          void visita(Rotulo *r);
          void visita(ListaRotulo *listaRotulo);
          void visita(ListaAcesso *listaAcesso);
          void visita(AcessoLocal *ac);
          void visita(FrameMIPS *quadroMIPS);
          void visita(NoRegistrador *nr);
          void visita(NoFrame *nq);

          ///M�todos visita para MAQUINA ABSTRATA
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
class VisitanteTradutor : public Visitante {
    public:
		VisitanteTradutor();
		~VisitanteTradutor();
        Fragmento *pegarFragmento();
        void visita(NoPrograma          *prog   );
		void visita(NoId                *id     );
		void visita(NoLiteral           *lit    );
		void visita(NoAscii             *asc    );
		void visita(NoParenteses        *pa     );
		void visita(NoConteudo          *con    );
		void visita(NoEndereco          *ende   );
		void visita(NoNumInteiro        *ni     );
		void visita(NoNumReal           *nr     );
		void visita(NoArranjo           *arr    );
		void visita(NoListaExpr         *le     );
		void visita(NoListaFormal       *lf     );
		void visita(NoListaSentenca     *ls     );
		void visita(NoSe                *se     );
		void visita(NoSenao             *sen    );
		void visita(NoEnquanto          *enq    );
		void visita(NoBlocoCaso         *bc     );
		void visita(NoDesvia            *des    );
		void visita(NoEscolha           *sw     );
		void visita(NoImprime           *imp    );
		void visita(NoLeLinha           *leL    );
		void visita(NoRetorna           *ret    );
		void visita(NoLanca             *lan    );
		void visita(NoEscopo            *esc    );
		void visita(NoChamadaFuncao     *cha    );
		void visita(NoTenta             *te     );
		void visita(NoSentencaExpr      *senE   );
		void visita(NoDeclFuncao        *decF   );
		void visita(NoListaId           *lid    );
		void visita(NoDeclVariavel      *decV   );
		void visita(NoDeclTipo          *decT   );
		void visita(NoDeclLocalFuncao   *decLF  );
		void visita(NoDeclLocalVariavel *decLV  );
		void visita(NoDeclLocalPublico  *decLPub);
		void visita(NoDeclLocalPrivado  *decLpri);
		void visita(NoCorpoFuncao       *cF     );
		void visita(NoDeclClasse        *decC   );
		void visita(NoExprUnaria    	*expU   );
		void visita(NoExprBinaria       *expB   );
		void visita(NoExprAtrib         *atr    );
		void visita(NoExprAceCamp       *expAC  );
        void visita(NoVerdadeiro        *tr     );
        void visita(NoFalso             *fa     );
        void visita(NoEsse              *th     );
		void visita(NoNovo              *n      );
		void visita(NoTipo              *tp     );
		void visita(NoColchetes         *nc     );

	private:
	    /// Cria um rotulo para o literal usando fun��o e classe que ele pertence
	    char* RotuloNome(const char* nome, int cont, bool contador = true);
	    Stm          *ultimaStm;
	    Exp          *ultimaExp;
	    NoDeclClasse *classeAtual;
	    NoDeclFuncao *funcaoAtual;
	    Rotulo       *ultimoFim;
	    FrameMIPS    *frame;
	    Fragmento    *listaFragmento;
	    Temp         *resultadoEscolha;
	    int contLiteral, contLaco, contCaso, contEscolha, contComp;
};
#endif // VISITANTERI_H
