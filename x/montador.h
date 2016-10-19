#ifndef MONTADOR_H

#define MONTADOR_H

#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

#include "manipulador_de_arquivos.h"
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"
#include "manipulador_de_diretivas.h"
#include "manipulador_de_memoria.h"
#include "manipulador_de_instrucoes.h"
#include "manipulador_de_conversoes.h"
#include "manipulador_de_argumentos.h"

int primeira_montagem(Lista_ligada* programaLM, Lista_ligada **mapa, Lista_ligada **lista_de_rotulos, Lista_ligada **lista_de_simbolos, Lista_ligada **lista_de_desconhecidos);
int segunda_montagem(Lista_ligada** mapa, Lista_ligada *lista_de_rotulos, Lista_ligada *lista_de_simbolos, Lista_ligada *lista_de_desconhecidos);

FILE* saida;

#endif