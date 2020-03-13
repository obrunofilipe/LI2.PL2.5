#include <stdio.h>
#include "camada_de_dados.h"
int jogar(ESTADO *e, COORDENADA c) {
    atualiza_estado_jogo (e, c);
    printf("jogar %d %d\n", c.coluna, c.linha);
    return 1;
}