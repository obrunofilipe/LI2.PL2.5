#include "camada_de_dados.h"
#include "camada_de_interface.h"
#include <string.h>
#include <stdio.h>

int main()
{
    int jogadas;
    ESTADO *e = inicializar_estado();
    jogadas = 0;
    mostrar_tabuleiro(e,NULL);
    while (jogadas < 32){
        showPrompt(e);      //showprompt que irá colocar o prompt no ecra
        interpretador(e);
        jogadas  = obter_numero_de_jogadas(e);
    }
    return 0;
}
