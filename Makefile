main: main.o strings.o db.o
	gcc -o main main.o strings.o db.o -lsqlite3

main.o: main.c ./lib/strings.h ./include/core/db.h
	gcc -c main.c -o main.o

strings.o: ./lib/strings.c ./lib/strings.h
	gcc -c ./lib/strings.c

db.o: ./src/core/db.c ./include/core/db.h
	gcc -c ./src/core/db.c


