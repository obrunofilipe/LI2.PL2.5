#ifndef ___LOGICA_DO_PROGRAMA_H___
#define ___LOGICA_DO_PROGRAMA_H___

/**
 @file logica_do_programa.h
 Definições dos dados presentes no estado e das funções que o alteram
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
\brief Função para verificar se uma jogada é possível
@param e Apontador para o Estado atual
@param c Coordenada
@return O inteiro 1 se a jogada for possível, 0 em caso contrário
*/
int verificaJogada (ESTADO *e, COORDENADA c);

/**
\brief Função que verifica se o jogador 1 venceu
@param e Apontado para o Estado atual
@param c Coordenada
@return O inteiro 1 se venceu, 0 em caso contrário
*/
int verifica_Vitoria_Jog1 (ESTADO *e, COORDENADA c);

/**
\brief Função que verifica se o jogador 2 venceu
@param e Apontado para o Estado atual
@param c Coordenada
@return O inteiro 1 se venceu, 0 em caso contrário
*/
int verifica_Vitoria_Jog2 (ESTADO *e, COORDENADA c);
int verifica_Bloqueio (ESTADO *e, COORDENADA c);

#endif