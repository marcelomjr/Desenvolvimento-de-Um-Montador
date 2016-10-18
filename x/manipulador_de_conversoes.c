#include "manipulador_de_conversoes.h"

// converte qualquer base entre 2 e 16 em (string) para base 10 em (int).
long int base_string_para_decimal_int(char *string, int base)
{
	int tamanho = 0;
	long int numero = 0;
	long int potencia = 1;
	long int fator;

	// printf("base_string_para_decimal_int(string)[%s]\n",string );
	while (string[tamanho++] != '\0');

	for (int posicao = tamanho - 2; posicao >= 0; posicao--)
	{
		if (string[posicao] >= 'a' && string[posicao] <= 'f')
		{
			fator = (long int) string[posicao] - 'a' + 10;
		}
		else if (string[posicao] >= 'A' && string[posicao] <= 'F')
		{
			fator = (long int) string[posicao] - 'A' + 10;
		}
		else
		{
			fator = (long int) string[posicao] - '0';
		}
		numero = numero + (fator * potencia);
		potencia *= base;
	}

	return numero;
}

char * decimal_para_hex(long int numero, int num_digitos)
{
	char *num_convertido;
	char resto = 0;
	long int dividendo = numero;
	long int quociente = 0; // Divisor inicial.
	Lista_ligada *numero_invertido;
	Lista_ligada* apontador; 
	char *digito;
	int conta_digito = 0;

	cria_lista(&numero_invertido);

	do
	{
		resto = dividendo % 16;

		quociente = dividendo / 16;
		dividendo = quociente;		

		if (resto >= 0 && resto < 16)
		{
			switch (resto)
			{
				case (10):
				{
					resto = 'A';
					break;
				}
				case (11):
				{
					resto = 'B';
					break;
				}
				case (12):
				{
					resto = 'C';
					break;
				}
				case (13):
				{
					resto = 'D';
					break;
				}
				case (14):
				{
					resto = 'E';
					break;
				}
				case (15):
				{
					resto = 'F';
					break;
				}
				default:
				{
					resto += '0';
				}
			}

			digito = (char *) malloc (2 * sizeof(char));
			digito[0] = resto;
			digito[1] = '\0';
			
			adiciona_celula(&numero_invertido, digito, "", 0);
			conta_digito++;
		}		
	} while (quociente != 0);

	/* Verifica o tamanho da string */
	if (num_digitos <= conta_digito)
	{
		num_convertido = (char *) malloc ((conta_digito + 1) * sizeof(char));

		num_convertido[conta_digito] = '\0';

		apontador = numero_invertido;
		for (int posicao = conta_digito - 1; posicao >= 0; posicao--)
		{
			num_convertido[posicao] = apontador->string[0];
			apontador = apontador->prox;
		}
	}

	else
	{
		num_convertido = (char *) malloc ((num_digitos + 1) * sizeof(char));

		num_convertido[num_digitos] = '\0';

		// Preenche com zeros.
		for (int posicao = 0; posicao < num_digitos; posicao++)
		{
			num_convertido[posicao] = '0';
		}

		apontador = numero_invertido;
		for (int posicao = num_digitos - 1; apontador != NULL; posicao--)
		{
		 	num_convertido[posicao] = apontador->string[0];
			apontador = apontador->prox;
		}
	}

	remove_lista(&numero_invertido);

	return num_convertido;
}