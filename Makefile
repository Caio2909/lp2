
CC=clang

all: cadastro2 clean

cadastro2: cadastro2.o
	clang -o cadastro2 cadastro2.o
cadastro2.o: cadastro2.c	
	clang -o cadastro2.o -c cadastro2.c
clean:
	rm -rf *.o