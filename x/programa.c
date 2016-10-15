/*
 * programa.c
 *
 *  Created on: 13 de out de 2016
 *      Author: marcelo
 */
#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

int le_arquivo_de_entrada(char* arquivo_de_entrada);

int main(int argc,char *argv[])
{
	char* arquivo_de_entrada;
	char* arquivo_de_saida;

	printf("Numero de argumentos: %d\n", argc);

	if (argc == 1)
	{
		printf("Erro! Arquivo de entrada nao fornecido!\n");
		return 0;
	}

	printf("Arquivo de Entrada: %s\n", argv[1]);
	arquivo_de_entrada = argv[1];

	if (argc == 3)
	{
		printf("Arquivo de Saida: %s\n", argv[2]);
		arquivo_de_saida = argv[2];
	}

	if (argc > 3)
	{
		printf("Erro! Excesso de parametros.\n");
		return 0;
	}

	if (le_arquivo_de_entrada(arquivo_de_entrada) == 1)
	{
		printf("Erro na leitura do arquivo de entrada!\n");
		return 0;
	}

	return 0;
}
// Essa funcao le o arquivo de entrada.
int le_arquivo_de_entrada(char* arquivo_de_entrada)
{
	char temp = 0;
	int conta_char = 0;
	char *buffer;

	// Abertura do arquivo de entrada.
	FILE* ponteiro_arq_de_entrada = fopen(arquivo_de_entrada, "r");

	// Verifica se o arquivo foi aberto corretamente.
	if (ponteiro_arq_de_entrada == NULL)
	{
		printf("Arquivo \"%s\" nao foi encontrado!\n", arquivo_de_entrada);
		return 1;
	}

	// Percorre o arquivo ateh o final, lendo um caractere de cada vez.
	while (fscanf(ponteiro_arq_de_entrada, "%c", &temp) != EOF)
	{
		// Contador para o tamanho da linha.
		conta_char++;

		// Final de linha.
		if (temp == '\n')
		{
			if (conta_char != 1)
			{
				// Faz com que o ponteiro do arquivo retorne ao inicio da linha.
				fseek(ponteiro_arq_de_entrada, (-conta_char * sizeof(char)), SEEK_CUR);

				// Aloca o espaço necessário para o registro da linha.
				buffer = malloc(conta_char * sizeof(char));

				// Leitura de toda a linha de uma vez
				fread(buffer, (conta_char * sizeof(char)), 1, ponteiro_arq_de_entrada);

				// Determina o fim da string.
				buffer[conta_char - 1] = '\0';
				
				printf("[%s]", buffer);
				// pegar uma linha, colocar numa string e mandar para a função de analise.

				// Libera a memoria alocada.
				free(buffer);
			}
			
			// Zera contador de caracteres.
			conta_char = 0;
		}
	}
	// Fecha o arquivo de entrada.
	fclose(ponteiro_arq_de_entrada);
}
