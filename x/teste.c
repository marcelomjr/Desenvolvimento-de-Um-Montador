//teste.c
#include "manipulador_de_lista_ligada.h"

int main()
{
	
	Lista_ligada *prog;
	char h[] = "hoje";
	char e[] = "esta um dia ";
	char l[] = "lindo";
	cria_lista(&prog);
	
	adiciona_celula(&prog, h);
	adiciona_celula(&prog, e);
	adiciona_celula(&prog, l);

	imprime_lista(prog);
	remove_lista(&prog);
	imprime_lista(prog);
	printf("Fim do programa!\n");
	return 0;
}