###
#    Makefile for lws library
#
#    Lambda Calculus Workshop
#    C version
#    Ivan Pierre <ivan@kilroysoft.ch> 2015
###

sources := $(wildcard *.c)
objects := $(patsubst %.c,%.o,$(sources))

CFLAGS = -fPIC
LDFLAGS = -shared -W1,-soname,liblws.so.1 -o
CC = cc

liblws.so.1 : $(objects)
	$(CC) $(LDFLAGS) liblws.so.1.0.1 $(objects)

clean:
	rm -f *.o lcw
