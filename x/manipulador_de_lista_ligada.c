// manipulador_de_lista_ligada.c

#include "manipulador_de_lista_ligada.h"

/* Cria uma lista ligada vazia.
 * Recebe como parametro o endereco de um ponteiro do tipo Lista_ligada.
 */
void cria_lista(Lista_ligada **lista)
{
	*lista = NULL;
}

void adiciona_celula(Lista_ligada **lista, char* str, int informacao)
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

	nova_celula->string = str;
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
				free((*lista)->string);
			}

		free(*lista);
		*lista = temp;
	}
}

void imprime_lista(Lista_ligada *lista)
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
		printf("[%s] ", lista->string);
		lista = lista->prox;
	}
	printf("\n");
}
