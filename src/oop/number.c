/****
    number : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

Interface *INTERFACE_NUMBER = NULL;
Class *CLASS_BYTE = NULL;
Class *CLASS_SHORT = NULL;
Class *CLASS_INT = NULL;
Class *CLASS_LONG = NULL;
Class *CLASS_BIGINT = NULL;
Class *CLASS_RATIO = NULL;
Class *CLASS_FLOAT = NULL;
Class *CLASS_DOUBLE = NULL;
Class *CLASS_BIGDEC = NULL;

/*
	Static functions
*/
static  FuncDef	num_func_def[] =
	{
		{"static isNum",		1, &num_is_num},
		{"static coerce",		2, &num_coerce},
		{"static add",			2, &num_add},
		{"static addP",			2, &num_addP},
		{"static multiply",		2, &num_multiply},
		{"static multiplyP",	2, &num_multiplyP},
		{"static divide",		2, &num_divide},
		{"static quotient",		2, &num_quotient},
		{"static remainder",	2, &num_remainder},
		{"static equiv",		2, &num_equiv},
		{"static equal",		2, &num_equal},
		{"static lt",			2, &num_lt},
		{"static lte",			2, &num_lte},
		{"static gte",			2, &num_gte},
		{"static compare",		2, &num_compare},
		{"static and",			2, &num_and},
		{"static or",			2, &num_or},
		{"static xor",			2, &num_xor},
		{"static andNot",		2, &num_and_not},
		{"static clearBit",		2, &num_clear_bit},
		{"static setBit",		2, &num_set_bit},
		{"static flipBit",		2, &num_flip_bit},
		{"static testBit",		2, &num_test_bit},
		METHOD_DESC_END
	};

/**
	Helper functions
*/
static int max_num_type(Object *arg1, Object *arg2)
{
	TYPE type1 = arg1.type;
	TYPE type2 = arg2.type;
	if (type1 > type2)
		return type1 - BYTE;
	else
		return type2 - BYTE;
}

static Object *num_operator2(Object *x, Object *y, int function)
{
	START_FUN2;
	res = (*num_func1[function][x.type - BYTE])(x, y);
	END_FUN2;.
}

static Object *num_operator2_coerce(Object *x, Object *y, int function)
{
	START_FUN2;
	int type = max_type(x, y);
	res = (*num_func1[function][type])(x, y);
	END_FUN2;
}

// Number -> type
Object *num_to_type(Object *x, TYPE type)
{
	TYPE type_obj = x;
	switch(type_obj)
	{
		case NUM_BYTE:
			res = byte_to_type(x, type);
			break;

		case NUM_SHORT:
			res = short_to_type(x, type);
			break;

		case NUM_INT:
			res = num_to_type(x, type);
			break;

		case NUM_LONG:
			res = long_to_type(x, type);
			break;

		case NUM_BIGINT:
			res = bignum_to_type(x, type);
			break;

		case NUM_RATIO
			res = ratio_to_type(x, type);
			break;

		case NUM_FLOAT:
			res = float_to_type(x, type);
			break;

		case NUM_DOUBLE:
			res = double_to_type(x, type);
			break;

		case NUM_BIGDEC:
			res = bigdec_to_type(x, type);
			break;

		default:
			ABORT(ERR_CONVERSION, str_type(), str_type(type));
			break
	}

catch:
	return res;
}

//* test ***************
Object *is_num (Object *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Object *num_is_zero(Object *x);
{
	return num_operator1(x, NUM_IS_ZERO);
}

Object *num_is_neg(Object *x);
{
	return num_operator1(x, NUM_IS_NEG);
}

Object *num_is_pos(Object *x);
{
	return num_operator1(x, NUM_IS_POS);
}

// coerce
Object *num_coerce(Object *x, Object *type);
{

	return num_operator2(x, type, NUM_COERCE);
}

//* operators *************
Object *num_add(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_ADD);
}

Object *num_addP(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_ADDP);
}

Object *num_multiply(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_MULTIPLY);
}

Object *num_multiplyP(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_MULTIPLYP);
}

Object *num_divide(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_DIVIDE);
}

Object *num_quotient(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_QUOTIENT);
}

Object *num_remainder(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_REMAINDER);
}

Object *num_equiv(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_EQUIV);
}

Object *num_equal(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_EQUAL);
}

Object *num_lt(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_LT);
}

Object *num_lte(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_LTE);
}

Object *num_gte(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_GTE);
}

Object *num_compare(Object *x, Object *y);
{
	return num_operator2_coerce(x, y, NUM_COMPARE);
}

Object *num_negate(Object *x);
{
	return num_operator1(x, NUM_NEGATE);
}

Object *num_negateP(Object *x);
{
	return num_operator1(x, NUM_NEGATEP);
}

Object *num_inc(Object *x);
{
	return num_operator1(x, NUM_INC);
}

Object *num_incP(Object *x);
{
	return num_operator1(x, NUM_INCP);
}

Object *num_dec(Object *x);
{
	return num_operator1(x,NUM_DEC);
}

Object *num_decP(Object *x);
{
	return num_operator1(x, NUM_DECP);
}

//* bit functions **********
Object *num_not(Object *x)
{
	return num_operator1(x, NUM_NOT);
}

Object *num_and(Object *x, Object *y)
{
	return num_operator2_coerce(x, y, NUM_AND);
}

Object *num_or(Object *x, Object *y)
{
	return num_operator2_coerce(x, y, NUM_OR);
}

Object *num_xor(Object *x, Object *y)
{
	return num_operator2_coerce(x, y, NUM_XOR);
}

Object *num_and_not(Object *x, Object *y)
{
	return num_operator2_coerce(x, y, NUM_AND_NOT);
}

Object *num_clear_bit(Object *x, Object *pos)
{
	return num_operator2(x, pos, NUM_CLEAR_BIT);
}

Object *num_set_bit(Object *x, Object *pos)
{
	return num_operator2(x, pos, NUM_SET_BIT);
}

Object *num_flip_bit(Object *x, Object *pos)
{
	return num_operator2(x, pos, NUM_FLIP_BIT);
}

Object *num_test_bit(Object *x, Object *pos)
{
	return num_operator2(x, pos, NUM_TEST_BIT);
}

Object *num_shift_left(Object *x, Object *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_LEFT);
}

Object *num_shift_leftP(Object *x, Object *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_LEFTP);
}

Object *num_shift_right		(Object *x, Object *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_RIGHT);
}

Object *num_rot_left			(Object *x, Object *shift)
{
	return num_operator2(x, shift, NUM_ROT_LEFT);
}

Object *num_rot_right			(Object *x, Object *shift)
{
	return num_operator2(x, shift, NUM_ROT_RIGHT);
}

int num_hash_code(Object *x){
	return num_operator(x, NUM_HASHCODE);
}

int num_hasheq(Object *x){
	return num_operator(x, NUM_HASHED);
}
