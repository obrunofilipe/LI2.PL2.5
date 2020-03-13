#include "camada_de_dados.h"
#include "camada_de_interface.h"
#include <string.h>
int main()
{
    ESTADO *e = inicializar_estado();
    while (e->num_jogadas < 32){
        interpretador(e);
    }
    return 0;
}
