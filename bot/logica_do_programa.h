#ifndef BOT_LOGICA_DO_PROGRAMA_H_
#define BOT_LOGICA_DO_PROGRAMA_H_
#include "listas.h"
/**
 @file bot_logica_do_programa.h
 Definições da lógica do programa e das funções que a alteram
*/

/**
\brief Funções relacionadas à lógica do programa
*/


/**
\brief Função para jogar
@param estado Apontador para o Estado atual
@param c Coordenada
@return O inteiro 1
*/
int jogar(ESTADO *estado, COORDENADA c);

/**
\brief Função que verifica se o jogador 1 venceu
@param c Coordenada
@param minimax 0 ou 1 dependendo se é necessário dar print
@return O inteiro 1 se venceu, 0 em caso contrário
 */
//alter

int verifica_Vitoria_Jog1 (COORDENADA c, int minimax);

/**
\brief Função que verifica se o jogador 2 venceu
@param c Coordenada
@param minimax 0 ou 1 dependendo se é necessário dar print
@return O inteiro 1 se venceu, 0 em caso contrário
 */
//alterei esta funçao
int verifica_Vitoria_Jog2 (COORDENADA c, int minimax);

/**
\brief Função que verifica se um jogador está bloqueado, ou seja, não existe nenhuma possibilidade de efetuar uma jogada válida
@param e Apontador para o estado atual
@param c Coordenada
@return O inteiro 1 caso esteja bloqueado, 0 caso contrário
 */
int verifica_Bloqueio (ESTADO *e, COORDENADA c);

/**
\brief Função auxiliar para calcular a distância euclidiana até à posição 1
@param c Coordenada
@return A distância à posição 1
*/
int distancia_a_1 (COORDENADA *c);

/**
\brief Função auxiliar para calcular a distância euclidiana até à posição 2
@param c Coordenada
@return A distância à posição 2
*/
int distancia_a_2 (COORDENADA *c);

/**
\brief
@param e Apontador para o estado atual
@param L Lista de posições possíveis
@return A posição para a qual se pode mover de modo a ficar mais perto do objetivo
*/
COORDENADA* euristica (ESTADO *e, LISTA L);

/**
\brief Função para armazenar as posições possíveis de jogar
@param e Apontador para o estado atual
@param L Lista para ser alterada com as posições possíveis
@param posicoes Array de posições a avaliar
@return A lista L com todas as posições possíveis
*/
LISTA armazena_posicoes(CASA tab[8][8],LISTA L, COORDENADA *posicoes);

/**
\brief Função para colocar no ecrã as diversas componentes de uma lista
@param L A lista que deve ser reproduzida
*/
void print_LISTA(LISTA L);

/**
\brief Função para criar um array com as posições à volta da posição atual
@param a A coordenada atual
@param array Array a ser preenchido
 */
void criaArray_posicoes(COORDENADA a, COORDENADA* array);

/**
\brief Função para executar o comando jog
@param e Apontador para o estado atual
@param pos A posição atual
@return A melhor jogada possível de forma a aproximar-se do objetivo segundo o algoritmo da distância euclidiana
*/
COORDENADA jog (ESTADO  *e, COORDENADA pos);

/**
\brief Função para calcular a maximização do jogador segundo o minmax
@param c A coordenada atual
@param maximizingPlayer O jogador a ser maximizado
@return O valor da maximização
*/
int score_minimax (COORDENADA *c , int maximizingPlayer );

/**
\brief Função para aplicar a heurística minmax
@param tab O tabuleiro
@param c A coordenada atual
@param depth Número de camadas a analisar
@param maximizingPlayer Jogador a maximizar, ou seja, o jogador que vai utilizar a heurística
@param player Jogador adversário
@param alpha A melhor maximização até ao moment
@param beta A melhor minimização até ao momento
@return O melhor resultado obtido na heurística
 */
int minimax (CASA tab[8][8] , COORDENADA *c, int depth, int maximizingPlayer, int player, int alpha, int beta);


/**
\brief Função para executar o comando jog2
@param e Apontador para o estado atual
@param c Coordenada atual
@return A jogada que traz mais benefícios ao jogador atual e menos ao adversário segundo a heurística minmax
*/
COORDENADA jog2 (ESTADO *e, COORDENADA c);

#endif