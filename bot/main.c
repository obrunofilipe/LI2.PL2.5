#include <stdio.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"
#include "logica_do_programa.h"


int main(int argc, char *f_name[]) {

    FILE *f_in;

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

    //jogada do bot

    COORDENADA jogada, c;
    c = obter_ultima_jogada(e);

    if (obter_jogador_atual(e) == 1 && (distancia_a_1(&c) == 1 || distancia_a_1(&c) == 2)){
        jogada = jog(e, c);
    }
    else if (obter_jogador_atual(e) == 2 && (distancia_a_2(&c) == 1 || distancia_a_2(&c) == 2)){
        jogada = jog(e, c);
    }
    else {
        jogada = jog2(e, c);
    }
    jogar(e, jogada);
    if (verifica_Vitoria_Jog1(jogada,0))
        return 0;
    if(verifica_Vitoria_Jog2(jogada,0))
        return  0;
    if(verifica_Bloqueio(e,jogada))
        return 0;

    grava_dados(e, f_name[2]);

    return 0;

}