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

/*
    Access Environment from Node
*/
#define environment(node) (node ? ((Environment *)(node->val.compl)) : NULL)

/*
    Get environment map
*/
Node *env_map(Node *node)
{
	ASSERT(node, ERR_NULL_PTR);
	ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
	return link_node(environment(node)->map);
}

/*
    Get environment previous map
*/
Node *env_previous(Node *node)
{
	ASSERT(node, ERR_NULL_PTR);
	ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
	return link_node(environment(node)->previous);
}

/*
    Unalloc environment bindings
*/
Node *env_free(Node *node)
{
	ASSERT(node, ERR_NULL_PTR);
	ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
	environment(node)->map = unlink_node(environment(node)->map);
	unlink_node(environment(node)->previous);
	free(node->val.compl);
	free(node);
	return NULL;
}

/*
    New environment
*/
Node *environment(Node *previous, Node *map)
{
Node *node = NEW(IENVIRONMENT); // Create linked node

if(!node)
ABORT(ERR_CREATE_NEW, str_type(IENVIRONMENT));

environment(node)->previous = previous; // don't link
environment(node)->map = map;
return node; // Node is already linked
}

