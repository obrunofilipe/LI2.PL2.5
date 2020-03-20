#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#include "logica_do_programa.h"
#define BUF_SIZE 1024



void mostrar_tabuleiro(ESTADO *e, FILE *f_pointer) { // desenha o tabuleiro que esta declarado no estado
    COORDENADA c;
    char letras = 'a';
    if (f_pointer == NULL)
        f_pointer = stdout;
    for(int linhas = 7; linhas >= 0 ; linhas--){
        fprintf(f_pointer ,"%d ",linhas + 1 );                  // da print aos numeros que se encontram do lado esquerdo do tabuleiro que correspondem à linha da coordenada da peça
        c.linha = linhas;
        for(int colunas = 0; colunas < 8 ; colunas++){
            c.coluna = colunas;
            if(linhas == 7 && colunas == 7)
                fprintf(f_pointer ," 2 ");
            else if (linhas == 0 && colunas == 0)
                fprintf(f_pointer ," 1 ");
            else {
                switch (obter_estado_casa(e,c)) {
                    case VAZIO:
                        fprintf(f_pointer ," . ");
                        break;
                    case BRANCA:
                        fprintf(f_pointer ," * ");
                        break;
                    case PRETA:
                        fprintf(f_pointer ," # ");
                        break;
                }
            }
        }
        fprintf(f_pointer ,"\n");
    }
    fprintf(f_pointer,"  ");                   // este loop escreve em baixo do tabuleiro as letras que identificam a coluna das coordenadas do tabuleiro
    for(int i = 0 ; i < 8 ; i++){
        fprintf(f_pointer ," %c ",letras);
        letras++;
    }
    fprintf(f_pointer ,"\n");

}

int interpretador(ESTADO *e) { // interpretador que estava no guiao 5
    char linha[BUF_SIZE];
    char col[2], lin[2],file_name[64];
    FILE * f_pointer;

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        if (verificaJogada(e, coord)){
            incrementa_num_comandos(e);
            jogar(e, coord);
            mostrar_tabuleiro(e,NULL);
            if (verifica_Vitoria_Jog1(e, coord) == 1){
                printf("O Jogador 1 ganhou!");
                modifica_num_jogadas(e, 32);
            }
            else if (verifica_Vitoria_Jog2 (e, coord) == 1){
                printf ("O Jogador 2 ganhou!");
                modifica_num_jogadas(e, 32);
            }
        }
        else printf("A jogada introduzida é invalida. Jogue novamente.\n");
    }
    if(sscanf(linha , "Q") == 0){                        // termina o programa invocando uma funçao que altera o numero de jogadas na estrutura de dados
        return  0;
    }
    if(sscanf(linha,"gr %s",file_name) == 1){            // implementação do comando gr que cria um ficheiro e guarda o estado do tabuleiro
        f_pointer = fopen(file_name,"w");
        mostrar_tabuleiro(e,f_pointer);
        fclose(f_pointer);
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



