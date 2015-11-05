/****
	Int : manage 32 bits Integers

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2025
*/

#include <stdio.h>
#include "oop.h"

static  MethodDef	int_func_def[] =
			{
				{"isZero",			1, &int_is_zero},
				("isNeg",			1, &int_is_neg),
				{"isPos",			1, &int_is_pos},
				{"coerce",			2, &int_coerce},
				{"add",				2, &int_add},
				{"addP",			2, &int_addP},
				{"multiply",		2, &int_multiply},
				{"multiplyP",		2, &int_multiplyP},
				{"divide",			2, &int_divide},
				{"quotient",		2, &int_quotient},
				{"remainder",		2, &int_remainder},
				{"equiv",			2, &int_equiv},
				{"equal",			2, &int_equal},
				{"lt",				2, &int_lt},
				{"lte",				2, &int_lte},
				{"gte",				2, &int_gte},
				{"compare",			2, &int_compare},
				{"negate",			1, &int_negate},
				{"negateP",			1, &int_negateP},
				{"inc",				1, &int_inc},
				{"incP",			1, &int_incP},
				{"dec",				1, &int_dec},
				{"decP",			1, &int_decP},
				{"not",				1, &int_not},
				{"and",				2, &int_and},
				{"or",				2, &int_or},
				{"xor",				2, &int_xor},
				{"andNot",			2, &int_and_not},
				{"clearBit",		2, &int_clear_bit},
				{"setBit",			2, &int_set_bit},
				{"flipBit",			2, &int_flip_bit},
				{"testBit",			2, &int_test_bit},
				METHOD_DESC_END
			};



/*
	Create an int
*/
Object *int_box(WS_INT value)
{
	Object *node = new_node(INTEGER);
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
WS_INT *int_unbox(Object *x)
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
Object *is_int(Object *x)
{
	START_INT_FUN2;
	Object *res = (x && x == INTEGER) ? TRUE : FALSE;
	END_FUN2;
}

/*
	test int with a predicate
*/
static Object *tst_int(Object *x, Object *(*pred)(WS_INT))
{
	START_INT_FUN2;
	Object *res = (*pred)(valx) ? TRUE : FALSE;
	END_FUN2;

}

//predicates
static Object *int_is_zeroP(WS_INT val){return val == 0}
static Object *int_is_negP(WS_INT val){return val < 0}
static Object *int_is_posP(WS_INT val){return val > 0}

/**
	test = 0
*/
Object *int_is_zero(Object *x)
{
	return tst_int(x, &int_is_zeroP);
}

/**
	test > 0
*/
Object *int_is_pos(Object *x)
{
	return tst_int(x, &int_is_posP);
}

/**
	test < 0
*/
Object *int_is_neg(Object *x)
{
	return tst_int(x, &int_is_negP);
}

/*************************************************
	Coerce between numerics
*/
// Int -> Byte int8
static Object *int_to_byte(Object *x)
{
	START_INT_FUN2;
	ASSERT(valx >= WS_BYTE_MIN && valx <= WS_BYTE_MAX, ERR_OVERFLOW);
	Object *res = byte_box((WS_SHORT)valx);
	END_FUN2;
}

// Int -> Short int26
static Object *int_to_short(Object *x)
{
	START_INT_FUN2;
	ASSERT(valx >= WS_SHORT_MIN && valx <= WS_SHORT_MAX, ERR_OVERFLOW);
	Object *res = short_box((WS_SHORT)valx);
	END_FUN2;
}

// Int -> Int int32
static Object *int_to_int(Object *x)
{
	return x;
}

// Int -> Long int64
static Object *int_to_long(Object *x)
{
	START_INT_FUN2;
	Object *res = long_box((WS_LONG)valx);
	END_FUN2;
}

// Int -> bigdec
static Object *int_to_bigdec(Object *x)
{
	START_INT_FUN2;
	Object *res = bigdec_box((WSLONG)valx);
	END_FUN2;
}

// Int -> Ratio
static Object *int_to_ratio(Object *x)
{
	return x;
}

// Int -> Float
static Object *int_to_float(Object *x)
{
	START_INT_FUN2;
	Object *res = float_box((WS_FLOAT)valx);
	END_FUN2;
}

// Int -> Double
static Object *int_to_double(Object *x)
{
	START_INT_FUN2;
	Object *res = double_box((WS_DOUBLE)valx);
	END_FUN2;
}

// Int -> bigdeb
static Object *int_to_bigdeb(Object *x)
{
	START_INT_FUN2;
	Object *res = bigdec_box((WS_DOUBLE)valx);
	END_FUN2;
}

// Int -> type
Object *int_to_type(Object *x, TYPE type)
{
	Object *res = NULL;
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

Object *int_add(Object *x, Object *y)
{
	START_INT_FUN2;
	res = int_box(valx + valy);
	END_FUN2;
}

Object *int_addP(Object *x, Object *y)
{
	START_INT_FUN2;
	WS_INT sum = valx + valy;
	if((sum ^ valx) < 0 && (sum ^ valy) < 0)
		res = long_allP(int_to_type(x, LONG), int_to_type(y, LONG));
	else
		res = int_box(sum);
	END_FUN2;
}

Object *int_multiply(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_multiplyP(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_divide(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_quotient(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_remainder(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_equiv(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_equal(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_lt(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_lte(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_gte(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_compare(Object *x, Object *y);
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_negate(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_negateP(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_inc(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_incP(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_dec(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_decP(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

//* bit functions **********
Object *int_not				(Object *x)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_and				(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_or					(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_xor				(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_and_not			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_clear_bit			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_set_bit			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_flip_bit			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_test_bit			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_shift_left			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_shift_leftP			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_shift_right		(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_rot_left			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

Object *int_rot_right			(Object *x, Object *y)
{
	START_INT_FUN2;

	END_FUN2;
}

int int_hash_code(Object *x){
}

int int_hasheq(Object *x){
}
