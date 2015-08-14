/****
    Functions, lambdas, macros and specials

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "nodes.h"
#include "function.h"

/*
    Functions
*/
typedef struct
{
    bool                is_macro;
    bool                is_special;
    Node                *closure; // as a previous Env
    Node                *args;    // seq of symbols to create local Env
                                  // for function call manage variadic arguments
                                  // and to coerce types
    union
    {
        Node            *(*func) (Node *args, Node *values);
        Node            *body;
    } func;
} Function;

/*
    Access Env from Node
*/
static Function *GET_FUNCTION(Node *node)
{
    return (Function *)node ? (node->val.compl) : NULL;
}

Node *function_is_macro(Node *node)
{
    return GET_FUNCTION(node)->is_macro ? true_node : false_node;
}

Node *function_is_special(Node *node)
{
    return GET_FUNCTION(node)->is_special ? true_node : false_node;
}

Node *function_clojure(Node *node)
{
    Node *res = GET_FUNCTION(node)->closure;
    if(!res)
        return nil_node;
    return link_node(res);
}

Node *function_args(Node *node)
{
    Node *res = GET_FUNCTION(node)->args;
    if(!res)
        return nil_node;
    return link_node(res);
}

/*
    Unalloc function
*/
Node *function_free(Node *node)
{
    ASSERT(node, "free_function : null environment");
    ASSERT_TYPE(node, FUNCTION, "free_function : Bad type %s", str_type(node->type));
    unlink_node(GET_FUNCTION(node)->args);
    unlink_node(GET_FUNCTION(node)->closure);
    unlink_node(GET_FUNCTION(node)->func.body);
    return node;
}

