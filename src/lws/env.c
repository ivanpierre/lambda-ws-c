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
    Environment. There is only uninterned (local) symbol, so we can
    only keep the symbol name
*/
typedef struct Env
{
    struct Node     *previous; // Environment
    struct Node     *map; // map [String Value]
} Env;

/*
    Access Env from Node
*/
static Env *env(Node *node)
{
    return (Env *)(node->val.compl);
}

/*
    Unalloc environment bindings
*/
Node *free_env(Node *node)
{
    ASSERT(node, "free_env : null environment");
    ASSERT_TYPE(node, ENVIRONMENT, "free_env : Bad type %s", str_type(node->type));
    if(env(node)->map)
    {
        env(node)->map = free_coll(env(node)->map);
    }
    return NULL;
}

