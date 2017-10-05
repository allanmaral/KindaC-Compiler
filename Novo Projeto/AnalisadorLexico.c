#include <stdio.h>
#include <string.h>
#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "TabelaSimbolos.h"
#include "ASA.h"

#define TAMANHO_LEXEMA 32
#define TAMANHO_BUFFER 4096
static TabelaReservada tabelaReservado;
static char caractereAtual;      /**< Último caractere lindo pelo autômato*/
static int estado;               /**< Estado atual do autômato  */
static char* lexema;             /**< Vetor de caracteres adicionados ao lexema  */
static int posicaoLexema;        /**< Posição a adicionar um caractere no lexema  */
static int tamLexema;            /**< Tamanho total do vetor de caracteres lexema  */
static int linha;                /**< Linha atual do arquivo  */
static int coluna;               /**< Coluna atual do arquivo  */

/** Dados do leitor de arquivos
 */
static char    buffer[TAMANHO_BUFFER];     /**< Buffer de leitura  */
static int     caractereAtualBuffer = 0;   /**< Índice do último caractere lido */
static FILE*   arquivo = NULL;             /**< Arquivo aberto */


/** \brief Construtor do leitor de arquivo
  *
  * \param arquivo LeitorArquivo*
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  * \param tamanhoBuffer unsigned int tamanho do buffer de leitura
  *
  */
void inicializarLeitor(){
    // Se for um arquivo valido
    if(arquivo){
        // Inicialçiza o leitor
        int elementosLidos;
        elementosLidos = fread(buffer, 1, TAMANHO_BUFFER, arquivo);
        if(elementosLidos < TAMANHO_BUFFER){ buffer[elementosLidos] = (char)0; }

    } else{ // Arquivo invalido
          saidaErro(ErroArquivoInvalido, 0, 0);
          exit(1);
      }
}

/** \brief Destrutor do leitor de arquivo
 *
 * \param arquivo LeitorArquivo* arquivo a ser destruído
 *
 */
void destruirLeitor(){
    if(arquivo && arquivo != stdin){ fclose(arquivo); }
    arquivo = NULL;
    caractereAtualBuffer = TAMANHO_BUFFER;
}

/** \brief Lê o próximo caracter de um arquivo
 *
 *
 * \return char Caracter lido
 *
 */
 static void pegarProximoCaractere(){
    // Se tiver passado do tamanho do buffer, volta pro inicio
    if(caractereAtualBuffer >= TAMANHO_BUFFER){
        int elementosLidos;
        // Le o arquivo
        elementosLidos = fread(buffer, 1, TAMANHO_BUFFER, arquivo);
        // Se não ler o mesmo numero de elementos, pode ser erro ou fim de arquivo
        if(elementosLidos < TAMANHO_BUFFER){ buffer[elementosLidos] = (char)0; }
        caractereAtualBuffer = 0;
    }
    caractereAtual = buffer[caractereAtualBuffer++];
    coluna++;
}

/** \brief Função que reinicializa o "automato"
  *
  */
static void reinicializaAutomato(){ pegarProximoCaractere(); posicaoLexema = 0; estado = 1; }

char* pegarLexema(){ return lexema; }

/** \brief Função que obtem a linha do arquivo lido pelo automato
 *
 *  \return linha atual do arquivo
 */
int pegarLinha() { return linha; }

/** \brief Função que obtem a coluna do arquivo lido pelo automato
 *
 *  \return coluna atual do arquivo
 */
int pegarColuna() { return coluna; }

/** \brief Construtor do analisador léxico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(FILE* fluxo){
    lexema = (char*) malloc(TAMANHO_LEXEMA*(sizeof(char)));
    posicaoLexema = 0;
    tamLexema     = TAMANHO_LEXEMA;
    linha         = 1;
    coluna        = 0;
    arquivo       = fluxo;
    int elementosLidos;
    elementosLidos = fread(buffer, 1, TAMANHO_BUFFER, arquivo);
    if(elementosLidos < TAMANHO_BUFFER){ buffer[elementosLidos] = (char)0; }
    pegarProximoCaractere();
}

/** \brief Procedimento que adiciona o caractere atual
  *       do autômato ao seu vetor de caracteres (lexema)
  */
static void incrementaLexema(){
    //Verifica se não existe posição disponível realocando caso necessário
    if(posicaoLexema >= tamLexema -1){
        tamLexema += TAMANHO_LEXEMA;
        lexema=(char *)realloc(lexema, tamLexema*(sizeof(char)));
    }
    //Adiciona o caractere
    lexema[posicaoLexema] = caractereAtual;
    posicaoLexema++;
    //Garante que o lexema sempre termine com \0
    lexema[posicaoLexema] = '\0';
    pegarProximoCaractere();
}

/** \brief Função que define as transições do autômato
  */
int proximoToken(){
    posicaoLexema = 0;
    int pronto = 0; estado = 1;
    while(pronto != 1){
        switch(estado){
            case 1 :
                if(isspace(caractereAtual)){
                    if(caractereAtual == '\n'){
                        coluna = 0;
                        pegarProximoCaractere();
                        linha++;
                    } else if(caractereAtual == '\t'){
						       coluna += 3;
							   pegarProximoCaractere();
						   } else { pegarProximoCaractere(); }
                }
                else if(isalpha(caractereAtual) || caractereAtual == '_'){
						 estado = 2;
						 incrementaLexema();
					 } else if(isdigit(caractereAtual)){
						        estado = 3;
						        incrementaLexema();
						    } else{
								  switch(caractereAtual){
									  case '.' : estado =  4; incrementaLexema(); break;
									  case '\'': estado =  9; incrementaLexema(); break;
									  case '"' : estado = 12; incrementaLexema(); break;
									  case '/' : estado = 14; incrementaLexema(); break;
									  case '|' : estado = 18; incrementaLexema(); break;
									  case '&' : estado = 19; incrementaLexema(); break;
									  case '-' : estado = 20; incrementaLexema(); break;
									  case '=' : estado = 21; incrementaLexema(); break;
									  case '<' : estado = 22; incrementaLexema(); break;
									  case '>' : estado = 23; incrementaLexema(); break;
									  case '!' : estado = 24; incrementaLexema(); break;

									  case ';' : pegarProximoCaractere(); return PONTO_VIRGULA; break;
									  case ':' : pegarProximoCaractere(); return DOIS_PONTOS;   break;
									  case ',' : pegarProximoCaractere(); return VIRGULA;       break;
									  case '[' : pegarProximoCaractere(); return COLCHETE_ESQ;  break;
									  case ']' : pegarProximoCaractere(); return COLCHETE_DIR;  break;
									  case '(' : pegarProximoCaractere(); return PARENTESE_ESQ; break;
									  case ')' : pegarProximoCaractere(); return PARENTESE_DIR; break;
									  case '{' : pegarProximoCaractere(); return CHAVE_ESQ;     break;
									  case '}' : pegarProximoCaractere(); return CHAVE_DIR;     break;
									  case '+' : pegarProximoCaractere(); return ADICAO;        break;
									  case '%' : pegarProximoCaractere(); return PORCENTO;      break;
									  case '*' : pegarProximoCaractere(); return ASTERISCO;     break;
									  case EOF : pegarProximoCaractere(); return TOKEN_EOF;     break;
									  case '\0': pegarProximoCaractere(); return TOKEN_EOF;     break;
									  default:
										  saidaErro(ErroCaractereInvalido, linha, coluna);
										  reinicializaAutomato();
								  }
						      }
							  break;
            case 2 :
                if(isalnum(caractereAtual)) { incrementaLexema(); }
                else if(caractereAtual == '_') { incrementaLexema(); }
					 else{
					 	 Atributo *auxiliar = tabelaReservado.busca(lexema);
					 	 if(auxiliar != NULL) { return auxiliar->pegarToken(); }
					 	 else{
					 	     auxiliar = (Atributo*)malloc(sizeof(Atributo));
					 	 	 auxiliar->atribuirToken(ID);
					 	 	 obtemTabelaIdentificador()->insere(lexema,auxiliar);
					 	 	 return ID;
					 	 }
					 }
					 break;
            case 3 :
                if(isdigit(caractereAtual)) { incrementaLexema(); }
                else if(caractereAtual == '.') { estado = 5; incrementaLexema(); }
					 else if(caractereAtual == 'e' || caractereAtual == 'E'){
					 	 	  estado = 6;
					 	 	  incrementaLexema();
					 	  } else{
					 	 	    Atributo *auxiliar;
					 	 	    auxiliar = (Atributo*)malloc(sizeof(Atributo));
					 	 	    auxiliar->atribuirToken(NUM_INTEIRO);
					 	 	    obtemTabelaInteiro()->insere(lexema,auxiliar);
					 	 	    return NUM_INTEIRO;
					 	    }
						    break;
            case 4 :
                if(isdigit(caractereAtual)) { estado = 5; incrementaLexema(); }
                else if(caractereAtual == 'e' || caractereAtual == 'E'){
                         estado = 6;
                         incrementaLexema();
                     } else if(caractereAtual == '.') {
                                estado = 25;
                                incrementaLexema();
                            } else { return PONTO; }
					   break;
            case 25:
                if(caractereAtual == '.') { pegarProximoCaractere(); return TRES_PONTOS; }
                else {
                    saidaErro(ErroNumeroMalFormado, linha, coluna);
                    reinicializaAutomato();
                }
                break;
            case 5 :
                if(isdigit(caractereAtual)) { incrementaLexema(); }
                else if(caractereAtual == 'e' || caractereAtual == 'E'){
                         estado = 6;
                         pegarProximoCaractere();
                     } else{
                           Atributo *auxiliar;
                           auxiliar = (Atributo*)malloc(sizeof(Atributo));
                           auxiliar->atribuirToken(NUM_REAL);
                           obtemTabelaReal()->insere(lexema,auxiliar);
                           return NUM_REAL;
                       }
					   break;
            case 6 :
                if(isdigit(caractereAtual)) { estado = 7; incrementaLexema(); }
                else if(caractereAtual == '+' || caractereAtual == '-'){
                         estado = 8;
                         incrementaLexema();
                     } else{
                           saidaErro(ErroNumeroMalFormado, linha, coluna);
                           reinicializaAutomato();
                       }
					   break;
            case 7 :
                if(isdigit(caractereAtual)) { incrementaLexema(); }
                else{
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(NUM_REAL);
                    obtemTabelaReal()->insere(lexema,auxiliar);
                    return NUM_REAL;
                }
				break;
            case 8 :
                if(isdigit(caractereAtual)) { estado = 7; incrementaLexema(); }
                else{
                    saidaErro(ErroNumeroMalFormado, linha, coluna);
                    reinicializaAutomato();
                }
				break;
            case 9 :
                if(caractereAtual == '\''){
                    saidaErro(ErroCaractereVazio, linha, coluna);
                    incrementaLexema();
                    reinicializaAutomato();
                } else if(caractereAtual == '\0' || caractereAtual == EOF){
                           saidaErro(ErroCaractereMalFormado, linha, coluna);
                           return TOKEN_EOF;
                       } else if(caractereAtual == '\\') { estado = 10; incrementaLexema(); }
                              else { estado = 11; incrementaLexema(); }
                break;
            case 10 :
                if(caractereAtual == '\0' || caractereAtual == EOF){
                    saidaErro(ErroCaractereMalFormado, linha, coluna);
                    return TOKEN_EOF;
                }
                else { estado = 11; incrementaLexema(); }
				break;
            case 11 :
                if(caractereAtual == '\''){
                    incrementaLexema();
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    obtemTabelaLiteral()->insere(lexema,auxiliar);
                    return ASCII;
                } else if(caractereAtual == '\0' || caractereAtual == EOF){
                           saidaErro(ErroCaractereMalFormado, linha, coluna);
                           return TOKEN_EOF;
                       } else{
                             saidaErro(ErroFaltaAspaSimples, linha, coluna);
                             reinicializaAutomato();
                         }
					     break;
            case 12 :
                if(caractereAtual == '\\') { estado = 13; incrementaLexema(); }
                else if(caractereAtual == '\0' || caractereAtual == EOF){
                    saidaErro(ErroFaltaAspasDupla, linha, coluna);
                    return TOKEN_EOF;
                } else if(caractereAtual == '"'){
                           incrementaLexema();
                           Atributo *auxiliar;
                           auxiliar = (Atributo*)malloc(sizeof(Atributo));
                           auxiliar->atribuirToken(LITERAL);
                           obtemTabelaLiteral()->insere(lexema,auxiliar);
                           return LITERAL;
                       } else if(caractereAtual == '\n'){
                                  coluna=0;
                                  linha++;
                                  saidaErro(ErroFaltaAspasDupla, linha, coluna);
                                  reinicializaAutomato();
                              } else { incrementaLexema(); }
				       		    break;
            case 13 :
                if(caractereAtual == '\0' || caractereAtual == EOF){
                    saidaErro(ErroFaltaAspasDupla, linha, coluna);
                    return TOKEN_EOF;
                } else { estado = 12; incrementaLexema(); }
            break;
            case 14 :
                if(caractereAtual == '/'){
                    estado = 15;
                    posicaoLexema = 0;
                    pegarProximoCaractere();
                } else if(caractereAtual == '*'){
                           estado = 16;
                           posicaoLexema = 0;
                           pegarProximoCaractere();
                       } else { return DIVISAO; }
                         break;
            case 15 :
                if(caractereAtual == '\0' || caractereAtual == EOF) { return TOKEN_EOF; }
                else if(caractereAtual == '\n'){
                         linha++;
                         coluna = 0;
                         pegarProximoCaractere();
                         estado = 1;
                     } else if(caractereAtual == '\t'){
                                coluna += 3;
                                pegarProximoCaractere();
                            } else { pegarProximoCaractere(); }
                              break;
            case 16 :
                if(caractereAtual == '*'){
                    estado = 17;
                    pegarProximoCaractere();
                } else if(caractereAtual == '\n'){
                           linha++;
                           coluna = 0;
                           pegarProximoCaractere();
                       } else if(caractereAtual == '\t'){
                                  coluna += 3;
                                  pegarProximoCaractere();
                              } else if(caractereAtual == '\0' || caractereAtual == EOF){
                                         saidaErro(ErroComentarioNaoTerminado, linha, coluna);
                                         return TOKEN_EOF;
                                     } else { pegarProximoCaractere(); }
                                       break;
            case 17 :
                if(caractereAtual == '*'){ pegarProximoCaractere(); }
                else if(caractereAtual == '\0' || caractereAtual == EOF){
                         saidaErro(ErroComentarioNaoTerminado, linha, coluna);
                         return TOKEN_EOF;
                     } else if(caractereAtual == '/'){
                                estado = 1;
                                pegarProximoCaractere();
                            } else if(caractereAtual == '\n'){
                                       estado = 16;
                                       linha++;
                                       coluna = 0;
                                       pegarProximoCaractere();
                                   } else if(caractereAtual == '\t'){
                                              estado = 16;
                                              coluna += 3;
                                              pegarProximoCaractere();
                                          } else { estado = 16; pegarProximoCaractere(); }
                                            break;
            case 18 :
                if(caractereAtual == '|') { pegarProximoCaractere(); return OU_CC; }
                else { return OU; }
				break;
            case 19 :
                if(caractereAtual == '&') { pegarProximoCaractere(); return E; }
                else { return E_COMERCIAL; }
				break;
            case 20 :
                if(caractereAtual == '>') { pegarProximoCaractere(); return PONTEIRO; }
                else { return SUBTRACAO; }
				break;
            case 21 :
                if(caractereAtual == '=') { pegarProximoCaractere(); return COMPARACAO; }
                else { return ATRIBUICAO; }
				break;
            case 22 :
                if(caractereAtual == '=') { pegarProximoCaractere(); return MENOR_IGUAL; }
                else { return MENOR; }
				break;
            case 23 :
                if(caractereAtual == '=') { pegarProximoCaractere(); return MAIOR_IGUAL; }
                else { return MAIOR; }
				break;
            case 24 :
                if(caractereAtual == '=') { pegarProximoCaractere(); return DIFERENTE; }
                else { return NEGACAO; }
                break;
        }
    }
    return 0;
}
void imprimeTabelaPalavrasReservadas(){
    tabelaReservado.imprime();
}
/** \brief Destrutor do Analisador Léxico
  *
  */
void destruirAnalizadorLexico() {destruirLeitor(); free(lexema); }
