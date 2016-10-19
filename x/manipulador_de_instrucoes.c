// manipulador_de_instrucoes.c

#include "manipulador_de_instrucoes.h"
#include "manipulador_de_caracteres.h"

int tratador_de_instrucoes(Lista_ligada **instrucao, Lista_ligada **lista_de_desconhecidos, Lista_ligada **mapa, int *palavra_atual, char *orientacao)
{
	char *string_do_numero, *arg, *rotulo;
	int tamanho;
	long int num_decimal;
	Lista_ligada *argumento = (*instrucao)->prox;
	int numero_da_instrucao = identifica_instrucao(*instrucao);
	char meia_palavra[12];
	
	if (numero_da_instrucao == -1)
	{
		return 1;
	}

	string_do_numero = decimal_para_hex(numero_da_instrucao, 2);

	meia_palavra[0] = string_do_numero[0];
	meia_palavra[1] = string_do_numero[1];

	free(string_do_numero);

	// Caso a intrucao nao necessite do campo de memoria (RSH  e LSH).
	if (numero_da_instrucao == 20 || numero_da_instrucao == 21)
	{
		meia_palavra[2] = '0';
		meia_palavra[3] = '0';
		meia_palavra[4] = '0';
	}

	else
	{
		// Verifica se ha argumentos para a instrucao.
		if ((*instrucao)->prox == NULL || (*instrucao)->info != (*instrucao)->prox->info)
		{	
			printf("ERROR on line %d\n", (int) (*instrucao)->info);
			printf("A instrucao %s necessita de  um argumento!\n", (*instrucao)->string);
			return 1;
		}

		/* Antes de verificar o argumento eh necessario descobrir se ele esta delimitado
		 * por aspas duplas, caso positivo elas deverao ser retiradas. */
		tamanho = getTamanho(argumento->string);

		if (argumento->string[0] != '"' || argumento->string[tamanho - 2] != '"')
		{
			printf("ERROR on line %d\n", (int) (*instrucao)->info);
			printf("O argumento de uma instrucao deve ser colocado entre aspas duplas!\n");
			return 1;	
		}

		// Atualiza a string da lista ligada, retirando as aspas.
		argumento->string[tamanho - 2] = '\0';
		argumento->string = copia_string(argumento->string, 1);

		// Verifica se o argumento eh um decimal.
		if (verifica_decimal (argumento, 0, 1023, &num_decimal, FALSE))
		{

			arg = decimal_para_hex(num_decimal, 3);

			meia_palavra[2] = arg[0];
			meia_palavra[3] = arg[1];
			meia_palavra[4] = arg[2];
		}

		// Verifica se o argumento eh um hexadecimal.
		else if (verifica_hexadecimal(argumento, 0, 1023, FALSE))
		{
			// Ignora o "0x" do numero hexadecimal.
			arg = copia_string(argumento->string, 2);

			meia_palavra[2] = arg[7];
			meia_palavra[3] = arg[8];
			meia_palavra[4] = arg[9];
		}
		
		// Verifica se o argumento eh um rotulo.
		else if (verifica_rotulo(argumento, FALSE))
		{
			rotulo  = copia_string(argumento->string, 0);

			adiciona_celula(lista_de_desconhecidos, rotulo, copia_string(orientacao, 0), *palavra_atual);

			meia_palavra[2] = 'R';
			meia_palavra[3] = 'R';
			meia_palavra[4] = 'R';
		}

		// Caso o argumento seja invalido.
		else
		{
			printf("ERROR on line %d\n", (int) (*instrucao)->info);
			printf("Argumento de instrucao invalido: %s. Utilize decimais (0:1023), hexadecimais ou rotulos!\n", argumento->string);
			return 1;
		}
	}
		
		avanca_meia_palavra(mapa, meia_palavra, orientacao, palavra_atual);

		*instrucao = (*instrucao)->prox;

		return 0;
}

int identifica_instrucao(Lista_ligada *instrucao)
{
	if (compara_strings("LD", instrucao->string) == TRUE)
	{
		return 1;
	}
	else if (compara_strings("LD-", instrucao->string) == TRUE)
	{
		return 2;
	}
	else if (compara_strings("LD|", instrucao->string) == TRUE)
	{
		return 3;
	}
	else if (compara_strings("LDmq", instrucao->string) == TRUE)
	{
		return 10;
	}
	else if (compara_strings("LDmq_mx", instrucao->string) == TRUE)
	{
		return 9;
	}
	else if (compara_strings("ST", instrucao->string) == TRUE)
	{
		return 33;
	}
	else if (compara_strings("JMP", instrucao->string) == TRUE)
	{
		return 0; //?????????????????????????????????????????????????????????????
	}
	else if (compara_strings("JUMP+", instrucao->string) == TRUE)
	{
		return 0; //?????????????????????????????????????????????????????????????
	}
	else if (compara_strings("ADD", instrucao->string) == TRUE)
	{
		return 5;
	}
	else if (compara_strings("ADD|", instrucao->string) == TRUE)
	{
		return 7;
	}
	else if (compara_strings("SUB", instrucao->string) == TRUE)
	{
		return 6;
	}
	else if (compara_strings("SUB|", instrucao->string) == TRUE)
	{
		return 8;
	}
	else if (compara_strings("MUL", instrucao->string) == TRUE)
	{
		return 11;
	}
	else if (compara_strings("DIV", instrucao->string) == TRUE)
	{
		return 12;
	}
	else if (compara_strings("LSH", instrucao->string) == TRUE)
	{
		return 20;
	}
	else if (compara_strings("RSH", instrucao->string) == TRUE)
	{
		return 21;
	}
	else if (compara_strings("STaddr", instrucao->string) == TRUE)
	{
		return 0;//??????????????????????????????????????????????????
	}
	else
	{
		printf("ERROR on line %d\n", (int) instrucao->info);
		printf("Elemento nao identificado: %s!\n",instrucao->string);
		return -1;
	}
}

