#ifndef VISITANTE_H
#define VISITANTE_H
#include "ASA.h"
class Visitante{
	public:
		virtual ~Visitante(){};
		virtual void visita(NoPrograma *prog) = 0;
		virtual void visita(Id       *id  ) = 0;
		virtual void visita(Literal  *lit ) = 0;
		virtual void visita(Ascii    *asc ) = 0;
		virtual void visita(Parenteses *pa) = 0;
		virtual void visita(Conteudo  *con) = 0;
		virtual void visita(Endereco *ende ) = 0;
		virtual void visita(NumInteiro *ni) = 0;
		virtual void visita(NumReal   *nr ) = 0;
		virtual void visita(Arranjo   *arr) = 0;
		virtual void visita(ListaExpr *le ) = 0;
		virtual void visita(ListaFormal *lf) = 0;
		virtual void visita(ListaSentenca *ls ) = 0;
		virtual void visita(If            *se ) = 0;
		virtual void visita(Else          *sen) = 0;
		virtual void visita(While         *enq) = 0;
		virtual void visita(BlocoCaso     *bc ) = 0;
		virtual void visita(Break         *des) = 0;
		virtual void visita(Switch        *sw ) = 0;
		virtual void visita(Print         *imp) = 0;
		virtual void visita(ReadLn        *leL) = 0;
		virtual void visita(Return        *ret) = 0;
		virtual void visita(Escopo        *esc) = 0;
		virtual void visita(ChamadaFuncao *cha) = 0;
		virtual void visita(Try           *te ) = 0;
		virtual void visita(SentencaExpr  *senE) = 0;
		virtual void visita(DeclFuncao    *decF) = 0;
		virtual void visita(ListaId       *lid ) = 0;
		virtual void visita(DeclVariavel  *decV) = 0;
		virtual void visita(DeclTipo           *decT) = 0;
		virtual void visita(DeclLocalFuncao  *decLF   ) = 0;
		virtual void visita(DeclLocalVariavel *decLV  ) = 0;
		virtual void visita(DeclLocalPublic   *decLPub) = 0;
		virtual void visita(DeclLocalPrivate  *decLpri) = 0;
		virtual void visita(DeclClasse        *decC ) = 0;
		virtual void visita(ExprUnaria    	  *expU ) = 0;
		virtual void visita(ExprBinaria       *expB ) = 0;
		virtual void visita(ExprAtrib         *atr  ) = 0;
		virtual void visita(ExprAceCamp       *expAC) = 0;
        virtual void visita(True              *tr) = 0;
        virtual void visita(False             *fa) = 0;
        virtual void visita(This              *th) = 0;
		virtual void visita(New               *n    ) = 0;

};

#endif // VISITANTE_H

