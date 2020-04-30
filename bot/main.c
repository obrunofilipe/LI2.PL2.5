#include <stdio.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"
#include "logica_do_programa.h"
#include "listas.h"


int main(int argc, char *f_name[]) {
    FILE *f_in;
    FILE *f_out;

    ESTADO *e = inicializar_estado();

    //pegar no estado dado no ficheiro passado como argumento

    f_in = fopen(f_name[1],"r");
    if(f_in == NULL)
        printf("Erro ao ler ficheiro!\n");
    else {
        ler_tabuleiro(e,f_in);
        ler_movs(e,f_in);
    }
    fclose(f_in);
    mostrar_tabuleiro(e,NULL);

    //jogada do bot

    COORDENADA jogada;
    jogada = jog2(e, obter_ultima_jogada(e));
    jogar(e, jogada);
    mostrar_tabuleiro(e,NULL);
    if (verifica_Vitoria_Jog1(jogada,0))
        return 0;
    if(verifica_Vitoria_Jog2(jogada,0))
        return  0;
    if(verifica_Bloqueio(e,jogada))
        return 0;

    grava_dados(e, f_name[2]);

}
