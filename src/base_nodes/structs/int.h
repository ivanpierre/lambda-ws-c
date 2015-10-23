/****
    Int : manage 32 bits Integers

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef INT_H
#define INT_H

/*
	Int structure
*/
typedef struct
{
	WS_INT 	value;
} Int;

//* Boxing ****************
Object    *int_box				(WS_INT value);
WS_INT  int_unbox				(Object *node);

//* test ***************
Object    *is_int					(Object *node);
Object	*int_is_zero			(Object *node);
Object	*int_is_neg				(Object *node);
Object	*int_is_pos				(Object *node);

// coerce
Object 	*int_coerce				(Object *node, TYPE type);

//* operators *************
Object 	*int_add				(Object *x, Object *y);
Object 	*int_addP				(Object *x, Object *y);

Object 	*int_multiply			(Object *x, Object *y);
Object 	*int_multiplyP			(Object *x, Object *y);

Object 	*int_divide				(Object *x, Object *y);

Object 	*int_quotient			(Object *x, Object *y);

Object 	*int_remainder			(Object *x, Object *y);

Object 	*int_equiv				(Object *x, Object *y);

Object 	*int_lt					(Object *x, Object *y);
Object 	*int_lte				(Object *x, Object *y);
Object 	*int_gte				(Object *x, Object *y);
Object 	*int_compare			(Object *x, Object *y);

Object 	*int_negate				(Object *x);
Object 	*int_negateP			(Object *x);

Object 	*int_inc				(Object *x);
Object 	*int_incP				(Object *x);

Object 	*int_dec				(Object *x);
Object 	*int_decP				(Object *x);

//* bit functions **********
Object	*int_not				(Object *x);
Object	*int_and				(Object *x, Object *y);
Object	*int_or					(Object *x, Object *y);
Object	*int_xor				(Object *x, Object *y);
Object	*int_and_not			(Object *x, Object *y);

Object	*int_clear_bit			(Object *x, Object *y);
Object	*int_set_bit			(Object *x, Object *y);
Object	*int_flip_bit			(Object *x, Object *y);
Object	*int_test_bit			(Object *x, Object *y);

Object	*int_shift_left			(Object *x, Object *y);
Object	*int_shift_leftP		(Object *x, Object *y);
Object	*int_shift_right		(Object *x, Object *y);
Object	*int_rot_left			(Object *x, Object *y);
Object	*int_rot_right			(Object *x, Object *y);

//* hash ***********************
int 	int_hash_code			(Object *x);
int 	int_hasheq				(Object *x);

//* MACROS *********************

//* INT_UNBOX *********************
#define INT_UNBOX(val, node) \
	ASSERT(node, ERR_VAR_UNBOUND); \
	ASSERT_TYPE(node, INTEGER); \
	WS_INT val = ((Int *)STRUCT(node))->value

//* START_INT_FUN1 ******
#define START_INT_FUN1 \
	Object *res = NULL; \
	PUSH_ARGS(1, x); \
	INT_UNBOX(valx, x)

//* START_INT_FUN2 ******
#define START_INT_FUN2 \
	Object *res = NULL; \
	PUSH_ARGS(2, x, y); \
	INT_UNBOX(valx, x); \
	INT_UNBOX(valy, y)

#endif
