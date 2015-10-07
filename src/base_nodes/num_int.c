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
	get value of int
*/
WS_INT *int_unbox(Node *x)
{
	INT_UNBOX(valx, x);
	return valx;

	//*********************
	catch:
	return 0;
}

/*
	test if node is an int
*/
Node *is_int(Node *x)
{
	START_INT_FUN1;
	Node *res = (x && x->type == INTEGER) ? TRUE : FALSE;
	END_FUN1;
}

/*
	test int with a predicate
*/
static Node *tst_int(Node *x, Node *(*pred)())
{
	START_INT_FUN1;
	Node *res = (*pred)(valx) ? TRUE : FALSE;
	END_FUN1;

}

//predicates
static Node *int_is_zeroP(WS_INT val){return val == 0}
static Node *int_is_negP(WS_INT val){return val < 0}
static Node *int_is_posP(WS_INT val){return val > 0}

/**
	test = 0
*/
Node *int_is_zero(Node *x)
{
	return tst_int(x, &int_is_zeroP);
}

/**
	test > 0
*/
Node *int_is_pos(Node *x)
{
	return tst_int(x, &int_is_posP);
}

/**
	test < 0
*/
Node *int_is_neg(Node *x)
{
	return tst_int(x, &int_is_negP);
}

/*************************************************
	Coerce between numerics
*/
// Int -> Int int32
static Node *int_to_int(Node *x)
{
	return x;
}

// Int -> Long int64
static Node *int_to_long(Node *x)
{
	START_INT_FUN1;
	Node *res = long_box((WS_LONG)valx);
	END_FUN1;
}

// Int -> Float
static Node *int_to_float(Node *x)
{
	START_INT_FUN1;
	Node *res = float_box((WS_FLOAT)valx);
	END_FUN1;
}

// Int -> Double
static Node *int_to_double(Node *x)
{
	START_INT_FUN1;
	Node *res = double_box((WS_DOUBLE)valx);
	END_FUN1;
}

// Int -> type
Node *int_to_type(Node *x, TYPE type)
{
	START_INT_FUN1;
	switch(type)
	{
		case WS_BYTE:
			res = int_to_byte(valx);
			break;

		case WS_SHORT:
			res = int_to_short(valx);
			break;

		case WS_INT:
			res = int_to_int(valx);
			break;

		case WS_LONG:
			res = int_to_long(valx);
			break;

		case WS_FLOAT:
			res = int_to_float(valx);
			break;

		case WS_DOUBLE:
			res = int_to_double(valx);
			break;

		default:
			ABORT(ERR_CONVERSION, str_type(INTEGER), str_type(type));
			break
	}
	END_FUN1;
}

/********************************
	operators
*/

Node *int_add(Node *x, Node *y);
{
	START_INT_FUN2;
	res = int_box(valx + valy);
	END_FUN2;
}

Node *int_addP(Node *x, Node *y);
{
	START_INT_FUN2;
	WS_INT sum = valx + valy;
	if((sum ^ valx) < 0 && (sum ^ valy) < 0)
		res = long_allP(int_to_type(x, LONG), int_to_type(y, LONG));
	else
		res = int_box(sum);
	END_FUN2;
}

Node *int_multiply(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_multiplyP(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_divide(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_quotient(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_remainder(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_equiv(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_lt(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_lte(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_gte(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_negate(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_negateP(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_inc(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_incP(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_dec(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_decP(Node *x);
{
	START_INT_FUN1;

	END_FUN1;
}
