#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"

void copiaTabuleiro (CASA tab[8][8] ,CASA tabuleiro[8][8]){
    for(int linhas = 0; linhas < 8 ;linhas++){
        for(int colunas = 0; colunas < 8 ; colunas++){
            tab[linhas][colunas] = tabuleiro[linhas][colunas];
        }
    }
}

void inicializar_tabuleiro(CASA tab[8][8]){ //incializa o tabuleiro
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
                tab [linha] [coluna] = VAZIO;
        }
    }
}


int obter_jogador_atual(ESTADO *estado){ // retorna o numero do jogador atual
    return estado->jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *estado){ // retorna o numero de jogadas que esta armazenado no estado
    return estado->num_jogadas;
}

void atualiza_estado_casa (ESTADO *e, COORDENADA c){ // atualiza a casa para a qual foi jogada para BRANCA
    int coluna, linha;
    coluna = c.coluna;
    linha = c.linha;
    e->tab[linha][coluna] = BRANCA;
}

void atualiza_estado_jogo

CASA obter_estado_casa(ESTADO *e, COORDENADA c){ // retorna o estado de uma casa do tabuleiro (VAZIO , BRANCA , PRETA)
    int coluna, linha;
    CASA estadoCasa;
    coluna = c.coluna;
    linha = c.linha;
    estadoCasa = e->tab[linha][coluna];
    return estadoCasa;
}

ESTADO *inicializar_estado(){
    CASA tabuleiro[8][8];                                   // declarar o tabuleiro
    ESTADO *estadoJogo = (ESTADO *) malloc(sizeof(ESTADO)); // declarar o estado
    inicializar_tabuleiro(tabuleiro);                       // modifica a matriz  tabuleiro
    estadoJogo->jogador_atual = 1;                          // inicializa o jogador_atual
    estadoJogo->num_jogadas = 0;                            // inicializa o número de jogadas
    copiaTabuleiro(estadoJogo->tab,tabuleiro);              // copia a matris modificada para a matriz do estado
    estadoJogo->ultima_jogada.coluna = 5;                   //incializa a coordenada coluna da ultima jogada
    estadoJogo->ultima_jogada.linha = 4;                    //incializa a coordenada linha da ultima jogada
    return estadoJogo;
}

void atualiza_estado_jogo (ESTADO *e, COORDENADA c){
    int coluna, linha;
    coluna = c.coluna;
    linha = c.linha;
    e->tab[linha][coluna] = BRANCA;
    e->ultima_jogada.coluna = coluna;
    e->ultima_jogada.linha = linha;
    e->num_jogadas++;
}
