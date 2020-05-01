#include <stdio.h>
#include <math.h>
#include "camada_de_dados.h"
#include "listas.h"
#include "logica_do_programa.h"
#include <stdlib.h>
#define MENOS_INFINITO -10000000
#define MAIS_INFINITO 10000000

int jogar(ESTADO *e, COORDENADA c) {
        atualiza_estado_jogo (e, c);
        printf("jogar %d %d\n", c.coluna, c.linha);
        return 1;
}

int verificaJogada (ESTADO *e, COORDENADA c) {
    int r;
    int l_anterior = obter_ultima_jogada(e).linha;
    int c_anterior = obter_ultima_jogada(e).coluna;
    if ((c.coluna == c_anterior + 1 || c.coluna == c_anterior - 1 || c.coluna == c_anterior)
    && (c.linha == l_anterior + 1 || c.linha == l_anterior - 1 || c.linha == l_anterior)
    && obter_estado_casa(e->tab, c) == VAZIO){
        r = 1;
    }
    else
        r = 0;

    return r;
}

int verifica_Vitoria_Jog1 (COORDENADA c, int minimax){
    if (c.linha == 0 && c.coluna == 0){
        if(!minimax)
            printf("JOGADOR 1 GANHOU");
        return 1;
    }
    else return 0;
}

int verifica_Vitoria_Jog2 (COORDENADA c ,int minimax){
    if (c.linha == 7 && c.coluna == 7) {
        if(!minimax)
            printf("JOGADOR 2 GANHOU");
        return 1;
    }
    else return 0;
}

int verifica_Bloqueio (ESTADO *e, COORDENADA c){
    COORDENADA c_baixo = {c.coluna, c.linha-1};
    COORDENADA c_cima = {c.coluna, c.linha+1};
    COORDENADA c_direita = {c.coluna+1, c.linha};
    COORDENADA c_esquerda = {c.coluna-1, c.linha};
    COORDENADA c_direita_baixo = {c.coluna+1, c.linha-1};
    COORDENADA c_direita_cima = {c.coluna+1, c.linha+1};
    COORDENADA c_esquerda_baixo = {c.coluna-1, c.linha-1};
    COORDENADA c_esquerda_cima = {c.coluna-1, c.linha+1};

    CASA baixo = obter_estado_casa(e->tab, c_baixo);
    CASA cima = obter_estado_casa(e->tab, c_cima);
    CASA direita = obter_estado_casa(e->tab, c_direita);
    CASA esquerda = obter_estado_casa(e->tab, c_esquerda);
    CASA direita_baixo = obter_estado_casa(e->tab, c_direita_baixo);
    CASA direita_cima = obter_estado_casa(e->tab, c_direita_cima);
    CASA esquerda_baixo = obter_estado_casa(e->tab, c_esquerda_baixo);
    CASA esquerda_cima = obter_estado_casa(e->tab, c_esquerda_cima);

    if (c.linha == 7 && c.coluna == 0){
        if (direita == PRETA && direita_baixo == PRETA && baixo == PRETA) {
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 0 && c.coluna == 7){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 0){
        if (esquerda == PRETA && esquerda_cima == PRETA && cima == PRETA && direita_cima == PRETA && direita == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.linha == 7){
        if (esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.coluna == 0){
        if (cima == PRETA && direita_cima == PRETA && direita == PRETA && direita_baixo == PRETA && baixo == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else if (c.coluna == 7){
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
    else {
        if (cima == PRETA && esquerda_cima == PRETA && esquerda == PRETA && esquerda_baixo == PRETA && baixo == PRETA && direita_baixo == PRETA && direita == PRETA && direita_cima == PRETA){
            printf("O Jogador %d ficou bloqueado...", obter_jogador_atual(e) );
            return 1;
        }
        else return 0;
    }
}

int distancia_a_1 (COORDENADA *c){
    int dist;
    dist = ((c->coluna * c->coluna) + (c->linha * c->linha));
    return dist;
}

int distancia_a_2 (COORDENADA *c){
    int dist;
    dist = (((c->coluna - 7)*(c->coluna - 7)) + ((c->linha - 7)*(c->linha - 7)));
    return dist;
}

COORDENADA* euristica (ESTADO *e, LISTA L){
    COORDENADA *menor;
    menor = L->valor;
    while (!lista_esta_vazia (L)){
        if (obter_jogador_atual(e) == 1){
            if (distancia_a_1 (L->valor) < distancia_a_1(menor)){
                menor = L->valor;
            }
        }
        else {
            if (distancia_a_2 (L->valor) < distancia_a_2(menor)){
                menor = L->valor;
            }
        }
        L = proximo(L);
    }
    return menor;
}

LISTA armazena_posicoes(CASA tab[8][8] ,LISTA L, COORDENADA *posicoes){
    for(int i = 0; i < 8 ; i++){
        if( (tab[posicoes[i].linha][posicoes[i].coluna]) != PRETA && posicoes[i].coluna >= 0 && posicoes[i].coluna <= 7
                                                                  && posicoes[i].linha  >= 0 && posicoes[i].linha  <= 7 )
        L = insere_cabeca(L,posicoes + i);
    }
    return L;
}

void print_LISTA(LISTA L){
    COORDENADA *c;
    while(L != NULL){
        c = L->valor;
        printf("%d%d",c->coluna,c->linha);
        printf("(%d) ",distancia_a_1(c));
        L = L->proximo;
    }
    printf("\n");
}

void criaArray_posicoes(COORDENADA a, COORDENADA* array){
    int offset_linha, //usado para calcular as coordenadas à volta de a
    offset_coluna,//usado para calcular as coordenadas à volta de a
    linha,        //nova coordenada
    coluna,       //nova coordenada
    index;        //indice para percorrer o array
    index = 0;
    for(offset_linha = -1 ; offset_linha <= 1 ; offset_linha++){
        linha = a.linha + offset_linha;
        for(offset_coluna = -1 ; offset_coluna <= 1; offset_coluna++){
            coluna = a.coluna + offset_coluna;
            if (a.linha != linha || a.coluna != coluna){
                array[index].linha = linha;
                array[index].coluna = coluna;
                index++;
            }
        }
    }
}


COORDENADA jog (ESTADO  *e, COORDENADA pos){
    COORDENADA posicoes[8];
    COORDENADA *melhor;
    LISTA JOGADAS_POSSIVEIS;
    JOGADAS_POSSIVEIS = NULL;
    criaArray_posicoes(pos, posicoes);
    JOGADAS_POSSIVEIS = armazena_posicoes(e->tab,JOGADAS_POSSIVEIS,posicoes);

    melhor = euristica(e,JOGADAS_POSSIVEIS);
    print_LISTA(JOGADAS_POSSIVEIS);
    incrementa_num_comandos(e);
    liberta_lista(JOGADAS_POSSIVEIS);
    return *melhor;
}
int score_minimax (COORDENADA *c , int maximizingPlayer ){
   int score;
    if(maximizingPlayer == 1)
        score = distancia_a_2(c) - distancia_a_1(c);
    else
        score = distancia_a_1(c) - distancia_a_2(c);
    return score;
}

int minimax (CASA tab[8][8] , COORDENADA *c, int depth, int maximizingPlayer, int player, int alpha, int beta){
    int Score, bestScore;
    LISTA  JOGADAS_POSSIVEIS = NULL;
    COORDENADA posicoes[8],*cf,copia_tab[8][8];
    criaArray_posicoes(*c,posicoes);
    JOGADAS_POSSIVEIS = armazena_posicoes(tab,JOGADAS_POSSIVEIS,posicoes);

    if (depth <= 0)
        return score_minimax(c, maximizingPlayer);
    //verifica vitoria
    if(verifica_Vitoria_Jog1(*c,1) && maximizingPlayer == 1 )
        return Score = MAIS_INFINITO;
    else if (verifica_Vitoria_Jog1(*c,1) && maximizingPlayer != 1)
        return Score = MENOS_INFINITO;
    if(verifica_Vitoria_Jog2(*c,1) && maximizingPlayer == 2)
        return Score = MAIS_INFINITO;
    else if(verifica_Vitoria_Jog2(*c,1) && maximizingPlayer != 2)
        return Score = MENOS_INFINITO;

    if(player == maximizingPlayer){
        bestScore = MENOS_INFINITO;
       //verificar bloqueio
       if(lista_esta_vazia(JOGADAS_POSSIVEIS))
           return Score = MENOS_INFINITO;
       //verificar vitoria


       //maximizar o score
       while(JOGADAS_POSSIVEIS != NULL){
           cf = JOGADAS_POSSIVEIS->valor;
           tab[c->linha][c->coluna] = PRETA;
           tab[cf->linha][cf->coluna] = BRANCA;
           Score = minimax(tab,JOGADAS_POSSIVEIS->valor, depth - 1 , maximizingPlayer , switch_player(player),alpha,beta);
           tab[c->linha][c->coluna] = BRANCA;
           tab[cf->linha][cf->coluna] = VAZIO;
           if(Score > bestScore)
               bestScore = Score;
           if(Score >= beta)
               return bestScore;
           if(Score > alpha)
               alpha = Score;
           JOGADAS_POSSIVEIS = remove_cabeca(JOGADAS_POSSIVEIS);
       }
       return bestScore;
    }
    else{
        bestScore = MAIS_INFINITO;
       //verificar bloqueio
       if(lista_esta_vazia(JOGADAS_POSSIVEIS))
           return Score = MAIS_INFINITO;
        if (depth <= 0)
            score_minimax(JOGADAS_POSSIVEIS->valor, maximizingPlayer);
       //minimizar o score
       while(JOGADAS_POSSIVEIS != NULL){
           cf = JOGADAS_POSSIVEIS->valor;
           tab[c->linha][c->coluna] = PRETA;
           tab[cf->linha][cf->coluna] = BRANCA;
           Score = minimax(tab,JOGADAS_POSSIVEIS->valor, depth - 1 , maximizingPlayer , switch_player(player),alpha,beta);
           tab[c->linha][c->coluna] = BRANCA;
           tab[cf->linha][cf->coluna] = VAZIO;
           if(Score < bestScore)
               bestScore = Score;
           if(Score <= alpha)
               return bestScore;
           if(Score < beta)
               beta = Score;
           JOGADAS_POSSIVEIS = remove_cabeca(JOGADAS_POSSIVEIS);
       }
       return bestScore;
    }
}

int bloqueio_minimax(CASA tab[8][8], LISTA CASAS_DISPONIVEIS){
    COORDENADA *c;
    int result = 1;
    while(!lista_esta_vazia(CASAS_DISPONIVEIS)){
        c = CASAS_DISPONIVEIS->valor;
        if(obter_estado_casa(tab,*c) != PRETA)
            result = 0;
        CASAS_DISPONIVEIS = remove_cabeca(CASAS_DISPONIVEIS);
    }
    return result;
}


COORDENADA jog2 (ESTADO *e, COORDENADA last_mov){
    LISTA JOGADAS_POSSIVEIS;
    COORDENADA posicoes[8], *mov,*bestMov;
    int score, bestScore,jogador,alpha,beta;
    alpha = MENOS_INFINITO;
    beta = MAIS_INFINITO;
    bestScore = MENOS_INFINITO;
    JOGADAS_POSSIVEIS = NULL;
    criaArray_posicoes(last_mov,posicoes);
    JOGADAS_POSSIVEIS = armazena_posicoes(e->tab,JOGADAS_POSSIVEIS,posicoes);
    bestMov = JOGADAS_POSSIVEIS->valor;
    while(JOGADAS_POSSIVEIS != NULL){
        mov = JOGADAS_POSSIVEIS->valor;
        altera_estado_casa(e,last_mov,'#');
        altera_estado_casa(e,*mov,'*');
        jogador = obter_jogador_atual(e);
        score = minimax(e->tab,mov,14,obter_jogador_atual(e),switch_player(obter_jogador_atual(e)), alpha,beta);  //calcular o score de cada uma das opçoes disponiveis
        altera_estado_casa(e,last_mov,'*');
        altera_estado_casa(e,*mov,'.');
        if(score > bestScore){
           bestScore = score;
           bestMov = JOGADAS_POSSIVEIS->valor;
        }
        if(score >= beta)
            return *bestMov;
        if(score > alpha)
            alpha = score;
        JOGADAS_POSSIVEIS = remove_cabeca(JOGADAS_POSSIVEIS);
    }
    return *bestMov;
}
