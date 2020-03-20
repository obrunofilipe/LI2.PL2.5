#include <stdio.h>
#ifndef ___CAMADA_DE_INTERFACE_H___
#define ___CAMADA_DE_INTERFACE_H___



void mostrar_tabuleiro(ESTADO *e, FILE * f_pointer);
int interpretador(ESTADO *e);
void showPrompt (ESTADO *e); // coloca o prompt no ecra

#endif