/*
 * programa.c
 *
 *  Created on: 13 de out de 2016
 *      Author: marcelo
 */
#include "montador.h"

int registra_rotulo(Lista_ligada** lista_de_rotulos, Lista_ligada* rotulo, int palavra_atual, char orientacao)
{
	char chr;
	char *lado; // Lado esquerdo ou direito da palavra de memoria.

	if (verifica_rotulo(rotulo, TRUE) == FALSE)
	{
		return 1;
	}
	
	lado = (char *) malloc(2 * sizeof(char));
	lado[0] = orientacao;
	lado[1] = '\0';

	adiciona_celula(lista_de_rotulos, rotulo->string, lado, palavra_atual);

	return 0;
}

int primeira_montagem(Lista_ligada* programaLM, char mapa[][13])
{
	Lista_ligada *apontador;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..ELIMINAR
	
	// Flags para os elementos do programa.
	boolean instrucao, diretiva, rotulo;
	
	// Flag para avisar que o restante da linha pode ser dispensado (comentarios).
	boolean fim_de_linha;

	/* Variaveis relacionadas aos rotulos */
	Lista_ligada *lista_de_rotulos;


	/* Variaveis relacionadas a diretivas */
	diretivas diretiva_identificada;
	Lista_ligada *lista_de_constantes;
	// Rotulos e simbolos.
	Lista_ligada *lista_de_desconhecidos;
	int align = 0;

	/* Variaveis relacionadas ao mapa de memoria */
	int palavra_atual = 0;
	char orientacao = 'E';

	// Variaveis auxiliares
	char caractere;			// Armazena um char do elemento analisado.
	int posicao;			// indice da posicao atual verificada de um elemento.
	int num_char; 			// Tamanho de cada elemento.
	int linha_atual = -1;	// Identificador da linha atual do programa em liguagem de montagem.

	// Criacao de uma lista ligada para registrar os rotulos e seus enderecos.
	cria_lista(&lista_de_rotulos);

	// Criacao de uma lista ligada para registrar as constantes do programa.
	cria_lista(&lista_de_constantes);

	// Criacao de uma lista ligada para registrar os rotulos e simbolos desconhecidos.
	cria_lista(&lista_de_desconhecidos);

	// Percorre todo o programa em liguagem de montagem.
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
				if (diretiva)
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Nao eh permitido mais de uma diretiva por linha!\n");
					return 1;	
				}
				if (instrucao)
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Diretivas e instrucoes nao podem ser utilizadas na mesma linha!\n");
					return 1;
				}	
				if (posicao == 0)
				{
					diretiva = TRUE;
					if (tratador_de_diretivas(&apontador, &lista_de_constantes, &lista_de_desconhecidos, &palavra_atual, &align, &orientacao, mapa) == 1)
					{
						return 1;
					}

				}
				else
				{
					printf("ERROR on line %d\n", apontador->info);
					printf("Diretiva invalida!\n");
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
					if (posicao == (num_char - 1))
					{
						// Retira o ':' do rotulo.
						// apontador->string[num_char - 1] = '\0';>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VER se precisa ser assim
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
	
	if (primeira_montagem(programaLM, mapa_de_memoria) == 1)
	{
		return 0;
	}

	return 0;
}
