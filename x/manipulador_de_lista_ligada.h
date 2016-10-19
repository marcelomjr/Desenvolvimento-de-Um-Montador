//manipulador_de_lista_ligada.h
#ifndef MANIPULADOR_DE_LISTA_LIGADA_H

#define MANIPULADOR_DE_LISTA_LIGADA_H

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "manipulador_de_caracteres.h"

struct lista
{
	long int info;
	char *string;
	char *string2;
	struct lista *prox;
} typedef Lista_ligada;

void cria_lista(Lista_ligada **lista);

void adiciona_celula(Lista_ligada **lista, char* str1, char* str2, int informacao);

void imprime_lista(Lista_ligada *lista, int opcao_de_string);

void remove_lista(Lista_ligada** lista);

#endif