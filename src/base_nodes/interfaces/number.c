/****
    number : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "object.h"
#include "number.h"

static  FuncDef	num_func_def[] =
			{
				{"isZero",		1, &num_is_zero},
				("isNeg",		1, &num_is_neg),
				{"isPos",		1, &num_is_pos},
				{"coerce",		2, &num_coerce},
				{"add",			2, &num_add},
				{"add'",		2, &num_addP},
				{"multiply",	2, &num_multiply},
				{"multiply'",	2, &num_multiplyP},
				{"divide",		2, &num_divide},
				{"quotient",	2, &num_quotient},
				{"remainder",	2, &num_remainder},
				{"equiv",		2, &num_equiv},
				{"equal",		2, &num_equal},
				{"lt",			2, &num_lt},
				{"lte",			2, &num_lte},
				{"gte",			2, &num_gte},
				{"compare",		2, &num_compare},
				{"negate",		1, &num_negate},
				{"negateP",		1, &num_negateP},
				{"inc",			1, &num_inc},
				{"incP",		1, &num_incP},
				{"dec",			1, &num_dec},
				{"decP",		1, &num_decP},
				{"not",			1, &num_not},
				{"and",			2, &num_and},
				{"or",			2, &num_or},
				{"xor",			2, &num_xor},
				{"andNot",		2, &num_and_not},
				{"clearBit",	2, &num_clear_bit},
				{"setBit",		2, &num_set_bit},
				{"flipBit",		2, &num_flip_bit},
				{"testBit",		2, &num_test_bit},
			};

//* helper functions *****
// Table of all numeric funtion with 1 argument
static Object *(**num_funct1[])(Object *arg1) =
			{
				&byte_funct1;
				&num_funct1;
				&long_funct1;
				&bignum_funct1;
				&ratio_funct1;
				&float_funct1;
				&double_funct1;
				&bigdec_funct1;
			};

// Table of all numeric funtion pointer with 2 argument
static Object *(**num_funct2[])(Object *arg1, Object *arg2)[];
			{
				&byte_funct2;
				&num_funct2;
				&long_funct2;
				&bignum_funct2;
				&ratio_funct2;
				&float_funct2;
				&double_funct2;
				&bigdec_funct2;
			};

/**
	Heloper functions
*/
static int max_type(Object *arg1, Object *arg2)
{
	TYPE type1 = arg1.type;
	TYPE type2 = arg2.type;
	if (type1 > type2)
		return type1 - BYTE;
	else
		return type2 - BYTE;
}

static Object *num_operator1(Object *x, int function)
{
	START_FUN1;
	res = (*num_func1[function][x.type - BYTE])(x);
	END_FUN1;
}

static Object *num_operator2(Object *x, Object *y, int function)
{
	START_FUN2;
	res = (*num_func1[function][x.type - BYTE])(x, y);
	END_FUN2;
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
	TYPE type_obj = x->type;
	switch(type_obj)
	{
		case WS_BYTE:
			res = byte_to_type(x, type);
			break;

		case WS_SHORT:
			res = short_to_type(x, type);
			break;

		case WS_INT:
			res = num_to_type(x, type);
			break;

		case WS_LONG:
			res = long_to_type(x, type);
			break;

		case WS_BIGINT:
			res = bignum_to_type(x, type);
			break;

		case WS_RATIO
			res = ratio_to_type(x, type);
			break;

		case WS_FLOAT:
			res = float_to_type(x, type);
			break;

		case WS_DOUBLE:
			res = double_to_type(x, type);
			break;

		case WS_BIGDEC:
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
