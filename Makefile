# Makefile for t9 program
# CSE374

# default target
t9: T9.o Trie.o
	gcc -Wall -g -o t9 T9.o Trie.o

# individual source files
Trie.o: Trie.c Trie.h
	gcc -Wall -g -c Trie.c

T9.o: T9.c Trie.h
	gcc -Wall -g -c T9.c

clean:
	rm Trie.o
	rm T9.o