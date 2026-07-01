CC = gcc
CFLAGS = -g -O0 -Wall -Wextra

main: main.o strings.o playground.o db.o updater.o net_api.o
	$(CC) $(CFLAGS) -o main main.o strings.o playground.o db.o updater.o net_api.o -lsqlite3 -pthread

main.o: main.c ./lib/strings.h ./tests/playground.h
	$(CC) $(CFLAGS) -c main.c -o main.o

strings.o: ./lib/strings.c ./lib/strings.h
	$(CC) $(CFLAGS) -c ./lib/strings.c -o strings.o

playground.o: ./tests/playground.h ./tests/playground.c ./src/net_api.c ./include/net_api.h ./include/db.h ./include/updater.h
	$(CC) $(CFLAGS) -c ./tests/playground.c -o playground.o

net_api.o: ./src/net_api.c ./include/net_api.h
	$(CC) $(CFLAGS) -c ./src/net_api.c -o net_api.o

db.o: ./src/db.c ./include/db.h ./include/schema.h
	$(CC) $(CFLAGS) -c ./src/db.c -o db.o

updater.o: ./src/updater.c ./include/updater.h ./include/net_api.h
	$(CC) $(CFLAGS) -c ./src/updater.c -o updater.o