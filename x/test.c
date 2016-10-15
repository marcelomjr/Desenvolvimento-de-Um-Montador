int main()
{
	int *a, *b;
	int d = 3;	

	printf("a: %u.\n", a);		// endereço salvo em a
	printf("&a: %u.\n", &a);	// endereço de a
	printf("*a: %u.\n", *a);	// conteudo do endereço salvo em a

	printf("&d: %u.\n", &d);

	return 0;
}