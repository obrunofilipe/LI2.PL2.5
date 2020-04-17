#include <stdio.h>
#include <math.h>
#include "camada_de_dados.h"
#include "listas.h"

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
    && obter_estado_casa(e, c) == VAZIO){
        r = 1;
    }
    else
        r = 0;

    return r;
}

int verifica_Vitoria_Jog1 (ESTADO *e, COORDENADA c){
    if (c.linha == 0 && c.coluna == 0){
        printf("JOGADOR 1 GANHOU");
        return 1;
    }
    else return 0;
}

int verifica_Vitoria_Jog2 (ESTADO *e, COORDENADA c){
    if (c.linha == 7 && c.coluna == 7) {
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

    CASA baixo = obter_estado_casa(e, c_baixo);
    CASA cima = obter_estado_casa(e, c_cima);
    CASA direita = obter_estado_casa(e, c_direita);
    CASA esquerda = obter_estado_casa(e, c_esquerda);
    CASA direita_baixo = obter_estado_casa(e, c_direita_baixo);
    CASA direita_cima = obter_estado_casa(e, c_direita_cima);
    CASA esquerda_baixo = obter_estado_casa(e, c_esquerda_baixo);
    CASA esquerda_cima = obter_estado_casa(e, c_esquerda_cima);

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

float distancia_a_1 (COORDENADA *c){
    float dist;
    dist = sqrt ((c->coluna * c->coluna) + (c->linha * c->linha));
    return dist;
}

float distancia_a_2 (COORDENADA *c){
    float dist;
    dist = sqrt (((c->coluna - 7)*(c->coluna - 7)) + ((c->linha - 7)*(c->linha - 7)));
    return dist;
}

COORDENADA* euristica (ESTADO *e, LISTA L){
    COORDENADA *menor,atual;
    atual = obter_ultima_jogada(e);
    menor = &atual;
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

LISTA armazena_posicoes(ESTADO *e,LISTA L, COORDENADA *posicoes){
    for(int i = 0; i < 8 ; i++){
        if(obter_estado_casa(e,posicoes[i]) != PRETA && posicoes[i].coluna >= 0 && posicoes[i].coluna <= 7
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
        printf("(%f) ",distancia_a_1(c));
        L = L->proximo;
    }
    printf("\n");
}

COORDENADA jog (ESTADO  *e, COORDENADA pos){
    COORDENADA posicoes[8];
    COORDENADA *melhor;
    LISTA JOGADAS_POSSIVEIS;
    JOGADAS_POSSIVEIS = NULL;
    //A
    posicoes[0].coluna = pos.coluna - 1;
    posicoes[0].linha  = pos.linha + 1;
    //B
    posicoes[1].coluna = pos.coluna;
    posicoes[1].linha  = pos.linha + 1;
    //C
    posicoes[2].coluna = pos.coluna + 1;
    posicoes[2].linha  = pos.linha + 1;
    //D
    posicoes[3].coluna = pos.coluna - 1;
    posicoes[3].linha  = pos.linha ;
    //E
    posicoes[4].coluna = pos.coluna + 1;
    posicoes[4].linha  = pos.linha;
    //F
    posicoes[5].coluna = pos.coluna - 1 ;
    posicoes[5].linha  = pos.linha - 1;
    //G
    posicoes[6].coluna = pos.coluna;
    posicoes[6].linha  = pos.linha - 1;
    //H
    posicoes[7].coluna = pos.coluna + 1;
    posicoes[7].linha  = pos.linha - 1;

   JOGADAS_POSSIVEIS = armazena_posicoes(e,JOGADAS_POSSIVEIS,posicoes);
   melhor = euristica(e,JOGADAS_POSSIVEIS);
   print_LISTA(JOGADAS_POSSIVEIS);
   return *melhor;
}
