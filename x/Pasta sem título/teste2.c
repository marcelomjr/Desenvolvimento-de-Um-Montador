#include "manipulador_de_lista_ligada.h"
#include <stdio.h>

int main()
{
	char ch1[] = "0123456789";
	char ch2[] = "2222222222";
	Lista_ligada *lista;
	cria_lista(&lista);

	printf("%s\n", ch1);
	printf("%s\n", ch2);
	adiciona_celula(&lista, ch1, ch2, 0);

	imprime_lista(lista, 12);

	lista->string[2] = '\0';

	printf("%s\n", ch1);
	printf("%s\n", ch2);

	return 0;
}