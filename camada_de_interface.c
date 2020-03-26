#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#include "logica_do_programa.h"
#define BUF_SIZE 1024



void mostrar_tabuleiro(ESTADO *e, FILE *f_pointer) { // desenha o tabuleiro que esta declarado no estado
    COORDENADA c;
    char letras = 'a';
    int print_in_stdout = 0;      // indica se estamos a fazer print num ficheiro ou no stdout, utilizado para restringir o que é armazenado no ficheiro
    if (f_pointer == NULL) {      // verifica que se existe algum  ficheiro aberto caso contrario o f_pointer passa a ser stdout
        f_pointer = stdout;
        print_in_stdout = 1;
    }
    for(int linhas = 7; linhas >= 0 ; linhas--){
        if(print_in_stdout)
            printf("%d ",linhas + 1 );                  // da print aos numeros que se encontram do lado esquerdo do tabuleiro que correspondem à linha da coordenada da peça
        c.linha = linhas;
        for(int colunas = 0; colunas < 8 ; colunas++){
            c.coluna = colunas;
            if(linhas == 7 && colunas == 7) {
                if(obter_estado_casa(e,c) == BRANCA)
                    fprintf(f_pointer, " * " );
                else
                    fprintf(f_pointer, " 2 ");
            }
            else if (linhas == 0 && colunas == 0)
                if(obter_estado_casa(e,c) == BRANCA)
                    fprintf(f_pointer, " * " );
                else
                    fprintf(f_pointer, " 1 ");
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
    if(print_in_stdout)
        printf("  ");                   // este loop escreve em baixo do tabuleiro as letras que identificam a coluna das coordenadas do tabuleiro
    for(int i = 0 ; i < 8 && print_in_stdout ; i++){
        printf(" %c ",letras);
        letras++;
    }
    fprintf(f_pointer ,"\n");

}
void printMOVS(ESTADO *e){
    int num_jogadas = obter_numero_de_jogadas(e);
    JOGADA jogada;
    char jogada_j1_Coluna, jogada_j1_Linha, jogada_j2_Coluna, jogada_j2_Linha;
    for(int i = 0 ; i < num_jogadas - 1 ; i++ ){
        jogada = obter_estado_jogada(e,i);
        jogada_j1_Linha = jogada.jogador1.linha + '1';
        jogada_j1_Coluna = jogada.jogador1.coluna + 'a';
        jogada_j2_Linha = jogada.jogador2.linha + '1';
        jogada_j2_Coluna = jogada.jogador2.coluna + 'a';
        printf("%2d: %c%c %c%c \n", i + 1,jogada_j1_Coluna,jogada_j1_Linha,jogada_j2_Coluna,jogada_j2_Linha);
    }
}

int interpretador(ESTADO *e) { // interpretador que estava no guiao 5
    char linha[BUF_SIZE];
    char col[2], lin[2],file_name[64];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        int jogadorAnterior = obter_jogador_atual(e);
        if (verificaJogada(e, coord)){
            incrementa_num_comandos(e);
            if (verifica_Vitoria_Jog1(e, coord) == 1){
                printf("O Jogador 1 ganhou!");
                modifica_num_jogadas(e, 31);
            }
            else if (verifica_Vitoria_Jog2 (e, coord) == 1){
                printf ("O Jogador 2 ganhou!");
                modifica_num_jogadas(e, 31);
            }
            jogar(e, coord);
            mostrar_tabuleiro(e,NULL);
        }
        else printf("A jogada introduzida é invalida. Jogue novamente.\n");
        if (verifica_Bloqueio(e, coord)){
            printf("O Jogador %d ficou bloqueado... O Jogador %d é o vencedor!", obter_jogador_atual(e), jogadorAnterior);
            modifica_num_jogadas(e, 32);
        }
    }
    if(strlen(linha) == 2 && sscanf(linha , "Q") == 0){                        // termina o programa retornando 0 que quebra o ciclo do main
        return  0;
    }
    if(sscanf(linha,"gr %s",file_name) == 1){            // implementação do comando gr que cria um ficheiro e guarda o estado do tabuleiro
        grava_dados(e,file_name);                        // grava o estado do tabuleiro num ficheiro
    }
    if(sscanf(linha,"ler %s",file_name) == 1)
        ler_dados(e,file_name);
    if(strlen(linha) == 5 && sscanf(linha,"movs") == 0)
        printMOVS(e);
    return 1;
}

void showPrompt (ESTADO *e){
    int num_comandos, jogadorAtual, num_jogadas;
    num_comandos = obter_num_comandos(e);
    jogadorAtual = obter_jogador_atual(e);
    num_jogadas = obter_numero_de_jogadas(e);
    printf("# nº comandos: %d  JOGADOR: %d  (%d) $ ",num_comandos, jogadorAtual, num_jogadas);
}



