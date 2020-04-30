#include "camada_de_dados.h"
#include "camada_de_interface.h"
#include <string.h>
#include <stdio.h>


int main()
{
    int jogadas,quit;
    ESTADO *e = inicializar_estado();
    jogadas = 0;
    quit = 1;
    mostrar_tabuleiro(e,NULL);
    while (jogadas < 32 && quit != 0){
        showPrompt(e);                       //showprompt que irá colocar o prompt no ecra
        quit = interpretador(e);
        jogadas = obter_numero_de_jogadas(e);
    }

    return 0;
}
