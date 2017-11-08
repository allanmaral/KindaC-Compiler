#ifndef REP_INTERMEDIARIA_H
#define REP_INTERMEDIARIA_H

class VisitanteRI;

class Fragmento;
class Procedimento;
class Literal;
class Variavel;

///## Frame
///######################
class Temp;
class ListaTemp;
class Rotulo;
class ListaRotulo;

class AcessoLocal;
class ListaAcesso;
class Frame;
class FrameMIPS;


///## MAQUINA ABSTRATA
///######################
// Classes abstratas
class Exp;
class Stm;

// Especializações de Exp
class CONST;
class CONSTF;
class NAME;
class TEMP;
class BINOP;
class MEM;
class CALL;
class ESEQ;

// Especializações de Stm
class MOVE;
class EXP;
class JUMP;
class CJUMP;
class SEQ;
class LABEL;


class Fragmento {
    public:
        Fragmento* proximoFragmento;
    public:
        Fragmento();
        virtual ~Fragmento();
        virtual void aceita(VisitanteRI *vri);
};

class Procedimento : public Fragmento {
    public:
        Frame *frame;
        Stm   *corpo;
    public:
        Procedimento(Frame* frame, Stm* corpo);
        ~Procedimento();
        void aceita(VisitanteRI *vri);
};

class Literal : public Fragmento {
    public:
        char   *literal;
        Rotulo *rotulo;
    public:
        Literal(char* literal);
        ~Literal();
        void aceita(VisitanteRI* vri);
};

class Variavel : public Fragmento {
    public: //TODO
        Atributo *tipo;
        int tamanho;
    public:
        Variavel(Atributo *tipo, int tamanho);
        ~Variavel();
        void aceita()
};


///## MAQUINA ABSTRATA
///######################

// Classes abstratas
class Exp {
    public:
        Exp();
        virtual ~Exp() = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};

class Stm {
    public:
        virtual ~Stm() = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};

// Especializações de Exp
class CONST : public Exp {
    public:
        int constante;
    public:
        CONST(int i);
        ~CONST();
        void aceita(VisitanteRI *vri);
};

class CONSTF : public Exp {
    public:
        float constante;
    public:
        CONSTF(float j);
        ~CONSTF();
        void aceita(VisitanteRI *vri);
};

class NAME : public Exp {
    public:

    public:

};

class TEMP : public Exp {

};

class BINOP : public Exp {

};

class MEM : public Exp {

};

class CALL : public Exp {

};

class ESEQ : public Exp {

};

// Especializações de Stm
class MOVE;
class EXP;
class JUMP;
class CJUMP;
class SEQ;
class LABEL;


#endif // REP_INTERMEDIARIA_H
