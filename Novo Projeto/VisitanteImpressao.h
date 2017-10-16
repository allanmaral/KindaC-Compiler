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
		void visita(NoDeclLocalPublic   *decLPub);
		void visita(NoDeclLocalPrivate  *decLpri);
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
};

#endif // VISITANTEIMPRESSAO_H

