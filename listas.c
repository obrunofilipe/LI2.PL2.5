#include <_stdio.h>
#include <stdlib.h>
#include "listas.h"

LISTA criar_lista(){
    LISTA  l;
    l = malloc( sizeof(NODO) );
    return l;
}

LISTA insere_cabeca(LISTA L, void *valor){
    LISTA  nodo_novo;
    if(L != NULL){
        nodo_novo = criar_lista();
        nodo_novo->valor   = valor;
        nodo_novo->proximo = L;
    }
    else {
        L = criar_lista(L);
        L->valor = valor;
        L->proximo = NULL;
    }
    return L;
}

void *devolve_cabeca(LISTA L){
    return  L->valor;
}

LISTA proximo(LISTA L){
    L = L->proximo;
    return L;
}

LISTA remove_cabeca(LISTA L){
    LISTA C;
    C = L;
    L = L->proximo;
    free(C);
    return L;
}
int lista_esta_vazia(LISTA L){
    if(L == NULL)
        return 1;
    else
        return 0;
}