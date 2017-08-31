#include "TrieReservada.h"
#include "Tokens.h"

TrieReservada::TrieReservada():Trie(){
    inicializarReservada();
}
/** \brief imprimeLexema
 *  Função para colocar a string associada a um lexema no stdout
 * \param
 *  saida: lexema a ser impresso
 *  atr: atributo do lexema que será impresso juntamente com ele
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
 *  Função para colocar no stdout a descrição da tabela antes de imprimi-la
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
