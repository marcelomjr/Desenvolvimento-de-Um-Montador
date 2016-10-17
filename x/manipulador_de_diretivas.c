#include "manipulador_de_diretivas.h"

int tratador_de_diretivas(Lista_ligada **diretiva, Lista_ligada **lista_de_cte, Lista_ligada **lista_de_desconhecidos, int *palavra_atual, int *align, char *orientacao, char mapa[][13])
{
	// DIRETIVA SET.
	if (compara_strings((*diretiva)->string, ".set"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->prox->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info || (*diretiva)->info != (*diretiva)->prox->prox->info)
		{
			printf("ERROR on line %d\n", (*diretiva)->info);
			printf("A diretiva .set necessita de dois argumentos!\n");
			return 1;
		}

		if (trata_set((*diretiva), lista_de_cte) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox->prox;
		return 0;
	}

	// DIRETIVA ORG.
	else if (compara_strings((*diretiva)->string, ".org"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info)
		{
			printf("ERROR on line %d\n", (*diretiva)->info);
			printf("A diretiva .org necessita de  um argumento!\n");
			return 1;
		}

		if (trata_org((*diretiva)->prox, palavra_atual) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox;
		return 0;
	}

	// DIRETIVA ALIGN.
	else if (compara_strings((*diretiva)->string, ".align"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info)
		{
			printf("ERROR on line %d\n", (*diretiva)->info);
			printf("A diretiva .align necessita de  um argumento!\n");
			return 1;
		}

		if (trata_align((*diretiva)->prox, align) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox;
		return 0;
	}

	// DIRETIVA WFILL.
	else if (compara_strings((*diretiva)->string, ".wfill"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->prox->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info || (*diretiva)->info != (*diretiva)->prox->prox->info)
		{
			printf("ERROR on line %d\n", (*diretiva)->info);
			printf("A diretiva .wfill necessita de dois argumentos!\n");
			return 1;
		}

		if (trata_wfill((*diretiva), lista_de_desconhecidos, mapa, palavra_atual, orientacao) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox->prox;

		return 0;
	}
	// DIRETIVA WORD
	else if (compara_strings((*diretiva)->string, ".word"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info)
		{	
			printf("ERROR on line %d\n", (*diretiva)->info);
			printf("A diretiva .word necessita de  um argumento!\n");
			return 1;
		}

		if (trata_word((*diretiva)->prox, lista_de_desconhecidos, mapa, palavra_atual, orientacao) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox;
	}
	else
	{
		printf("ERROR on line %d\n", (*diretiva)->info);
		printf("Diretiva inexistente!\n");
		return 1;
	}
}

int trata_set(Lista_ligada *set, Lista_ligada **lista_de_cte)
{
	Lista_ligada *argumento1 = set->prox;
	Lista_ligada *argumento2 = set->prox->prox;
	int tamanho, posicao;
	int num_decimal = -1;
	char *arg1, *arg2;

	if (verifica_simbolo(argumento1, TRUE))
	{
		arg1 = copia_string(argumento1->string, 0);
	}
	else
	{
		return 1;
	}
	}


	
		printf("ERROR on line %d\n", argumento1->info);
		printf("A diretiva .org aceita decimais apenas entre o intervalo 0 1023!\n");

		if (!(verifica_decimal (argumento2, 0, 2147483647, &num_decimal, FALSE))
	{
	}	
	 || verifica_hexadecimal(argumento2, FALSE)))
	}
	{
		return 1;
	}

	// Preparacao para fornecer o argumento 1.
	for (posicao = 0; argumento1->string[posicao] != '\0'; posicao++);
	tamanho = posicao;
	arg1 = (char *) malloc(tamanho * sizeof(char));

	// copia o argumento 1 para o vetor arg1.
	for (posicao = 0; argumento1->string[posicao] != '\0'; posicao++)
	{
		arg1[posicao] = argumento1->string[posicao];
	}
	arg1[posicao] = '\0';

	// Preparacao para fornecer argumento numero 2.
	// Isso significa que o argumento eh um decimal.
	if (num_decimal != -1)
	{
		arg2 = decimal_para_hex(num_decimal, 10)

	}
	// Isso significa que o argumento 2 eh um hexadecimal.
	else
	{
		// Ignora o "0x" do numero hexadecimal.
		arg2 = copia_string(argumento2->string, 2);
	}

	adiciona_celula(lista_de_cte, arg1, arg2, -1);

	return 0;
}

int trata_org(Lista_ligada *argumento1, int *palavra_atual)
{
	int num_decimal;
	int posicao;
	char *arg1;
	char temp[10];

	if (verifica_decimal (argumento1, 0, 1023, &num_decimal, FALSE))
	{
		if (!(num_decimal >= 0 && num_decimal <= 1023))
		{
			printf("ERROR on line %d\n", numero->info);
			printf("A diretiva .org aceita decimais apenas entre o intervalo 0 1023!\n");
		}
	}
	else if (verifica_hexadecimal(argumento1, FALSE))
	{
		// Ignora o "0x" do numero hexadecimal.
		for (posicao = 2; argumento1->string[posicao] != '\0'; posicao++)
		{
			temp[posicao] = argumento1->string[posicao];
		}

		num_decimal = base_string_para_decimal_int(temp, 16);

		if (num_decimal > 1023)
		{
			printf("ERROR on line %d\n", numero->info);
			printf("Numero hexadecimal maior do que a ultima posicao de memoria (0x0000000400)!\n");
		}
	}
	else
	{
		printf("ERROR on line %d\n", numero->info);
		printf("O argumento da diretiva .org deve ser um decimal(0:123) ou hexadecimal (Ex: 0x0000000000)!\n");
		return 1;
	}

	*palavra_atual = num_decimal;
}

int trata_align(Lista_ligada *argumento1, int *align)
{
	int num_decimal;

	if (verifica_decimal (argumento1, 1023, &num_decimal, TRUE) == 1)
	{
		return 1;
	}
	else
	{
		printf("ERROR on line %d\n", numero->info);
		printf("Parametro de .align deve ser um inteiro entre 0 1023!\n");
		return 1;
	}
	align = num_decimal;
}

int trata_wfill(Lista_ligada *wfill, Lista_ligada **lista_de_desconhecidos, char mapa[][13], int *palavra_atual, char *orientacao)
{
	Lista_ligada *argumento1 = wfill->prox;
	Lista_ligada *argumento2 = wfill->prox->prox;

	int tamanho, posicao;
	int num_decimal1 = -1, num_decimal2 = -1;
	char *arg1, *arg2 = NULL;

	// Verifica se o primeiro argumento eh valido.
	if (!verifica_decimal (argumento1, 1023, &num_decimal1, TRUE))
	{
		return 1;
	}
	palavra_atual += num_decimal1;

	// Verifica o segundo argumento.
	if (verifica_hexadecimal(argumento2, FALSE))
	{
		// Nao precisa deixar espaco para o "0x".
		tamanho = getTamanho(argumento2->string) - 1;

		arg2 = (char *) malloc(tamanho * sizeof(char));

		for (posicao = 2; posicao < tamanho + 2; posicao++)
		{
			arg2[posicao - 2] = argumento2->string[posicao];
		}
		arg2[tamanho - 2] = '\0';

		if (preenche_palavra_n_vezes(mapa, arg2, palavra_atual, orientacao, num_decimal1) == 1)
		{
			return 1;
		}
		return 0;
	}
	else if (verifica_decimal (argumento2, -2147483648, 2147483647, &num_decimal2, FALSE))
	{	
		arg2 = decimal_para_hex(int numero, int num_digitos);
		if (preenche_palavra_n_vezes(mapa, arg2, palavra_atual, orientacao, num_decimal1) == 1)
		{
			return 1;
		}
		return 0;
	}
	else if (verifica_rotulo(argumento2, FALSE) || boolean verifica_simbolo(argumento2, FALSE))
	{
		arg2 = (char *) malloc(11 * sizeof(char));

		for (posicao = 0; posicao < 10; posicao++)
		{
			arg2[posicao] = '?';
		}
		arg2[10] = '\0';
		// Marca essas palavras para sabermos que elas deverao ser alteradas.
		if (preenche_palavra_n_vezes(mapa, arg2, palavra_atual, orientacao, num_decimal1) == 1)
		{
			return 1;
		}

		return 0;
	}
	else
	{
		printf("ERROR on line %d\n", argumento2->info);
		printf("Argumento invalido para a diretiva .wfill!\n");
		return 1;
	}
}

int trata_word(Lista_ligada *argumento1, Lista_ligada **lista_de_desconhecidos, char mapa[][13], int *palavra_atual, char *orientacao)
{
	int num_decimal;
	int posicao;
	char *arg1;
	char temp[10];

	// Verifica se o argumento eh um decimal.
	if (verifica_decimal (argumento1, 0, 4294967295, &num_decimal, FALSE))
	{
		if (!(num_decimal >= 0 && num_decimal <= 4294967295))
		{
			printf("ERROR on line %d\n", numero->info);
			printf("A diretiva .word aceita decimais apenas entre o intervalo 0 1023!\n");
			return 1;
		}
		else
		{
			arg1 = decimal_para_hex(num_decimal, 10);

			if (preenche_palavra_n_vezes(mapa, arg1, palavra_atual, orientacao, 1) == 1)
			{
				return 1;
			}
		}
	}
	// Verifica se o argumento eh um hexadecimal.
	else if (verifica_hexadecimal(argumento1, FALSE))
	{
		// Ignora o "0x" do numero hexadecimal.
		arg1 = copia_string(argumento1->string, 2);

		// numero decimal em int para verificar os limites.
		num_decimal = base_string_para_decimal_int(arg1, 16);

		// Verifica se o argumentoe esta dentro dos limites.
		if (!(num_decimal >= 0 && num_decimal <= 4294967295))
		{
			printf("ERROR on line %d\n", numero->info);
			printf("Numero hexadecimal maior do que a ultima posicao de memoria (0x0000000400)!\n");
		}
		else
		{
			if (preenche_palavra_n_vezes(mapa, arg1, palavra_atual, orientacao, 1) == 1)
			{
				return 1;
			}
		}
	}
	// Verifica se o argumento 1 eh um rotulo ou simbolo.
	else if (verifica_rotulo(argumento1, FALSE) || boolean verifica_simbolo(argumento1, FALSE))
	{
		arg1 = (char *) malloc(11 * sizeof(char));

		for (posicao = 0; posicao < 10; posicao++)
		{
			arg1[posicao] = '?';
		}

		arg1[10] = '\0';

		// Marca essa palavra para sabermos que ela devera ser alterada.
		if (preenche_palavra_n_vezes(mapa, arg1, palavra_atual, orientacao, 1) == 1)
		{
			return 1;
		}

		return 0;
	}
	else
	{
		printf("ERROR on line %d\n", numero->info);
		printf("O argumento da diretiva .org deve ser um decimal(0:123) ou hexadecimal (Ex: 0x0000000000)!\n");
		return 1;
	}
}