/****
	Environment

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

/*
	Unalloc environment bindings
*/
Node *free_env(Node *node)
{
	ASSERT(node, "free_env : null environment");
	ASSERT_TYPE(node, ENVIRONMENT, "free_env : Bad type %s", str_type(node->type));
	if(node->val.env->map)
	{
		node->val.env->map = free_coll(node->val.env->map);
	}
	return NULL;
}

/*
	String representation of environment
	returns linked allocated String
*/
Node *string_env(Node *node)
{
	ASSERT(node, "string_env : null environment");
	ASSERT_TYPE(node, ENVIRONMENT, "string_env : Bad type %s", str_type(node->type));
	if(node->val.env->map)
	{
		Node *map = string_node(node->val.env->map);
		Node *res = sprintf_string("<%s map=%s>",
									str_type(ENVIRONMENT),
									map->val.string);
		unlink_node(map);
		return res;
	}
	return sprintf_string("<%s map=null>", str_type(ENVIRONMENT));
}
