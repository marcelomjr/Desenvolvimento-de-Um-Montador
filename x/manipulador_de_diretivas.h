#ifndef MANIPULADOR_DE_DIRETIVAS

#define MANIPULADOR_DE_DIRETIVAS

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"
#include "manipulador_de_memoria.h"
#include "manipulador_de_argumentos.h"
#include "manipulador_de_conversoes.h"

extern FILE* saida;

int tratador_de_diretivas(Lista_ligada **diretiva, Lista_ligada **lista_de_simbolos, Lista_ligada **lista_de_desconhecidos, int *palavra_atual, int *align, char *orientacao, Lista_ligada **mapa);
int trata_set(Lista_ligada *set, Lista_ligada **lista_de_simbolos);
int trata_org(Lista_ligada *argumento1, int *palavra_atual);
int trata_align(Lista_ligada *argumento1,Lista_ligada **mapa, int *align, char *orientacao, int *num_palavra);
int trata_wfill(Lista_ligada *wfill, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao, int align);
int trata_word(Lista_ligada *argumento1, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao, int align);

#endif