ex01: main.o utils.o parsing.o
	gcc main.o utils.o parsing.o -o ex01
main.o: main.c
	gcc -c main.c -o main.o
utils.o: utils.c
	gcc -c utils.c -o utils.o
parsing.o: parsing_zip.c
	gcc -c parsing_zip.c -o parsing.o

