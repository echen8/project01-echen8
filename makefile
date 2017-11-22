all: main.c
	gcc -o shell main.c
run: all
	./shell
clean:
	rm *~
