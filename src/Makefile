# very simplified Makefile working with minimal makefile version

lcw : main.o global.o atom.o collections.o env.o function.o numbers.o reader.o seq.o string.o
	cc -o lcw main.o global.o atom.o collections.o env.o function.o numbers.o reader.o seq.o string.o

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

numbers.o : nodes.h
	cc -c numbers.c

reader.o : reader.c nodes.h
	cc -c reader.c

seq.o : seq.c nodes.h
	cc -c seq.c

string.o : string.c nodes.h
	cc -c string.c

# .o : .c .h
# 	cc -c .c

clean:
	rm -f *.o lcw
