/*
 * programa.c
 *
 *  Created on: 13 de out de 2016
 *      Author: marcelo
 */
#include "montador.h"

int main(int argc,char *argv[])
{
	char* arquivo_de_entrada;
	char* arquivo_de_saida;
	Lista_ligada* programaLM;

	if (verifica_parametros(argc, argv, &arquivo_de_entrada, &arquivo_de_saida) == 1)
	{
		return 0;
	}

	programaLM = le_arquivo_de_entrada(arquivo_de_entrada);

	if (programaLM == NULL)
	{
		printf("Erro na leitura do arquivo de entrada!\n");
		return 0;
	}

	imprime_lista(programaLM);
	
	return 0;
}
