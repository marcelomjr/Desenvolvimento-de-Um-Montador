//manipulador_de_memoria.h
#ifndef MANIPULADOR_DE_MEMORIA

#define MANIPULADOR_DE_MEMORIA

void avanca_meias_palavra(int *palavra_atual, char *orientacao, int quantidade);
void imprime_mapa(char mapa[][13]);
void preenche_enderecos(char mapa[][13]);
void inicializa_mapa(char mapa[][13]);

#endif