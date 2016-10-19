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
		printf("ERROR on line %d\n", (int) elemento->info);
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
	Lista_ligada *apontador = *mapa;
	char *endereco;
	int palavra_atual = -1;
	Lista_ligada *temp1, *temp2;

	for (; apontador != NULL; apontador = apontador->prox)
	{
		if (palavra_atual < apontador->info)
		{
			printf("\n");	
			endereco = decimal_para_hex(apontador->info, 3);
			printf("%s ", endereco);
			palavra_atual = apontador->info;
			
		}
		
		for (int posicao = 0; posicao < 5; posicao++)
		{
			if (posicao == 2)
			{
					printf(" ");
			}
			printf("%c", apontador->string[posicao]);
		}
		// Caso esteja no lado esquerdo.
		if (apontador->string2[0] == 'E')
		{
			printf(" ");
			if ((apontador->prox == NULL) || (apontador->prox->string2[0] == 'E'))
			{
				printf("00 000");
			}
		}
		// caso esteja no lado direito.
		else
		{
			if ((apontador->prox != NULL) && (apontador->prox->string2[0] == 'D'))
			{
			
			temp1 = apontador;
			temp2 = apontador->prox;
			apontador->prox = NULL;

			adiciona_celula(mapa, "00000", "E", apontador->prox->info);
			apontador = temp1;
			apontador->prox->prox = temp2;
			}
		}
	}
	printf("\n");
}