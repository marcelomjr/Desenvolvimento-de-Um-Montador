// manipulador_de_lista_ligada.c
void inicializa_lista(Lista_ligada *lista)
{
	*lista->prox = NULL;
}

void adiciona_celula(Lista_ligada **lista, char **nova_info)
{
	Lista_ligada **ponteiro;
	Lista_ligada *nova_celula;

	for (ponteiro = lista; ponteiro->prox != NULL; ponteiro = ponteiro->prox);

	ponteiro->prox = nova_celula;

	nova_celula = (Linha_prog**) malloc(sizeof(Lista_ligada*));

	nova_celula->prox = NULL;

	nova_celula->linha = linha;
}

void desaloca_lista()
{

}

void imprime_lista(Lista_ligada *lista)
{
	while (lista->prox != NULL)
	{
		printf("[%s]\n", lista->linha);
		lista = lista->prox;
	}
}
