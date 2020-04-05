#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"
#define BUF_SIZE 1024



void inicializar_tabuleiro(CASA tab[8][8]){ //incializa o tabuleiro
    int linha,coluna;
    for(linha = 7; linha >= 0 ; linha--){
        for(coluna = 0 ; coluna < 8 ; coluna++){
            tab [linha] [coluna] = VAZIO;
        }
    }
    tab [4][4] = BRANCA;
}
// retorna a jogada selecionada no array pelo num_jogadas
JOGADA obter_estado_jogada(ESTADO *e , int num_jogadas){
    return e->jogadas[num_jogadas];
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
    CASA tabuleiro[8][8];                                   // declarar o tabuleiro
    ESTADO *estadoJogo = (ESTADO *) malloc(sizeof(ESTADO)); // declarar o estado
    inicializar_tabuleiro(estadoJogo->tab);                 // modifica a matriz  tabuleiro
    estadoJogo->jogador_atual = 1;                          // inicializa o jogador_atual
    estadoJogo->num_jogadas = 0;                            // inicializa o número de jogadas
    estadoJogo->ultima_jogada.coluna = 4;                   // incializa a coordenada coluna da ultima jogada
    estadoJogo->ultima_jogada.linha = 4;                    // incializa a coordenada linha da ultima jogada
    estadoJogo->movimentos_j2 = 0;
    estadoJogo->movimentos_j1 = 0;
    return estadoJogo;
}

void atualiza_estado_jogo (ESTADO *e, COORDENADA c){
    int coluna, linha, jogadorAtual;

    coluna = c.coluna;
    linha = c.linha;
    jogadorAtual = obter_jogador_atual(e);
    e->tab[e->ultima_jogada.linha][e->ultima_jogada.coluna] = PRETA; // muda a peca anterior para vazio
    e->tab[linha][coluna] = BRANCA; // muda a peça em que o jogador pretende jogar
    e->ultima_jogada = c;           // altera a ultima jogada
    if(jogadorAtual == 1) {         // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas].jogador1 = c;
        e->jogador_atual = 2;
        e->movimentos_j1++;
    }
    else { // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas].jogador2 = c;
        e->jogador_atual = 1 ;
        e->num_jogadas++;               // aumenta o numero de jogadas
        e->movimentos_j2++;
    }
}
int obter_numero_movimentos(ESTADO *e , int jogador){
    if(jogador == 1)
        return e->movimentos_j1;
    else
        return  e->movimentos_j2;
}

void mudar_jogador_atual (ESTADO *e, int jogador){
    e->jogador_atual = jogador;
}

void incrementa_num_comandos(ESTADO *e){
    e->num_comandos++;
}

int obter_num_comandos(ESTADO *e){
    return e->num_comandos;
}

void modifica_num_jogadas (ESTADO *e , int numJogadas){
    e->num_jogadas = numJogadas;
}

COORDENADA obter_ultima_jogada(ESTADO *e ){
    return e->ultima_jogada;
}

void altera_ultima_jogada(ESTADO * e , COORDENADA c){
    e->ultima_jogada = c;
}

void altera_movimentos_j1 (ESTADO *e, int mov_j1){
    e->movimentos_j1 = mov_j1;
}

void altera_movimentos_j2 (ESTADO *e, int mov_j2){
    e->movimentos_j2 = mov_j2;
}

void altera_estado_casa(ESTADO *e, COORDENADA posicao, char estado){
    CASA casa_alterada;
    switch(estado){
        case '.':
            casa_alterada = VAZIO;
            break;
        case '*':
            casa_alterada = BRANCA;
            break;
        case '#':
            casa_alterada = PRETA;
            break;
    }
    e->tab[posicao.linha][posicao.coluna] = casa_alterada;
}
void altera_array_jogadas(ESTADO * e , COORDENADA mov, int jogada , int  jogador ){
    if(jogador == 1)
        e->jogadas[jogada-1].jogador1 = mov;
    else
        e->jogadas[jogada-1].jogador2 = mov;
}

void grava_dados(ESTADO *e , char * file_name ){
    FILE * f_pointer;
    f_pointer = fopen(file_name,"w");
    mostrar_tabuleiro(e,f_pointer);
    printMOVS(e,f_pointer);
    fclose(f_pointer);
    incrementa_num_comandos(e);
}

int ler_tabuleiro(ESTADO *e , FILE * f_pointer){
    for(int l = 7; l >= 0 ; l--){
        char linha[BUF_SIZE];
        fgets(linha,BUF_SIZE,f_pointer);
        for(int c = 0 ; c < 15 ; c++) {
            COORDENADA posicao = {c/2, l};
            if (c % 2 == 0) {
                altera_estado_casa(e, posicao, linha[c]);
            }
        }
    }
    return 1;
}

void ler_movs(ESTADO * e, FILE * f_pointer){
    char linha[BUF_SIZE];
    int numjogadas ,jogada,movimentos_j1,movimentos_j2;
    char movJ1[3],movJ2[3];
    jogada = 0;
    numjogadas = 0;
    movimentos_j1 = 0;
    movimentos_j2 = 0;
    while(fgets(linha,BUF_SIZE,f_pointer) != NULL){
        if(strlen(linha) == 11 && sscanf(linha,"%02d: %s %s",&jogada,movJ1,movJ2) == 3) {
            COORDENADA jogada_j1 = {movJ1[0] - 'a', movJ1[1] - '1'};
            COORDENADA jogada_j2 = {movJ2[0] - 'a', movJ2[1] - '1'};
            altera_array_jogadas(e,jogada_j1,jogada  ,1);
            altera_array_jogadas(e,jogada_j2,jogada , 2);
            altera_ultima_jogada(e,jogada_j2);
            ++numjogadas;
            ++movimentos_j1;
            ++movimentos_j2;
            mudar_jogador_atual(e, 1);
        }
        if(strlen(linha) < 11 && sscanf(linha,"%02d: %s",&jogada,movJ1) == 2){
            COORDENADA jogada_j1 = {movJ1[0] - 'a', movJ1[1] - '1'};
            altera_array_jogadas(e,jogada_j1,jogada  ,1);
            altera_ultima_jogada(e,jogada_j1);
            ++movimentos_j1;
            mudar_jogador_atual(e, 2);
        }
    }
    modifica_num_jogadas(e,numjogadas);
    altera_movimentos_j1 (e, movimentos_j1);
    altera_movimentos_j2 (e, movimentos_j2);
}

void reinicia_pos (ESTADO *e, int pos, JOGADA *jog){
    int i, movs_j1, movs_j2, n_jogadas;
    movs_j1 = 0;
    movs_j2 = 0;
    n_jogadas = 0;
    inicializar_tabuleiro(e->tab);
    mostrar_tabuleiro(e, NULL);
    for (i = 0; i < pos; i++) {
        altera_estado_casa(e, jog[i].jogador1, '#');
        altera_estado_casa(e, jog[i].jogador2, '#');
        movs_j1++;
        movs_j2++;
        n_jogadas++;
    }
    if (pos != 0){
        altera_estado_casa(e, jog[i-1].jogador2, '*');
    }
    altera_ultima_jogada(e, jog[i-1].jogador2);
    modifica_num_jogadas(e, n_jogadas);
    altera_movimentos_j1(e,movs_j1);
    altera_movimentos_j2(e,movs_j2);
}


JOGADA *obter_array_jogadas (ESTADO *e){
    return e->jogadas;
}
