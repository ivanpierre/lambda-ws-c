# very simplified Makefile working with minimal makefile version

lcw : main.o list.o map.o reader.o symbol.o types.o
	cc -o lcw main.o list.o map.o reader.o symbol.o types.o

types.h : global.h
	touch types.h

main.o : main.c types.h
	cc -c main.c

chunks.o : chunks.c chunks.h
	cc -c chunks.c

gc.o : gc.c gc.h
	cc -c gc.c

list.o : list.c list.h
	cc -c list.c

map.o : map.c map.h
	cc -c map.c

reader.o : reader.c reader.h
	cc -c reader.c

segment.o : segment.c segment.h
	cc -c segment.c

symbol.o : symbol.c symbol.h
	cc -c symbol.c

types.o : types.c types.h
	cc -c types.c

# .o : .c .h
# 	cc -c .c


clean:
	rm -f *.o lcw
