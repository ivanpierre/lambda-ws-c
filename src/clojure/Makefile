###
#    Makefile for clojure-like executable
#
#    Lambda Calculus Workshop
#    C version
#    Ivan Pierre <ivan@kilroysoft.ch> 2015
###

sources := $(wildcard *.c)
objects := $(patsubst %.c,%.o,$(sources))

vpath %.h ../lws

CFLAGS = -fPIC -I. -I../lws
LDFLAGS = -o
LDLIBS = -L. -llws
CC = cc -g

clojure : $(objects) liblws.so
	$(CC) $(LDFLAGS) $@ $(objects) $(LDLIBS)

liblws.so : ../lws/liblws.so
	cp ../lws/liblws.so .

clean:
	rm -f *.o lib* clojure
