main: main.o strings.o playground.o
	gcc -o main main.o strings.o playground.o

main.o: main.c ./lib/strings.h ./tests/playground.h
	gcc -c main.c -o main.o

strings.o: ./lib/strings.c ./lib/strings.h
	gcc -c ./lib/strings.c

playground.o: ./tests/playground.c ./tests/playground.h
	gcc -c ./tests/playground.c