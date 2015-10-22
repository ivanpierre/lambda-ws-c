/****
    number : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
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
static Node *(**num_funct1[])(Node *arg1) =
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
static Node *(**num_funct2[])(Node *arg1, Node *arg2)[];
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
static int max_type(Node *arg1, Node *arg2)
{
	TYPE type1 = arg1.type;
	TYPE type2 = arg2.type;
	if (type1 > type2)
		return type1 - BYTE;
	else
		return type2 - BYTE;
}

static Node *num_operator1(Node *x, int function)
{
	START_FUN1;
	res = (*num_func1[function][x.type - BYTE])(x);
	END_FUN1;
}

static Node *num_operator2(Node *x, Node *y, int function)
{
	START_FUN2;
	res = (*num_func1[function][x.type - BYTE])(x, y);
	END_FUN2;
}

static Node *num_operator2_coerce(Node *x, Node *y, int function)
{
	START_FUN2;
	int type = max_type(x, y);
	res = (*num_func1[function][type])(x, y);
	END_FUN2;
}

// Number -> type
Node *num_to_type(Node *x, TYPE type)
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
Node *is_num (Node *x)
{
	START_INT_FUN1;

	END_FUN1;
}

Node *num_is_zero(Node *x);
{
	return num_operator1(x, NUM_IS_ZERO);
}

Node *num_is_neg(Node *x);
{
	return num_operator1(x, NUM_IS_NEG);
}

Node *num_is_pos(Node *x);
{
	return num_operator1(x, NUM_IS_POS);
}

// coerce
Node *num_coerce(Node *x, Node *type);
{

	return num_operator2(x, type, NUM_COERCE);
}

//* operators *************
Node *num_add(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_ADD);
}

Node *num_addP(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_ADDP);
}

Node *num_multiply(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_MULTIPLY);
}

Node *num_multiplyP(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_MULTIPLYP);
}

Node *num_divide(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_DIVIDE);
}

Node *num_quotient(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_QUOTIENT);
}

Node *num_remainder(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_REMAINDER);
}

Node *num_equiv(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_EQUIV);
}

Node *num_equal(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_EQUAL);
}

Node *num_lt(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_LT);
}

Node *num_lte(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_LTE);
}

Node *num_gte(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_GTE);
}

Node *num_compare(Node *x, Node *y);
{
	return num_operator2_coerce(x, y, NUM_COMPARE);
}

Node *num_negate(Node *x);
{
	return num_operator1(x, NUM_NEGATE);
}

Node *num_negateP(Node *x);
{
	return num_operator1(x, NUM_NEGATEP);
}

Node *num_inc(Node *x);
{
	return num_operator1(x, NUM_INC);
}

Node *num_incP(Node *x);
{
	return num_operator1(x, NUM_INCP);
}

Node *num_dec(Node *x);
{
	return num_operator1(x,NUM_DEC);
}

Node *num_decP(Node *x);
{
	return num_operator1(x, NUM_DECP);
}

//* bit functions **********
Node *num_not(Node *x)
{
	return num_operator1(x, NUM_NOT);
}

Node *num_and(Node *x, Node *y)
{
	return num_operator2_coerce(x, y, NUM_AND);
}

Node *num_or(Node *x, Node *y)
{
	return num_operator2_coerce(x, y, NUM_OR);
}

Node *num_xor(Node *x, Node *y)
{
	return num_operator2_coerce(x, y, NUM_XOR);
}

Node *num_and_not(Node *x, Node *y)
{
	return num_operator2_coerce(x, y, NUM_AND_NOT);
}

Node *num_clear_bit(Node *x, Node *pos)
{
	return num_operator2(x, pos, NUM_CLEAR_BIT);
}

Node *num_set_bit(Node *x, Node *pos)
{
	return num_operator2(x, pos, NUM_SET_BIT);
}

Node *num_flip_bit(Node *x, Node *pos)
{
	return num_operator2(x, pos, NUM_FLIP_BIT);
}

Node *num_test_bit(Node *x, Node *pos)
{
	return num_operator2(x, pos, NUM_TEST_BIT);
}

Node *num_shift_left(Node *x, Node *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_LEFT);
}

Node *num_shift_leftP(Node *x, Node *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_LEFTP);
}

Node *num_shift_right		(Node *x, Node *shift)
{
	return num_operator2(x, shift, NUM_SHIFT_RIGHT);
}

Node *num_rot_left			(Node *x, Node *shift)
{
	return num_operator2(x, shift, NUM_ROT_LEFT);
}

Node *num_rot_right			(Node *x, Node *shift)
{
	return num_operator2(x, shift, NUM_ROT_RIGHT);
}

int num_hash_code(Node *x){
	return num_operator(x, NUM_HASHCODE);
}

int num_hasheq(Node *x){
	return num_operator(x, NUM_HASHED);
}
