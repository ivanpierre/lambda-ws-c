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
static Node *tst_int(Node *x, Node *(*pred)(WS_INT))
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
// Int -> Byte int8
static Node *int_to_byte(Node *x)
{
	START_INT_FUN1;
	ASSERT(valx >= WS_BYTE_MIN && valx <= WS_BYTE_MAX, ERR_OVERFLOW);
	Node *res = byte_box((WS_SHORT)valx);
	END_FUN1;
}

// Int -> Short int16
static Node *int_to_short(Node *x)
{
	START_INT_FUN1;
	ASSERT(valx >= WS_SHORT_MIN && valx <= WS_SHORT_MAX, ERR_OVERFLOW);
	Node *res = short_box((WS_SHORT)valx);
	END_FUN1;
}

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

// Int -> bigdec
static Node *int_to_bigdec(Node *x)
{
	START_INT_FUN1;
	Node *res = bigdec_box((WSLONG)valx);
	END_FUN1;
}

// Int -> Ratio
static Node *int_to_ratio(Node *x)
{
	return x;
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

// Int -> bigdeb
static Node *int_to_bigdeb(Node *x)
{
	START_INT_FUN1;
	Node *res = bigdec_box((WS_DOUBLE)valx);
	END_FUN1;
}

// Int -> type
Node *int_to_type(Node *x, TYPE type)
{
	Node *res = NULL;
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

		case WS_BIGINT:
			res = int_to_bigint(valx);
			break;

		case WS_RATIO
			res = int_to_ratio(valx);
			break;

		case WS_FLOAT:
			res = int_to_float(valx);
			break;

		case WS_DOUBLE:
			res = int_to_double(valx);
			break;

		case WS_BIGDEC:
			res = int_to_bigdec(valx);
			break;

		default:
			ABORT(ERR_CONVERSION, str_type(INTEGER), str_type(type));
			break
	}

catch:
	return res;

catch:
	return NULL;
}

/********************************
	operators
*/

Node *int_add(Node *x, Node *y)
{
	START_INT_FUN2;
	res = int_box(valx + valy);
	END_FUN2;
}

Node *int_addP(Node *x, Node *y)
{
	START_INT_FUN2;
	WS_INT sum = valx + valy;
	if((sum ^ valx) < 0 && (sum ^ valy) < 0)
		res = long_allP(int_to_type(x, LONG), int_to_type(y, LONG));
	else
		res = int_box(sum);
	END_FUN2;
}

Node *int_multiply(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_multiplyP(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_divide(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_quotient(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_remainder(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_equiv(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_equal(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_lt(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_lte(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_gte(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_compare(Node *x, Node *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_negate(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_negateP(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_inc(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_incP(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_dec(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_decP(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

//* bit functions **********
Node *int_not				(Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *int_and				(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_or					(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_xor				(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_and_not			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_clear_bit			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_set_bit			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_flip_bit			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_test_bit			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_shift_left			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_shift_leftP			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_shift_right		(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_rot_left			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Node *int_rot_right			(Node *x, Node *y)
{
	START_INT_FUN2;

	END_FUN2;
}

int int_hash_code(Node *x){
}

int int_hasheq(Node *x){
}
