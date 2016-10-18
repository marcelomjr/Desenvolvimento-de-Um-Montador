// manipulador_de_instrucoes.c

#include "manipulador_de_instrucoes.h"
#include "manipulador_de_caracteres.h"


int tratador_de_instrucoes(Lista_ligada **instrucao, Lista_ligada **lista_de_rotulos_desc, char mapa[][13], int *palavra_atual, char *orientacao)
{
	char *string_do_numero, *arg, *rotulo, *lado;
	int deslocamento = 0, tamanho;
	long int num_decimal;
	Lista_ligada *argumento = (*instrucao)->prox;
	int numero_da_instrucao = identifica_instrucao(*instrucao);
	boolean rotulo_valido;
	
	if (numero_da_instrucao == -1)
	{
		return 1;
	}

	if (*orientacao == 'D')
	{
		deslocamento = 5;
	}
	string_do_numero = decimal_para_hex(numero_da_instrucao, 2);

	mapa[*palavra_atual][3 + deslocamento] = string_do_numero[0];
	mapa[*palavra_atual][4 + deslocamento] = string_do_numero[1];

	free(string_do_numero);

	// Caso a intrucao nao necessite do campo de memoria (RSH  e LSH).
	if (numero_da_instrucao == 20 || numero_da_instrucao == 21)
	{
		mapa[*palavra_atual][5 + deslocamento] = '0';
		mapa[*palavra_atual][6 + deslocamento] = '0';
		mapa[*palavra_atual][7 + deslocamento] = '0';
	}

	else
	{
		if ((*instrucao)->prox == NULL || (*instrucao)->info != (*instrucao)->prox->info)
		{	
			printf("ERROR on line %d\n", (*instrucao)->info);
			printf("A instrucao %s necessita de  um argumento!\n", (*instrucao)->string);
			return 1;
		}

		/* Antes de verificar o argumento eh necessario descobrir se ele esta delimitado
		 * por aspas duplas, caso positivo elas deverao ser retiradas. */
		tamanho = getTamanho(argumento->string);

		if (argumento->string[0] != '"' || argumento->string[tamanho - 2] != '"')
		{
			printf("ERROR on line %d\n", (*instrucao)->info);
			printf("O argumento de uma instrucao deve ser colocado entre aspas duplas!\n");
			return 1;	
		}

		// Atualiza a string da lista ligada.
		argumento->string[tamanho - 2] = '\0';
		argumento->string = copia_string(argumento->string, 1);

		// Verifica se o argumento eh um decimal.
		if (verifica_decimal (argumento, 0, 1023, &num_decimal, FALSE))
		{

			arg = decimal_para_hex(num_decimal, 3);

			mapa[*palavra_atual][5 + deslocamento] = arg[0];
			mapa[*palavra_atual][6 + deslocamento] = arg[1];
			mapa[*palavra_atual][7 + deslocamento] = arg[2];
		}
		// Verifica se o argumento eh um hexadecimal.
		else if (verifica_hexadecimal(argumento, 0, 1023, FALSE))
		{
			// Ignora o "0x" do numero hexadecimal.
			arg = copia_string(argumento->string, 2);

			mapa[*palavra_atual][5 + deslocamento] = arg[7];
			mapa[*palavra_atual][6 + deslocamento] = arg[8];
			mapa[*palavra_atual][7 + deslocamento] = arg[9];
		}
		
		// Verifica se o argumento eh um rotulo.
		else if (verifica_rotulo(argumento, FALSE))
		{
			rotulo  = copia_string(argumento->string, 0);
			// Orientacao do rotulo.
			lado = (char *) malloc(2 * sizeof(char));
			lado[0] = *orientacao;
			lado[1] = '\0';

			adiciona_celula(lista_de_rotulos_desc, rotulo, lado, *palavra_atual);
		}

		// Caso o argumento seja invalido.
		else
		{
			printf("ERROR on line %d\n", (*instrucao)->info);
			printf("Argumento de instrucao invalido: %s. Utilize decimais (0:1023), hexadecimais ou rotulos!\n", argumento->string);
			return 1;
		}
	}
		*instrucao = (*instrucao)->prox;
		avanca_meias_palavra(palavra_atual, orientacao, 1);
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
		printf("ERROR on line %d\n", instrucao->info);
		printf("Elemento nao identificado: %s!\n",instrucao->string);
		return -1;
	}
}

