#ifndef VISITANTEIMPRESSAO_H
#define VISITANTEIMPRESSAO_H
#include "Visitante.h"


class VisitanteImpressao: public Visitante{
	private:
	int nivel;

	public:
		VisitanteImpressao();
		~VisitanteImpressao(){};
		void calculaNivel();
        void visita(NoPrograma          *prog   ) = 0;
		void visita(NoId                *id     ) = 0;
		void visita(NoLiteral           *lit    ) = 0;
		void visita(NoAscii             *asc    ) = 0;
		void visita(NoParenteses        *pa     ) = 0;
		void visita(NoConteudo          *con    ) = 0;
		void visita(NoEndereco          *ende   ) = 0;
		void visita(NoNumInteiro        *ni     ) = 0;
		void visita(NoNumReal           *nr     ) = 0;
		void visita(NoArranjo           *arr    ) = 0;
		void visita(NoListaExpr         *le     ) = 0;
		void visita(NoListaFormal       *lf     ) = 0;
		void visita(NoListaSentenca     *ls     ) = 0;
		void visita(NoSe                *se     ) = 0;
		void visita(NoSenao              *sen    ) = 0;
		void visita(NoEnquanto             *enq    ) = 0;
		void visita(NoBlocoCaso         *bc     ) = 0;
		void visita(NoDesvia             *des    ) = 0;
		void visita(NoEscolha            *sw     ) = 0;
		void visita(NoImprime             *imp    ) = 0;
		void visita(NoLeLinha            *leL    ) = 0;
		void visita(NoRetorna            *ret    ) = 0;
		void visita(NoEscopo            *esc    ) = 0;
		void visita(NoChamadaFuncao     *cha    ) = 0;
		void visita(NoTenta               *te     ) = 0;
		void visita(NoSentencaExpr      *senE   ) = 0;
		void visita(NoDeclFuncao        *decF   ) = 0;
		void visita(NoListaId           *lid    ) = 0;
		void visita(NoDeclVariavel      *decV   ) = 0;
		void visita(NoDeclTipo          *decT   ) = 0;
		void visita(NoDeclLocalFuncao   *decLF  ) = 0;
		void visita(NoDeclLocalVariavel *decLV  ) = 0;
		void visita(NoDeclLocalPublic   *decLPub) = 0;
		void visita(NoDeclLocalPrivate  *decLpri) = 0;
		void visita(NoDeclClasse        *decC   ) = 0;
		void visita(NoExprUnaria    	*expU   ) = 0;
		void visita(NoExprBinaria       *expB   ) = 0;
		void visita(NoExprAtrib         *atr    ) = 0;
		void visita(NoExprAceCamp       *expAC  ) = 0;
        void visita(NoVerdadeiro              *tr     ) = 0;
        void visita(NoFalso             *fa     ) = 0;
        void visita(NoEsse              *th     ) = 0;
		void visita(NoNovo               *n      ) = 0;
		void visita(NoTipo              *tp     ) = 0;
		void visita(NoColchetes         *nc     ) = 0;
};

#endif // VISITANTEIMPRESSAO_H

