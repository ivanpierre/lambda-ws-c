/****
    Environment

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "environment.h"
#include "free_internal.h"

/*
    Constructor
*/
Node *environment(Node *previous, Node *map)
{
	Node *res          = NULL;

	if (!node_isa_type(previous, INIL))
	{
		ASSERT_NODE(previous, IENVIRONMENT);
	}
	ASSERT_NODE(map, IMAP);

	res = new_node(IENVIRONMENT);
	ASSERT(res, ERR_CREATE_NEW, str_type(IENVIRONMENT));

	Environment *env = STRUCT(res);
	ASSIGN(env->previous, previous);
	ASSIGN(env->map, map);
	unlink_node(previous);
	unlink_node(map);
	return res;

	//**********
	error_assert:
	unlink_node(res);
	unlink_node(previous);
	unlink_node(map);
	return NULL;
}

/*
    Get environment map
*/
Node *environment_map(Node *node)
{
	ACCESS_NODE(Environment, map, IENVIRONMENT, IMAP);
}

/*
    Get environment previous map
*/
Node *environment_previous(Node *node)
{
	ACCESS_NODE(Environment, previous, IENVIRONMENT, IENVIRONMENT);
}

/*
    Unalloc environment bindings
*/
Node *environment_free(Node *node)
{
	ASSERT(node, ERR_NULL_PTR);
	ASSERT_TYPE(node, IENVIRONMENT);

	Environment *env = STRUCT(node);
	unlink_node(env->map);
	unlink_node(env->previous);

	free(node);

	error_assert:
	return NULL;
}

