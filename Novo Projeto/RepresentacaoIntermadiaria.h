#ifndef REP_INTERMEDIARIA_H
#define REP_INTERMEDIARIA_H

class Atributo;

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

class NoFrame;
class NoRegistrador;


///## MAQUINA ABSTRATA
///######################
/// Classes abstratas
class Exp;
class Stm;

/// Especializações de Exp
class ListaExp;
class CONST;
class CONSTF;
class NAME;
class TEMP;
class BINOP;
class MEM;
class CALL;
class ESEQ;

/// Especializações de Stm
class ListaStm;
class MOVE;
class EXP;
class JUMP;
class CJUMP;
class SEQ;
class LABEL;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_E,
    OP_OU,
    OP_DLE,  // DESLOCAMENTO ESQUERDA
    OP_DLD,  // DESLOCAMENTO DIREITA
    OP_DLDA, // DESLOCAMENTO DIREITA ARTITIMETICO
    OP_NEQ,
    OP_EQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
} Operadores;

//class Atributo;///apenas para compilar classe aoida nao foi implementada
class Fragmento {
    public:
        Fragmento* proximoFragmento;
        void InsereLista(Fragmento* frag);
    public:
        Fragmento();
        virtual ~Fragmento();
        virtual void aceita(VisitanteRI *vri)=0;
};

class Procedimento : public Fragmento {
    public:
        Frame  *frame;
        Stm    *corpo;
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
        Literal(char *literal, Rotulo *rotulo);
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
        void aceita(VisitanteRI *vri);
};

///## Frame
///######################
class Temp{
    public:
        char *temp;
        static int contador;
    public:
        Temp();
        Temp(char *temp);
        ~Temp();
        const char* obterString();
        void aceita(VisitanteRI *vri);
};
class ListaTemp{
    public:
        Temp *temp;
        ListaTemp *proximoTemp;
    public:
        ListaTemp(Temp *temp, ListaTemp *proximoTemp);
        ~ListaTemp();
        void aceita(VisitanteRI *vri);
};
class Rotulo{
    public:
        char *rotulo;
        static int contador;
    public:
        Rotulo();
        Rotulo(char *rotulo);
        ~Rotulo();
        const char* obterString();
        void aceita(VisitanteRI *vri);
};
class ListaRotulo{
    public:
        Rotulo *rotulo;
        ListaRotulo *proximoRotulo;
    public:
        ListaRotulo(Rotulo *rotulo,ListaRotulo *proximoRotulo);
        ~ListaRotulo();
        void aceita(VisitanteRI *vri);

};
class AcessoLocal{
    public:
        AcessoLocal();
        virtual ~AcessoLocal();
        virtual Exp *codigoAcesso() = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};
class ListaAcesso{
    public:
        AcessoLocal *acessoLocal;
        ListaAcesso *proximoAcesso;
    public:
        ListaAcesso(AcessoLocal *acessoLocal,ListaAcesso *proximoAcesso);
        ~ListaAcesso();
        void aceita(VisitanteRI *vri);

};
class Frame{
    public:
        Frame();
        virtual ~Frame();
        virtual AcessoLocal *insereParametro(bool escapa, int deslocamento) = 0;
        virtual AcessoLocal *insereLocal(bool escapa, int deslocamento) = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};

class FrameMIPS{
     public:
        Rotulo *rotulo;
        Temp *tempRetorno;
        ListaAcesso *variaveisLocais;
        int numeroParametros;
        int deslocamentoVariaveisLocais;
        int deslocamentoParametros;
     public:
        FrameMIPS(Rotulo *rotulo,ListaAcesso *variaveisLocais, int deslocamentoVariaveisLocais,
                  int deslocamentoParametros);
        ~FrameMIPS();
        AcessoLocal *insereParametro(bool escapa, int deslocamento);
        AcessoLocal *insereLocal(bool escapa, int deslocamento);
        void aceita(VisitanteRI *vri);
};
class NoFrame: public AcessoLocal{
    public:
        int deslocamento;
        Exp *exp;
    public:
        NoFrame(int deslocamento);
        ~NoFrame();
        Exp *codigoAcesso();
        void aceita(VisitanteRI *vri);
};
class NoRegistrador: public AcessoLocal{
    public:
        Temp *temp;
        Exp *exp;
    public:
        NoRegistrador(Temp *temp);
        ~NoRegistrador();
        Exp *codigoAcesso();
        void aceita(VisitanteRI *vri);
};
///## MAQUINA ABSTRATA
///######################

/// Classes abstratas
class Exp {
    public:
        virtual ~Exp() = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};
class Stm {
    public:
        virtual ~Stm() = 0;
        virtual void aceita(VisitanteRI *vri) = 0;
};
/// Especializações de Exp
class ListaExp: public Exp{
    public:
        Exp *exp;
        ListaExp *proximoExp;
    public:
        ListaExp(Exp *exo, ListaExp *proximoExp);
        ~ListaExp();
        void aceita(VisitanteRI *vri);
};
class CONST : public Exp {
    public:
        int ci;
    public:
        CONST(int ci);
        ~CONST();
        void aceita(VisitanteRI *vri);
};
class CONSTF : public Exp {
    public:
        float cf;
    public:
        CONSTF(float cf);
        ~CONSTF();
        void aceita(VisitanteRI *vri);
};
class NAME : public Exp {
    public:
        Rotulo *n;
    public:
        NAME(Rotulo *n);
        ~NAME();
        void aceita(VisitanteRI *vri);
};
class TEMP : public Exp {
    public:
        Temp *t;
    public:
        TEMP(Temp *t);
        ~TEMP();
        void aceita(VisitanteRI *vri);
};
class BINOP : public Exp {
    public:
        int op;
        Exp *e1;
        Exp *e2;
    public:
        BINOP(int op, Exp *e1, Exp *e2);
        ~BINOP();
        void aceita(VisitanteRI *vri);
};
class MEM : public Exp {
    public:
        Exp *e;
    public:
        MEM(Exp *e);
        ~MEM();
        void aceita(VisitanteRI *vri);
};
class CALL : public Exp {
    public:
        Exp *f;
        ListaExp *parametros;
    public:
         CALL(Exp *f, ListaExp *parametros);
        ~CALL();
        void aceita(VisitanteRI *vri);
};
class ESEQ : public Exp {
    public:
        Stm *s;
        Exp *e;
    public:
        ESEQ(Stm *sentenca, Exp *exp);
        ~ESEQ();
        void aceita(VisitanteRI *vri);
};
/// Especializações de Stm
class ListaStm : public Stm{
    public:
        Stm *stm;
        ListaStm *proximoStm;
    public:
        ListaStm(Stm *stm, ListaStm *proximoStm);
        ~ListaStm();
        void aceita(VisitanteRI *v);

};
class MOVE : public Stm {
    public:
        Exp *e1;
        Exp *e2;
    public:
        MOVE(Exp *e1, Exp *e2);
        ~MOVE();
        void aceita(VisitanteRI *v);
};
class EXP : public Stm {
    public:
        Exp *e;
    public:
        EXP(Exp *e);
        ~EXP();
        void aceita(VisitanteRI *vri);
};
class JUMP : public Stm {
     public:
        Exp *e;
     public:
        JUMP(Exp *e);
        ~JUMP();
        void aceita(VisitanteRI *vri);
};
class CJUMP : public Stm {
    public:
        int op;
        Exp *e1;
        Exp *e2;
        Rotulo *verdadeiro;
        Rotulo *falso;
    public:
        CJUMP(int op, Exp *e1, Exp *e2, Rotulo *verdadeiro, Rotulo *falso);
        ~CJUMP();
        void aceita(VisitanteRI *v);
};
class SEQ : public Stm {
    public:
        Stm *s1;
        Stm *s2;
    public:
        SEQ(Stm *s1, Stm *s2);
        ~SEQ();
        void aceita(VisitanteRI *vri);
};
class LABEL : public Stm {
    public:
        Rotulo *n;
    public:
        LABEL(Rotulo *n);
        ~LABEL();
        void aceita(VisitanteRI *vri);
};
#endif // REP_INTERMEDIARIA_H
