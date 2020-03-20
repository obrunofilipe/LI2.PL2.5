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