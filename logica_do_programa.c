#include <stdio.h>
#include "camada_de_dados.h"
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
    if (((c.linha == 7 && c.coluna == 7) || (c.linha == 0 && c.coluna == 0)) && obter_jogador_atual(e) == 1)
        return 1;
    else return 0;
}

int verifica_Vitoria_Jog2 (ESTADO *e, COORDENADA c){
    if (((c.linha == 7 && c.coluna == 7) || (c.linha == 0 && c.coluna == 0)) && obter_jogador_atual(e) == 2)
        return 1;
    else return 0;
}

int verifica_Bloqueio (ESTADO *e, COORDENADA c){
    CASA baixo = e->tab[c.linha-1][c.coluna];
    CASA cima = e->tab[c.linha+1][c.coluna];
    CASA direita = e->tab[c.linha][c.coluna+1];
    CASA esquerda = e->tab[c.linha][c.coluna-1];
    CASA direita_baixo = e->tab[c.linha-1][c.coluna+1];
    CASA direita_cima = e->tab[c.linha+1][c.coluna+1];
    CASA esquerda_baixo = e->tab[c.linha-1][c.coluna-1];
    CASA esquerda_cima = e->tab[c.linha+1][c.coluna-1];

    if (c.linha == 7 && c.coluna == 0){
        if (direita == PRETA && direita_baixo == PRETA && baixo == PRETA)
            return 1;
        else return 0;
    }
    else if (c.linha == 0 && c.coluna == 7){
        if (e->tab[c.linha][c.coluna-1] == PRETA && e->tab[c.linha+1][c.coluna-1] == PRETA && e->tab[c.linha+1][c.coluna] == PRETA)
            return 1;
        else return 0;
    }
    else if (c.linha == 0){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA && direita_cima == PRETA && direita == PRETA)
            return 1;
        else return 0;
    }
    else if (c.linha == 7){
        if (esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA)
            return 1;
        else return 0;
    }
    else if (c.coluna == 0){
        if (cima == PRETA && direita_cima == PRETA && direita == PRETA && direita_baixo == PRETA && baixo == PRETA)
            return 1;
        else return 0;
    }
    else if (c.coluna == 7){
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA)
            return 1;
        else return 0;
    }
    else {
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA && direita_cima == PRETA)
            return 1;
        else return 0;
    }
}