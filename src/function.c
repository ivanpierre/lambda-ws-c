/****
	Functions, lambdas, macros and specials

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "nodes.h"

/*
	Unalloc function
*/
Node *free_function(Node *node)
{
	ASSERT(node, "free_function : null environment");
	ASSERT_TYPE(node, FUNCTION, "free_function : Bad type %s", str_type(node->type));
	if(node->val.function->closure)
		node->val.function->closure = free_node(node->val.function->closure);
	return NULL;
}

/*
	String representation function
	returns linked allocated String
*/
Node *string_function(Node *node)
{
	ASSERT(node, "string_env : null environment");
	ASSERT_TYPE(node, FUNCTION, "string_env : Bad type %s", str_type(node->type));
	if(node->val.function->closure)
	{
		Node *map = string_node(node->val.function->closure);
		Node *res = sprintf_string("<%s macro=%s special=%s closure=%s>",
									str_type(FUNCTION),
									node->val.function->is_macro ? "yes" : "no",
									node->val.function->is_special ? "yes" : "no",
									map->val.string);
		unlink_node(map);
		return res;
	}
	return sprintf_string("<%s macro=%s special=%s closure=null>",
						   str_type(FUNCTION),
						   node->val.function->is_macro ? "yes" : "no",
						   node->val.function->is_special ? "yes" : "no");
}

/*
	Unalloc lambda
*/
Node *free_lambda(Node *node)
{
	ASSERT(node, "free_lambda : null environment");
	ASSERT_TYPE(node, LAMBDA, "free_lambda : Bad type %s", str_type(node->type));
	if(node->val.lambda->closure)
		node->val.lambda->closure = free_node(node->val.lambda->closure);
	return NULL;
}

/*
	String representation lambda
	returns linked allocated String
*/
Node *string_lambda(Node *node)
{
	ASSERT(node, "string_lambda : null environment");
	ASSERT_TYPE(node, LAMBDA, "string_env : Bad type %s", str_type(node->type));
	if(node->val.function->closure)
	{
		Node *map = string_node(node->val.function->closure);
		Node *res = sprintf_string("<%s macro=%s special=%s closure=%s>",
									str_type(LAMBDA),
									node->val.lambda->is_macro ? "yes" : "no",
									node->val.lambda->is_special ? "yes" : "no",
									map->val.string);
		unlink_node(map);
		return res;
	}
	return sprintf_string("<%s macro=%s special=%s closure=null>",
						   str_type(LAMBDA),
						   node->val.lambda->is_macro ? "yes" : "no",
						   node->val.lambda->is_special ? "yes" : "no");
}
