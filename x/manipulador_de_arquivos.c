#include "manipulador_de_arquivos.h"

int verifica_parametros(int argc,char *argv[], char **arquivo_de_entrada, char **arquivo_de_saida)
{
	switch (argc)
	{
		case (1):
		{
			fprintf(saida, "Erro! Arquivo de entrada nao fornecido!\n");
			return 1;
		}

		case (2):
		{
			*arquivo_de_entrada = argv[1];
			fprintf(saida, "Arquivo de Entrada: %s\n", *arquivo_de_entrada);
			return 0;
		}

		case (3):
		{
			*arquivo_de_entrada = argv[1];	
			// fprintf(saida, "Arquivo de Entrada: %s\n", *arquivo_de_entrada);

			*arquivo_de_saida = argv[2];
			// fprintf(saida, "Arquivo de Saida: %s\n", *arquivo_de_saida);
			return 0;
		}
		default:
		{
			fprintf(saida, "Erro! Excesso de parametros.\n");
			return 1;
		}
	}
}

// Essa funcao le o arquivo de entrada.
Lista_ligada* le_arquivo_de_entrada(char* arquivo_de_entrada)
{
	char temp = 0;
	int cursor_inicio = 0, cursor_fim = 0;
	int conta_linha = 1, tamanho;
	char *buffer;
	Lista_ligada *programa;
	boolean linha_vazia = TRUE;

	// Abertura do arquivo de entrada.
	FILE* ponteiro_arq_de_entrada = fopen(arquivo_de_entrada, "r");

	// Verifica se o arquivo foi aberto corretamente.
	if (ponteiro_arq_de_entrada == NULL)
	{
		fprintf(saida, "Arquivo \"%s\" nao foi encontrado!\n", arquivo_de_entrada);
		return NULL;
	}

	// Cria lista encadeada para registrar o programa em linguagem de montagem.
	cria_lista(&programa);

	// Percorre o arquivo ateh o final, lendo um caractere de cada vez.
	while (fscanf(ponteiro_arq_de_entrada, "%c", &temp) != EOF)
	{
		// Contador para o tamanho da linha.
		cursor_fim++;
		// Verifica se a linha nao esta vazia, ou seja so possui espacos.
		if (linha_vazia && temp != ' ' && temp != '\t' && temp != '\n')
		{
			linha_vazia = FALSE;
		}

		// Verifica se nao eh apenas um espaco em branco ou uma linha vazia.
		else if (((temp == ' ' || temp == '\t') && cursor_fim - cursor_inicio == 1) || (temp == '\n' && linha_vazia))
		{
			cursor_inicio++;
		}

		// Final de linha ou quando encontra um espaco ou tab.
		else if (temp == '\n' || temp == ' ' || temp == '\t')
		{
			tamanho = cursor_fim - cursor_inicio;
			if (tamanho > 1)
			{
				// Faz com que o ponteiro do arquivo retorne ao inicio do objeto analisado.
				fseek(ponteiro_arq_de_entrada, (-tamanho * sizeof(char)), SEEK_CUR);

				// Aloca o espaço necessário para o registro da linha.
				buffer = malloc(tamanho * sizeof(char));

				// Leitura de toda a linha de uma vez
				fread(buffer, (tamanho * sizeof(char)), 1, ponteiro_arq_de_entrada);

				// Determina o fim da string.
				buffer[tamanho - 1] = '\0';
				
				adiciona_celula(&programa, buffer, "", conta_linha);
			}
			// caso seja um espaco
			if (temp == ' ' || temp == '\t')
			{
				cursor_inicio = cursor_fim;
			}
		}
		if (temp == '\n')
		{
			// Incrementa o contador de linhas.
			conta_linha++;

			// Zera os cursores.
			cursor_inicio = 0;
			cursor_fim = 0;

			// Reinicia a flag.
			linha_vazia = TRUE;
		}
	}

	// Fecha o arquivo de entrada.
	fclose(ponteiro_arq_de_entrada);

	return programa;
}

FILE * get_arquivo_de_escrita(char *arquivo_de_saida)
{
	FILE* temp = fopen(arquivo_de_saida, "w");

	if (temp == NULL)
	{
		temp = fopen(arquivo_de_saida, "w");
	}

	if (temp == NULL)
	{
		fprintf(stdout, "Erro ao abrir o arquivo de saida: %s\n", arquivo_de_saida);
	}
	return temp;
}
void grava_arquivo_de_saida(Lista_ligada *mapa)
{
	int palavra_atual;
	char *endereco;

	if (mapa != NULL)
	{
		endereco = decimal_para_hex(mapa->info, 3);
		fprintf(saida, "%s ", endereco);
		palavra_atual = mapa->info;
	}
	for (; mapa != NULL; mapa = mapa->prox)
	{
		if (palavra_atual != mapa->info)
		{
			fprintf(saida, "\n");
			endereco = decimal_para_hex(mapa->info, 3);
			fprintf(saida, "%s ", endereco);
			palavra_atual = mapa->info;
		}
		
		for (int posicao = 0; posicao < 5; posicao++)
		{
			if (posicao == 2)
			{
				fprintf(saida, " ");
			}
			fprintf(saida, "%c", mapa->string[posicao]);
		}
		// Caso esteja no lado esquerdo.
		if (mapa->string2[0] == 'E')
		{
			fprintf(saida, " ");

			// Completa com zeros o lado direito da palavra.
			if (mapa->prox == NULL || mapa->prox->string2[0] == 'E')
			{
				fprintf(saida, "00 000");
			}

		}
	}
	fprintf(saida, "\n");

	if (saida != NULL)
	{
		fclose(saida);
	}
}