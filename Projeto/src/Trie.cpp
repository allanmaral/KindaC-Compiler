#include "Trie.h"
#include "TabelaSimbolos.h"

Trie::Trie() { raiz = new No_Trie(); altura = 0; }
/** \brief insere
 *  Fun��o para fazer a inser��o de lexemas dentro da tabela de simbolos
 * \param
 *  entrada: lexema a ser inserido na tabela
 *  atributo: atributo associado ao lexema
 * \param
 */
void Trie::insere(char* entrada, Atributo* atributo){
    int indice = 0;
    No_Trie *no = raiz;
    No_Trie *auxiliar = NULL;
    char caractere;

    while(entrada[indice] != '\0'){ ///Percorre todo os caracteres da entrada
        caractere = entrada[indice];
        auxiliar = no->pegarCaractere(caractere);   ///para cada caractere busca o filho correspondente do n� atual
        if(auxiliar == NULL){   ///se esse filho nao existir, o cria e associa o n� atual a ele
            auxiliar = new No_Trie();
            no->atribuirCaractere(caractere, auxiliar);
            no = auxiliar;
        } else{ ///se o filho existir, apenas desce um n�vel da �rvore
            no = no->pegarCaractere(caractere);
          }
        indice++;
    }
    if(altura < indice + 1) { altura = indice + 1; }
    ///ao chegar no final da string, coloca o n� atual como chave e associa o atributo � ele
    no->atribuirChave(true);
    no->atribuirAtributo(atributo);
}
/** \brief imprime
 *  Fun��o para imprimir todos os lexemas guardados dentro da tabela
 */
void Trie::imprime(){
    imprimeCabecalho();
    char saida[altura + 1];
    imprimeRecursivo(saida, 0, raiz);
}
/** \brief imprimeRecursivo
 *  Fun��o recursiva auxiliar para percorrer a trie
 * \param
 *  saida: string parcial que � usada na impress�o
 * \param
 */
void Trie::imprimeRecursivo(char* saida, int indice, No_Trie *n){
    if(n->EChave()){///Para cada n� que for chave, imprime o caminho que foi percorrido pela recurs�o
        saida[indice] = '\0';
        imprimeLexema(saida, n->pegarAtributo());
    }
    No_Trie *filho = NULL;
    ///Para cada filho n�o nulo do n� atual,
    for(unsigned int caractere = 0; caractere < TAMANHO_ALFABETO; caractere++){
        ///coloca o caractere correspondente na saida e desce um n�vel
        filho = n->pegarCaractere(caractere);
        if(filho != NULL){
            saida[indice] = caractere;
            imprimeRecursivo(saida, indice + 1, filho);
        }
    }
}
/** \brief busca
 *  Fun��o que busca um lexema na trie e retorna o atributo associado a ele
 * \param
 *  entrada: lexema a ser buscado
 * \param
 * \return
 *  Atributo associado a esse lexema
 */
Atributo* Trie::busca(char *entrada){
    int indice = 0;
    No_Trie *no = raiz;
    while(entrada[indice] != '\0'){///enquanto percorre toda a entrada buscada
        no = no->pegarCaractere(entrada[indice]);
        if(no == NULL){///se encontrar um n� nulo pelo caminho, a entrada n�o existe
            return NULL;
        }
        indice++;
    }
    if(no->EChave()){///se n�o encontrou nenhum n� nulo pelo caminho e o n� que parou � uma chave, ent�o encontrou a entrada
        return no->pegarAtributo();
    }
    return NULL;
}

/** \brief calcularTamanhoLexema
 *  FUn��o para calcular o tamanho de lexemas
 * \param
 * lexema: lexema para ser calculado o seu tamanho
 * \return
 *  Tamanho do lexema
 */
int Trie::calcularTamanhoLexema(char *lexema){
    int total = 0;
    while( lexema[total] != '\0') { total++; }
    return total;
}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void Trie::imprimeLexema(char* saida, Atributo * atr){
    fprintf(stdout,"[%s]\n", saida);
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void Trie::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"---------------TABELA------------------\n");
    fprintf(stdout,"---------------------------------------\n");
}
Trie::~Trie() { delete raiz; }

TrieIdentificador::TrieIdentificador():Trie(){}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void TrieIdentificador::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void TrieIdentificador::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"       TABELA DE IDENTIFICADORES       \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieIdentificador::~TrieIdentificador() { }

TrieInteiro::TrieInteiro():Trie(){}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void TrieInteiro::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void TrieInteiro::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE INTEIROS          \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieInteiro::~TrieInteiro() { }

TrieLiteral::TrieLiteral():Trie(){}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void TrieLiteral::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void TrieLiteral::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"          TABELA DE LITERAIS           \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieLiteral::~TrieLiteral() { }

TrieReal::TrieReal():Trie(){}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void TrieReal::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void TrieReal::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE REAIS             \n");
    fprintf(stdout,"---------------------------------------\n");
}
TrieReal::~TrieReal() { }

TrieReservada::TrieReservada():Trie(){
    inicializarReservada();
}

/** \brief imprimeLexema
 *  Fun��o para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que ser� impresso juntamente com ele
 */
void TrieReservada::imprimeLexema(char* saida, Atributo *atr){
    int tam = calcularTamanhoLexema(saida);
    tam = 26 - tam;
    fprintf(stdout,"%s", saida);
    while(tam > 1){
        fprintf(stdout," ");
        tam--;
    }
    fprintf(stdout," %i\n", atr->pegarToken());
}

/** \brief imprimeCabecalho
 *  Fun��o para colocar no stdout a descri��o da tabela antes de imprimi-la
 */
void TrieReservada::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"     TABELA DE PALAVRAS RESERVADAS     \n");
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"LEXEMA                   Token numerico\n");
}

void TrieReservada::inicializarReservada(){
    Atributo* auxiliar;
    auxiliar = new Atributo(); auxiliar->atribuirToken(DEFINICAO_TIPO); insere((char*)"typedef", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESTRUTURA);      insere((char*)"struct", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CLASSE);         insere((char*)"class", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PUBLICO);        insere((char*)"public", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PRIVADO);        insere((char*)"private", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(INTEIRO);        insere((char*)"int", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(REAL);           insere((char*)"float", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(BOLEANO);        insere((char*)"bool", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CARACTERE);      insere((char*)"char", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(SE);             insere((char*)"if", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(SENAO);          insere((char*)"else", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ENQUANTO);       insere((char*)"while", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESCOLHA);        insere((char*)"switch", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(DESVIA);         insere((char*)"break", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(IMPRIME);        insere((char*)"print", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(LE_LINHA);       insere((char*)"readln", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(RETORNA);        insere((char*)"return", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(LANCA);          insere((char*)"throw", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(TENTA);          insere((char*)"try", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(PEGA);           insere((char*)"catch", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(CASO);           insere((char*)"case", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(NOVO);           insere((char*)"new", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(VERDADEIRO);     insere((char*)"true", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(FALSO);          insere((char*)"false", auxiliar);
    auxiliar = new Atributo(); auxiliar->atribuirToken(ESSE);           insere((char*)"this", auxiliar);
}
TrieReservada::~TrieReservada() { }

Atributo::Atributo() { /*Construtor*/ }
int Atributo::pegarToken(){ return token; }
void Atributo::atribuirToken(int t) { token = t; }
Atributo::~Atributo() { /*Destrutor*/ }

No_Trie::No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++) { caracteres[i] = NULL; }
    atributos = NULL;
    chave = false;
}

/** \brief pegarCaractere
 *  Fun��o para retornar o filho correspondente � um caractere informado
 * \param
 * c: caractere a ser buscado no vetor de caracteres
 * \return
 *  O filho buscado a partir do caractere informado
 */
No_Trie* No_Trie::pegarCaractere(char c) { return caracteres[(int)c]; }

/** \brief atribuirCaractere
 *  Fun��o para atribuir � posi��o do vetor de caractere um n� informadado
 * \param
 * c: caractere correspondente a posi��o do vetor de caracteres
 * n: n� a ser atribuido nessa posi��o
 * \param
 */
void No_Trie::atribuirCaractere(char c, No_Trie* n) { caracteres[(int)c] = n; }

/** \brief pegarAtributo
 *  Retornar o atributo armazenado neste n�
 */
Atributo* No_Trie::pegarAtributo() { return atributos; }

/** \brief atribuirAtributo
 *  Fun��o para atribuir um atributo passado como par�metro a este n�
 * \param
 * p: atributo a ser armazenado
 * \param
 */
void No_Trie::atribuirAtributo(Atributo *p) { atributos = p; }

/** \brief atribuirChave
 *  Fun��o para definir se o npo eh chave ou n�o
 * \param
 * c: booleano para ser atribuido a variavel da classe 'chave'
 * \param
 */
void No_Trie::atribuirChave(bool c) { chave = c; }

/** \brief EChave
 * Fun��o que retorna se o n� eh um n� chave ou n�o
 * \param
 * \param
 * \return
 *  Retorna a variavel chave
 *
 */
bool No_Trie::EChave() { return chave; }

No_Trie::~No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        if(caracteres[i] != NULL){ delete caracteres[i]; }
    }
    if(atributos != NULL){ delete atributos; }
}
