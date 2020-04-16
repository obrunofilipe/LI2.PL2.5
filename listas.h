#ifndef _LISTAS_H
#define _LISTAS_H

typedef struct nodo {
    void *valor;
    struct nodo *proximo;
} NODO, *LISTA;

//cria uma lista
LISTA criar_lista();
//insere um novo elemento à cabeça
LISTA insere_cabeca(LISTA L, void *valor);
//devolve a cabeça da Lista
void *devolve_cabeca(LISTA L);
//devolve a cauda da lista
LISTA proximo(LISTA L);
// remove a cabeça da lista libertando o espaço ocupado e retorna a cauda
LISTA remove_cabeca(LISTA L);
//Devolve verdadeiro se a lista é vazia
int lista_esta_vazia(LISTA L);

#endif
