#include "manipulador_de_diretivas.h"

int tratador_de_diretivas(Lista_ligada **diretiva, Lista_ligada **lista_de_simbolos, Lista_ligada **lista_de_desconhecidos, int *palavra_atual, int *align, char *orientacao, Lista_ligada **mapa)
{
	// DIRETIVA SET.
	if (compara_strings((*diretiva)->string, ".set"))
	{
		if ((*diretiva)->prox == NULL || (*diretiva)->prox->prox == NULL || (*diretiva)->info != (*diretiva)->prox->info || (*diretiva)->info != (*diretiva)->prox->prox->info)
		{
			fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
			fprintf(saida, "A diretiva .set necessita de dois argumentos!\n");
			return 1;
		}

		if (trata_set((*diretiva), lista_de_simbolos) == 1)
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
			fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
			fprintf(saida, "A diretiva .org necessita de  um argumento!\n");
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
			fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
			fprintf(saida, "A diretiva .align necessita de  um argumento!\n");
			return 1;
		}

		if (trata_align((*diretiva)->prox, mapa, align, orientacao, palavra_atual) == 1)
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
			fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
			fprintf(saida, "A diretiva .wfill necessita de dois argumentos!\n");
			return 1;
		}
		if (trata_wfill(*diretiva, lista_de_desconhecidos, mapa, palavra_atual, orientacao, *align) == 1)
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
			fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
			fprintf(saida, "A diretiva .word necessita de  um argumento!\n");
			return 1;
		}

		if (trata_word((*diretiva)->prox, lista_de_desconhecidos, mapa, palavra_atual, orientacao, *align) == 1)
		{
			return 1;
		}

		*diretiva = (*diretiva)->prox;
		return 0;
	}
	else
	{
		fprintf(saida, "ERROR on line %d\n", (int) (*diretiva)->info);
		fprintf(saida, "Diretiva inexistente!\n");
		return 1;
	}
}

int trata_set(Lista_ligada *set, Lista_ligada **lista_de_simbolos)
{
	Lista_ligada *argumento1 = set->prox;
	Lista_ligada *argumento2 = set->prox->prox;
	long int num_decimal;

	fprintf(saida, "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
	// Verifica se o argumento 1 eh um simbolo.
	if (!verifica_simbolo(argumento1, TRUE))
	{
		return 1;	
	}

	// Verifica se o argumento 2 eh valido.

	// Verifica se o argumento 2 eh um numero hexadecimal.
	if (verifica_hexadecimal(argumento2, 0, 2147483647, FALSE))
	{
		num_decimal = base_string_para_decimal_int(copia_string(argumento2->string, 2), 16);
	}
	else if (!verifica_decimal (argumento2, 0, 2147483647 , &num_decimal, FALSE))
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento2->info);
		fprintf(saida, "Argumento 2 invalido para a diretiva .set!\n");
		return 1;
	}
	
	adiciona_celula(lista_de_simbolos, argumento1->string, "", num_decimal);

	return 0;
}

int trata_org(Lista_ligada *argumento1, int *palavra_atual)
{
	long int num_decimal;
	char *arg1;

	if (verifica_decimal (argumento1, 0, 1023, &num_decimal, FALSE))
	{
		*palavra_atual = num_decimal;

		return 0;
	}
	else if (verifica_hexadecimal(argumento1, 0, 1023, FALSE))
	{
		// Ignora o "0x" do numero hexadecimal.
		arg1 = copia_string(argumento1->string, 2);

		num_decimal = base_string_para_decimal_int(arg1, 16);

		*palavra_atual = num_decimal;
		// orientacao = 'E'talvez resolvaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

		return 0;
	}
	else
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento1->info);
		fprintf(saida, "O argumento da diretiva .org deve ser um decimal(0:123) ou hexadecimal (Ex: 0x0000000000)!\n");
		return 1;
	}
}

int trata_align(Lista_ligada *argumento1,Lista_ligada **mapa, int *align, char *orientacao, int *num_palavra)
{
	long int num_decimal;
	int temp;

	if (verifica_decimal(argumento1, 1, 1023, &num_decimal, FALSE))
	{
		if (orientacao[0] == 'D')
		{
			orientacao[0] = 'E';	
		}

		(*align) = num_decimal;

		if ((*num_palavra) == 0 || (*num_palavra) % (*align) != 0)
		{
			if (*num_palavra < (*align))
			{
				*num_palavra = (*align);
			}
			else if (*num_palavra > (*align))
			{
				temp = (int) (*num_palavra) / (*align);
				temp++;
				(*num_palavra) = temp * (*align);
			}
		}

		return 0;
	}
	else
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento1->info);
		fprintf(saida, "Parametro de .align deve ser um decimal inteiro entre 1 e 1023!\n");
		return 1;
	}
	
}

int trata_wfill(Lista_ligada *wfill, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao, int align)
{
	Lista_ligada *argumento1 = wfill->prox;
	Lista_ligada *argumento2 = wfill->prox->prox;
	char meia_palavra1[6];
	char meia_palavra2[6];
	boolean argumento_valido = FALSE, rotulo_ou_simbolo = FALSE;
	long int num_decimal1, num_decimal2;
	char *numero_da_linha, *arg2;
	int contador;

	if (orientacao[0] == 'D')
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento1->info);
		fprintf(saida, "A diretiva .wfill nao pode ser utilizada quando se esta no lado direito da palavra de memoria!\n");
		return 1;
	}

	// Verifica se o primeiro argumento eh valido.
	if (!verifica_decimal (argumento1, 1, 1023, &num_decimal1, TRUE))
	{
		return 1;
	}

	// Verifica se o segundo argumento eh um hexadecimal.
	if (verifica_hexadecimal(argumento2, -2147483648, 2147483647, FALSE))
	{
		// Nao precisa deixar espaco para o "0x".
		arg2 = copia_string(argumento2->string, 2);			

		// Ignora o "0x" do numero hexadecimal.
		quebra_string(arg2, meia_palavra1, meia_palavra2);

		free(arg2);

		argumento_valido = TRUE;
	}
	// Verifica se o segundo argumento eh um decimal.
	else if (verifica_decimal (argumento2, -2147483648, 2147483647, &num_decimal2, FALSE))
	{	
		arg2 = decimal_para_hex(num_decimal2, 10);

		quebra_string(arg2, meia_palavra1, meia_palavra2);

		argumento_valido = TRUE;
	}
	// Verifica se o segundo argumento eh um rotulo.
	else if (verifica_rotulo(argumento2, FALSE) || verifica_simbolo(argumento2, FALSE))
	{
		for (contador = 0; contador < 5; contador++)
		{
			meia_palavra1[contador] = '?';
			meia_palavra2[contador] = '?';
		}

		meia_palavra1[contador] = '\0';
		meia_palavra2[contador] = '\0';

		rotulo_ou_simbolo = TRUE;
		argumento_valido = TRUE;
	}

	if (argumento_valido)
	{
		for (contador = 0; contador < num_decimal1; contador++)
		{
			if (rotulo_ou_simbolo)
			{
				// Salva o numero da linha para indicar erro caso nao identique o objeto como simbolo ou rotulo existente.
				numero_da_linha = decimal_para_hex(argumento2->info, 4);

				// Salva o objeto na lista dos simbolos desconhecidos.
				// Salvando o objeto em string, o numero da linha do programa em string2 e o numero da palavra de memoria em info da lista ligada.
				adiciona_celula(lista_de_desconhecidos, argumento2->string, numero_da_linha, *palavra_atual);

				free(numero_da_linha);

			}
			avanca_meia_palavra(mapa, meia_palavra1, orientacao, palavra_atual, align, TRUE);
			// Como verifiquei que o orientacao era a esquerda, tenho certeza que posso colocar a outra metade a direita.
			avanca_meia_palavra(mapa, meia_palavra2, orientacao, palavra_atual, align, TRUE);
		}

		return 0;
	}

	else
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento2->info);
		fprintf(saida, "Argumento invalido para a diretiva .wfill!\n");
		return 1;
	}
}

int trata_word(Lista_ligada *argumento1, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao, int align)
{
	long int num_decimal;
	char *numero_da_linha;
	boolean argumento_valido = FALSE;
	char meia_palavra1[6];
	char meia_palavra2[6];
	char *palavara_inteira;

	if (orientacao[0] == 'D')
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento1->info);
		fprintf(saida, "A diretiva .word nao pode ser utilizada quando se esta no lado direito da palavra de memoria!\n");
		return 1;
	}

	// Verifica se o argumento eh um decimal.
	if (verifica_decimal (argumento1, 0, 4294967295, &num_decimal, FALSE))
	{
		// converte o decimal para hexadecimal e quebra a palavra ao meio.
		palavara_inteira = decimal_para_hex(num_decimal, 10);
		quebra_string(palavara_inteira, meia_palavra1, meia_palavra2);
		
		argumento_valido = TRUE;
		
		free(palavara_inteira);
	}

	// Verifica se o argumento eh um hexadecimal.
	else if (verifica_hexadecimal(argumento1, 0, 4294967295, FALSE))
	{
		// Ignora o "0x" do numero hexadecimal.
		quebra_string(copia_string(argumento1->string, 2), meia_palavra1, meia_palavra2);

		argumento_valido = TRUE;
	}

	// Verifica se o argumento 1 eh um rotulo ou simbolo.
	else if (verifica_rotulo(argumento1, FALSE) || verifica_simbolo(argumento1, FALSE))
	{
		// Marcador para saber que eh um simbolo.	
		for (int posicao = 0; posicao < 5; posicao++)
		{
			meia_palavra1[posicao] = '?';
			meia_palavra2[posicao] = '?';
		}

		meia_palavra1[5] = '\0';
		meia_palavra2[5] = '\0';

		// Salva o numero da linha para indicar erro caso nao identique o objeto como simbolo ou rotulo existente.
		numero_da_linha = decimal_para_hex(argumento1->info, 4);

		// Salva o objeto na lista dos simbolos desconhecidos.
		// Salvando o objeto em string, o numero da linha do programa em string2 e o numero da palavra de memoria em info da lista ligada.
		adiciona_celula(lista_de_desconhecidos, argumento1->string, numero_da_linha, *palavra_atual);

		free(numero_da_linha);

		argumento_valido = TRUE;
	}

	if (argumento_valido)
	{
		avanca_meia_palavra(mapa, meia_palavra1, orientacao, palavra_atual, align, TRUE);
		// Como verifiquei que o orientacao era a esquerda, tenho certeza que posso colocar a outra metade a direita.
		avanca_meia_palavra(mapa, meia_palavra2, orientacao, palavra_atual, align, TRUE);
	}
	else
	{
		fprintf(saida, "ERROR on line %d\n", (int) argumento1->info);
		fprintf(saida, "O argumento da diretiva .word deve ser um decimal(0:123) ou hexadecimal (Ex: 0x0000000010)!\n");
		return 1;
	}

	return 0;
}
