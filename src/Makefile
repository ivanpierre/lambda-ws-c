# very simplified Makefile working with minimal makefile version

lcw : main.o integer.o list.o map.o reader.o string.o symbol.o types.o
	cc -o lcw main.o integer.o list.o map.o reader.o string.o symbol.o types.o

types.h : global.h
	touch types.h

main.o : main.c types.h
	cc -c main.c

integer.o : integer.c integer.h types.h
	cc -c integer.c

list.o : list.c list.h types.h
	cc -c list.c

map.o : map.c map.h types.h
	cc -c map.c

reader.o : reader.c reader.h types.h
	cc -c reader.c

string.o : string.c string.h types.h
	cc -c string.c

symbol.o : symbol.c symbol.h types.h
	cc -c symbol.c

types.o : types.c types.h types.h
	cc -c types.c

# .o : .c .h
# 	cc -c .c

clean:
	rm -f *.o lcw
