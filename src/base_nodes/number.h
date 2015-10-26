/****
    Number , generic numbers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NUMBER_H
#define NUMBER_H

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

extern Interface *CLASS_NUMBER;
extern Class *CLASS_BYTE;
extern Class *CLASS_SHORT;
extern Class *CLASS_INT;
extern Class *CLASS_LONG;
extern Class *CLASS_BIGINT;
extern Class *CLASS_RATIO;
extern Class *CLASS_FLOAT;
extern Class *CLASS_DOUBLE;
extern Class *CLASS_BIGDEC;

// index of function
enum
{
	NUM_BYTE,
	NUM_SHORT,
	NUM_INT,
	NUM_LONG,
	NUM_BIGINT,
	NUM_RATIO
	NUM_FLOAT,
	NUM_DOUBLE,
	NUM_BIGDEC
};

//* test ***************
Object	*is_num					(Object *node);

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

//* bit functions **********
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
