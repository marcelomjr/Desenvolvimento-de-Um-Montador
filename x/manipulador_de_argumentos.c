
#include "manipulador_de_argumentos.h"

boolean verifica_hexadecimal(Lista_ligada *numero, long int min, long int max, boolean imprime_erros)
{
	int posicao;
	int tamanho;
	char *aux;
	long int menos_1_hex = 1099511627775; 		// 0xFFFFFFFFFF
	long int menor_negativo_hex = 1030792151040; 	// 0xF000000000
	long int numero_decimal;
	char chr;
	boolean numero_valido = TRUE;

	for (posicao = 0; numero->string[posicao] != '\0'; posicao++);
	tamanho = posicao;
	
	if (tamanho != 12 || numero->string[0] != '0' || numero->string[1] != 'x')
	{		
		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) numero->info);
			fprintf(saida, "Numeros hexadecimais devem possuir 12 digitos e comecar com \"0x\" (Ex: 0x0000000000)!\n");
		}
		return FALSE;
	}

	for (posicao = 2; posicao < 12 && numero_valido; posicao++)
	{
		chr = numero->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'F') || (chr >= 'a' && chr <= 'f')))
		{
			if (imprime_erros)
			{
				fprintf(saida, "ERROR on line %d\n", (int) numero->info);
				fprintf(saida, "Caractere \'%c\' eh invalido para um numero hexadecimal!\n", chr);
			}
			return FALSE;		
		}

	}
	aux = copia_string(numero->string, 2);

	numero_decimal = base_string_para_decimal_int(aux, 16);

	/* Se numero_decimal for maior do que menor_negativo_hex quer dizer que o primeiro eh negativo
	 * representacao de complemento de dois. */
	if (numero_decimal > menor_negativo_hex)
	{
		numero_decimal = (long int) -(menos_1_hex - numero_decimal + 1);
	}

	if (!(numero_decimal >= min && numero_decimal <= max))
	{
		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) numero->info);
			fprintf(saida, "O argumento deve estar no intervalo (0x%s:0x%s)!\n", decimal_para_hex(min, 10), decimal_para_hex(max, 10));
		}
		return FALSE;
	}

	return TRUE;
}

boolean verifica_decimal (Lista_ligada *numero, long int min, long int max, long int *num_decimal, boolean imprime_erros)
{
	int posicao = 0;
	boolean numero_valido = TRUE;
	char caractere;
	int valor;
	boolean negativo = FALSE;

	if (numero->string[0] == '-')
	{
		negativo = TRUE;
		numero->string[0] = '0';	
	}

	for (; numero->string[posicao] != '\0' && numero_valido; posicao++)
	{
		caractere = numero->string[posicao];
		if (!(caractere >= '0' && caractere <= '9'))
		{
			if (imprime_erros)
			{
				fprintf(saida, "ERROR on line %d\n", (int) numero->info);
				fprintf(saida, "Caractere \'%c\' eh invalido para um numero decimal!\n", caractere);
			}
			return FALSE;		
		}
	}


	valor = base_string_para_decimal_int(numero->string, 10);

	if (negativo)
	{
		valor *= -1;
	}

	if (valor >= min && valor <=max)
	{
		*num_decimal = valor;
		return TRUE;
	}
	else
	{
		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) numero->info);
			fprintf(saida, "Numero decimal esperado deveria estar no intervalo (%ld:%ld)!\n", min, max);
		}
		return FALSE;
	}
}

boolean verifica_rotulo(Lista_ligada *rotulo, boolean imprime_erros)
{
	boolean rotulo_valido = TRUE;
	char chr;

	if (rotulo->string[0] >= '0' && rotulo->string[0] <= '9')
	{
		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) rotulo->info);
			fprintf(saida, "Rotulos nao podem ser iniciados com um numero!\n");
		}
		return FALSE;
	}

	for (int posicao = 0; rotulo->string[posicao] != '\0' && rotulo_valido; posicao++)
	{
		chr = rotulo->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '_'))
		{
			if (imprime_erros)
			{
				fprintf(saida, "ERROR on line %d\n", (int) rotulo->info);
				fprintf(saida, "Caractere \'%c\' eh invalido para um rotulo!\n", chr);
			}
			return FALSE;
		}
	}
	
	return TRUE;
}

boolean verifica_simbolo(Lista_ligada *simbolo, boolean imprime_erros)
{
	boolean simbolo_valido = TRUE;
	char chr;

	if (simbolo->string[0] >= '0' && simbolo->string[0] <= '9')
	{
		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) simbolo->info);
			fprintf(saida, "Simbolos nao podem ser iniciados com um numero!\n");
		}
		return FALSE;
	}

	for (int posicao = 0; simbolo->string[posicao] != '\0' && simbolo_valido; posicao++)
	{
		chr = simbolo->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '_'))
		{

		if (imprime_erros)
		{
			fprintf(saida, "ERROR on line %d\n", (int) simbolo->info);
			fprintf(saida, "Caractere \'%c\' eh invalido para um simbolo!\n", chr);
		}
			return FALSE;		
		}
	}
	return TRUE;
}

