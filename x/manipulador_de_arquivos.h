// manipulador_de_arquivos.h
#ifndef MANIPULADOR_DE_ARQUIVOS_H

#define MANIPULADOR_DE_ARQUIVOS_H

#include <stdio.h>
#include <stdlib.h>

#include "manipulador_de_lista_ligada.h"

Lista_ligada* le_arquivo_de_entrada(char* arquivo_de_entrada);
int verifica_parametros(int argc,char *argv[], char **arquivo_de_entrada, char **arquivo_de_saida);

#endif
