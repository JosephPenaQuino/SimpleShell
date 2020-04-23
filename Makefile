CFLAGS=-Wall -g
all:
	@gcc -o main main.c
debug:
	@gcc -o main -D_DEBUG main.c
clean:
	@rm main
