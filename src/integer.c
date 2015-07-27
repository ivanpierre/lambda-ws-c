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
		return 0;
	}
	return ((integer *)i)->value;
}
