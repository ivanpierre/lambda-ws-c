/****
	Number

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "number.h"

/////// Integers
/*
	Create an integer
*/
Node *integer(long value)
{
	Node *node = new_node(IINTEGER);
	ASSERT(node, ERR_CREATE_NEW, str_type(IINTEGER));
	Integer *integer = STRUCT(node);
	integer->integer = value;
	return node; // already linked

	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	Return value of integer
*/
long number_integer(Node *node)
{
	Integer *integer = STRUCT(node);
	long res = integer->integer;
	unlink_node(&node);
	return res;
}

/*
	test if node is an integer
*/
Node *integer_Q_(Node *node)
{
	Node *res = (node && node->type->int_type == IINTEGER) ? TRUE : FALSE;
	unlink_node(&node);
	return res;
}

////// Decimals
/*
	Create a decimal
*/
Node *decimal(double value)
{
	Node *node = new_node(IDECIMAL);
	ASSERT(node, ERR_CREATE_NEW, str_type(IDECIMAL));
	Decimal *decimal = STRUCT(node);
	decimal->decimal = value;
	return node; // already linked

	error_assert:
	unlink_node(&node);
	return NULL;
}

/*
	Return value of integer
*/
double number_decimal(Node *node)
{
	Decimal *decimal = STRUCT(node);
	double res = decimal->decimal;
	unlink_node(&node);
	return res;
}

/*
	test if node is a decimal
*/
Node *decimal_Q_(Node *node)
{
	Node *res = (node && node->type->int_type == IINTEGER) ? TRUE : FALSE;
	unlink_node(&node);
	return res;
}

/*
    unalloc number
*/
Node *number_free(Node **node)
{
    free(*node);
	*node = NULL;
    return NULL;
}
