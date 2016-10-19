//manipulador_de_argumentos.h3
#include "tipos.h"
#include "manipulador_de_lista_ligada.h"
#include "manipulador_de_conversoes.h"

extern FILE* saida;

boolean verifica_hexadecimal(Lista_ligada *numero, long int min, long int max, boolean imprime_erros);
boolean verifica_decimal (Lista_ligada *numero, long int min, long int max, long int *num_decimal, boolean imprime_erros);
boolean verifica_rotulo(Lista_ligada *rotulo, boolean imprime_erros);
boolean verifica_simbolo(Lista_ligada *simbolo, boolean imprime_erros);