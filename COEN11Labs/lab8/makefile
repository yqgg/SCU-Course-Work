CC=gcc
CFLAGS=-g -Wall -Werror
DEPS = lab8.h
%.0: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lab8: main.c list.c file.c lab8.h
	gcc -o lab8 main.c list.c file.c lab8.h
test: lab8
	./lab8 text.txt


