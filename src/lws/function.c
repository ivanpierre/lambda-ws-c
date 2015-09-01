/****
    Functions, lambdas, macros and specials

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "function.h"

Node *function_is_macro(Node *node)
{
	ACCESS_BOOL(Function, is_macro, ICALLABLE);
}

Node *function_is_special(Node *node)
{
	ACCESS_BOOL(Function, is_special, ICALLABLE);
}

Node *function_closure(Node *node)
{
	ACCESS_NODE(Function, closure, ICALLABLE, IENVIRONMENT);
}

Node *function_args(Node *node)
{
	ACCESS_NODE(Function, args, ICALLABLE, IARRAY);
}

Node *function_body(Node *node)
{
	ACCESS_NODE(Function, func.body, ILAMBDA, ILIST);
}

void *function_func(Node *node)
{
	ACCESS_PTR(Function, func.func, IFUNCTION);
}

/*
    Unalloc function
*/
Node *function_free(Node **node)
{
	ASSERT_TYPE(*node, ICALLABLE);
	Function *func = STRUCT(*node);
	unlink_node(&func->is_macro);
	unlink_node(&func->is_special);
	unlink_node(&func->args);
	unlink_node(&func->closure);
	if((*node)->type->int_type == ILAMBDA)
		unlink_node(&func->func.body);
	free(*node);
	*node = NULL;

	error_assert:
	return *node;
}

