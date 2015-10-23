/****
    Number : generic numbers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBER_H
#define NUMBER_H

#include "num_int.h"

// Integers
#define WS_BYTE_MIN		INT8_MIN
#define WS_BYTE_MAX		INT8_MAX

#define WS_SHORT_MIN	SHORT16_MIN
#define WS_SHORT_MAX	SHORT16_MAX

#define WS_INT_MIN		INT32_MIN
#define WS_BYTE_MAX		INT32_MAX

#define WS_LONG_MIN		INT64_MIN
#define WS_LONG_MAX		INT64_MAX

// Decimal
#define WS_FLOAT_MIN	FLT_MIN
#define WS_FLOAT_MAX	FLT_MAX

#define WS_DOUBLE_MIN	DBL_MIN
#define WS_DOUBLE_MAX	DBL_MAX

// index of function
enum
{
	NUM_IS_ZERO,
	NUM_IS_NEG,
	NUM_IS_POS,
	NUM_COERCE,
	NUM_ADD,
	NUM_ADDP,
	NUM_MULTIPLY,
	NUM_MULTIPLYP,
	NUM_DIVIDE,
	NUM_QUOTIENT,
	NUM_REMAIDER,
	NUM_EQUIV,
	NUM_EQUAL,
	NUM_LT,
	NUM_LTE,
	NUM_GTE,
	NUM_NEGATE,
	NUM_NEGATEP,
	NUM_INC,
	NUM_INCP,
	NUM_DEC,
	NUM_DECP,
	NUM_NOT
	NUM_AND,
	NUM_OR,
	NUM_XOR,
	NUM_AND_NOT,
	NUM_CLEAR_BIT,
	NUM_SET_BIT,
	NUM_FLIP_BIT,
	NUM_TEST_BIT,
	NUM_HASH_CODE,
	NUM_HASHEQ
};

//* test ***************
Object    *is_num					(Object *node);
Object	*num_is_zero			(Object *node);
Object	*num_is_neg				(Object *node);
Object	*num_is_pos				(Object *node);

// coerce
Object 	*num_coerce				(Object *node, TYPE type);

//* operators *************
Object 	*num_add				(Object *x, Object *y);
Object 	*num_addP				(Object *x, Object *y);

Object 	*num_multiply			(Object *x, Object *y);
Object 	*num_multiplyP			(Object *x, Object *y);

Object 	*num_divide				(Object *x, Object *y);

Object 	*num_quotient			(Object *x, Object *y);

Object 	*num_remainder			(Object *x, Object *y);

Object 	*num_equiv				(Object *x, Object *y);

Object 	*num_lt					(Object *x, Object *y);
Object 	*num_lte				(Object *x, Object *y);
Object 	*num_gte				(Object *x, Object *y);
Object 	*num_compare			(Object *x, Object *y);

Object 	*num_negate				(Object *x);
Object 	*num_negateP			(Object *x);

Object 	*num_inc				(Object *x);
Object 	*num_incP				(Object *x);

Object 	*num_dec				(Object *x);
Object 	*num_decP				(Object *x);

//* bit functions **********
Object	*num_not				(Object *x);
Object	*num_and				(Object *x, Object *y);
Object	*num_or					(Object *x, Object *y);
Object	*num_xor				(Object *x, Object *y);
Object	*num_and_not			(Object *x, Object *y);

Object	*num_clear_bit			(Object *x, Object *y);
Object	*num_set_bit			(Object *x, Object *y);
Object	*num_flip_bit			(Object *x, Object *y);
Object	*num_test_bit			(Object *x, Object *y);

Object	*num_shift_left			(Object *x, Object *y);
Object	*num_shift_leftP		(Object *x, Object *y);
Object	*num_shift_right		(Object *x, Object *y);
Object	*num_rot_left			(Object *x, Object *y);
Object	*num_rot_right			(Object *x, Object *y);

//* hash ***********************
int 	num_hash_code			(Object *x);
int 	num_hasheq				(Object *x);

//* MACROS *******
//* START_FUN1 ******
#define START_FUN1 \
	Object *res = NULL; \
	PUSH_ARGS(1, x)

//* START_INT_FUN2 ******
#define START_FUN2 \
	Object *res = NULL; \
	PUSH_ARGS(2, x, y);

//******
#define END_FUN1 \
	CATCH_ERROR; \
	POP_ARGS(1, x); \
	return res; \
	\
	catch: \
	POP_ARGS(1, x); \
	return NULL

//*******
#define END_FUN2 \
	CATCH_ERROR; \
	POP_ARGS(2, x, y); \
	return res; \
    \
	catch: \
	POP_ARGS(2, x, y); \
	return NULL

#endif
