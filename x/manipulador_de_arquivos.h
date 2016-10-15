// manipulador_de_arquivos.h

struct linha_prog
{
	char *linha;
	struct linha *prox;
} typedef Linha_prog;

int le_arquivo_de_entrada(char* arquivo_de_entrada);
void inicializa_lista(Linha_prog **programa);
void adiciona_linha(Linha_prog **programa, char **linha);
void imprime_lista(*lista);