/*
 * programa.c
 *
 *  Created on: 13 de out de 2016
 *      Author: marcelo
 */
#include "montador.h"


int main(int argc,char *argv[])
{
	char* arquivo_de_entrada;
	char* arquivo_de_saida;
	Lista_ligada* programaLM; // Lista para o programa em Linguagem de Maquina.
	Lista_ligada *mapa;

	/* Lista de rotulos. */
	Lista_ligada *lista_de_rotulos;

	/* Lista de simbolos */
	Lista_ligada *lista_de_simbolos;

	// Lista de rotulos e simbolos desconhecidos.
	Lista_ligada *lista_de_desconhecidos;
	

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
	printf("\n");

	if (primeira_montagem(programaLM, &mapa, &lista_de_rotulos, &lista_de_simbolos, &lista_de_desconhecidos) == 1)
	{
		return 0;
	}

	// printf("\n\nMapa de memoria:\n");
// 
	// imprime_lista(mapa,123);
	// imprime_mapa(&mapa);

	// printf("\n\nLista de desconhecidos\n");

	// imprime_lista(lista_de_desconhecidos, 123);

	if (segunda_montagem(&mapa, lista_de_rotulos, lista_de_simbolos, lista_de_desconhecidos) == 1)
	{
		return 1;
	}
	
	if (argc == 3)
	{
		grava_arquivo_de_saida(mapa, arquivo_de_saida);	
	}
	else
	{
		imprime_mapa(&mapa);
	}
	
	return 0;
}

int primeira_montagem(Lista_ligada* programaLM, Lista_ligada **mapa, Lista_ligada **lista_de_rotulos, Lista_ligada **lista_de_simbolos, Lista_ligada **lista_de_desconhecidos)
{
	Lista_ligada *apontador;//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..ELIMINAR
	
	// Flags para os elementos do programa.
	boolean instrucao, diretiva, rotulo, elemento_identificado;
	
	// Flag para avisar que o restante da linha pode ser dispensado (comentarios).
	boolean fim_de_linha;

	int align = 0;

	/* Variaveis relacionadas ao mapa de memoria */
	int palavra_atual = 0;
	char orientacao[] = "E";

	// Variaveis auxiliares
	char caractere;			// Armazena um char do elemento analisado.
	int posicao;			// indice da posicao atual verificada de um elemento.
	int num_char; 			// Tamanho de cada elemento.
	int linha_atual = -1;	// Identificador da linha atual do programa em liguagem de montagem.

	// Criacao de lista ligada para registrar o mapa de memoria.
	cria_lista(mapa);

	// Criacao de uma lista ligada para registrar os rotulos e seus enderecos.
	cria_lista(lista_de_rotulos);

	// Criacao de uma lista ligada para registrar as constantes do programa.
	cria_lista(lista_de_simbolos);

	// Criacao de lista ligada para registrar os rotulos e simbolos desconhecidos.
	cria_lista(lista_de_desconhecidos);

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
		
		// Determina o numero de caracteres na string sem o '\0'.
		num_char = getTamanho(apontador->string) - 1;

		elemento_identificado = FALSE;
		// Percorre a string buscando determinar qual eh o elemento (instrucao, diretiva, etc)
		for (posicao = 0; posicao < num_char && !fim_de_linha; posicao++)
		{
			caractere = apontador->string[posicao];
			// Identificou um comentario.
			if (caractere == '#')
			{
				if (posicao == 0)
				{
					elemento_identificado = TRUE;
					for (; apontador->prox != NULL && apontador->prox->info == linha_atual; apontador = apontador->prox);
					fim_de_linha = TRUE;
				}
				else
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Comentario invalido!\n");
					return 1;
				}
			}
			// Identificou uma diretiva
			else if (caractere == '.')
			{
				if (diretiva)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh permitido mais de uma diretiva por linha!\n");
					return 1;	
				}
				if (instrucao)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Diretivas e instrucoes nao podem ser utilizadas na mesma linha!\n");
					return 1;
				}	
				if (posicao == 0)
				{
					diretiva = TRUE;
					elemento_identificado = TRUE;

					if (tratador_de_diretivas(&apontador, lista_de_simbolos, lista_de_desconhecidos, &palavra_atual, &align, orientacao, mapa) == 1)
					{
						return 1;
					}
					printf("Diretiva ok na linha: %d\n",(int) apontador->info);

				}
				else
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Diretiva invalida!\n");
					return 1;
				}
			}

			// Identificou um rotulo.
			else if (caractere == ':')
			{
				printf("rotulo na linha %d: %s\n", (int) apontador->info, apontador->string);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				if (rotulo)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh possivel haver dois rotulos em uma mesma linha!\n");
					return 1;
				}
				else if (diretiva)
				{	
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh possivel inserir rotulos apos diretivas!\n");
					return 1;
				}
				else if (instrucao)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh possivel inserir instrucoes apos diretivas!\n");
					return 1;
				}
				else
				{
					if (posicao == (num_char - 1))
					{
						// Retira o ':' do rotulo.
						apontador->string[num_char - 1] = '\0';

						rotulo = TRUE;
						elemento_identificado = TRUE;
						printf("rotulo atualizado: [%s]\n", apontador->string);
						if (!verifica_rotulo(apontador, TRUE))
						{
							return 1;
						}
						// Salva um rotulo, em string o seu "representacao" e em info a palavra de memoria. 
						adiciona_celula(lista_de_rotulos, apontador->string, orientacao, palavra_atual);						
					}
					else
					{
						printf("ERROR on line %d\n", (int) apontador->info);
						printf("Rotulo invalido!\n");
						return 1;
					}
				}
			}
		}
		if (!elemento_identificado)
		{
			if (instrucao)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh possivel haver duas instrucoes em uma mesma linha!\n");
					return 1;
				}
				if (diretiva)
				{
					printf("ERROR on line %d\n", (int) apontador->info);
					printf("Nao eh possivel inserir diretivas e instrucoes na mesma linha!\n");
					return 1;
				}

			printf("Identificou uma instrucao: %s\n", apontador->string);

			if (tratador_de_instrucoes(&apontador, lista_de_desconhecidos, mapa, &palavra_atual, orientacao, align) == 1)
			{
				return 1;
			}

			instrucao = TRUE;
		}
		// Fim da analise de um elemento.
	}
	printf("\n\nRotulos:\n");
	imprime_lista(*lista_de_rotulos, 123);//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	return 0;
}

int segunda_montagem(Lista_ligada** mapa, Lista_ligada *lista_de_rotulos, Lista_ligada *lista_de_simbolos, Lista_ligada *lista_de_desconhecidos)
{
	Lista_ligada *cursor, *objeto_encontrado;
	Lista_ligada *apontador = *mapa;
	Lista_ligada *linha_no_programa; // Para quando nao achar o objeto.
	int num_palavra;
	char *objeto;
	char *numero;
	boolean achou;

	printf("Estou na sergunda montagem\n");

	// Percorre todo o mapa apenas uma vez completando os simbolos e rotulos desconhecidos.
	for (;apontador != NULL; apontador = apontador->prox)
	{
		printf("enrou no foor\n");
		if (apontador->string2[0] == 'E' && apontador->string[0] == '?')
		{
			printf("entrou no if: %d\n",(int) apontador->info );
			num_palavra = apontador->info;

			achou = FALSE;
			// Procura a palavra por seu identificador na lista de objetos desconhecidos.
			for (cursor = lista_de_desconhecidos; cursor != NULL && !achou; cursor = cursor->prox)
			{
				// Caso tenha encontrado, salva a string do objeto, para procura-lo na lista de rotulos ou de simbolos.
				if (cursor->info == num_palavra)
				{
					linha_no_programa = cursor;

					// Salva o objeto
					objeto = copia_string(cursor->string, 0);
					achou = TRUE;
				}
			}

			if (!achou)
			{
				printf("Erro no montador (segunda montagem)\n");
				return 1;
			}

			achou = FALSE;
			// Verifica se o objeto esta na lista dos rotulos.
			for (cursor = lista_de_rotulos; cursor != NULL && !achou; cursor = cursor->prox)
			{
				if (compara_strings(objeto, cursor->string) == TRUE)
				{
					objeto_encontrado = cursor;
					achou = TRUE;
				}
			}

			// Se nao esta verifica na lista dos simbolos
			if (!achou)
			{
				for (cursor = lista_de_simbolos; cursor != NULL && !achou; cursor = cursor->prox)
				{	
					if (compara_strings(objeto, cursor->string) == TRUE)
					{
						objeto_encontrado = cursor;
						achou = TRUE;
					}
				}				
			}
			if (!achou)
			{
				printf("ERROR on line %d\n", (int) (int) base_string_para_decimal_int(linha_no_programa->string2, 10));
				printf("O objeto \"%s\"nao foi definido como rotulo nem simbolo!\n", linha_no_programa->string);
				return 1;
			}
			// Caso tenha achado
			else
			{
				
				numero = decimal_para_hex(objeto_encontrado->info, 10);
				
				for (int posicao = 0; posicao < 5; posicao++)
				{
					apontador->string[posicao] = numero[posicao];
					apontador->prox->string[posicao] = numero[posicao + 5];
				}
			}

		}
		// Verifica se eh  um rotulo faltante
		else if (apontador->string[2] == 'R')
		{
			printf("ultimo\n");
			num_palavra = apontador->info;

			achou = FALSE;
			// Procura a palavra por seu identificador na lista de objetos desconhecidos.
			for (cursor = lista_de_desconhecidos; cursor != NULL && !achou; cursor = cursor->prox)
			{
				// Caso tenha encontrado, salva a string do objeto, para procura-lo na lista de rotulos.
				if (cursor->info == num_palavra)
				{
					linha_no_programa = cursor;

					// Salva o objeto
					objeto = copia_string(cursor->string, 0);
					achou = TRUE;
				}
			}

			if (!achou)
			{
				printf("Erro no montador (segunda montagem)\n");
				return 1;
			}

			achou = FALSE;

			// Verifica se o objeto esta na lista dos rotulos.
			for (cursor = lista_de_rotulos; cursor != NULL && !achou; cursor = cursor->prox)
			{
				if (compara_strings(objeto, cursor->string) == TRUE)
				{
					objeto_encontrado = cursor;
					achou = TRUE;
				}
			}
			if (!achou)
			{
				printf("ERROR on line %d\n", (int) (int) base_string_para_decimal_int(linha_no_programa->string2, 10));
				printf("O objeto \"%s\"nao foi definido como rotulo nem simbolo!\n", linha_no_programa->string);
				return 1;
			}
			// Caso tenha achado
			else
			{
				numero = decimal_para_hex(objeto_encontrado->info, 3);

				apontador->string[2] = numero[0];
				apontador->string[3] = numero[1];
				apontador->string[4] = numero[2];

				/* Por padrao as instrucoes que sao influencias pelo orientacao do rotulo sao setadas para a esquerda.
				 * Portanto se verificarmos que o seu rotulo aponta para um endereco a direita, devemos alterar para a instrucao correspondente. */
				if (objeto_encontrado->string2[0] == 'D')
				{
					// Instrucao JUMP.
					if (apontador->string[0] == '0' && apontador->string[1] == 'D')
					{
						apontador->string[1] = 'E';
					}
					// Instrucao JUMP+
					else if (apontador->string[1] == '0' && apontador->string[1] == 'F')
					{
						apontador->string[0] = '1';
						apontador->string[1] = '0';
					}
					// Instrucao STOR M
					else if (apontador->string[1] == '1' && apontador->string[1] == '2')
					{
						apontador->string[0] = '1';
						apontador->string[1] = '3';
					}

				}
			}
		}
	}

	return 0;
}