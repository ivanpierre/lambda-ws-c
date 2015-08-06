/****
	Integer

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
Node *new_integer(Integer value)
{
	Node *node = new_node(INTEGER);

	if(!node)
		return NULL;

	node->val.integer = value;

	return link_node(node);
}

/*
	Return value of integer
*/
Integer get_integer(Node *node)
{
	return node->val.integer;
}

/*
	test if node is an integer
*/
bool integerp(Node *node)
{
	return node && node->type == INTEGER;
}

////// Decimals
/*
	Create a decimal
*/
Node *new_decimal(Decimal value)
{
	Node *node = new_node(INTEGER);
	node->val.decimal = value;
	return link_node(node);
}

/*
	Return value of integer
*/
Decimal get_decimal(Node *node)
{
	return node->val.decimal;
}

/*
	test if node is a decimal
*/
bool decimalp(Node *node)
{
	return node && node->type & DECIMAL;
}

