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
	Node *tmp_node = NULL;
	Node *res = NULL;
	ASSERT_NODE(node, tmp_node, ICALLABLE);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	res = func->is_macro ? TRUE : NIL;

	unlink_node(&tmp_node);
	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

Node *function_is_special(Node *node)
{
	Node *tmp_node = NULL;
	Node *res = NULL;
	ASSERT_NODE(node, tmp_node, ICALLABLE);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	res = func->is_special ? TRUE : NIL;

	unlink_node(&tmp_node);
	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

Node *function_closure(Node *node)
{
	Node *tmp_node = NULL;
	Node *res = NULL;

	ASSERT_NODE(node, tmp_node, ICALLABLE);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	link_node(&res, func->closure);
	unlink_node(&tmp_node);

	if (!res)
		res = NIL;
	if (res != NIL)
		ASSERT_TYPE(res, IENVIRONMENT);

	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

Node *function_args(Node *node)
{
	Node *tmp_node = NULL;
	Node *res = NULL;

	ASSERT_NODE(node, tmp_node, ICALLABLE);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	link_node(&res, func->args);
	unlink_node(&tmp_node);

	if (!res)
		res = NIL;
	if (res != NIL)
		ASSERT_TYPE(res, IARRAY);

	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

Node *function_body(Node *node)
{
	Node *tmp_node = NULL;
	Node *res = NULL;

	ASSERT_NODE(node, tmp_node, ILAMBDA);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	link_node(&res, func->args);
	unlink_node(&tmp_node);

	if (!res)
		res = NIL;
	if (res != NIL)
	ASSERT_TYPE(res, ILIST);

	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

void *function_func(Node *node)
{
	Node *tmp_node = NULL;
	Node *res = NULL;

	ASSERT_NODE(node, tmp_node, ILAMBDA);
	unlink_node(&node);

	Function *func = STRUCT(tmp_node);
	link_node(&res, func->args);
	unlink_node(&tmp_node);

	if (!res)
		res = NIL;
	if (res != NIL)
	ASSERT_TYPE(res, ILIST);

	return res;

	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	unlink_node(&res);
	return NULL;
}

/*
    Unalloc function
*/
Node *function_free(Node **node)
{
	Function *func = STRUCT(*node);
	ASSERT_TYPE(*node, ICALLABLE);
	unlink_node(&func->is_macro);
	unlink_node(&func->is_special);
	unlink_node(&func->args);
	unlink_node(&func->closure);
	unlink_node(&func->func.body);
	free(*node);
	*node = NULL;

	error_assert:
	return *node;
}

