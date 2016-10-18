//manipulador_de_instrucoes.h
#ifndef MANIPULADOR_DE_INSTRUCOES

#define MANIPULADOR_DE_INSTRUCOES
#include <stdio.h>
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_memoria.h"

int tratador_de_instrucoes(Lista_ligada **instrucao, Lista_ligada **lista_de_rotulos_desc, char mapa[][13], int *palavra_atual, char *orientacao);
int identifica_instrucao(Lista_ligada *instrucao);


#endif