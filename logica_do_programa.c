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
        if (direita == PRETA && direita_baixo == PRETA && baixo == PRETA)
            return 1;
        else return 0;
    }
    else if (c.linha == 0 && c.coluna == 7){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA)
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