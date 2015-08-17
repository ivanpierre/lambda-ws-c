/****
	Number

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

/////// Integers
/*
	Create an integer
*/
Node *integer(Integer value)
{
	Node *node = NEW(INTEGER);

	if(!node)
		return NULL;

	node->val.integer = value;

	return link_node(node);
}

/*
	Return value of integer
*/
Integer number_integer(Node *node)
{
	return node->val.integer;
}

/*
	test if node is an integer
*/
Node *integer_Q_(Node *node)
{
	return (node && node->type & INTEGER) ? true : false;
}

////// Decimals
/*
	Create a decimal
*/
Node *decimal(Decimal value)
{
	Node *node = NEW(INTEGER);
	node->val.decimal = value;
	return link_node(node);
}

/*
	Return value of integer
*/
Decimal number_decimal(Node *node)
{
	return node->val.decimal;
}

/*
	test if node is a decimal
*/
Node *decimal_Q_(Node *node)
{
	return (node && node->type & DECIMAL) ? true : false;
}

/*
    unalloc number
*/
Node *number_free(Node *node)
{
    free(node);
    return NULL;
}
