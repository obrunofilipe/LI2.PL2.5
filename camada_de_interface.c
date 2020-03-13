#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#include "logica_do_programa.h"
#define BUF_SIZE 1024


void mostrar_tabuleiro(ESTADO *e) { // desenha o tabuleiro que esta declarado no estado
    for(int linhas = 0; linhas < 8 ; linhas++){
        for(int colunas = 0; colunas < 8 ; colunas++){
            if(linhas == 0 && colunas == 7)
                printf(" 2 ");
            else if (linhas == 7 && colunas == 0)
                printf(" 1 ");

            else {
                switch (e->tab[linhas][colunas]) {
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

}

int interpretador(ESTADO *e) { // interpretador que estava no guiao 5
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}
