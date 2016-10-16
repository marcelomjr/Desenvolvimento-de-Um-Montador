//manipulador_de_lista_ligada.h
#ifndef MANIPULADOR_DE_LISTA_LIGADA_H

#define MANIPULADOR_DE_LISTA_LIGADA_H

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

struct lista
{
	int info;
	char *string;
	struct lista *prox;
} typedef Lista_ligada;

void cria_lista(Lista_ligada **lista);

void adiciona_celula(Lista_ligada **lista, char* str, int informacao);

void imprime_lista(Lista_ligada *lista);

void remove_lista(Lista_ligada** lista);

#endif