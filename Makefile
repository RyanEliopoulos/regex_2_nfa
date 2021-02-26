main: main.o stack.o core.o nfaBuilder.o ancillary.o
	gcc -o main main.o stack.o core.o nfaBuilder.o ancillary.o

main.o: main.c
	gcc -c main.c

stack.o: stack.c
	gcc -c stack.c

core.o: core.c
	gcc -c core.c

nfaBuilder.o: nfaBuilder.c
	gcc -c nfaBuilder.c

ancillary.o: ancillary.c
	gcc -c ancillary.c

debug: main.o stack.o core.o nfaBuilder.o ancillary.o
	gcc -g -o main main.o stack.o core.o nfaBuilder.o ancillary.o
