###
#    Makefile for lws library
#
#    Lambda Calculus Workshop
#    C version
#    Ivan Pierre <ivan@kilroysoft.ch> 2015
###

sources := $(wildcard *.c)
objects := $(patsubst %.c,%.o,$(sources))

CFLAGS = -fPIC -g
LDFLAGS = -shared -W1,-soname,liblws.so.1 -o
CC = cc

all: clean liblws.so

liblws.so : $(objects)
	$(CC) $(LDFLAGS) liblws.so $(objects)

clean:
	rm -f *.o lcw
