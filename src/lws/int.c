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
#include "integer.h"

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

    //*********************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	Return value of integer
*/
long integer_integer(Node *node)
{
    ASSERT_NODE(node, tmp_node, IINTEGER);
	Integer *integer = STRUCT(node);
	long res = integer->integer;
	unlink_node(tmp_node);
	return res;

    //*********************
	error_assert:
	unlink_node(tmp_node);
	return 0l;
}

/*
	test if node is an integer
*/
Node *integer_Q_(Node *node)
{
    ASSERT_NODE(node, INODES);
	Node *res = (node && node->type->int_type == IINTEGER) ? TRUE : FALSE;
	unlink_node(node);
	return res;

    //*******************
	error_assert:
	unlink_node(node);
	return NULL;
}
