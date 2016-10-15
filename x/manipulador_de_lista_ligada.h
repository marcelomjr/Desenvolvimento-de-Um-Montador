//manipulador_de_lista_ligada.h

struct lista
{
	char *info;
	struct linha *prox;
} typedef Lista_ligada;

void inicializa_lista(Lista_ligada *lista);
void adiciona_celula(Lista_ligada **lista, char **nova_info);
void imprime_lista(Lista_ligada *lista);