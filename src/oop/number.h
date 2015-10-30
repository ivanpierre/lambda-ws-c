/****
    Number , generic numbers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBER_H
#define NUMBER_H

#define Number Object

// Integers
#define WS_BYTE_MIN		INT8_MIN
#define WS_BYTE_MAX		INT8_MAX

#define WS_SHORT_MIN	SHORT16_MIN
#define WS_SHORT_MAX	SHORT16_MAX

#define WS_INT_MIN		INT32_MIN
#define WS_INT_MAX		INT32_MAX

#define WS_LONG_MIN		INT64_MIN
#define WS_LONG_MAX		INT64_MAX

// Decimal
#define WS_FLOAT_MIN	FLT_MIN
#define WS_FLOAT_MAX	FLT_MAX

#define WS_DOUBLE_MIN	DBL_MIN
#define WS_DOUBLE_MAX	DBL_MAX

extern Interface	*NUMBER;
extern Class		*BYTE;
extern Class		*SHORT;
extern Class		*INTEGER;
extern Class		*LONG;
extern Class		*BIGINT;
extern Class		*RATIO;
extern Class		*FLOAT;
extern Class		*DOUBLE;
extern Class		*BIGDEC;

// index of function
enum
{
	NUM_BYTE,
	NUM_SHORT,
	NUM_INT,
	NUM_LONG,
	NUM_BIGINT,
	NUM_RATIO,
	NUM_FLOAT,
	NUM_DOUBLE,
	NUM_BIGDEC
};

//* test ***************
Object	*is_num					(Number *node);

// coerce
Object 	*num_coerce				(Number *node, Class *class);

//* operators *************
Object 	*num_add				(Number *x, Number *y);
Object 	*num_addP				(Number *x, Number *y);

Object 	*num_multiply			(Number *x, Number *y);
Object 	*num_multiplyP			(Number *x, Number *y);

Object 	*num_divide				(Number *x, Number *y);

Object 	*num_quotient			(Number *x, Number *y);

Object 	*num_remainder			(Number *x, Number *y);

Object 	*num_equiv				(Number *x, Number *y);

Object 	*num_lt					(Number *x, Number *y);
Object 	*num_lte				(Number *x, Number *y);
Object 	*num_gte				(Number *x, Number *y);
Object 	*num_compare			(Number *x, Number *y);

//* bit functions **********
Object	*num_and				(Number *x, Number *y);
Object	*num_or					(Number *x, Number *y);
Object	*num_xor				(Number *x, Number *y);
Object	*num_and_not			(Number *x, Number *y);

Object	*num_clear_bit			(Number *x, Number *y);
Object	*num_set_bit			(Number *x, Number *y);
Object	*num_flip_bit			(Number *x, Number *y);
Object	*num_test_bit			(Number *x, Number *y);

Object	*num_shift_left			(Number *x, Number *y);
Object	*num_shift_leftP		(Number *x, Number *y);
Object	*num_shift_right		(Number *x, Number *y);
Object	*num_rot_left			(Number *x, Number *y);
Object	*num_rot_right			(Number *x, Number *y);

//* hash ***********************
int 	num_hash_code			(Number *x);
int 	num_hasheq				(Number *x);

//* MACROS *******
//* START_FUN1 ******
#define START_FUN1 \
	Number *res = NULL; \
	PUSH_ARGS(1, x)

//* START_INT_FUN2 ******
#define START_FUN2 \
	Number *res = NULL; \
	PUSH_ARGS(2, x, y);

//******
#define END_FUN1 \
	CATCH_ERROR; \
	POP_ARGS(1, x); \
	return res; \
	\
	catch, \
	POP_ARGS(1, x); \
	return NULL

//*******
#define END_FUN2 \
	CATCH_ERROR; \
	POP_ARGS(2, x, y); \
	return res; \
    \
	catch, \
	POP_ARGS(2, x, y); \
	return NULL

#endif
