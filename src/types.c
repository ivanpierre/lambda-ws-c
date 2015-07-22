/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "types.h"

/*
	Struct to get the type
*/
typedef struct {
	TYPES   type;
} node;

/*
	Node of type TYPE
*/
typedef struct {
	TYPES   type;
	void    *segment;
	int     (*equals)(void *node1, void *node2);
	int     (*cmp)(void * node1, void *node2);
	void    *(*eval)(void *node);
	void    (*unlink)(void *node);
	void    (*link)(void *node);
	void    (*print)(void *node);
} type;

/*
	return type of node
*/
TYPES get_type(void *n)
{
	if(!n)
		return NULL_TYPE;
	return ((node *)n)->type;
}

/*
	Is node of type TYPE
*/
boolean typep(void *node)
{
	return get_type(node) == TYPE;
}

/*
    Is node NULL
*/
boolean nullp(void *node)
{
	return !node;
}


