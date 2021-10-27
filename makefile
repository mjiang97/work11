all: work11.o
	gcc -o program work11.o
work11.o: work11.c
	gcc -x c -c work11.c
run:
	./program
clean:
	rm *.o 