/****
	Integer

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "integer.h"

typedef struct
{
	NODE;
	long        value;
} integer;

/*
	Create an integer
*/
node *make_integer(long value)
{
	node *i = create_node(INTEGER);

	if(nullp(i))
		return NULL;

	((integer *)i)->value = value;

	return link_node(i);
}

/*
	test if node is an integer
*/
node *integerp(node *node)
{
	return (get_type(node) == INTEGER) ? link_node(node) : NIL;
}

/*
	Return value of integer
	TODO should be able to do coercision
*/
long get_integer(node *i)
{
	switch(get_type(i))
	{
		case INTEGER:
			return ((integer *)i)->value;

		default:
			error("get_integer : node is not an integer\n");
			return 0l;
	}
}

/*
	print integer
*/
static node *print_integer(node *node)
{
	if(!integerp(node))
	{
		error("print_integer : node is not an integer\n");
		return NIL;
	}
	char *formatted;
	asprintf(&formatted, "%ld", get_integer(node));
	if(formatted)
		return make_string(formatted);
	else
		return make_string_alloc("<badly formatted Integer>");
}

/*
	init type INTEGER, so the type exists in the types... ;)
*/
bool init_integer_type()
{
	node *integer =
	set_type(INTEGER, create_type( "integer",
						sizeof(integer),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						NULL,   // free
						&print_integer));  // print
	if(!integer)
	{
		error("init_integer_types : error creating type\n");
		return FALSE;
	}
	unlink_node(integer);
	return TRUE;
}

