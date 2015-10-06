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
Node    *int_box				(WS_INT value);
WS_INT  int_unbox				(Node *node);

//* test ***************
Node    *is_int					(Node *node);
Node	*int_is_zero			(Node *node);
Node	*int_is_neg				(Node *node);
Node	*int_is_pos				(Node *node);

// coerce
Node 	*int_to_type			(Node *node, TYPE type);

//* operators *************
Node 	*int_add				(Node *x, Node *y);
Node 	*int_addP				(Node *x, Node *y);

Node 	*int_multiply			(Node *x, Node *y);
Node 	*int_multiplyP			(Node *x, Node *y);

Node 	*int_divide				(Node *x, Node *y);

Node 	*int_quotient			(Node *x, Node *y);

Node 	*int_remainder			(Node *x, Node *y);

Node 	*int_equiv				(Node *x, Node *y);

Node 	*int_lt					(Node *x, Node *y);
Node 	*int_lte				(Node *x, Node *y);
Node 	*int_gte				(Node *x, Node *y);

Node 	*int_negate				(Node *x);
Node 	*int_negateP			(Node *x);

Node 	*int_inc				(Node *x);
Node 	*int_incP				(Node *x);

Node 	*int_dec				(Node *x);
Node 	*int_decP				(Node *x);

//* MACROS *********************

//* INT_UNBOX *********************
#define INT_UNBOX(val, node) \
	ASSERT(node, ERR_VAR_UNBOUND); \
	ASSERT_TYPE(node, INTEGER); \
	WS_INT val = ((Int *)STRUCT(node))->value

//* START_INT_FUN1 ******
#define START_INT_FUN1 \
	Node *res = NULL; \
	PUSH_ARGS(1, x); \
	INT_INBOX(valx, x)

//* START_INT_FUN2 ******
#define START_INT_FUN2 \
	Node *res = NULL; \
	PUSH_ARGS(2, x, y); \
	INT_INBOX(valx, x); \
	INT_INBOX(valy, y)

#endif
