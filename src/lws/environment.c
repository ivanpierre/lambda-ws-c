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
	Node *tmp_previous = NIL;
	Node *tmp_map      = NULL;
	Node *res          = NULL;

	if (!node_isa_type(previous, INIL))
	{
		ASSERT_NODE(previous, tmp_previous, IENVIRONMENT);
	}
	ASSERT_NODE(map, tmp_map, IMAP);

	res = new_node(IENVIRONMENT);
	ASSERT(res, ERR_CREATE_NEW, str_type(IENVIRONMENT));

	Environment *env = STRUCT(res);
	env->previous = link_node(&env->previous, tmp_previous);
	env->map = link_node(&env->map, tmp_map);
	unlink_node(&tmp_previous);
	unlink_node(&tmp_map);
	return res;

	//**********
	error_assert:
	unlink_node(&res);
	unlink_node(&tmp_previous);
	unlink_node(&tmp_map);
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
Node *environment_free(Node **node)
{
	ASSERT(*node, ERR_NULL_PTR);
	ASSERT_TYPE(*node, IENVIRONMENT);

	Environment *env = STRUCT(*node);
	unlink_node(&env->map);
	unlink_node(&env->previous);

	free(*node);
	*node = NULL;
	return NULL;

	error_assert:
	return NULL;
}

