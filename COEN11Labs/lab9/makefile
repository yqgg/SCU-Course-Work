CC=gcc
CFLAGS=-g -Wall -Werror
DEPS = lab9.h
%.0: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab9: main.c list.c file.c lab9.h
	gcc -o lab9 main.c list.c file.c lab9.h -lpthread
test: lab9
	./lab9 data.txt


