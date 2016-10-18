// manipulador_de_caracteres.h
#ifndef MANIPULADOR_DE_CARACTERES

#define MANIPULADOR_DE_CARACTERES

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

int getTamanho(char *string);
char * copia_string(char *string1, int inicio);
boolean compara_strings(char *string1, char *string2);
void quebra_string(char *fonte, char *string1, char *string2);

#endif