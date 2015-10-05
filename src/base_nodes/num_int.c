/****
	Int : manage 32 bits Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "type.h"

// include all number headers in order to have conversion functions
#include "number.h"

/*
	Create an int
*/
Node *int_box(WS_INT value)
{
	Node *node = new_node(INTEGER);
	ASSERT(node, ERR_CREATE_NEW, str_type(INTEGER));
	Integer *integer = STRUCT(node);
	integer->value = value;
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
    ASSERT_TYPE(node, INTEGER);
	Int *integer = STRUCT(node);
	WS_INT value = integer->value;
	POP_ARGS(1, node);
	return value;

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
	Node *res = (node && node->type->int_type == INTEGER) ?
					TRUE : FALSE;
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
	ASSERT_TYPE(node, INTEGER);
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
static Node *int_is_zero(WS_INT val){return val == 0}
static Node *int_is_neg(WS_INT val){return val < 0}
static Node *int_is_pos(WS_INT val){return val > 0}

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
	Coerce between numerics
*/
// Int -> Byte int8
static Node *int_to_byte(Node *node)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	ASSERT(val >= WS_BYTE_MIN && val <= WS_BYTE_MAX, ERR_OVERFLOW);
	Node *res = byte_box((WS_BYTE)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Int -> Short int16
static Node *int_to_short(Node *node)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	ASSERT(val >= WS_SHORT_MIN && val <= WS_SHORT_MAX, ERR_OVERFLOW);
	Node *res = short_box((WS_SHORT)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Int -> Int int32
static Node *int_to_int(Node *node)
{
	return node;
}

// Int -> Long int64
static Node *int_to_long(Node *node)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	Node *res = long_box((WS_LONG)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Node *int_to_ratio(Node *node)

// Int -> Float
static Node *int_to_float(Node *node)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	Node *res = float_box((WS_FLOAT)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Int -> Double
static Node *int_to_double(Node *node)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	Node *res = double_box((WS_DOUBLE)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}

// Int -> type
static Node *int_to_double(Node *node, TYPE type)
{
	PUSH_ARGS(1, node);
	WS_INT val = int_unbox(node);
	Node *res = NULL;
	switch(type)
	{
		case WS_BYTE:
	}
	Node *res = double_box((WS_DOUBLE)val);
	POP_ARGS(1, node);
	return res;

    //*******************
	catch:
	POP_ARGS(1, node);
	return NULL;
}
