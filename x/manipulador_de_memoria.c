// manipulador_de_memoria.c

#include "manipulador_de_memoria.h"

void avanca_meias_palavra(int *palavra_atual, char *orientacao, int quantidade)
{
	for (int contador = 0; contador < quantidade; contador++)
	{
		if (*orientacao == 'E')
		{
			*orientacao = 'D';	
		}
		else
		{
			*palavra_atual += 1;
			*orientacao = 'E';
		}
	}
}

void imprime_mapa(char mapa[][13])
{
	int palavra, posicao;

	for (palavra = 0; palavra < 1024; palavra++)
	{
		for (posicao = 0; posicao < 13; posicao++)
		{
			if (posicao == 3 || posicao == 5 || posicao == 8 ||posicao == 10)
			{
					printf(" ");
			}
				printf("%c", mapa[palavra][posicao]);
		}
		printf("\n");

	}
}

void preenche_enderecos(char mapa[][13])
{
	int palavra, posicao;
	char *temp;

	for (palavra = 0; palavra < 1024; palavra++)
	{
		temp = decimal_para_hex(palavra, 3);
		
		mapa[palavra][0] = temp[0];
		mapa[palavra][1] = temp[1];
		mapa[palavra][2] = temp[2];
	}
}

void inicializa_mapa(char mapa[][13])
{
	int palavra, posicao;

	for (palavra = 0; palavra < 1024; palavra++)
	{
		for (posicao = 3; posicao < 13; posicao++)
		{
			mapa[palavra][posicao] = '0';
		}
	}
}