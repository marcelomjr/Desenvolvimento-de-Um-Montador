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
// As 3 strings devem possuir tamanho 11.
void quebra_string(char *fonte, char string1[], char string2[])
{
	int posicao;

	for (posicao = 0; posicao < 5; posicao++)
	{
		string1[posicao] = fonte[posicao];
		string2[posicao] = fonte[posicao + 5];
	}

	string1[5] = '\0';
	string2[5] = '\0';
}

char * copia_string(char *string1, int inicio)
{
	int posicao;
	int tamanho;
	char *string2;

	tamanho = getTamanho(string1);

	string2 = (char *) malloc ((tamanho - inicio) * sizeof(char));

	for (posicao = 0; posicao < tamanho; posicao++)
	{
		string2[posicao] = string1[inicio + posicao];
	}
	
	return string2;
}