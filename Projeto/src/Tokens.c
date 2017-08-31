#include "Tokens.h"
#include "AnalisadorLexico.h"

/** \brief Traduz o numero do token em uma string
 *  \param token int Token a ser traduzido
 *  \return String com nome do token
 */
void ImprimeToken(int token) {
    switch(token){
            case DEFINICAO_TIPO  :  fprintf(stdout, "DEFINICAO_TIPO\n");                break;
            case ESTRUTURA       :  fprintf(stdout, "ESTRUTURA\n");                     break;
            case CLASSE          :  fprintf(stdout, "CLASSE\n");                        break;
            case PUBLICO         :  fprintf(stdout, "PUBLICO\n");                       break;
            case PRIVADO         :  fprintf(stdout, "PRIVADO\n");                       break;
            case INTEIRO         :  fprintf(stdout, "INTEIRO\n");                       break;
            case REAL            :  fprintf(stdout, "REAL\n");                          break;
            case BOLEANO         :  fprintf(stdout, "BOLEANO\n");                       break;
            case CARACTERE       :  fprintf(stdout, "CARACTERE\n");                     break;
            case SE              :  fprintf(stdout, "SE\n");                            break;
            case SENAO           :  fprintf(stdout, "SENAO\n");                         break;
            case ENQUANTO        :  fprintf(stdout, "ENQUANTO\n");                      break;
            case ESCOLHA         :  fprintf(stdout, "ESCOLHA\n");                       break;
            case DESVIA          :  fprintf(stdout, "DESVIA\n");                        break;
            case IMPRIME         :  fprintf(stdout, "IMPRIME\n");                       break;
            case LE_LINHA        :  fprintf(stdout, "LE_LINHA \n");                     break;
            case RETORNA         :  fprintf(stdout, "RETORNA\n");                       break;
            case LANCA           :  fprintf(stdout, "LANCA\n");                         break;
            case TENTA           :  fprintf(stdout, "TENTA\n");                         break;
            case PEGA            :  fprintf(stdout, "PEGA\n");                          break;
            case CASO            :  fprintf(stdout, "CASO\n");                          break;
            case NOVO            :  fprintf(stdout, "NOVO\n");                          break;
            case VERDADEIRO      :  fprintf(stdout, "VERDADEIRO\n");                    break;
            case FALSO           :  fprintf(stdout, "FALSO\n");                         break;
            case ESSE            :  fprintf(stdout, "ESSE\n");                         break;
            case ID              :  fprintf(stdout, "ID.%s\n", pegarLexema());          break;
            case COLCHETE_ESQ    :  fprintf(stdout, "COLCHETE_ESQ\n");                  break;
            case COLCHETE_DIR    :  fprintf(stdout, "COLCHETE_DIR\n");                  break;
            case CHAVE_ESQ       :  fprintf(stdout, "CHAVE_ESQ\n");                     break;
            case CHAVE_DIR       :  fprintf(stdout, "CHAVE_DIR\n");                     break;
            case PARENTESE_ESQ   :  fprintf(stdout, "PARENTESE_ESQ\n");                 break;
            case PARENTESE_DIR   :  fprintf(stdout, "PARENTESE_DIR\n");                 break;
            case MAIOR           :  fprintf(stdout, "MAIOR \n");                        break;
            case MENOR           :  fprintf(stdout, "MENOR\n");                         break;
            case MAIOR_IGUAL     :  fprintf(stdout, "MAIOR_IGUAL\n");                   break;
            case MENOR_IGUAL     :  fprintf(stdout, "MENOR_IGUAL\n");                   break;
            case COMPARACAO      :  fprintf(stdout, "COMPARACAO\n");                    break;
            case ATRIBUICAO      :  fprintf(stdout, "ATRIBUICAO\n");                    break;
            case ADICAO          :  fprintf(stdout, "ADICAO\n");                        break;
            case SUBTRACAO       :  fprintf(stdout, "SUBTRACAO\n");                     break;
            case DIVISAO         :  fprintf(stdout, "DIVISAO\n");                       break;
            case ASTERISCO       :  fprintf(stdout, "ASTERISCO\n");                     break;
            case OU              :  fprintf(stdout, "OU\n");                            break;
            case PONTO           :  fprintf(stdout, "PONTO\n");                         break;
            case DOIS_PONTOS     :  fprintf(stdout, "DOIS_PONTOS\n");                   break;
            case PONTO_VIRGULA   :  fprintf(stdout, "PONTO_VIRGULA\n");                 break;
            case PONTEIRO        :  fprintf(stdout, "PONTEIRO\n");                      break;
            case E_COMERCIAL     :  fprintf(stdout, "E_COMERCIAL\n");                   break;
            case E               :  fprintf(stdout, "E\n");                             break;
            case DIFERENTE       :  fprintf(stdout, "DIFERENTE\n");                     break;
            case PORCENTO        :  fprintf(stdout, "PORCENTO\n");                      break;
            case OU_CC           :  fprintf(stdout, "OU_CC\n");                         break;
            case NUM_INTEIRO     :  fprintf(stdout, "NUM_INTEIRO.%s\n", pegarLexema()); break;
            case NUM_REAL        :  fprintf(stdout, "NUM_REAL.%s\n", pegarLexema());    break;
            case LITERAL         :  fprintf(stdout, "LITERAL.%s\n", pegarLexema());     break;
            case NEGACAO         :  fprintf(stdout, "NEGACAO\n");                       break;
            case VIRGULA         :  fprintf(stdout, "VIRGULA\n");                       break;
            case ERRO            :  fprintf(stdout, "ERRO\n");                          break;
            case EOF             :  fprintf(stdout, "EOF\n");                           break;
            default              :  fprintf(stdout, "Valor invalido! Token:%d\n", token);
        }
}
