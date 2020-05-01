#include <stdio.h>
#ifndef BOT_CAMADA_DE_INTERFACE_H_
#define BOT_CAMADA_DE_INTERFACE_H_

/**
 @file bot_camada_de_interface.h
 Definições dos dados da interface e das funções que a alteram
*/

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
\brief Função para colocar os movs de um ficheiro
@param e Apontador para o estado atual
@param f_pointer Nome do ficheiro
*/
void printMOVS(ESTADO *e,FILE * f_pointer);

#endif