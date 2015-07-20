# very simplified Makefile working with minimal makefile version

lcw : main.o types.o
	cc -o lcw main.o types.o

main.o : main.c
	cc -c main.c

types.o : types.c
	cc -c types.c

clean:
	rm -f *.o lcw