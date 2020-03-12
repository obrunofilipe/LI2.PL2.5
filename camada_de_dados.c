#include <stdio.h>
#include "camada_de_dados.h"

void inicializar_tabuleiro(CASA *tab){
    int linha,coluna;
    for(linha = 0; linha < 8 ; linha++){
        if(linha == 3){
            for(coluna = 0 ; coluna < 8 ; coluna++){
                if(coluna == 4)
                    tab [linha] [coluna] = BRANCA;
                else
                    tab [linha] [coluna] = VAZIO;
            }
        }
        else {
            for(coluna = 0; coluna < 8 ; coluna++)
                tabuleiro [linha] [coluna] = VAZIO;
        }
    }
}




ESTADO *inicializar_estado(){
    CASA tabuleiro[8][8]; // declarar o tabuleiro
    ESTADO estadoJogo;    // declarar o estado
    inicializar_tabuleiro(tabuleiro);  // modifica a matriz  tabuleiro
	estadoJogo.jogador_atual = 1;      // inicializa o jogador_atual
	estadoJogo.num_jogadas = 0;        // inicializa o número de jogadas
	strcpy(estadoJogo.tab, tabuleiro); // copia a matris modificada para a matriz do estado
	estadoJogo.ultima_jogada = {5,4};



}

