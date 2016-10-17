#include "manipulador_de_caracteres.h"

boolean compara_strings(char *string1, char *string2)
{
	int posicao = 0;
	int tam1, tam2;
	boolean strings_iguais = TRUE;

	for (posicao = 0; string1[posicao] != '\0'; posicao++);
	tam1 = posicao;
	
	for (posicao = 0; string2[posicao] != '\0'; posicao++);
	tam2 = posicao;
	
	if (tam1 != tam2)
	{
		strings_iguais = FALSE;	
	}

	else
	{
		for (posicao = 0; strings_iguais && string1[posicao] != '\0'; posicao++)
		{
			if (string1[posicao] != string2[posicao])
			{
				strings_iguais = FALSE;	
			}
		}
	}

	return strings_iguais;
}

int getTamanho(char *string)
{
	int posicao = 0;
	while (string[posicao++] != '\0');

	return posicao;
}

char * copia_string(char *string1, int inicio)
{
	int posicao;
	int tamanho;
	char *string2;

	for (posicao = 0; string1[posicao] != '\0'; posicao++);
	tamanho = posicao;

	string2 = (char *) malloc ((tamanho - inicio) * sizeof(char));

	for (posicao = 0; posicao < tamanho; posicao++)
	{
		string2[posicao] = string1[inicio + posicao];
	}

	return string2;
}

int base_string_para_decimal_int(char *string, int base)
{
	int tamanho = 0;
	int numero = 0;
	int potencia = 1;

	while (string[tamanho++] != '\0');

	for (int posicao = tamanho - 1; posicao >= 0; posicao--)
	{
		numero = numero + (int) ((string[posicao] - 30) * potencia);
		potencia *= base;
	}

}

char * decimal_para_hex(int numero, int num_digitos)
{
	char *num_convertido;
	char resto = 0;
	int dividendo = numero;
	int quociente = 0; // Divisor inicial.
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
			
			adiciona_celula(&numero_invertido, digito, NULL, 0);
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

//Recebe como parametro uma string de 10 caracteres.
int preenche_palavra_n_vezes(Lista_ligada* elemento, char mapa[][13], char *palavra, int palavra_atual, char orientacao, int n)
{
	if (orientacao == 'D')
	{
		printf("ERROR on line %d\n", elemento->info);
		printf("Nao eh possivel colocar um dado de 40 bits na instrucao a direita da palavra de memoria!\n");
		return 1;
	}
	while (n >= 0)
	{
		for (int posicao = 0; posicao < 10; posicao++)
		{
			mapa[palavra_atual][posicao + 3] = palavra[posicao];
		}
		n--;
	}
}

boolean verifica_hexadecimal(Lista_ligada *numero, boolean imprime_erros)
{
	int posicao;
	int tamanho;
	char chr;
	boolean numero_valido = TRUE;

	for (posicao = 0; numero->string[posicao] != '\0'; posicao++);
	tamanho = posicao;
	
	if (tamanho != 12 || numero->string[0] != '0' || numero->string[1] != 'x')
	{		
		if (imprime_erros)
		{
			printf("ERROR on line %d\n", numero->info);
			printf("Numeros hexadecimais devem possuir 12 digitos e comecar com \"0x\" (Ex: 0x0000000000)!\n");
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
				printf("ERROR on line %d\n", numero->info);
				printf("Caractere \'%c\' eh invalido para um numero hexadecimal!\n", chr);
			}
			return FALSE;		
		}

	}

	return TRUE;
}

boolean verifica_decimal (Lista_ligada *numero, int min, int max, int *num_decimal, boolean imprime_erros)
{
	int posicao;
	boolean numero_valido = TRUE;
	char caractere;
	int valor;
	int potencia = 1;

	for (posicao = 0; numero->string[posicao] != '\0' && numero_valido; posicao++)
	{
		caractere = numero->string[posicao];
		if (!(caractere >= '0' && caractere <= '9'))
		{
			if (imprime_erros)
			{
				printf("ERROR on line %d\n", numero->info);
				printf("Caractere \'%c\' eh invalido para um numero decimal!\n", caractere);
			}
			return FALSE;		
		}
	}

	valor = base_string_para_decimal_int(numero->string, 10);

	printf("Testeeeeeeeeeeeedecimal: %d\n", valor);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	if (valor >= min && valor <=max)
	{
		*num_decimal = valor;
		return TRUE;
	}
	else
	{
		if (imprime_erros)
		{
			printf("ERROR on line %d\n", numero->info);
			printf("Numero decimal deve ser entre os limites de %d e %d!\n", min, max);
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
			printf("ERROR on line %d\n", rotulo->info);
			printf("Rotulos nao podem ser iniciados com um numero!\n");
		}
		return FALSE;
	}

	for (int posicao = 0; rotulo->string[posicao] != ':' && rotulo_valido; posicao++)
	{
		chr = rotulo->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '_'))
		{
			if (imprime_erros)
			{
				printf("ERROR on line %d\n", rotulo->info);
				printf("Caractere \'%c\' eh invalido para um rotulo!\n", chr);
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
			printf("ERROR on line %d\n", simbolo->info);
			printf("Simbolos nao podem ser iniciados com um numero!\n");
		}
		return FALSE;
	}

	for (int posicao = 0; simbolo->string[posicao] != ':' && simbolo_valido; posicao++)
	{
		chr = simbolo->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '_'))
		{

		if (imprime_erros)
		{
			printf("ERROR on line %d\n", simbolo->info);
			printf("Caractere \'%c\' eh invalido para um simbolo!\n", chr);
		}
			return FALSE;		
		}
	}
	return TRUE;
}