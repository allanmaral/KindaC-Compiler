#include "TabelaSimbolos.h"
#include "AnalisadorLexico.h"
#include <stdio.h>
#include <string.h>

TabelaSimbolos::TabelaSimbolos() { raiz = new No_Trie(); altura = 0; }
void TabelaSimbolos::limpa(){
    delete raiz;
    raiz = NULL;
    raiz = new No_Trie();
}

/** \brief insere
 *  Função para fazer a inserção de lexemas dentro da tabela de simbolos
 * \param
 *  entrada: lexema a ser inserido na tabela
 *  atributo: atributo associado ao lexema
 * \param
 */
void TabelaSimbolos::insere(char* entrada, Atributo* atributo){
    int indice = 0;
    No_Trie *no = raiz;
    No_Trie *auxiliar = NULL;
    char caractere;

    while(entrada[indice] != '\0'){ ///Percorre todo os caracteres da entrada
        caractere = entrada[indice];
        auxiliar = no->pegarCaractere(caractere);   ///para cada caractere busca o filho correspondente do nó atual
        if(auxiliar == NULL){   ///se esse filho nao existir, o cria e associa o nó atual a ele
            auxiliar = new No_Trie();
            no->atribuirCaractere(caractere, auxiliar);
            no = auxiliar;
        } else{ ///se o filho existir, apenas desce um nível da árvore
            no = no->pegarCaractere(caractere);
          }
        indice++;
    }
    if(altura < indice + 1) { altura = indice + 1; }
    ///ao chegar no final da string, coloca o nó atual como chave e associa o atributo à ele
    no->atribuirChave(true);
    no->atribuirAtributo(atributo);
}
/** \brief imprime
 *  Função para imprimir todos os lexemas guardados dentro da tabela
 */
void TabelaSimbolos::imprime(){
    imprimeCabecalho();
    char saida[altura + 1];
    imprimeRecursivo(saida, 0, raiz);
}
/** \brief imprimeRecursivo
 *  Função recursiva auxiliar para percorrer a TabelaSimbolos
 * \param
 *  saida: string parcial que é usada na impressão
 * \param
 */
void TabelaSimbolos::imprimeRecursivo(char* saida, int indice, No_Trie *n){
    if(n->EChave()){///Para cada nó que for chave, imprime o caminho que foi percorrido pela recursão
        saida[indice] = '\0';
        n->pegarAtributo()->imprime();
    }
    No_Trie *filho = NULL;
    ///Para cada filho não nulo do nó atual,
    for(unsigned int caractere = 0; caractere < TAMANHO_ALFABETO; caractere++){
        ///coloca o caractere correspondente na saida e desce um nível
        filho = n->pegarCaractere(caractere);
        if(filho != NULL){
            saida[indice] = caractere;
            imprimeRecursivo(saida, indice + 1, filho);
        }
    }
}
/** \brief busca
 *  Função que busca um lexema na TabelaSimbolos e retorna o atributo associado a ele
 * \param
 *  entrada: lexema a ser buscado
 * \param
 * \return
 *  Atributo associado a esse lexema
 */
Atributo* TabelaSimbolos::busca(char *entrada){
    int indice = 0;
    No_Trie *no = raiz;
    while(entrada[indice] != '\0'){///enquanto percorre toda a entrada buscada
        no = no->pegarCaractere(entrada[indice]);
        if(no == NULL){///se encontrar um nó nulo pelo caminho, a entrada não existe
            return NULL;
        }
        indice++;
    }
    ///se não encontrou nenhum nó nulo pelo caminho e o nó que parou é uma chave, então encontrou a entrada
    if(no->EChave()){
        return no->pegarAtributo();
    }
    return NULL;
}

/** \brief calcularTamanhoLexema
 *  FUnção para calcular o tamanho de lexemas
 * \param
 * lexema: lexema para ser calculado o seu tamanho
 * \return
 *  Tamanho do lexema
 */
int TabelaSimbolos::calcularTamanhoLexema(char *lexema){
    int total = 0;
    while( lexema[total] != '\0') { total++; }
    return total;
}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaSimbolos::imprimeLexema(char* saida, Atributo * atr){
    fprintf(stdout,"[%s]\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaSimbolos::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"---------------TABELA------------------\n");
    fprintf(stdout,"---------------------------------------\n");
}
void TabelaSimbolos::deleteTabela(No_Trie* no){
    for(int i = 0; i < TAMANHO_ALFABETO; i++){
        if(no->pegarCaractere(i) != NULL){ deleteTabela(no->pegarCaractere(i));}
    }
    delete no;
}
TabelaSimbolos::~TabelaSimbolos() { deleteTabela(raiz); }

TabelaIdentificador::TabelaIdentificador():TabelaSimbolos(){}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaIdentificador::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaIdentificador::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"       TABELA DE IDENTIFICADORES       \n");
    fprintf(stdout,"---------------------------------------\n");
}
TabelaIdentificador::~TabelaIdentificador() { }

TabelaInteiro::TabelaInteiro():TabelaSimbolos(){}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaInteiro::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaInteiro::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE INTEIROS          \n");
    fprintf(stdout,"---------------------------------------\n");
}
TabelaInteiro::~TabelaInteiro() { }

TabelaLiteral::TabelaLiteral():TabelaSimbolos(){}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaLiteral::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaLiteral::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"          TABELA DE LITERAIS           \n");
    fprintf(stdout,"---------------------------------------\n");
}
TabelaLiteral::~TabelaLiteral() { }

TabelaReal::TabelaReal():TabelaSimbolos(){}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaReal::imprimeLexema(char* saida, Atributo *atr){
    fprintf(stdout,"%s\n", saida);
}

/** \brief imprimeCabecalho
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaReal::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"           TABELA DE REAIS             \n");
    fprintf(stdout,"---------------------------------------\n");
}
TabelaReal::~TabelaReal() { }

TabelaReservada::TabelaReservada():TabelaSimbolos(){
    inicializarReservada();
}

/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
 */
void TabelaReservada::imprimeLexema(char* saida, Atributo *atr){
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
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
 */
void TabelaReservada::imprimeCabecalho(){
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"     TABELA DE PALAVRAS RESERVADAS     \n");
    fprintf(stdout,"---------------------------------------\n");
    fprintf(stdout,"LEXEMA                   Token numerico\n");
}

void TabelaReservada::inicializarReservada(){
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
TabelaReservada::~TabelaReservada() { }

Atributo::Atributo() { lexema=NULL; }
int Atributo::pegarToken(){ return token; }
char* Atributo::pegarLexema(){ return lexema; }
void Atributo::atribuirToken(int t) { token = t; }
void Atributo::atribuirLexema(const char* l) {
    lexema=(char*)malloc(sizeof(char) * (strlen(l) + 1));
    strcpy(lexema,l);
}
void Atributo::imprime(){
    fprintf(stdout,"[%s]\n", lexema);
}
Atributo::~Atributo() { free(lexema); }

No_Trie::No_Trie(){
    for(int i = 0; i < TAMANHO_ALFABETO; i++) { caracteres[i] = NULL; }
    atributos = NULL;
    chave = false;
}

/** \brief pegarCaractere
 *  Função para retornar o filho correspondente à um caractere informado
 * \param
 * c: caractere a ser buscado no vetor de caracteres
 * \return
 *  O filho buscado a partir do caractere informado
 */
No_Trie* No_Trie::pegarCaractere(char c) { return caracteres[(int)c]; }

/** \brief atribuirCaractere
 *  Função para atribuir à posição do vetor de caractere um nó informadado
 * \param
 * c: caractere correspondente a posição do vetor de caracteres
 * n: nó a ser atribuido nessa posição
 * \param
 */
void No_Trie::atribuirCaractere(char c, No_Trie* n) { caracteres[(int)c] = n; }

/** \brief pegarAtributo
 *  Retornar o atributo armazenado neste nó
 */
Atributo* No_Trie::pegarAtributo() { return atributos; }

/** \brief atribuirAtributo
 *  Função para atribuir um atributo passado como parâmetro a este nó
 * \param
 * p: atributo a ser armazenado
 * \param
 */
void No_Trie::atribuirAtributo(Atributo *p) { atributos = p; }

/** \brief atribuirChave
 *  Função para definir se o npo eh chave ou não
 * \param
 * c: booleano para ser atribuido a variavel da classe 'chave'
 * \param
 */
void No_Trie::atribuirChave(bool c) { chave = c; }

/** \brief EChave
 * Função que retorna se o nó eh um nó chave ou não
 * \param
 * \param
 * \return
 *  Retorna a variavel chave
 *
 */
bool No_Trie::EChave() { return chave; }

No_Trie::~No_Trie(){
    if(atributos != NULL){ delete atributos; }
}
AtributoClasse::AtributoClasse():Atributo(){
    funcoes = new TabelaSimbolos();
    variaveis = new TabelaSimbolos();
    heranca = NULL;
}
AtributoClasse::~AtributoClasse(){
    delete funcoes;
    delete variaveis;
    free(lexema);
}
void AtributoClasse::adicionarFuncao(AtributoFuncaoClasse* atributo){
    funcoes->insere(atributo->pegarLexema(), atributo);
}

void AtributoClasse::adicionarVariavel(AtributoVariavelClasse* atributo){
    variaveis->insere(atributo->pegarLexema(), atributo);
}
Atributo* AtributoClasse::buscaFuncao(char* id){
    return funcoes->busca(id);
}
Atributo* AtributoClasse::buscaVariavel(char* id){
    return variaveis->busca(id);
}
AtributoFuncao::AtributoFuncao():Atributo(){
    parametros = new TabelaSimbolos();
    variaveisLocais = new TabelaSimbolos();
}
AtributoFuncao::~AtributoFuncao(){
    delete parametros;
    delete variaveisLocais;
    free(lexema);
}
void AtributoFuncao::adicionarParametro(AtributoVariavel* atributo){
    parametros->insere(atributo->pegarLexema(),atributo);
}
void AtributoFuncao::adicionarVariavel(AtributoVariavel* atributo){
    variaveisLocais->insere(atributo->pegarLexema(),atributo);
}
Atributo* AtributoFuncao::busca(char* id) {
    Atributo *resultado = parametros->busca(id);
    if(!resultado) resultado = variaveisLocais->busca(id);
    return resultado;
}
Atributo* AtributoFuncao::buscaParametro(char* id){
    return parametros->busca(id);
}
Atributo* AtributoFuncao::buscaVariavel(char* id){
    return variaveisLocais->busca(id);
}
void AtributoVariavel::atribuiArranjo(int arranjo){
    this->arranjo = arranjo;
}
int AtributoVariavel::pegarArranjo(){
    return arranjo;
}
AtributoVariavel::AtributoVariavel():Atributo(){
    tipo = 0;
    ponteiro = false;
    arranjo = 0;
    acesso = NULL;
}
AtributoVariavel::~AtributoVariavel(){
    delete tipo;
    free(lexema);
}
void AtributoVariavel::atribuirTipo(Tipo *tipo){
    this->tipo = tipo;
}
void AtributoVariavel::atribuiPonteiro(bool ponteiro){
    this->ponteiro = ponteiro;
}
bool AtributoVariavel::pegarPonteiro(){
    return ponteiro;
}
Tipo* AtributoVariavel::pegarTipo(){
    return tipo;
}
void AtributoVariavel::atribuiAcesso(AcessoLocal *acesso){
    this->acesso = acesso;
}
AcessoLocal* AtributoVariavel::pegarAcesso(){
    return acesso;
}
AtributoFuncaoClasse::AtributoFuncaoClasse():AtributoFuncao(){
    publico = true;
}
AtributoFuncaoClasse::~AtributoFuncaoClasse(){
    if(retorno) delete retorno;
}
void AtributoFuncaoClasse::atribuiPublico(bool publico){
    this->publico = publico;
}
bool AtributoFuncaoClasse::pegaPublico(){
    return publico;
}
AtributoVariavelClasse::AtributoVariavelClasse():AtributoVariavel(){
    publico = true;
}
AtributoVariavelClasse::~AtributoVariavelClasse(){free(lexema);}
void AtributoVariavelClasse::atribuiPublico(bool publico){
    this->publico = publico;
}
bool AtributoVariavelClasse::pegaPublico(){
    return publico;
}
AtributoTipo::AtributoTipo():Atributo(){
    variaveis = new TabelaSimbolos();
}
void AtributoTipo::adicionarVariavel(AtributoVariavel* var){
    variaveis->insere(var->pegarLexema(), var);
}
Atributo* AtributoTipo::buscaVariavel(char* id){
    return variaveis->busca(id);
}
AtributoTipo::~AtributoTipo(){}
void AtributoClasse::atribuirHeranca(Atributo* heranca){
    this->heranca = heranca;
    free(lexema);
}
Atributo* AtributoClasse::pegarHeranca(){
    return heranca;
}
Tipo::Tipo(int tipo){
    this->tipo = tipo;
}
Tipo::~Tipo(){}
int Tipo::pegaTipo(){
    return tipo;
}
void Tipo::atribuirTipo(int tipo){
    this->tipo = tipo;
}
TipoId::TipoId(char* lexema, int primitivo):Tipo(primitivo){
    this->lexema=(char*)malloc(sizeof(char) * (strlen(lexema) + 1));
    strcpy(this->lexema,lexema);
}
char* TipoId::pegarLexema(){
    return lexema;
}
void TipoId::atribuirLexema(char* lexema){
    if(this->lexema != NULL){
        delete []lexema;
    }
    this->lexema=(char*)malloc(sizeof(char) * (strlen(lexema) + 1));
    strcpy(this->lexema,lexema);
}
TipoId::~TipoId(){
    delete []lexema;
}
TabelaSimbolos* AtributoClasse::pegarVariaveis(){
    return variaveis;
}
TabelaSimbolos* AtributoClasse::pegarFuncoes(){
    return funcoes;
}
TabelaSimbolos* AtributoTipo::pegaVariaveis(){
    return variaveis;
}
void AtributoFuncao::atribuirParametros(TabelaSimbolos* parametros){
    this->parametros = parametros;
}
TabelaSimbolos* AtributoFuncao::pegarVariaveisLocais(){
    return variaveisLocais;
}
TabelaSimbolos* AtributoFuncao::pegarParametros(){
    return parametros;
}
void AtributoFuncao::atribuirVariaveis(TabelaSimbolos* variaveis){
    this->variaveisLocais = variaveis;
}
void AtributoFuncao::atribuirPonteiro(bool ponteiro){
    this->ponteiro = ponteiro;
}
bool AtributoFuncao::pegarPonteiro(){
    return ponteiro;
}
void AtributoFuncao::adicionarRetorno(Tipo* atributo){
    this->retorno = atributo;
}
Tipo* AtributoFuncao::pegarRetorno(){
    return retorno;
}

