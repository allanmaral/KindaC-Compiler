#ifndef VISITANTE_H
#define VISITANTE_H
#include "ASA.h"
class Visitante{
	public:
		virtual ~Visitante(){};
		virtual void visita(NoPrograma *prog) = 0;
		virtual void visita(NoId       *id  ) = 0;
		virtual void visita(NoLiteral  *lit ) = 0;
		virtual void visita(NoAscii    *asc ) = 0;
		virtual void visita(NoParenteses *pa) = 0;
		virtual void visita(NoConteudo  *con) = 0;
		virtual void visita(NoEndereco *ende ) = 0;
		virtual void visita(NoNumInteiro *ni) = 0;
		virtual void visita(NoNumReal   *nr ) = 0;
		virtual void visita(NoArranjo   *arr) = 0;
		virtual void visita(NoListaExpr *le ) = 0;
		virtual void visita(NoListaFormal *lf) = 0;
		virtual void visita(NoListaSentenca *ls ) = 0;
		virtual void visita(NoIf            *se ) = 0;
		virtual void visita(NoElse          *sen) = 0;
		virtual void visita(NoWhile         *enq) = 0;
		virtual void visita(NoBlocoCaso     *bc ) = 0;
		virtual void visita(NoBreak         *des) = 0;
		virtual void visita(NoSwitch        *sw ) = 0;
		virtual void visita(NoPrint         *imp) = 0;
		virtual void visita(NoReadLn        *leL) = 0;
		virtual void visita(NoReturn        *ret) = 0;
		virtual void visita(NoEscopo        *esc) = 0;
		virtual void visita(NoChamadaFuncao *cha) = 0;
		virtual void visita(NoTry           *te ) = 0;
		virtual void visita(NoSentencaExpr  *senE) = 0;
		virtual void visita(NoDeclFuncao    *decF) = 0;
		virtual void visita(NoListaId       *lid ) = 0;
		virtual void visita(NoDeclVariavel  *decV) = 0;
		virtual void visita(NoDeclTipo           *decT) = 0;
		virtual void visita(NoDeclLocalFuncao  *decLF   ) = 0;
		virtual void visita(NoDeclLocalVariavel *decLV  ) = 0;
		virtual void visita(NoDeclLocalPublic   *decLPub) = 0;
		virtual void visita(NoDeclLocalPrivate  *decLpri) = 0;
		virtual void visita(NoDeclClasse        *decC ) = 0;
		virtual void visita(NoExprUnaria    	  *expU ) = 0;
		virtual void visita(NoExprBinaria       *expB ) = 0;
		virtual void visita(NoExprAtrib         *atr  ) = 0;
		virtual void visita(NoExprAceCamp       *expAC) = 0;
        virtual void visita(NoTrue              *tr) = 0;
        virtual void visita(NoFalse             *fa) = 0;
        virtual void visita(NoThis              *th) = 0;
		virtual void visita(NoNew               *n    ) = 0;
		virtual void visita(NoTipo              *tp   ) = 0;

};

#endif // VISITANTE_H

