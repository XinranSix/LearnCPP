.PHONY: all clean
all: hello
hello: main.o sum.o
	gcc -o hello main.o sum.o
main.o: main.c
	gcc -c main.c
sum.o: sum.c
	gcc -c sum.c
clean:
	rm -f main.o sum.o hello