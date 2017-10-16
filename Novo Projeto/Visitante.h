#ifndef VISITANTE_H
#define VISITANTE_H
#include "ASA.h"
class Visitante{
	public:
		virtual ~Visitante(){};
		virtual void visita(NoPrograma          *prog   ) = 0;
		virtual void visita(NoId                *id     ) = 0;
		virtual void visita(NoLiteral           *lit    ) = 0;
		virtual void visita(NoAscii             *asc    ) = 0;
		virtual void visita(NoParenteses        *pa     ) = 0;
		virtual void visita(NoConteudo          *con    ) = 0;
		virtual void visita(NoEndereco          *ende   ) = 0;
		virtual void visita(NoNumInteiro        *ni     ) = 0;
		virtual void visita(NoNumReal           *nr     ) = 0;
		virtual void visita(NoArranjo           *arr    ) = 0;
		virtual void visita(NoListaExpr         *le     ) = 0;
		virtual void visita(NoListaFormal       *lf     ) = 0;
		virtual void visita(NoListaSentenca     *ls     ) = 0;
		virtual void visita(NoSe                *se     ) = 0;
		virtual void visita(NoSenao             *sen    ) = 0;
		virtual void visita(NoEnquanto          *enq    ) = 0;
		virtual void visita(NoBlocoCaso         *bc     ) = 0;
		virtual void visita(NoDesvia            *des    ) = 0;
		virtual void visita(NoEscolha           *sw     ) = 0;
		virtual void visita(NoImprime           *imp    ) = 0;
		virtual void visita(NoLeLinha           *leL    ) = 0;
		virtual void visita(NoRetorna           *ret    ) = 0;
		virtual void visita(NoLanca             *lan    ) = 0;
		virtual void visita(NoEscopo            *esc    ) = 0;
		virtual void visita(NoChamadaFuncao     *cha    ) = 0;
		virtual void visita(NoTenta             *te     ) = 0;
		virtual void visita(NoSentencaExpr      *senE   ) = 0;
		virtual void visita(NoDeclFuncao        *decF   ) = 0;
		virtual void visita(NoListaId           *lid    ) = 0;
		virtual void visita(NoDeclVariavel      *decV   ) = 0;
		virtual void visita(NoDeclTipo          *decT   ) = 0;
		virtual void visita(NoDeclLocalFuncao   *decLF  ) = 0;
		virtual void visita(NoDeclLocalVariavel *decLV  ) = 0;
		virtual void visita(NoDeclLocalPublic   *decLPub) = 0;
		virtual void visita(NoDeclLocalPrivate  *decLpri) = 0;
		virtual void visita(NoCorpoFuncao       *cF     ) = 0;
		virtual void visita(NoDeclClasse        *decC   ) = 0;
		virtual void visita(NoExprUnaria    	*expU   ) = 0;
		virtual void visita(NoExprBinaria       *expB   ) = 0;
		virtual void visita(NoExprAtrib         *atr    ) = 0;
		virtual void visita(NoExprAceCamp       *expAC  ) = 0;
        virtual void visita(NoVerdadeiro        *tr     ) = 0;
        virtual void visita(NoFalso             *fa     ) = 0;
        virtual void visita(NoEsse              *th     ) = 0;
		virtual void visita(NoNovo              *n      ) = 0;
		virtual void visita(NoTipo              *tp     ) = 0;
		virtual void visita(NoColchetes         *nc     ) = 0;
};
#endif // VISITANTE_H

