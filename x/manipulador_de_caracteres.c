#include "manipulador_de_caracteres.h"


int registra_rotulo(Lista_ligada** lista_de_rotulos, Lista_ligada* rotulo, int palavra_atual, char orientacao)
{
	char *lado; // Lado esquerdo ou direito da palavra de memoria.
	char *_rotulo;
	int tamanho;

	if (!verifica_rotulo(rotulo, TRUE))
	{
		return 1;
	}

	_rotulo = copia_string(rotulo->string, 0);
	tamanho = getTamanho(_rotulo);

	// Retira os ':' do rotulo para este ser armazenado.
	_rotulo[tamanho - 2] = '\0';

	// Orientacao do rotulo.
	lado = (char *) malloc(2 * sizeof(char));
	lado[0] = orientacao;
	lado[1] = '\0';

	adiciona_celula(lista_de_rotulos, _rotulo, lado, palavra_atual);

	return 0;
}

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
		printf("ERROR on line %d\n", numero->info);
		printf("O argumento deve estar no intervalo (0x%s:0x%s)!\n", decimal_para_hex(min, 10), decimal_para_hex(max, 10));
		return 1;
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
				printf("ERROR on line %d\n", numero->info);
				printf("Caractere \'%c\' eh invalido para um numero decimal!\n", caractere);
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
			printf("ERROR on line %d\n", numero->info);
			printf("Numero decimal esperado deveria estar no intervalo (%ld:%ld)!\n", min, max);
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

