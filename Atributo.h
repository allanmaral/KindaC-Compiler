#ifndef ATRIBUTO_H
#define ATRIBUTO_H
#include <stdlib.h>
#include <stdio.h>

class Atributo
{
    public:
        Atributo();
        int pegarToken();
        void atribuirToken(int t);
        virtual ~Atributo();
    private:
        int token;
};

#endif // ATRIBUTO_H
