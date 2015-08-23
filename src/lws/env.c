/****
    Environment

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "env.h"

/*
    Access Env from Node
*/
#define ENV(node) (node ? ((Env *)(node->val.compl)) : NULL)

/*
    Get environment map
*/
Node *env_map(Node *node)
{
    ASSERT(node, ERR_NULL_PTR);
    ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
    return link_node(ENV(node)->map);
}

/*
    Get environment previous map
*/
Node *env_previous(Node *node)
{
    ASSERT(node, ERR_NULL_PTR);
    ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
    return link_node(ENV(node)->previous);
}

/*
    Unalloc environment bindings
*/
Node *env_free(Node *node)
{
    ASSERT(node, ERR_NULL_PTR);
    ASSERT_TYPE(node, BENVIRONMENT, str_type(node->type));
    ENV(node)->map = unlink_node(ENV(node)->map);
    unlink_node(ENV(node)->previous);
    free(node->val.compl);
    free(node);
    return NULL;
}

/*
    New environment
*/
Node *env(Node *previous, Node *map)
{
	Node *node = NEW(IENVIRONMENT); // Create linked node

	if(!node)
		ABORT(ERR_CREATE_NEW, str_type(IENVIRONMENT));

	ENV(node)->previous = previous; // don't link
	ENV(node)->map = map;
	return node; // Node is already linked
}

