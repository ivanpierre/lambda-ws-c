# very simplified Makefile working with minimal makefile version

liblws.so.1 : atom.o collections.o env.o function.o named.o nodes.o numbers.o string.o
	gcc -shared -W1,-soname,liblws.so.1 -o liblws.so.1.0.1 atom.o collections.o env.o \
	    function.o named.o nodes.o numbers.o string.o

#	ar rcs liblws.a atom.o collections.o env.o function.o named.o nodes.o numbers.o string.o

atom.o : atom.c nodes.h
	cc -c -fPIC atom.c

collections.o : nodes.h
	cc -c -fPIC collections.c

env.o : env.c nodes.h
	cc -c -fPIC env.c

function.o : function.c nodes.h
	cc -c -fPIC function.c

named.o : named.c nodes.h
	cc -c -fPIC named.c

nodes.o : nodes.c nodes.h
	cc -c -fPIC nodes.c

numbers.o : numbers.c nodes.h
	cc -c -fPIC numbers.c

string.o : string.c nodes.h
	cc -c -fPIC string.c

# .o : .c .h
# 	cc -c .c

clean:
	rm -f *.o lcw
