all: executa

compila:
	clear
	gcc -std=c99 -pedantic -Wall -o montador *.c -g
	rm -rf *.o

executa: compila
	./montador prog.hex saida.hex
	
gdb: compila
	gdb montador 
