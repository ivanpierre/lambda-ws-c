/****
    Environment

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "env.h"

/*
    Environment. There is only uninterned (local) symbol, so we can
    only keep the symbol name
*/
typedef struct
{
    struct Node     *previous; // Environment
    struct Node     *map; // map [String Value]
} Env;

/*
    Access Env from Node
*/
#define ENV(node) (node ? ((Env *)(node->val.compl)) : NULL)

/*
    Get environment map
*/
Node *env_map(Node *node)
{
    ASSERT(node, "null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "Bad type %s", str_type(node->type));
    return link_node(ENV(node)->map);
}

/*
    Get environment previous map
*/
Node *env_previous(Node *node)
{
    ASSERT(node, "null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "Bad type %s", str_type(node->type));
    return link_node(ENV(node)->previous);
}

/*
    Unalloc environment bindings
*/
Node *env_free(Node *node)
{
    ASSERT(node, "null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "Bad type %s", str_type(node->type));
    ENV(node)->map = unlink_node(ENV(node)->map);
    unlink_node(ENV(node)->previous);
    return node;
}

/*
    New environment
*/
Node *env(Node *previous, Node *map)
{
	Node *node = NEW(ENVIRONMENT); // Create linked node

	if(!node)
		ABORT("cannor create new environment");

	ENV(node)->previous = previous; // don't link
	ENV(node)->map = map;
	return node; // Node is already linked
}

