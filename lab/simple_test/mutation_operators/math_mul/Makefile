
CC ~= /opt/llvm-3.9/bin/clang

OBJS=math_mul.o

default: main
	./main

main: $(OBJS)
	clang -Wall -o main $(OBJS) main.c

%.o:
	clang -S -emit-llvm $*.c
	clang -c $*.c

clean:
	rm -rf main
	rm -rf *.o
	rm -rf *.bc
