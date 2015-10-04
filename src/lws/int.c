/****
	Int : manage 32 bits Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

// include all number headers in order to have conversion functions
#include "number.h"

/*
	Create an int
*/
Node *int(WS_INT value)
{
	Node *node = new_node(IINTEGER);
	ASSERT(node, ERR_CREATE_NEW, str_type(IINTEGER));
	Integer *integer = STRUCT(node);
	integer->integer = value;
	return unlink_new(node);

    //*********************
	catch:
	unlink_node(node);
	return NULL;
}

/*
	Return value of int
*/
WS_INT int_unbox(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	Int *integer = STRUCT(node);
	WS_INT res = integer->integer;
	POP_ARGS(1, node);
	return res;

    //*********************
	catch:
	POP_ARGS(1, node);
	return 0l;
}

/*
	test if node is an int
*/
Node *is_int(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	Node *res = (node && node->type->int_type == IINTEGER) ? TRUE : FALSE;
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

/*
	test int with a predicate
*/
static Node *tst_int(Node *node, Node *(*pred)())
{
	PUSH_ARGS(1, node);
	ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = (*pred)(val) ? TRUE : FALSE;
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

//predicates
static Node *is_zero(WS_INT val){return val == 0}
static Node *is_neg(WS_INT val){return val < 0}
static Node *is_pos(WS_INT val){return val > 0}

/**
	test = 0
*/
Node *int_is_zero(Node *node)
{
	return tst_int(node, &is_zero);
}

/**
	test > 0
*/
Node *int_is_pos(Node *node)
{
	return tst_int(node, &is_pos);
}

/**
	test < 0
*/
Node *int_is_neg(Node *node)
{
	return tst_int(node, &is_neg);
}

/*************************************************
	Coerce to other numerics
****/
// Byte int8
Node *int_to_byte(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = byte_box(val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Short int16
Node *int_to_short(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = short_box(val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Node	*int_to_integer			(Node *node)

// Long int64
Node *int_to_long(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = long_box(val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Node *int_to_ratio(Node *node)

// Float
Node *int_to_float(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = float_box(val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Double
Node *int_to_double	(Node *node)
{
	PUSH_ARGS(1, node);
    ASSERT_TYPE(node, IINTEGER);
	WS_INT val = int_unbox(node);
	Node *res = double_box(val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}
