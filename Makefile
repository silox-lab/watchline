main: main.o strings.o net_api.o
	gcc -o main main.o strings.o net_api.o

main.o: main.c ./lib/strings.h ./include/core/net_api.h
	gcc -c main.c -o main.o

strings.o: ./lib/strings.c ./lib/strings.h
	gcc -c ./lib/strings.c

net_api.o: ./src/core/net_api.c ./include/core/net_api.h
	gcc -c ./src/core/net_api.c
