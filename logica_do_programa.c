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
    && (c.linha == l_anterior + 1 || c.linha == l_anterior - 1 || c.linha == l_anterior)){
        r = 1;
    }
    else
        r = 0;

    return r;
}

