// manipulador_de_memoria.c

#include "manipulador_de_memoria.h"

/*
 * Oberservacao: Para registar a metade direita de um numero de 40 bits deve-se mandar "D" no argumento char *orientacao.
 */
void avanca_meia_palavra(Lista_ligada **mapa, char *meia_palavra, char *orientacao, int *num_palavra, int align, boolean num_40_bits)
{
	
	if (align == 0)
	{
		adiciona_celula(mapa, meia_palavra, orientacao, *num_palavra);

		if (orientacao[0] == 'E')
		{
			orientacao[0] = 'D';	
		}
		// Esta na direita
		else
		{
			orientacao[0] = 'E';	
			(*num_palavra) += 1;
		}
	}
	// align != 0
	else
	{
		// Verifica se esta a esquerda.
		if (orientacao[0] == 'E')
		{
			adiciona_celula(mapa, meia_palavra, orientacao, *num_palavra);

			if (num_40_bits)
			{
				orientacao[0] = 'D';
			}
			else
			{
				(*num_palavra) += align;
			}
		}
		// Nesse caso esta a direita
		else
		{
			if (!num_40_bits)
			{
				orientacao[0] = 'E';
			}

			adiciona_celula(mapa, meia_palavra, orientacao, *num_palavra);

			if (num_40_bits)
			{
				orientacao[0] = 'E';
				(*num_palavra) += align;
			}
		}
		
		
	}
}

void imprime_mapa(Lista_ligada** mapa)
{
	Lista_ligada *apontador = *mapa;
	char *endereco;
	int palavra_atual = -1;
	
	for (; apontador != NULL; apontador = apontador->prox)
	{
		if (palavra_atual != apontador->info)
		{
			fprintf(saida, "\n");	
			endereco = decimal_para_hex(apontador->info, 3);
			fprintf(saida, "%s ", endereco);
			palavra_atual = apontador->info;
			
		}
		
		for (int posicao = 0; posicao < 5; posicao++)
		{
			if (posicao == 2)
			{
					fprintf(saida, " ");
			}
			fprintf(saida, "%c", apontador->string[posicao]);
		}
		// Caso esteja no lado esquerdo.
		if (apontador->string2[0] == 'E')
		{
			fprintf(saida, " ");
		}
	}
	fprintf(saida, "\n");
}