/*
 * programa.c
 *
 *  Created on: 13 de out de 2016
 *      Author: marcelo
 */
#include "montador.h"
boolean identifica_diretiva(char *elemento)
{

}

int identifica_elementos(Lista_ligada** programaLM)
{
	Lista_ligada *apontador;
	int num_linha = 0;
	int cursor = -1; // Valor para identificar a linha 0.

	// Encontra o numero de linhas nao vazias;
	for (apontador = *programaLM; apontador != NULL; apontador = apontador->prox)
	{
		if (apontador->info > cursor)
		{
			cursor = apontador->info;
			num_linha++;
		}
	}

	printf("linhas_n_vazias: %d\n", num_linha);

	// Lista_ligada *linha = *programaLM;
	// int posicao, cursor;
	// boolean instrucao, diretiva, rotulo;
	// boolean fim_de_linha;

	// while (linha != NULL)
	// {
	// 	instrucao = FALSE;
	// 	diretiva = FALSE;
	// 	rotulo = FALSE;
	// 	fim_de_linha = FALSE;
	// 	posicao = 0;

	// 	cursor = 0; 
	// 	printf("=========== LINHA %d (INICIO) ===========\n", linha->info);

	// 	while (linha->string[posicao] != '\0' && !fim_de_linha)
	// 	{
	// 		printf("cursor: %d| linha->string[%d]: %c\n", cursor, posicao, linha->string[posicao]);
	// 		// Comentario.
	// 		if (linha->string[posicao] == '#')
	// 		{
	// 			fim_de_linha = TRUE;
	// 			printf("comentário na linha: %d \n", linha->info);
	// 		}

	// 		// Rotulo.
	// 		else if (linha->string[posicao] == ':')
	// 		{
	// 			if (rotulo)
	// 			{
	// 				printf("ERROR on line %d\n", linha->info);
	// 				printf("Em cada linha pode haver apenas um rotulo!\n");
	// 				return 1;
	// 			}
	// 			else if (diretiva)
	// 			{
	// 				printf("ERROR on line %d\n", linha->info);
	// 				printf("Rotulos nao sao permitidos apos diretivas numa mesma linha!\n");
	// 				return 1;
	// 			}
	// 			else if (instrucao)
	// 			{
	// 				printf("ERROR on line %d\n", linha->info);
	// 				printf("Rotulos nao sao permitidos apos instrucoes numa mesma linha!\n");
	// 				return 1;
	// 			}

	// 			else
	// 			{
	// 				rotulo = TRUE;
	// 				printf("Rotulo na linha: %d\n", linha->info);
	// 				printf("[");
	// 				for (int i = cursor; i < posicao; i++)
	// 				{
	// 					printf("%c", linha->string[i]);
						
	// 				}
	// 				printf("]\n");
	// 				cursor = posicao + 1;
	// 			}
	// 		}

	// 		// Diretiva.
	// 		else if (linha->string[posicao] == '.')
	// 		{
	// 			if (!instrucao)
	// 			{
	// 				diretiva = TRUE;
	// 			}
				
	// 		}

	// 		else if (linha->string[posicao] == ' ')
	// 		{
	// 			else if (!diretiva && !instrucao)
	// 			{
	// 				cursor++;
	// 			}

	// 		}
	// 		// else
	// 		// {
	// 		// 	cursor = posicao + 1;
	// 		// }
	// 		posicao++;
	// 	}

	// 	printf("=========== LINHA %d (FIM) ==============\n\n", linha->info);
	// 	linha = linha->prox;
		
	// }
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
			
			adiciona_celula(&numero_invertido, digito, 0);
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

int main(int argc,char *argv[])
{
	char* arquivo_de_entrada;
	char* arquivo_de_saida;
	Lista_ligada* programaLM;
	char mapa_de_memoria[1024][13];

	if (verifica_parametros(argc, argv, &arquivo_de_entrada, &arquivo_de_saida) == 1)
	{
		return 0;
	}

	programaLM = le_arquivo_de_entrada(arquivo_de_entrada);

	if (programaLM == NULL)
	{
		printf("Erro na leitura do arquivo de entrada!\n");
		return 0;
	}

	imprime_lista(programaLM);

	// inicializa_mapa(mapa_de_memoria);
	preenche_enderecos(mapa_de_memoria);
	// imprime_mapa(mapa_de_memoria);
	
	if (identifica_elementos(&programaLM) == 1)
	{
		return 0;
	}
	return 0;
}
