//manipulador_de_memoria.h
#ifndef MANIPULADOR_DE_MEMORIA

#define MANIPULADOR_DE_MEMORIA

#include <stdio.h>
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"

void avanca_meias_palavra(int *palavra_atual, char *orientacao, int quantidade);
void imprime_mapa(char mapa[][13]);
void preenche_enderecos(char mapa[][13]);
void inicializa_mapa(char mapa[][13]);

#endif