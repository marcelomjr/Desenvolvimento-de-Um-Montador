#include "manipulador_de_arquivos.h"

// Essa funcao le o arquivo de entrada.
int le_arquivo_de_entrada(char* arquivo_de_entrada)
{
	char temp = 0;
	int conta_char = 0;
	char **programa;

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

void inicializa_lista(Linha_prog **programa)
{
	*programa = NULL;
}

void adiciona_linha(Linha_prog **programa, char **linha)
{
	Linha_prog **ponteiro;
	Linha_prog *nova_linha;

	for (ponteiro = programa; ponteiro->prox != NULL; ponteiro = ponteiro->prox);

	ponteiro->prox = nova_linha;

	nova_linha = (Linha_prog**) malloc(sizeof(Linha_prog*));

	nova_linha->prox = NULL;

	nova_linha->linha = linha;
}

void desaloca_lista()
{

}

void imprime_lista(*lista)
{
	while (lista->prox != NULL)
	{
		printf("[%s]\n", lista->linha);
		lista = lista->prox;
	}
}

