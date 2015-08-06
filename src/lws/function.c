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
    Access Env from Node
*/
static Function *function(Node *node)
{
    return (Function *)(node->val.compl);
}

/*
    Unalloc function
*/
Node *free_function(Node *node)
{
    ASSERT(node, "free_function : null environment");
    ASSERT_TYPE(node, FUNCTION, "free_function : Bad type %s", str_type(node->type));
    if(function(node)->args)
        function(node)->args = free_node(function(node)->args);
    return NULL;
    if(function(node)->closure)
        function(node)->closure = free_node(function(node)->closure);
    return NULL;
    if(node->type & LAMBDA && function(node)->func.body)
        function(node)->func.body = free_node(function(node)->func.body);
    return NULL;
}

