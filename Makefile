TARGET=MAKE
CC=clang
SRC=$(wildcard *.c)
all: argc arquivo_funcoes funcoes
argc: argc.o
	clang -o argc.o
arquivo_funcoes:arquivo_funcoes.c
	clang -c arquivo_funcoes.c
funcoes: funcoes.c funcoesh.h
	clang -o $@ -c $<
arquivo: arquivo.o
	clang -o arquivo.o

