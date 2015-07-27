/****
	Integer

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "integer.h"

typedef struct {
	NODE;
	long        value;
} integer;

/*
	Create an integer
*/
node *make_integer(long value) {
	node *i = create_node(INTEGER);

	if(nullp(i))
		return NULL;

	((integer *)i)->value = value;

	return link_node(i);
}

/*
	test if node is an integer
*/
bool integerp(node *node) {
	return get_type(node) == INTEGER;
}

/*
	Return value of integer
*/
long get_integer(node *i) {
	if(!integerp(i)) {
		error("node is not an integer\n");
		return 0l;
	}
	return ((integer *)i)->value;
}

/*
	print string
*/
static void print_integer(node *node) {
	fprintf(stdout, "%l", get_integer(node));
}

/*
	init type INTEGER, so the type exists in the types... ;)
*/
bool init_integer_type()
{
	types[INTEGER] = create_type( "integer",
						sizeof(type),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						NULL,   // free
						&print_integer);  // print
	if(nullp((node *)types[TYPE])) {
		error("init_integer_types : error creating type\n");
		return FALSE;
	}
	return TRUE;
}

