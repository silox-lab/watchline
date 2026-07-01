CC = gcc
CFLAGS = -g -O0 -Wall -Wextra
BUILD_DIR = build

$(BUILD_DIR)/main: \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/strings.o \
	$(BUILD_DIR)/playground.o \
	$(BUILD_DIR)/db.o \
	$(BUILD_DIR)/updater.o \
	$(BUILD_DIR)/net_api.o
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3 -pthread

$(BUILD_DIR)/main.o: main.c ./lib/strings.h ./tests/playground.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/strings.o: ./lib/strings.c ./lib/strings.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/playground.o: ./tests/playground.c ./tests/playground.h ./include/net_api.h ./include/db.h ./include/updater.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/net_api.o: ./src/net_api.c ./include/net_api.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/db.o: ./src/db.c ./include/db.h ./include/schema.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/updater.o: ./src/updater.c ./include/updater.h ./include/net_api.h
	$(CC) $(CFLAGS) -c $< -o $@