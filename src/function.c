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
	if(node->val.function->args)
		node->val.function->args = free_node(node->val.function->args);
	return NULL;
	if(node->val.function->closure)
		node->val.function->closure = free_node(node->val.function->closure);
	return NULL;
	if(node->type & LAMBDA && node->val.function->func.body)
		node->val.function->func.body = free_node(node->val.function->func.body);
	return NULL;
}

/*
	String representation for functions
	returns linked allocated String
*/
Node *string_function(Node *node)
{
	ASSERT(node, "string_function : null environment");
	ASSERT_TYPE(node, FUNCTION, "string_function : Bad type %s", str_type(node->type));
	Node *map = string_node(node->val.function->closure);
	Node *args = string_node(node->val.function->args);
//	Node *body = string_node(node->val.function->func.body);
	Node *res = sprintf_string("<%s macro=%s special=%s args=%s closure=%s>",
								node->type,
								node->val.function->is_macro ? "yes" : "no",
								node->val.function->is_special ? "yes" : "no",
								args->val.string,
								map->val.string);
	unlink_node(map);
	return res;
}

