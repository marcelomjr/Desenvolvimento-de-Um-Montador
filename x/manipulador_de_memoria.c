// manipulador_de_memoria.c

#include "manipulador_de_memoria.h"

void avanca_meia_palavra(Lista_ligada **mapa, char *meia_palavra, char *orientacao, int *num_palavra)
{
	printf("[%s:%d:%s]\n", meia_palavra, *num_palavra,orientacao);
	adiciona_celula(mapa, meia_palavra, orientacao, *num_palavra);
	
	if (orientacao[0] == 'E')
	{
		orientacao[0] = 'D';	
	}
	else
	{
		printf("num_palavra: %d\n", *num_palavra);
		*num_palavra += 1;
		orientacao[0] = 'E';
	}
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
	return 0;
}

void imprime_mapa(Lista_ligada** mapa)
{
	char *endereco;
	int palavra_atual = -1;
	Lista_ligada *temp1, *temp2;

	for (; (*mapa) != NULL; (*mapa) = (*mapa)->prox)
	{
		if (palavra_atual < (*mapa)->info)
		{
			printf("\n");	
			endereco = decimal_para_hex((*mapa)->info, 3);
			printf("%s ", endereco);
			palavra_atual = (*mapa)->info;
			
		}
		
		for (int posicao = 0; posicao < 5; posicao++)
		{
			if (posicao == 2)
			{
					printf(" ");
			}
			printf("%c", (*mapa)->string[posicao]);
		}
		// Caso esteja no lado esquerdo.
		if ((*mapa)->string2[0] == 'E')
		{
			printf(" ");
			if (((*mapa)->prox == NULL) || ((*mapa)->prox->string2[0] == 'E'))
			{
				printf("00 000");
			}
		}
		// caso esteja no lado direito.
		else
		{
			if (((*mapa)->prox != NULL) && ((*mapa)->prox->string2[0] == 'D'))
			{
			
			temp1 = (*mapa);
			temp2 = (*mapa)->prox;
			(*mapa)->prox = NULL;

			adiciona_celula(mapa, "00000", "E", (*mapa)->prox->info);
			(*mapa)->prox->prox = temp2;
			}
		}
	}
	printf("\n");
}