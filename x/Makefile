all: executa

compila:
	clear
	gcc -c montador.c
	gcc -c manipulador_de_arquivos.c
	gcc -c manipulador_de_lista_ligada.c

liga: compila
	gcc -o montador.x montador.o manipulador_de_lista_ligada.o manipulador_de_arquivos.o

executa: liga
	./montador.x prog.hex
clean:
	rm -rf *.o