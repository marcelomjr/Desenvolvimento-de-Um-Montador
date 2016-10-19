// manipulador_de_lista_ligada.c

#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_caracteres.h"

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

	// Insercao dos dados.
	nova_celula->string = copia_string(str1, 0);
	nova_celula->string2 = copia_string(str2, 0);

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
	int linha_atual = -1;

	while (lista != NULL)
	{
		if (lista->info != linha_atual)
		{
			linha_atual = lista->info;
			fprintf(saida, "\n");
			fprintf(saida, "%.2d:", linha_atual);
		}
		if (opcao_de_string == 1)
		{
			fprintf(saida, "[%s] ", lista->string);
		}
		else if (opcao_de_string == 2)
		{
			fprintf(saida, "[%s] ", lista->string2);
		}
		else if (opcao_de_string == 12)
		{
			fprintf(saida, "[%s|%s] ", lista->string, lista->string2);
		}
		else if (opcao_de_string == 123)
		{
			fprintf(saida, "[%ld|%s|%s] ", lista->info, lista->string, lista->string2);
		}
		lista = lista->prox;
	}
	fprintf(saida, "\n");
}
