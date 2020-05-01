#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#define BUF_SIZE 1024



void mostrar_tabuleiro(ESTADO *e, FILE *f_pointer){ // desenha o tabuleiro que esta declarado no estado
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
                if(obter_estado_casa(e->tab,c) == BRANCA)
                    fprintf(f_pointer, "*" );
                else
                    fprintf(f_pointer, "2");
            }
            else if (linhas == 0 && colunas == 0)
                if(obter_estado_casa(e->tab,c) == BRANCA)
                    fprintf(f_pointer, "*" );
                else
                    fprintf(f_pointer, "1");
            else {
                switch (obter_estado_casa(e->tab,c)) {
                    case VAZIO:
                        fprintf(f_pointer ,".");
                        break;
                    case BRANCA:
                        fprintf(f_pointer ,"*");
                        break;
                    case PRETA:
                        fprintf(f_pointer ,"#");
                        break;
                }
            }
        }
        fprintf(f_pointer ,"\n");
    }
    if(print_in_stdout)
        printf("  ");                   // este loop escreve em baixo do tabuleiro as letras que identificam a coluna das coordenadas do tabuleiro
    for(int i = 0 ; i < 8 && print_in_stdout ; i++){
        printf("%c",letras);
        letras++;
    }
    fprintf(f_pointer ,"\n");

}
void printMOVS(ESTADO *e, FILE * f_pointer){
    int i ,movimentos_j1,movimentos_j2; // varivel utilizada no ciclo
    int num_jogadas = obter_numero_de_jogadas(e); // numero total de jogadas efetuadas
    COORDENADA ultimajogada = obter_ultima_jogada(e); // ultimo movimento efetuado
    JOGADA jogada;
    char jogada_j1_Coluna, jogada_j1_Linha, jogada_j2_Coluna, jogada_j2_Linha, ultimaJogada_linha,ultimaJogada_coluna;
    movimentos_j1 = obter_numero_movimentos(e,1);
    movimentos_j2 = obter_numero_movimentos(e,2);
    if(f_pointer == NULL)
        f_pointer = stdout;
    for( i = 0; i < num_jogadas; i++ ){
        jogada = obter_estado_jogada(e,i); // obter a jogada correspondente ao indice i do array que armazena as jogadas no estado e
        jogada_j1_Linha = jogada.jogador1.linha + '1'; // converter as coordenadas da jogada que esta armazenada no array no indice i em caracteres
        jogada_j1_Coluna = jogada.jogador1.coluna + 'a';
        jogada_j2_Linha = jogada.jogador2.linha + '1';
        jogada_j2_Coluna = jogada.jogador2.coluna + 'a';
        fprintf(f_pointer,"%02d: %c%c %c%c \n", i + 1 ,jogada_j1_Coluna,jogada_j1_Linha,jogada_j2_Coluna,jogada_j2_Linha); // print dos movimentos no formato pretendido
    }
    if(movimentos_j1 > movimentos_j2){
        jogada = obter_estado_jogada(e,i);
        jogada_j1_Coluna = jogada.jogador1.coluna + 'a';
        jogada_j1_Linha = jogada.jogador1.linha + '1';
        fprintf(f_pointer,"%02d: %c%c\n",i + 1 , jogada_j1_Coluna,jogada_j1_Linha);
    }

    incrementa_num_comandos(e);

}
