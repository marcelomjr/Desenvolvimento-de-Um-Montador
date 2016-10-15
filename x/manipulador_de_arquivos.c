#include "manipulador_de_arquivos.h"

int verifica_parametros(int argc,char *argv[], char **arquivo_de_entrada, char **arquivo_de_saida)
{
	switch (argc)
	{
		case (1):
		{
			printf("Erro! Arquivo de entrada nao fornecido!\n");
			return 1;
		}

		case (2):
		{
			*arquivo_de_entrada = argv[1];
			printf("Arquivo de Entrada: %s\n", *arquivo_de_entrada);
			return 0;
		}

		case (3):
		{
			*arquivo_de_entrada = argv[1];	
			printf("Arquivo de Entrada: %s\n", *arquivo_de_entrada);

			*arquivo_de_saida = argv[2];
			printf("Arquivo de Saida: %s\n", *arquivo_de_saida);
			return 0;
		}
		default:
		{
			printf("Erro! Excesso de parametros.\n");
			return 1;
		}
	}
}

// Essa funcao le o arquivo de entrada.
Lista_ligada* le_arquivo_de_entrada(char* arquivo_de_entrada)
{
	char temp = 0;
	int conta_char = 0;
	char *buffer;
	Lista_ligada *programa;

	// Abertura do arquivo de entrada.
	FILE* ponteiro_arq_de_entrada = fopen(arquivo_de_entrada, "r");

	// Verifica se o arquivo foi aberto corretamente.
	if (ponteiro_arq_de_entrada == NULL)
	{
		printf("Arquivo \"%s\" nao foi encontrado!\n", arquivo_de_entrada);
		return NULL;
	}

	// Cria lista encadeada para registrar o programa em linguagem de montagem.
	cria_lista(&programa);

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
				
				adiciona_celula(&programa, buffer);

				// pegar uma linha, colocar numa string e mandar para a função de analise.
			}

			// Zera contador de caracteres.
			conta_char = 0;
		}

	}

	// Fecha o arquivo de entrada.
	fclose(ponteiro_arq_de_entrada);
	return programa;
}