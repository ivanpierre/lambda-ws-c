/****
    Number : generic numbers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBER_H
#define NUMBER_H

#include "int.h"

// Integers
typedef int_8_t			WS_BYTE;
#define WS_BYTE_MIN		INT8_MIN
#define WS_BYTE_MAX		INT8_MAX

typedef int_16_t		WS_SHORT;
#define WS_SHORT_MIN	SHORT16_MIN
#define WS_SHORT_MAX	SHORT16_MAX

typedef int_32_t		WS_INT;
#define WS_INT_MIN		INT32_MIN
#define WS_BYTE_MAX		INT32_MAX

typedef int_64_t		WS_LONG;
#define WS_LONG_MIN		INT64_MIN
#define WS_LONG_MAX		INT64_MAX

// Decimal
typedef float			WS_FLOAT;
#define WS_FLOAT_MIN	FLT_MIN
#define WS_FLOAT_MAX	FLT_MAX

typedef double			WS_DOUBLE;
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
Node    *is_num					(Node *node);
Node	*num_is_zero			(Node *node);
Node	*num_is_neg				(Node *node);
Node	*num_is_pos				(Node *node);

// coerce
Node 	*num_coerce				(Node *node, TYPE type);

//* operators *************
Node 	*num_add				(Node *x, Node *y);
Node 	*num_addP				(Node *x, Node *y);

Node 	*num_multiply			(Node *x, Node *y);
Node 	*num_multiplyP			(Node *x, Node *y);

Node 	*num_divide				(Node *x, Node *y);

Node 	*num_quotient			(Node *x, Node *y);

Node 	*num_remainder			(Node *x, Node *y);

Node 	*num_equiv				(Node *x, Node *y);

Node 	*num_lt					(Node *x, Node *y);
Node 	*num_lte				(Node *x, Node *y);
Node 	*num_gte				(Node *x, Node *y);
Node 	*num_compare			(Node *x, Node *y);

Node 	*num_negate				(Node *x);
Node 	*num_negateP			(Node *x);

Node 	*num_inc				(Node *x);
Node 	*num_incP				(Node *x);

Node 	*num_dec				(Node *x);
Node 	*num_decP				(Node *x);

//* bit functions **********
Node	*num_not				(Node *x);
Node	*num_and				(Node *x, Node *y);
Node	*num_or					(Node *x, Node *y);
Node	*num_xor				(Node *x, Node *y);
Node	*num_and_not			(Node *x, Node *y);

Node	*num_clear_bit			(Node *x, Node *y);
Node	*num_set_bit			(Node *x, Node *y);
Node	*num_flip_bit			(Node *x, Node *y);
Node	*num_test_bit			(Node *x, Node *y);

Node	*num_shift_left			(Node *x, Node *y);
Node	*num_shift_leftP		(Node *x, Node *y);
Node	*num_shift_right		(Node *x, Node *y);
Node	*num_rot_left			(Node *x, Node *y);
Node	*num_rot_right			(Node *x, Node *y);

//* hash ***********************
int 	num_hash_code			(Node *x);
int 	num_hasheq				(Node *x);

//* MACROS *******
//* START_FUN1 ******
#define START_FUN1 \
	Node *res = NULL; \
	PUSH_ARGS(1, x)

//* START_INT_FUN2 ******
#define START_FUN2 \
	Node *res = NULL; \
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
