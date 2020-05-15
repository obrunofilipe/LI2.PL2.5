#ifndef ZIPPROJETO_LISTAS_H
#define ZIPPROJETO_LISTAS_H

/**
 \brief Include de stdio.h
 */
#include <stdio.h>

/**
 \brief Include de stdlib.h
 */
#include <stdlib.h>

/**
 \brief Include de listas.h
 */
#include "listas.h"
/**
\brief Tipo de dados para definir uma lista
*/
typedef struct nodo {
    /** Valor atual */
    void *valor;
    /** Nodos seguintes */
    struct nodo *proximo;
} /** Nodo definido */
NODO,
/** apontador para o inicio da lista */
*LISTA;

/**
\brief Função para criar uma lista
@return A lista
*/
LISTA criar_lista();

/**
\brief Função para adicionar elementos à cabeça de uma lista
@param L A lista inicial
@param valor O valor para adicionar à lista
@return A lista com o valor adicionado à cabeça
*/
LISTA insere_cabeca(LISTA L, void *valor);

/**
\brief Função que devolve a cabeça de uma lista
@param L A lista
*/
void *devolve_cabeca(LISTA L);

/**
\brief Função que devolve a cauda de uma lista, ou seja, que devolve a lista sem o seu primeiro elemento
@param L A lista
@return A lista sem o seu o primeiro elemento
*/
LISTA proximo(LISTA L);

/**
\brief Função para retirar a cabeça de uma lista e esvaziar o espaço previamente ocupado pela cabeça
@param L A lista
@return A lista sem o primeiro elemento
*/
LISTA remove_cabeca(LISTA L);

/**
\brief Função para verificar se uma lista é vazia, isto é, não tem nenhum elemento
@param L A lista
@return O inteiro 1 caso a lista seja vazia, o inteiro 0 em caso contrário
*/
int lista_esta_vazia(LISTA L);

/**
\brief Função para libertar a memória alocada para uma lista
@param L A lista para se libertar a memória
@return Uma lista vazia
*/
LISTA liberta_lista (LISTA L);

#endif //ZIPPROJETO_LISTAS_H
