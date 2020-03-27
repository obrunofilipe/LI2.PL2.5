#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"
#define BUF_SIZE 1024



void inicializar_tabuleiro(CASA tab[8][8]){ //incializa o tabuleiro
    int linha,coluna;
    for(linha = 7; linha > 0 ; linha--){
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
    estadoJogo->num_jogadas = 1;                            // inicializa o número de jogadas
    estadoJogo->ultima_jogada.coluna = 4;                   //incializa a coordenada coluna da ultima jogada
    estadoJogo->ultima_jogada.linha = 4;                    //incializa a coordenada linha da ultima jogada
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
    if(jogadorAtual == 1 ) {        // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas - 1].jogador1 = c;
        e->jogador_atual = 2;
    }
    else { // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas - 1].jogador2 = c;
        e->jogador_atual = 1 ;
        e->num_jogadas++;               // aumenta o numero de jogadas
    }
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
        e->jogadas[jogada].jogador1 = mov;
    else
        e->jogadas[jogada].jogador2 = mov;
    printf("%d%d\n",e->jogadas[jogada].jogador1.coluna,e->jogadas[jogada].jogador1.linha);
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
    int numjogadas = 0;
    int jogada = 0;
    char movJ1[3],movJ2[3];
    while(fgets(linha,BUF_SIZE,f_pointer) != NULL){
        if(strlen(linha) == 11 && sscanf(linha,"%d: %s %s",&jogada,movJ1,movJ2) == 3) {
            COORDENADA jogada_j1 = {movJ1[0] - 'a', movJ1[1] - '1'};
            COORDENADA jogada_j2 = {movJ2[0] - 'a', movJ2[1] - '1'};
            altera_array_jogadas(e,jogada_j1,jogada - 1 ,1);
            altera_array_jogadas(e,jogada_j2,jogada - 1, 2);
            ++numjogadas;
        }
        if(strlen(linha) < 11 && sscanf(linha,"%02d: %s",&jogada,movJ1) == 2){
            COORDENADA jogada_j1 = {movJ1[0] - 'a', movJ1[1] - '1'};
            altera_array_jogadas(e,jogada_j1,jogada - 1 ,1);
            printf("%s\n",movJ1);
            ++numjogadas;
        }
    }
    modifica_num_jogadas(e,numjogadas);
}
/*
void ler_dados(ESTADO *e , char * file_name){
    FILE * f_pointer;
    char caracter;
    int linha,coluna;
    linha = 7;
    coluna = 0;
    f_pointer = fopen(file_name, "r");
    if(f_pointer != NULL){
        while((caracter = fgetc(f_pointer)) != EOF){
            switch(caracter){
                case '.':
                    e->tab[linha][coluna] = VAZIO;
                    coluna++;
                    break;
                case '#':
                    e->tab[linha][coluna] = PRETA;
                    coluna++;
                    break;
                case '*':
                    e->tab[linha][coluna] = BRANCA;
                    e->ultima_jogada.coluna = coluna;
                    e->ultima_jogada.linha = linha;
                    coluna++;
                    break;
                case '1':
                    e->tab[linha][coluna] = VAZIO;
                    coluna++;
                    break;
            }
            if(caracter == '\n') {
                linha--;
                coluna = 0;
            }
        }
    }
    else {
        printf("ERRO: Ficheiro desconhecido!\n");
    }
    fclose(f_pointer);
    mostrar_tabuleiro(e,NULL);
    incrementa_num_comandos(e);
}
 */