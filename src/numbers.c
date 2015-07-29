/****
	Integer

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "nodes.h"

/*
	Create an integer
*/
Node *new_integer(long value)
{
	Node *node = new_node(INTEGER);

	if(nullp(node))
		return NULL;

	node->val.integer = value;

	return link_node(node);
}

/*
	Return value of integer
*/
long get_integer(Node *node)
{
	Node tmp = integerp(node);
	if(tmp)
	{
		unlink(tmp);
		return node->val.integer;
	}

	unlink(tmp);
	return 0l;
}

/*
	test if node is an integer
*/
bool integerp(node *node)
{
	return (node->type == INTEGER) ? true_node : NIL;
}

/*
	print integer
*/
static Node *string_integer(Node *node)
{
	if(!integerp(node))
	{
		error("print_integer : Node is not an integer\n");
		return NIL;
	}

	char *formatted;
	asprintf(&formatted, "%ld", get_integer(node));

	if(formatted)
		return new_string(formatted);
	else
	{
		free(formatted);
		return make_string_alloc("<badly formatted Integer>");
	}
}
