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

int registra_rotulo(Lista_ligada** lista_de_rotulos, Lista_ligada* rotulo, int palavra_atual, char orientacao)
{
	char chr;
	boolean rotulo_valido = TRUE;
	char *orint; // Orientacao
	// printf("Wnrou rotulo: %s\n", rotulo->string);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if (rotulo->string[0] >= '0' && rotulo->string[0] <= '9')
	{

		printf("ERROR on line %d\n", rotulo->info);
		printf("Rotulos nao podem ser iniciados com um numero!\n");
		return 1;
	}

	for (int posicao = 0; rotulo->string[posicao] != ':' && rotulo_valido; posicao++)
	{
		chr = rotulo->string[posicao];
		if (!((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z') || chr == '_'))
		{
			printf("ERROR on line %d\n", rotulo->info);
			printf("caractere \'%c\' eh invalido para um rotulo!\n", chr);
			return 1;		
		}
	}
	
	orint = (char *) malloc(2 * sizeof(char));
	orint[0] = orientacao;
	orint[1] = '\0';
	adiciona_celula(lista_de_rotulos, rotulo->string, orint, palavra_atual);

	return 0;
}

int identifica_elementos(Lista_ligada* programaLM)
{
	Lista_ligada *apontador;
	Lista_ligada *lista_de_rotulos;
	boolean instrucao, diretiva, rotulo;
	boolean fim_de_linha;
	char caractere;
	int posicao, num_char;
	int linha_atual = -1;
	
	int cursor = -1; // Valor para identificar a linha 0.
	/* O valor do modulo dessa variavel representa a memoria do IAS, que vai de 0 a 1024.*/
	int palavra_atual = 0;;
	char orientacao = 'E';

	// Criacao de uma lista ligada para registrar os rotulos e seus enderecos.
	cria_lista(&lista_de_rotulos);

 	
	// Encontra o numero de linhas nao vazias;
	for (apontador = programaLM; (apontador != NULL && palavra_atual < 1024); apontador = apontador->prox)
	{
		// Nova linha
		if (linha_atual < apontador->info)
		{
			// Reset de flags.
			fim_de_linha = FALSE;
			instrucao = FALSE;
			diretiva = FALSE;
			rotulo = FALSE;
			// atualiza o numero da linha do programa em linguagem de montagem.
			linha_atual = apontador->info;
		}
		
		// Determina o numero de caracteres na string
		for (posicao = 0; apontador->string[posicao] != '\0'; posicao++);
		num_char = posicao;

		// Percorre a string buscando determinar qual eh o elemento (instrucao, diretiva, etc)
		for (posicao = 0; posicao < num_char && !fim_de_linha; posicao++)
		{
			caractere = apontador->string[posicao];
			// Identificou um comentario.
			if (caractere == '#')
			{
				if (posicao == 0)
				{
					for (; apontador->prox != NULL && apontador->prox->info == linha_atual; apontador = apontador->prox);
					fim_de_linha = TRUE;
				}
				else
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Comentario invalido!\n");
					return 1;
				}
			}
			// Identificou uma diretiva
			else if (caractere == '.')
			{
				if (posicao == 0)
				{
					diretiva = TRUE;
				}
				else
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Comentario invalido!\n");
					return 1;
				}
			}

			// Identificou um rotulo.
			else if (caractere == ':')
			{
				//printf("rotulo%d. Linha: %d\n", rotulo, apontador->info);>>>>>>>>>>>>>>>>>>>>>>>>
				if (rotulo)
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Nao eh possivel haver dois rotulos em uma mesma linha!\n");
					return 1;
				}
				else if (diretiva)
				{	
					printf("ERROR on line %d\n", apontador->info);
					printf("Nao eh possivel inserir rotulos apos diretivas!\n");
					return 1;
				}
				else if (instrucao)
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Nao eh possivel inserir instrucoes apos diretivas!\n");
					return 1;
				}
				else
				{
					if (posicao == num_char - 1)
					{
						rotulo = TRUE;

						if (registra_rotulo(&lista_de_rotulos, apontador, palavra_atual, orientacao) == 1)
						{
							return 1;
						}
					}
					else
					{
						printf("ERROR on line %d\n", apontador->info);
						printf("Rotulo invalido!\n");
						return 1;
					}
				}
			}
		}
	}
	imprime_lista(lista_de_rotulos, 12);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

	imprime_lista(programaLM, 1);

	inicializa_mapa(mapa_de_memoria);
	preenche_enderecos(mapa_de_memoria);
	// imprime_mapa(mapa_de_memoria);
	
	if (identifica_elementos(programaLM) == 1)
	{
		return 0;
	}

	return 0;
}
