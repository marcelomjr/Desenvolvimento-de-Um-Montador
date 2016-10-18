//manipulador_de_memoria.h
#ifndef MANIPULADOR_DE_MEMORIA

#define MANIPULADOR_DE_MEMORIA

#include <stdio.h>
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"
#include "manipulador_de_conversoes.h"

void avanca_meia_palavra(Lista_ligada **mapa, char *palavra, char *orientacao, int *num_palavra);
int preenche_palavra_n_vezes(Lista_ligada* elemento, char mapa[][13], char *palavra, int palavra_atual, char orientacao, int n);
void imprime_mapa(Lista_ligada** mapa);


#endif