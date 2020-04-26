#include <stdio.h>
#include <math.h>
#include "camada_de_dados.h"
#include "listas.h"
#include <stdlib.h>

int jogar(ESTADO *e, COORDENADA c) {
        atualiza_estado_jogo (e, c);
        printf("jogar %d %d\n", c.coluna, c.linha);
        return 1;
}

int verificaJogada (ESTADO *e, COORDENADA c) {
    int r;
    int l_anterior = obter_ultima_jogada(e).linha;
    int c_anterior = obter_ultima_jogada(e).coluna;
    if ((c.coluna == c_anterior + 1 || c.coluna == c_anterior - 1 || c.coluna == c_anterior)
    && (c.linha == l_anterior + 1 || c.linha == l_anterior - 1 || c.linha == l_anterior)
    && obter_estado_casa(e, c) == VAZIO){
        r = 1;
    }
    else
        r = 0;

    return r;
}

int verifica_Vitoria_Jog1 (ESTADO *e, COORDENADA c){
    if (c.linha == 0 && c.coluna == 0){
        printf("JOGADOR 1 GANHOU");
        return 1;
    }
    else return 0;
}

int verifica_Vitoria_Jog2 (ESTADO *e, COORDENADA c){
    if (c.linha == 7 && c.coluna == 7) {
        printf("JOGADOR 2 GANHOU");
        return 1;
    }
    else return 0;
}

int verifica_Bloqueio (ESTADO *e, COORDENADA c){
    COORDENADA c_baixo = {c.coluna, c.linha-1};
    COORDENADA c_cima = {c.coluna, c.linha+1};
    COORDENADA c_direita = {c.coluna+1, c.linha};
    COORDENADA c_esquerda = {c.coluna-1, c.linha};
    COORDENADA c_direita_baixo = {c.coluna+1, c.linha-1};
    COORDENADA c_direita_cima = {c.coluna+1, c.linha+1};
    COORDENADA c_esquerda_baixo = {c.coluna-1, c.linha-1};
    COORDENADA c_esquerda_cima = {c.coluna-1, c.linha+1};

    CASA baixo = obter_estado_casa(e, c_baixo);
    CASA cima = obter_estado_casa(e, c_cima);
    CASA direita = obter_estado_casa(e, c_direita);
    CASA esquerda = obter_estado_casa(e, c_esquerda);
    CASA direita_baixo = obter_estado_casa(e, c_direita_baixo);
    CASA direita_cima = obter_estado_casa(e, c_direita_cima);
    CASA esquerda_baixo = obter_estado_casa(e, c_esquerda_baixo);
    CASA esquerda_cima = obter_estado_casa(e, c_esquerda_cima);

    if (c.linha == 7 && c.coluna == 0){
        if (direita == PRETA && direita_baixo == PRETA && baixo == PRETA) {
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 0 && c.coluna == 7){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 0){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA && direita_cima == PRETA && direita == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 7){
        if (esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.coluna == 0){
        if (cima == PRETA && direita_cima == PRETA && direita == PRETA && direita_baixo == PRETA && baixo == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.coluna == 7){
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else {
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA && direita_cima == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
}

int distancia_a_1 (COORDENADA *c){
    int dist;
    dist = ((c->coluna * c->coluna) + (c->linha * c->linha));
    return dist;
}

int distancia_a_2 (COORDENADA *c){
    int dist;
    dist = (((c->coluna - 7)*(c->coluna - 7)) + ((c->linha - 7)*(c->linha - 7)));
    return dist;
}

COORDENADA* euristica (ESTADO *e, LISTA L){
    COORDENADA *menor;
    menor = L->valor;
    while (!lista_esta_vazia (L)){
        if (obter_jogador_atual(e) == 1){
            if (distancia_a_1 (L->valor) < distancia_a_1(menor)){
                menor = L->valor;
            }
        }
        else {
            if (distancia_a_2 (L->valor) < distancia_a_2(menor)){
                menor = L->valor;
            }
        }
        L = proximo(L);
    }
    return menor;
}

LISTA armazena_posicoes(ESTADO *e,LISTA L, COORDENADA *posicoes){
    for(int i = 0; i < 8 ; i++){
        if(obter_estado_casa(e,posicoes[i]) != PRETA && posicoes[i].coluna >= 0 && posicoes[i].coluna <= 7
                                                     && posicoes[i].linha  >= 0 && posicoes[i].linha  <= 7 )
        L = insere_cabeca(L,posicoes + i);
    }
    return L;
}

void print_LISTA(LISTA L){
    COORDENADA *c;
    while(L != NULL){
        c = L->valor;
        printf("%d%d",c->coluna,c->linha);
        printf("(%d) ",distancia_a_1(c));
        L = L->proximo;
    }
    printf("\n");
}

void criaArray_posicoes(COORDENADA a, COORDENADA* array){
    int offset_linha, //usado para calcular as coordenadas à volta de a
    offset_coluna,//usado para calcular as coordenadas à volta de a
    linha,        //nova coordenada
    coluna,       //nova coordenada
    index;        //indice para percorrer o array
    index = 0;
    for(offset_linha = -1 ; offset_linha <= 1 ; offset_linha++){
        linha = a.linha + offset_linha;
        for(offset_coluna = -1 ; offset_coluna <= 1; offset_coluna++){
            coluna = a.coluna + offset_coluna;
            if (a.linha != linha || a.coluna != coluna){
                array[index].linha = linha;
                array[index].coluna = coluna;
                index++;
            }
        }
    }
}


COORDENADA jog (ESTADO  *e, COORDENADA pos){
    COORDENADA posicoes[8];
    COORDENADA *melhor;
    LISTA JOGADAS_POSSIVEIS;
    JOGADAS_POSSIVEIS = NULL;
    criaArray_posicoes(pos, posicoes);
    JOGADAS_POSSIVEIS = armazena_posicoes(e,JOGADAS_POSSIVEIS,posicoes);

    melhor = euristica(e,JOGADAS_POSSIVEIS);
    print_LISTA(JOGADAS_POSSIVEIS);
    printf("jogar %d %d\n", melhor->coluna, melhor->linha);
    incrementa_num_comandos(e);
    liberta_lista(JOGADAS_POSSIVEIS);
    return *melhor;
}

int minimax (ESTADO *e, COORDENADA *c, int depth, int maximizingPlayer){
    LISTA JOGADAS_POSSIVEIS;
    JOGADAS_POSSIVEIS = NULL;
    int valor;

    if (depth == 0){
        return (distancia_a_1(c) - distancia_a_2(c));
    }

    if (maximizingPlayer == 1){
        COORDENADA posicoes[8];
        criaArray_posicoes(*c, posicoes);
        JOGADAS_POSSIVEIS = armazena_posicoes(e, JOGADAS_POSSIVEIS, posicoes);
        int menor = 1000000;
        int maior = -1000000;
        while (JOGADAS_POSSIVEIS->proximo != NULL){
            valor = minimax (e, JOGADAS_POSSIVEIS->valor, depth - 1, 2);
            if (obter_jogador_atual(e) == 1){
                if (valor < menor)
                    menor = valor;
            }
            else {
                if (valor > maior)
                    maior = valor;
            }
            JOGADAS_POSSIVEIS = JOGADAS_POSSIVEIS->proximo;
        }
        if (obter_jogador_atual(e) == 1)
            return menor;
        else return maior;
    }
    else {
        COORDENADA posicoes[8];
        criaArray_posicoes(*c, posicoes);
        JOGADAS_POSSIVEIS = armazena_posicoes(e, JOGADAS_POSSIVEIS, posicoes);
        int maior = -10000000;
        int menor = 10000000;
        while (JOGADAS_POSSIVEIS->proximo != NULL){
            valor = minimax (e, JOGADAS_POSSIVEIS->valor, depth - 1, 1);
            if (obter_jogador_atual(e) == 1){
                if (valor < menor)
                    menor = valor;
            }
            else {
                if (valor > maior)
                    maior = valor;
            }
            JOGADAS_POSSIVEIS = JOGADAS_POSSIVEIS->proximo;
        }
        if (obter_jogador_atual(e) == 1)
            return menor;
        else return maior;
    }
}

COORDENADA jog2 (ESTADO *e, COORDENADA c){
    LISTA JOGADAS_POSSIVEIS;
    COORDENADA posicoes[8];
    criaArray_posicoes(c, posicoes);
    JOGADAS_POSSIVEIS = armazena_posicoes(e, JOGADAS_POSSIVEIS, posicoes);


    COORDENADA *melhor;
    int valor_menor = 100000000;
    int atual;

    while (JOGADAS_POSSIVEIS->proximo != NULL){
        atual = minimax (e, JOGADAS_POSSIVEIS->valor, 5, e->jogador_atual);
        if (atual < valor_menor){
            valor_menor = atual;
            melhor = JOGADAS_POSSIVEIS->valor;
        }
        JOGADAS_POSSIVEIS = JOGADAS_POSSIVEIS->proximo;
    }
    return *melhor;
}
