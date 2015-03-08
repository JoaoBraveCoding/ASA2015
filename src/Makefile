
all: main

main: main.o
	gcc -o main -O3 -lm main.o
main.o: main.c
	gcc -c -O3 -ansi -Wall -lm main.c

clean:
	rm *.o main
