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
Node *integer(long value)
{
	TRACE("Va faire %s", str_type(IINTEGER));
	Node *node = NEW(IINTEGER);
	ASSERT(node, "Error creating integer");
	node->val.integer = value;
	TRACE("%s fait !", str_type(node->type));
	return node; // already linked
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
	return (node && node->type == IINTEGER) ? true : FALSE;
}

////// Decimals
/*
	Create a decimal
*/
Node *decimal(double value)
{
	TRACE("Va faire %s", str_type(IDECIMAL));
	Node *node = NEW(IDECIMAL);
	ASSERT(node, "Error creating decimal");
	node->val.decimal = value;
	TRACE("%s fait !", str_type(node->type));
	return node;
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
	return (node && node->type == IDECIMAL) ? true : FALSE;
}

/*
    unalloc number
*/
Node *number_free(Node *node)
{
    free(node);
    return NULL;
}
