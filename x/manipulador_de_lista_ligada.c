// manipulador_de_lista_ligada.c

#include "manipulador_de_lista_ligada.h"

/* Cria uma lista ligada vazia.
 * Recebe como parametro o endereco de um ponteiro do tipo Lista_ligada.
 */
void cria_lista(Lista_ligada **lista)
{
	*lista = NULL;
}

// Cria uma lista ligada generica.
void adiciona_celula(Lista_ligada **lista, char* str1, char* str2, int informacao)
{
	Lista_ligada* apontador;
	Lista_ligada* nova_celula = (Lista_ligada*) malloc(sizeof(Lista_ligada));

	if (*lista != NULL)
	{
		for (apontador = *lista; apontador->prox != NULL; apontador = apontador->prox);

		apontador->prox = nova_celula;
	}
	else
	{
		*lista = nova_celula;
	}

	nova_celula->prox = NULL;

	nova_celula->string = str1;
	nova_celula->string2 = str2;
	nova_celula->info = informacao;
}

void remove_lista(Lista_ligada** lista)
{
	Lista_ligada* temp;

	while (*lista != NULL)
	{
		temp = (*lista)->prox;

		if ((*lista)->string != NULL)
			{
				if ((*lista)->string != NULL)
				{
					free((*lista)->string);
				}
				if ((*lista)->string2 != NULL)
				{
					free((*lista)->string2);
				}
			}

		free(*lista);
		*lista = temp;
	}
}

/* Se opcao_de_string == 1 : imprime string
 * Se opcao_de_string == 2 : imprime string2
 * Se opcao_de_string == 12 : imprime as duas strings
 */
void imprime_lista(Lista_ligada *lista, int opcao_de_string)
{
	int linha_atual = 0;
	printf("%.2d:", linha_atual);

	while (lista != NULL)
	{
		if (lista->info > linha_atual)
		{
			printf("\n");
			linha_atual = lista->info;
			printf("%.2d:", linha_atual);
		}
		if (opcao_de_string == 1)
		{
			printf("[%s] ", lista->string);
		}
		else if (opcao_de_string == 2)
		{
			printf("[%s] ", lista->string2);
		}
		else if (opcao_de_string == 12)
		{
			printf("[%s|%s] ", lista->string, lista->string2);
		}
		lista = lista->prox;
	}
	printf("\n");
}
