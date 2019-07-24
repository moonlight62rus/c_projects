app: main.o parse.o
	gcc -o app main.o parse.o
main.o: main.c parse.h
	gcc -c main.c
parse.o: parse.c parse.h
	gcc -c parse.c
clean:
	rm main.o parse.o app