#include <stdio.h>
#include "camada_de_dados.h"
int jogar(ESTADO *e, COORDENADA c) {
        atualiza_estado_jogo (e, c);
        printf("jogar %d %d\n", c.coluna, c.linha);
        return 1;
}

int verificaJogada (ESTADO *e, COORDENADA c) {
    int r;
    COORDENADA cooord_anterior = e->ultima_jogada;
    int l_anterior = e->ultima_jogada.linha;
    int c_anterior = e->ultima_jogada.coluna;
    if ((c.coluna == c_anterior + 1 || c.coluna == c_anterior - 1 || c.coluna == c_anterior) && (c.linha == l_anterior + 1 || c.linha == l_anterior - 1 || c.linha == l_anterior)){
        r = 1;
    }
    else r = 0;
    return r;
}

//(coord.coluna == e->ultima_jogada.coluna + 1 || coord.coluna == e->ultima_jogada.coluna - 1 || coord.coluna == e->ultima_jogada.coluna)
// && (coord.linha == e->ultima_jogada.linha + 1 || coord.linha == e->ultima_jogada.linha - 1 || coord.linha == e->ultima_jogada.linha))