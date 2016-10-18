all: executa

compila:
	clear
	gcc -c montador.c
	gcc -c manipulador_de_arquivos.c
	gcc -c manipulador_de_lista_ligada.c
	gcc -c manipulador_de_caracteres.c
	gcc -c manipulador_de_diretivas.c
	gcc -c manipulador_de_memoria.c
	gcc -c manipulador_de_instrucoes.c

liga: compila
	gcc -o montador.x montador.o manipulador_de_lista_ligada.o manipulador_de_arquivos.o manipulador_de_caracteres.o manipulador_de_diretivas.o manipulador_de_memoria.o manipulador_de_instrucoes.o

executa: liga
	./montador.x prog.hex
clean:
	rm -rf *.o