#ifndef MANIPULADOR_DE_DIRETIVAS

#define MANIPULADOR_DE_DIRETIVAS

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"

int tratador_de_diretivas(Lista_ligada **diretiva, Lista_ligada **lista_de_cte, Lista_ligada **lista_de_desconhecidos, int *palavra_atual, int *align, char *orientacao, char mapa[][13]);
int trata_set(Lista_ligada *set, Lista_ligada **lista_de_cte);
int trata_org(Lista_ligada *argumento1, int *palavra_atual);
int trata_align(Lista_ligada *argumento1, int *align);
int trata_wfill(Lista_ligada *wfill, Lista_ligada **lista_de_desconhecidos, char mapa[][13], int *palavra_atual, char *orientacao);
int trata_word(Lista_ligada *argumento1, Lista_ligada **lista_de_desconhecidos, char mapa[][13], int *palavra_atual, char *orientacao);


#endif