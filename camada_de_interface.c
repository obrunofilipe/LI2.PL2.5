#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#include "logica_do_programa.h"
#define BUF_SIZE 1024


void mostrar_tabuleiro(ESTADO *e) { // desenha o tabuleiro que esta declarado no estado
    COORDENADA c;
    char letras = 'a';
    for(int linhas = 7; linhas >= 0 ; linhas--){
        printf("%d ",linhas + 1 );                  // da print aos numeros que se encontram do lado esquerdo do tabuleiro que correspondem à linha da coordenada da peça
        c.linha = linhas;
        for(int colunas = 0; colunas < 8 ; colunas++){
            c.coluna = colunas;
            if(linhas == 7 && colunas == 7)
                printf(" 2 ");
            else if (linhas == 0 && colunas == 0)
                printf(" 1 ");

            else {
                switch (obter_estado_casa(e,c)) {
                    case VAZIO:
                        printf(" . ");
                        break;
                    case BRANCA:
                        printf(" * ");
                        break;
                    case PRETA:
                        printf(" # ");
                        break;
                }
            }
        }
        printf("\n");
    }
    printf("  ");                   // este loop escreve em baixo do tabuleiro as letras que identificam a coluna das coordenadas do tabuleiro
    for(int i = 0 ; i < 8 ; i++){
        printf(" %c ",letras);
        letras++;
    }
    printf("\n");

}

int interpretador(ESTADO *e) { // interpretador que estava no guiao 5
    char linha[BUF_SIZE];
    char col[2], lin[2], quit[2];

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        if (verificaJogada(e, coord)){
            incrementa_num_comandos(e);
            jogar(e, coord);
            mostrar_tabuleiro(e);
        }
        else printf("A jogada introduzida é invalida. Jogue novamente.\n");
    }
    if(strlen(linha) == 2 && sscanf(linha, "%[Q]",quit) == 1){              // termina o programa invocando uma funçao que altera o numero de jogadas na estrutura de dados
        modifica_num_jogadas(e,32);
    }

    return 1;
}

void showPrompt (ESTADO *e){
    int num_comandos, jogadorAtual, num_jogadas;
    num_comandos = obter_num_comandos(e);
    jogadorAtual = obter_jogador_atual(e);
    num_jogadas = obter_numero_de_jogadas(e);
    printf("# nº comandos: %d  JOGADOR: %d  (%d) $ ",num_comandos, jogadorAtual, num_jogadas);
}


