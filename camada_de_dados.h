#ifndef ___CAMADA_DE_DADOS_H___
#define ___CAMADA_DE_DADOS_H___

#include <stdio.h>
/**
 @file camada_de_dados.h
 Definições dos dados presentes no estado e das funções que o alteram
*/

/**
\brief Tipos de dados que uma casa pode assumir
 Uma casa na qual esteja um jogador é BRANCA, na qual já tenha passsado um jogador é PRETA, se não reunir nenhuma das condições anteriores é VAZIA.
 */
typedef enum {VAZIO, BRANCA, PRETA} CASA;

/**
\brief Tipo de dados para definir uma coordenada
 */
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para definir uma jogada
 */
//JOGADA
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para guardar todas as jogadas efetuadas por um determinado jogador, o número máximo de jogadas possíveis são 32
 */
//JOGADAS
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados que definem o estado
 */
//ESTADO
typedef struct {
    /** O tabuleiro */
    CASA tab[8][8];
    /** A coordenada da última jogada */
    COORDENADA ultima_jogada;
    /** Armazena a informação sobre as jogadas */
    JOGADAS jogadas;
    /** Número de jogadas, utilizado no prompt */
    int num_jogadas;
    /**Número do jogador atual */
    int jogador_atual;
    /** Número do comando atual, utilizado no prompt */
    int num_comandos;
    int movimentos_j1;
    int movimentos_j2;
} ESTADO;



/**
\brief Função para criar o estado vazio
@returns O novo estado
*/
ESTADO *inicializar_estado();

/**
\brief Função para inicializar o tabuleiro
@param tab Tabuleiro
@returns O Tabuleiro inicial
*/
void inicializar_tabuleiro(CASA tab[8][8]);

/**
\brief Função para obter o número do jogador atual
@param estado Apontador para o estado atual
@return O número do jogador atual
*/
int obter_jogador_atual(ESTADO *estado);

/**
\brief Função para obter o número de jogadas efetuadas (cada jogada tem o movimento de dois jogadores)
@param estado Apontador para o estado atual
@return O número de jogadas efetuadas
*/
int obter_numero_de_jogadas(ESTADO *estado);

/**
\brief Função para obter o estado de uma casa do tabuleiro
@param e Apontador para o estado atual
@param c A coordenada
@return Se a casa está VAZIA, BRANCA ou PRETA
 */
CASA obter_estado_casa(ESTADO *e, COORDENADA c);

/**
\brief Função que atualiza o estado de jogo após cada jogada
@param e Apontador para o estado atual
@param c A coordenada
*/
void atualiza_estado_jogo (ESTADO *e, COORDENADA c);

/**
\brief Função que incrementa o número de comandos
@param e Apontador para o estado atual
*/
void incrementa_num_comandos(ESTADO *e);

/**
\brief Função para obter o número atual de comandos, utilizado no prompt
@param e Apontador para o estado atual
@return O número de comandos atual
*/
int obter_num_comandos(ESTADO *e);

/**
\brief Função para alterar o valor do número de jogadas, para quebrar o loop no main e para terminar o programa
@param e Apontador para o estado atual
@param numJogadas O número de jogadas atuais
*/
void modifica_num_jogadas (ESTADO *e , int numJogadas);
/**
\brief Função para obter a última jogada efetuada
@param e Apontador para o estado atual
@return A última jogada efetuada
*/
COORDENADA obter_ultima_jogada(ESTADO *e );

/**
\brief Função para gravar os dados atuais do tabuleiro (quando utilizado o comando gr)
@param e Apontador para o estado atual
@param file_name Nome do ficheiro que vai ser criado
*/
void grava_dados(ESTADO *e ,char  *file_name );

/**
\brief Função para ler um ficheiro e alterar o estado consoante esse ficheiro
@param e Apontador para o estado atual
@param file_name Nome do ficheiro para ser lido
*/
void ler_dados(ESTADO *e , char * file_name);

/**
\brief Função para obter uma jogada do Array
@param e Apontador para o estado atual
@param num_jogadas Número atual de jogadas
@return Jogada desejada
*/
int obter_numero_movimentos(ESTADO *e , int jogador);
JOGADA obter_estado_jogada(ESTADO *e , int num_jogadas);
JOGADA mudar_jogador_atual (ESTADO *e, int jogador);
void altera_ultima_jogada(ESTADO * e , COORDENADA c);
void altera_movimentos_j1 (ESTADO *e, int mov_j1);
void altera_movimentos_j2 (ESTADO *e, int mov_j2);
void altera_estado_casa(ESTADO *e, COORDENADA posicao, char estado);
void altera_array_jogadas(ESTADO * e, COORDENADA mov, int jogada, int jogador);
int ler_tabuleiro(ESTADO *e , FILE * f_pointer);
void ler_movs(ESTADO * e, FILE * f_pointer);
int obter_numero_movimentos(ESTADO *e , int jogador);
ESTADO* reinicia_pos (ESTADO *e, int pos, JOGADA *jog);
JOGADA *obter_array_jogadas (ESTADO *e);
#endif
