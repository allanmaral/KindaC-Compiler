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
		 void visita(Programa *prog);
		 void visita(Id       *id  );
		 void visita(Literal  *lit );
		 void visita(Ascii    *asc );
		 void visita(Parenteses *pa);
		 void visita(Conteudo  *con);
		 void visita(Endereco * ende );
		 void visita(NumInteiro *ni);
		 void visita(NumReal   *nr );
		 void visita(Arranjo   *arr);
		 void visita(ListaExpr *le );
		 void visita(ListaFormal *lf);
		 void visita(ListaSentenca *ls );
		 void visita(If            *se );
		 void visita(Else          *sen);
		 void visita(While         *enq);
		 void visita(BlocoCaso     *bc );
		 void visita(Break         *des);
		 void visita(Switch        *sw );
		 void visita(Print         *imp);
		 void visita(ReadLn        *leL);
		 void visita(Return        *ret);
		 void visita(Escopo        *esc);
		 void visita(ChamadaFuncao *cha);
		 void visita(Try           *te );
		 void visita(SentencaExpr  *senE);
		 void visita(DeclFuncao    *decF);
		 void visita(ListaId       *lid );
		 void visita(DeclVariavel  *decV);
		 void visita(DeclTipo           *decT);
		 void visita(DeclLocalFuncao  *decLF   );
		 void visita(DeclLocalVariavel *decLV  );
		 void visita(DeclLocalPublic   *decLPub);
		 void visita(DeclLocalPrivate  *decLpri);
		 void visita(DeclClasse        *decC );
		 void visita(ExprUnaria    	  *expU );
		 void visita(ExprBinaria       *expB );
		 void visita(ExprAtrib         *atr  );
		 void visita(ExprAceCamp       *expAC);
		 void visita(True              *tr);
         void visita(False             *fa);
         void visita(This              *th);
		 void visita(New               *n    );
};

#endif // VISITANTEIMPRESSAO_H

