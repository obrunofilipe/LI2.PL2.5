#include <stdio.h>
#include <stdlib.h>
#include "camada_de_dados.h"
#include "camada_de_interface.h"



void inicializar_tabuleiro(CASA tab[8][8]){ //incializa o tabuleiro
    int linha,coluna;
    for(linha = 7; linha > 0 ; linha--){
            for(coluna = 0 ; coluna < 8 ; coluna++){
                    tab [linha] [coluna] = VAZIO;
            }
    }
    tab [4][4] = BRANCA;
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
    e->num_jogadas++;               // aumenta o numero de jogadas
    if(jogadorAtual == 1 ) {        // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas - 1].jogador1 = c;
        e->jogador_atual = 2;
    }
    else { // armazena a jogada no array JOGADAS
        e->jogadas[e->num_jogadas - 1].jogador2 = c;
        e->jogador_atual = 1 ;
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

void grava_dados(ESTADO *e , * file_name ){
    FILE * f_pointer;
    f_pointer = fopen(file_name,"w");
    mostrar_tabuleiro(e,f_pointer);
    fclose(f_pointer);
}

void ler_dados(ESTADO *e , * file_name){
    FILE * f_pointer;
    char armazena_linha[25];
    int coluna, i_armazena_linha;
    printf("ler dados");
    f_pointer = fopen(file_name, "r");
    if(f_pointer == NULL)
        printf("ERRO: Ficheiro não encontrado!\n");
    else {
        printf("loop");
        for(int linha = 0 ; linha < 8 ; linha++){
            fscanf(f_pointer, "%s",armazena_linha);
            coluna = 0;
            i_armazena_linha = 0;
            while(coluna < 8 ){
                if(armazena_linha[coluna] == '1' || armazena_linha[coluna] == '2' || armazena_linha[coluna] == '*' ||
                   armazena_linha[coluna] == '#' || armazena_linha[coluna] == '.' ){
                    switch(armazena_linha[coluna]){
                        case '#':
                            e->tab[linha][coluna] = PRETA;
                            break;
                        case '*':
                            e->tab[linha][coluna] = BRANCA;
                            break;
                        default:
                            e->tab[linha][coluna] = VAZIO;
                            break;
                    }
                    coluna++;
                }
                i_armazena_linha++;
            }
        }
    }
    fclose(f_pointer);
    mostrar_tabuleiro(e,NULL);
}