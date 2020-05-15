#ifndef ZIPPROJETO_CAMADA_DE_INTERFACE_H
#define ZIPPROJETO_CAMADA_DE_INTERFACE_H
/**
 \brief Include de stdio.h
 */
#include <stdio.h>
/**
 \brief Include de camada_de_dados.h
 */
#include "camada_de_dados.h"

/**
 \brief Include de string.h
 */
#include <string.h>

/**
 \brief Include de logica_do_programa.h
 */
#include "logica_do_programa.h"

/**
\brief Tamanho da string lida
*/
#define BUF_SIZE 1024

/**
\brief Funções para alterarem a interface
*/

/**
\brief Função para mostrar o tabuleiro
@param e Apontador para o Estado atual
@param f_pointer Apontador de memória para a criação de um ficheiro
 */
void mostrar_tabuleiro(ESTADO *e, FILE * f_pointer);

/**
\brief
@param e Apontador para o Estado atual
@return 0 se houver algum erro ou terminar o jogo, 1 em caso contrário
*/
int interpretador(ESTADO *e);

/**
\brief Função para colocar o prompt no ecrã
@param e Apontador para o Estado atual
*/
void showPrompt (ESTADO *e);

/**
\brief Função para colocar os movs de um ficheiro
@param e Apontador para o estado atual
@param f_pointer Nome do ficheiro
*/
void printMOVS(ESTADO *e,FILE * f_pointer);

#endif //ZIPPROJETO_CAMADA_DE_INTERFACE_H
