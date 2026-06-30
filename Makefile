CC = gcc
CFLAGS = -g -O0 -Wall -Wextra

main: main.o strings.o playground.o db.o updater.o net_api.o
	$(CC) $(CFLAGS) -o main main.o strings.o playground.o db.o updater.o net_api.o -lsqlite3 -pthread

main.o: main.c ./lib/strings.h ./tests/playground.h
	$(CC) $(CFLAGS) -c main.c -o main.o

strings.o: ./lib/strings.c ./lib/strings.h
	$(CC) $(CFLAGS) -c ./lib/strings.c -o strings.o

playground.o: ./tests/playground.h ./tests/playground.c ./src/core/net_api.c ./include/core/net_api.h ./include/storage/db.h ./include/core/updater.h
	$(CC) $(CFLAGS) -c ./tests/playground.c -o playground.o

net_api.o: ./src/core/net_api.c ./include/core/net_api.h
	$(CC) $(CFLAGS) -c ./src/core/net_api.c -o net_api.o

db.o: ./src/storage/db.c ./include/storage/db.h ./include/storage/schema.h
	$(CC) $(CFLAGS) -c ./src/storage/db.c -o db.o

updater.o: ./src/core/updater.c ./include/core/updater.h ./include/core/net_api.h
	$(CC) $(CFLAGS) -c ./src/core/updater.c -o updater.o