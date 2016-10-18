// manipulador_de_instrucoes.c

#include "manipulador_de_instrucoes.h"
#include "manipulador_de_caracteres.h"

int identifica_instrucao(Lista_ligada **instrucao, Lista_ligada **lista_de_rotulos_desc)
{
	if (compara_strings("LD", (*instrucao)->string) == TRUE)
	{
		return 1;
	}
	else if (compara_strings("LD-", (*instrucao)->string) == TRUE)
	{
		return 2;
	}
	else if (compara_strings("LD|", (*instrucao)->string) == TRUE)
	{
		return 3;
	}
	else if (compara_strings("LDmq", (*instrucao)->string) == TRUE)
	{
		return 10;
	}
	else if (compara_strings("LDmq_mx", (*instrucao)->string) == TRUE)
	{
		return 9;
	}
	else if (compara_strings("ST", (*instrucao)->string) == TRUE)
	{
		return 33;
	}
	else if (compara_strings("JMP", (*instrucao)->string) == TRUE)
	{
		// return?????????????????????????????????????????????????????????????
	}
	else if (compara_strings("JUMP+", (*instrucao)->string) == TRUE)
	{
		// return?????????????????????????????????????????????????????????????
	}
	else if (compara_strings("ADD", (*instrucao)->string) == TRUE)
	{
		return 5;
	}
	else if (compara_strings("ADD|", (*instrucao)->string) == TRUE)
	{
		return 7;
	}
	else if (compara_strings("SUB", (*instrucao)->string) == TRUE)
	{
		return 6;
	}
	else if (compara_strings("SUB|", (*instrucao)->string) == TRUE)
	{
		return 8;
	}
	else if (compara_strings("MUL", (*instrucao)->string) == TRUE)
	{
		return 11;
	}
	else if (compara_strings("DIV", (*instrucao)->string) == TRUE)
	{
		return 12;
	}
	else if (compara_strings("LSH", (*instrucao)->string) == TRUE)
	{
		return 20;
	}
	else if (compara_strings("RSH", (*instrucao)->string) == TRUE)
	{
		return 21;
	}
	else if (compara_strings("STaddr", (*instrucao)->string) == TRUE)
	{
		// return??????????????????????????????????????????????????
	}
	else
	{
		printf("ERROR on line %d\n", (*instrucao)->info);
		printf("Elemento nao identificado: %s!\n"(*instrucao)->string);
		return 1;
	}


)
}