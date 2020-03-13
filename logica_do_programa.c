#include <stdio.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"

int jogar(ESTADO *e, COORDENADA c) {
    printf("jogar %d %d\n", c.coluna, c.linha);
    atualiza_estado_casa (e,coord);
    return 1;
}