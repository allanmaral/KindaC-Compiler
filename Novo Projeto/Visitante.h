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
class VisitanteImpressao: public Visitante{
	public:
		VisitanteImpressao();
		~VisitanteImpressao(){};
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
	private:
		int nivel;
		void calculaNivel();
};
#endif // VISITANTE_H

