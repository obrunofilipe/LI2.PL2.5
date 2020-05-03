/**
 @file camada_de_interface.c
 Dados presentes na interface e funções que a alteram
*/
#include <stdio.h>
#include <string.h>
#include "camada_de_dados.h"
#include "logica_do_programa.h"
/**
\brief Tamanho da string lida
*/
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
    JOGADA jogada;
    char jogada_j1_Coluna, jogada_j1_Linha, jogada_j2_Coluna, jogada_j2_Linha;
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
        fprintf(f_pointer,"%02d: %c%c %c%c\n", i + 1 ,jogada_j1_Coluna,jogada_j1_Linha,jogada_j2_Coluna,jogada_j2_Linha); // print dos movimentos no formato pretendido
    }
    if(movimentos_j1 > movimentos_j2){
        jogada = obter_estado_jogada(e,i);
        jogada_j1_Coluna = jogada.jogador1.coluna + 'a';
        jogada_j1_Linha = jogada.jogador1.linha + '1';
        fprintf(f_pointer,"%02d: %c%c\n",i + 1 , jogada_j1_Coluna,jogada_j1_Linha);
    }

    incrementa_num_comandos(e);

}

int interpretador(ESTADO *e) { // interpretador que estava no guiao 5
    char linha[BUF_SIZE];
    char col[2], lin[2],file_name[64];
    int numero_jogada;
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        if (verificaJogada(e, coord)){
            incrementa_num_comandos(e);
            if (verifica_Vitoria_Jog1(coord,0) == 1){
                return 0;
            }
            else if (verifica_Vitoria_Jog2 (coord,0)){
                return 0;
            }
            jogar(e, coord);
            mostrar_tabuleiro(e,NULL);
        }
        else printf("A jogada introduzida é invalida. Jogue novamente.\n");
        if (verifica_Bloqueio(e, coord)){
            return 0;
        }
    }
    if(strlen(linha) == 2 && strcmp(linha , "Q\n") == 0){                        // termina o programa retornando 0 que quebra o ciclo do main
        return  0;
    }
    if(sscanf(linha,"gr %s",file_name) == 1){            // implementação do comando gr que cria um ficheiro e guarda o estado do tabuleiro
        grava_dados(e,file_name);                        // grava o estado do tabuleiro num ficheiro
    }
    if(sscanf(linha,"ler %s",file_name) == 1) {
        FILE * f_pointer;
        f_pointer = fopen(file_name,"r");
        if(f_pointer == NULL)
            printf("Erro ao ler ficheiro!\n");
        else {
            ler_tabuleiro(e,f_pointer);
            ler_movs(e,f_pointer);
        }
        fclose(f_pointer);
        mostrar_tabuleiro(e,NULL);

    }
    if(strlen(linha) == 5 && strcmp(linha,"movs\n") == 0)
        printMOVS(e,NULL);
    if(sscanf(linha,"pos %d",&numero_jogada) == 1){
        altera_estado_casa(e, obter_ultima_jogada(e), '.');
        JOGADA *array_jog = obter_array_jogadas(e);
        reinicia_pos(e, numero_jogada, array_jog);
        mostrar_tabuleiro(e, NULL);
    }
    if(strlen(linha) == 4 && strcmp(linha,"jog\n") == 0){
        COORDENADA jogada;
        jogada = jog(e,obter_ultima_jogada(e));
        jogar(e, jogada);
        mostrar_tabuleiro(e,NULL);

        if (verifica_Vitoria_Jog1(jogada,0))
            return 0;
        if(verifica_Vitoria_Jog2(jogada,0))
            return  0;
        if(verifica_Bloqueio(e,jogada))
            return 0;
    }
    if(strlen(linha) == 5 && strcmp(linha,"jog2\n") == 0){
        COORDENADA jogada, c;
        c = obter_ultima_jogada(e);
        if (obter_jogador_atual(e) == 1 && (distancia_a_1(&c) == 1 || distancia_a_1(&c) == 2)){
            jogada = jog(e, c);
        }
        else if (obter_jogador_atual(e) == 2 && (distancia_a_2(&c) == 1 || distancia_a_2(&c) == 2)){
            jogada = jog(e, c);
        }
        else {
            jogada = jog2(e, c);
        }
        jogar(e, jogada);
        mostrar_tabuleiro(e,NULL);
        if (verifica_Vitoria_Jog1(jogada,0))
            return 0;
        if(verifica_Vitoria_Jog2(jogada,0))
            return  0;
        if(verifica_Bloqueio(e,jogada))
            return 0;
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