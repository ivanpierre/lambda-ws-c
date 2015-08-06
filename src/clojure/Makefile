################################################################
# Clojure-like makefile
# very simplified Makefile working with minimal makefile version

clojure : main.o global.o reader.o writer.o
	cc --o clojure main.o global.o reader.o writer.o -L../lws -llws

global.h : ../lws/nodes.h
	touch global.h

main.o : main.c global.h
	cc -c -fPIC main.c

global.o : global.c global.h
	cc -c -fPIC global.c

reader.o : reader.c ../lws/nodes.h
	cc -c -fPIC reader.c

writer.o : writer.c ../lws/nodes.h
	cc -c -fPIC string.c

# .o : .c .h
# 	cc -c .c

clean:
	rm -f *.o lcw
