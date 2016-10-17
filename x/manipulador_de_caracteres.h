// manipulador_de_caracteres.h
#ifndef MANIPULADOR_DE_CARACTERES

#define MANIPULADOR_DE_CARACTERES

#include <stdio.h>
#include "manipulador_de_lista_ligada.h"

// Funcoes de conversao de base.
char * decimal_para_hex(int numero, int num_digitos);
int base_string_para_decimal_int(char *string, int base);


// Funcoes de validacao de argumentos.
boolean verifica_hexadecimal(Lista_ligada *numero, boolean imprime_erros);
boolean verifica_decimal (Lista_ligada *numero, int min, int max, int *num_decimal, boolean imprime_erros);
boolean verifica_rotulo(Lista_ligada *rotulo, boolean imprime_erros);
boolean verifica_simbolo(Lista_ligada *simbolo, boolean imprime_erros);

// Funcoes de manipulacao de strings.
char * copia_string(char *string1, int inicio);
boolean compara_strings(char *string1, char *string2);

int preenche_palavra_n_vezes(Lista_ligada* elemento, char mapa[][13], char *palavra, int palavra_atual, char orientacao, int n);

#endif