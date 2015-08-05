# very simplified Makefile working with minimal makefile version

lcw : main.o global.o atom.o collections.o env.o function.o named.o nodes.o numbers.o reader.o string.o
	cc -o lcw main.o global.o atom.o collections.o env.o function.o named.o nodes.o numbers.o reader.o string.o

global.h : nodes.h
	touch global.h

main.o : main.c global.h
	cc -c main.c

global.o : global.c global.h

atom.o : atom.c nodes.h
	cc -c atom.c

collections.o : nodes.h
	cc -c collections.c

env.o : env.c nodes.h
	cc -c env.c

function.o : function.c nodes.h
	cc -c function.c

named.o : named.c nodes.h
	cc -c named.c

nodes.o : nodes.c nodes.h
	cc -c nodes.c

numbers.o : numbers.c nodes.h
	cc -c numbers.c

reader.o : reader.c nodes.h
	cc -c reader.c

string.o : string.c nodes.h
	cc -c string.c

# .o : .c .h
# 	cc -c .c

clean:
	rm -f *.o lcw
