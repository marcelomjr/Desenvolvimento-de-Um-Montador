//manipulador_de_instrucoes.h
#ifndef MANIPULADOR_DE_INSTRUCOES

#define MANIPULADOR_DE_INSTRUCOES
#include <stdio.h>
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_memoria.h"
#include "manipulador_de_argumentos.h"

int tratador_de_instrucoes(Lista_ligada **instrucao, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao, int align);
int identifica_instrucao(Lista_ligada *instrucao);


#endif