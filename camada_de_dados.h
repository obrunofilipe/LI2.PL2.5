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
\brief Função para obter o estado de uma casa
@param tab O tabuleiro
@param c Coordenada
@return O estado da casa
*/
CASA obter_estado_casa(CASA tab[8][8], COORDENADA c);

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
\brief Função para obter uma jogada do Array
@param e Apontador para o estado atual
@param jogador Número do jogador
@return O número de movimentos do jogador
*/
int obter_numero_movimentos(ESTADO *e , int jogador);

/**
\brief Função para obter uma jogada do Array
@param e Apontador para o estado atual
@param num_jogadas Número atual de jogadas
@return Jogada desejada
*/
JOGADA obter_estado_jogada(ESTADO *e , int num_jogadas);

/**
\brief Função para mudar para o outro jogador
@param e Apontador para o estado atual
@param jogador Número do jogador
@return
*/
void mudar_jogador_atual (ESTADO *e, int jogador);

/**
\brief Função para alterar a última jogada
@param e Apontador para o estado atual
@param c Coordenada
*/
void altera_ultima_jogada(ESTADO * e , COORDENADA c);

/**
\brief Função para alterar o número de movimentos do jogador 1
@param e Apontador para o estado atual
@param mov_j1 Novo número de movimentos do jogador 1
*/
void altera_movimentos_j1 (ESTADO *e, int mov_j1);

/**
\brief Função para alterar o número de movimentos do jogador 2
@param e Apontador para o estado atual
@param mov_j1 Novo número de movimentos do jogador 2
*/
void altera_movimentos_j2 (ESTADO *e, int mov_j2);

/**
\brief Função para alterar o estado que uma determinada casa está
@param e Apontador para o estado atual
@param posicao Casa a ser alterada
@param estado
 */
void altera_estado_casa(ESTADO *e, COORDENADA posicao, char estado);

/**
\brief Função para alterar uma jogada no array jogadas
@param e Apontador para o estado atual
@param mov Coordenada da jogada
@param jogada Número da jogada para ser alterada
@param jogador Número do jogador
*/
void altera_array_jogadas(ESTADO * e, COORDENADA mov, int jogada, int jogador);

/**
\brief Função para ler o tabuleiro de um ficheiro
@param e Apontador para o estado atual
@param f_pointer Nome do ficheiro para ler o tabuleiro
@return O inteiro 1
*/
int ler_tabuleiro(ESTADO *e , FILE * f_pointer);

/**
\brief Função para ler os movs de um ficheiro
@param e Apontador para o estado atual
@param f_pointer Nome do ficheiro para ler os movs
*/
void ler_movs(ESTADO * e, FILE * f_pointer);

/**
\brief Função para reinicir o pos
@param e Apontador para o estado atual
@param pos Número fornecido ao pos
@param jog Array das Jogadas
@return O estado depois de aplicado o comando pos
*/
void reinicia_pos (ESTADO *e, int pos, JOGADA *jog);

/**
\brief Função para obter o array das jogadas
@param e Apontador para o estado atual
@return O array das Jogadas
 */
JOGADA *obter_array_jogadas (ESTADO *e);

/**
\brief Função para alterar o jogador para o próximo
@param jogador O número do jogador atual
@return O número do próximo jogador
*/
int switch_player(int jogador );
#endif
