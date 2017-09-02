#include <stdio.h>
#include "AnalisadorLexico.h"
#include "GerenciadorErro.h"
#include "Atributo.h"
#include "TabelaSimbolos.h"
#include "Leitor.h"
#define TAMANHO_LEXEMA 32

static char caractereAtual;      /**< Último caractere lindo pelo autômato*/
static int estado;               /**< Estado atual do autômato  */
static char* lexema;             /**< Vetor de caracteres adicionados ao lexema  */
static int posicaoLexema;        /**< Posição a adicionar um caractere no lexema  */
static int tamLexema;            /**< Tamanho total do vetor de caracteres lexema  */
static int linha;                /**< Linha atual do arquivo  */
static int coluna;               /**< Coluna atual do arquivo  */

/** \brief Função que atualiza o caractere do leitor e aumenta uma coluna
  *
  */
static void pegarProximoCaractere(){
    coluna++;
    caractereAtual = lerProximoCaractere();
}

/** \brief Função que reinicializa o "automato"
  *
  */
static void reinicializaAutomato(){ pegarProximoCaractere(); posicaoLexema = 0; estado =1;}

char* pegarLexema(){ return lexema ; }

/** \brief Construtor do analisador léxico
  *
  * \param caminhoArquivo const char* Caminho do arquivo a ser lido
  */
void iniciaAnalisadorLexico(char *caminho){
    lexema = (char*) malloc(TAMANHO_LEXEMA*(sizeof(char)));
    posicaoLexema = 0;
    tamLexema     = TAMANHO_LEXEMA;
    linha         = 1;
    coluna        = 0;
    int res = inicializarLeitor(caminho);
    if(res == ARQUIVO_INVALIDO){
        saidaErro(ErroArquivoInvalido, 0, 0);
        exit(1);
    }
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
									  case EOF : pegarProximoCaractere(); return EOF;           break;
									  case '\0': pegarProximoCaractere(); return EOF;           break;
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
					 	 Atributo *auxiliar = buscaTabela(TABELA_RESERVADA, lexema);
					 	 if(auxiliar != NULL) { return auxiliar->pegarToken(); }
					 	 else{
					 	     auxiliar = (Atributo*)malloc(sizeof(Atributo));
					 	 	 auxiliar->atribuirToken(LITERAL);
					 	 	 insereTabela(TABELA_ID, lexema, auxiliar);
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
					 	 	    insereTabela(TABELA_INTEIRO, lexema, auxiliar);
					 	 	    return NUM_INTEIRO;
					 	    }
						    break;
            case 4 :
                if(isdigit(caractereAtual)) { estado = 5; incrementaLexema(); }
                else if(caractereAtual == 'e' || caractereAtual == 'E'){
                         estado = 6;
                         incrementaLexema();
                     } else { return PONTO; }
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
                           insereTabela(TABELA_REAL, lexema, auxiliar);
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
                    insereTabela(TABELA_REAL, lexema, auxiliar);
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
                           return EOF;
                       }
                       else if(caractereAtual == '\\') { estado = 10; incrementaLexema(); }
                            else { estado = 11; incrementaLexema(); }
					   	    break;
            case 10 :
                if(caractereAtual == '\0' || caractereAtual == EOF){
                    saidaErro(ErroCaractereMalFormado, linha, coluna);
                    return EOF;
                }
                else { estado = 11; incrementaLexema(); }
				break;
            case 11 :
                if(caractereAtual == '\''){
                    incrementaLexema();
                    Atributo *auxiliar;
                    auxiliar = (Atributo*)malloc(sizeof(Atributo));
                    auxiliar->atribuirToken(LITERAL);
                    insereTabela(TABELA_LITERAL, lexema, auxiliar);
                    return LITERAL;
                } else if(caractereAtual == '\0' || caractereAtual == EOF){
                           saidaErro(ErroCaractereMalFormado, linha, coluna);
                           return EOF;
                       } else{
                             saidaErro(ErroFaltaAspaSimples, linha, coluna);
                             reinicializaAutomato();
                         }
					     break;
            case 12 :
                if(caractereAtual == '\\') { estado = 13; incrementaLexema(); }
                else if(caractereAtual == '\0' || caractereAtual == EOF){
                    saidaErro(ErroFaltaAspasDupla, linha, coluna);
                    return EOF;
                } else if(caractereAtual == '"'){
                           incrementaLexema();
                           Atributo *auxiliar;
                           auxiliar = (Atributo*)malloc(sizeof(Atributo));
                           auxiliar->atribuirToken(LITERAL);
                           insereTabela(TABELA_LITERAL, lexema, auxiliar);
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
                    return EOF;
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
                if(caractereAtual == '\0' || caractereAtual == EOF) { return EOF; }
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
                                         return EOF;
                                     } else { pegarProximoCaractere(); }
                                       break;
            case 17 :
                if(caractereAtual == '*'){ pegarProximoCaractere(); }
                else if(caractereAtual == '\0' || caractereAtual == EOF){
                         saidaErro(ErroComentarioNaoTerminado, linha, coluna);
                         return EOF;
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
                if(caractereAtual == '|') { pegarProximoCaractere(); return E; }
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

/** \brief Destrutor do Analisador Léxico
  *
  */
void destruirAnalizadorLexico() {destruirLeitor(); free(lexema); }
