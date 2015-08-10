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
LDLIBS = -L../lws -llws
CC = cc

clojure : $(objects)
	$(CC) $(lflags) $@ $(objects) $(libflags)

clean:
	rm -f *.o lcw
