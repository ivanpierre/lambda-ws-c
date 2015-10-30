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
} Integer;

//* Boxing ****************
Integer *int_box				(WS_INT value);
WS_INT  int_unbox				(Integer *x);

//* test ***************
Object  *is_int					(Integer *x);
Object	*int_is_zero			(Integer *x);
Object	*int_is_neg				(Integer *x);
Object	*int_is_pos				(Integer *x);

// coerce
Object 	*int_coerce				(Integer *x, Class *class);

//* operators *************
Object 	*int_add				(Integer *x, Object *y);
Object 	*int_addP				(Integer *x, Object *y);

Object 	*int_multiply			(Integer *x, Object *y);
Object 	*int_multiplyP			(Integer *x, Object *y);

Object 	*int_divide				(Integer *x, Object *y);

Object 	*int_quotient			(Integer *x, Object *y);

Object 	*int_remainder			(Integer *x, Object *y);

Object 	*int_equiv				(Integer *x, Object *y);

Object 	*int_lt					(Integer *x, Object *y);
Object 	*int_lte				(Integer *x, Object *y);
Object 	*int_gte				(Integer *x, Object *y);
Object 	*int_compare			(Integer *x, Object *y);

Object 	*int_negate				(Integer *x);
Object 	*int_negateP			(Integer *x);

Object 	*int_inc				(Integer *x);
Object 	*int_incP				(Integer *x);

Object 	*int_dec				(Integer *x);
Object 	*int_decP				(Integer *x);

//* bit functions **********
Object	*int_not				(Integer *x);
Object	*int_and				(Integer *x, Object *y);
Object	*int_or					(Integer *x, Object *y);
Object	*int_xor				(Integer *x, Object *y);
Object	*int_and_not			(Integer *x, Object *y);

Object	*int_clear_bit			(Integer *x, Object *y);
Object	*int_set_bit			(Integer *x, Object *y);
Object	*int_flip_bit			(Integer *x, Object *y);
Object	*int_test_bit			(Integer *x, Object *y);

Object	*int_shift_left			(Integer *x, Object *y);
Object	*int_shift_leftP		(Integer *x, Object *y);
Object	*int_shift_right		(Integer *x, Object *y);
Object	*int_rot_left			(Integer *x, Object *y);
Object	*int_rot_right			(Integer *x, Object *y);

//* hash ***********************
int 	int_hash_code			(Integer *x);
int 	int_hasheq				(Integer *x);

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
