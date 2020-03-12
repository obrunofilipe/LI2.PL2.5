#include <stdio.h>
#include "camada_de_dados.h"

c{ //incializa o tabuleiro
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


int obter_jogador_atual(ESTADO *estado){ // retorna o numero do jogador atual
    return estado->jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *estado){ // retorna o numero de jogadas que esta armazenado no estado
    return estado->num_jogadas;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c){ // retorna o estado de uma casa do tabuleiro (VAZIO , BRANCA , PRETA)
    int coluna, linha;
    CASA estadoCasa;
    coluna = c.coluna;
    linha = c.linha;
    estadoCasa = e->tab[linha][coluna];
    return estadoCasa;
}

ESTADO *inicializar_estado(){
    CASA tabuleiro[8][8];              // declarar o tabuleiro
    ESTADO estadoJogo;                 // declarar o estado
    inicializar_tabuleiro(tabuleiro);  // modifica a matriz  tabuleiro
	estadoJogo.jogador_atual = 1;      // inicializa o jogador_atual
	estadoJogo.num_jogadas = 0;        // inicializa o número de jogadas
	strcpy(estadoJogo.tab, tabuleiro); // copia a matris modificada para a matriz do estado
	estadoJogo.ultima_jogada = {5,4};
return estadoJogo;
}

