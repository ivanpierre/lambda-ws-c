/****
    This is base for all named nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015

    Warning this implementation is based on C strings
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "nodes.h"
#include "named.h"

/*
    Named : symbols and kerywords
*/
typedef struct
{
    struct Node     *ns;
    struct Node     *name;
} Named;

/*
    Access named data
*/
static Named *GET_NAMED(Node *node)
{
    return  (Named *)(node->val.compl);
}

/*
    Create a linked string, don't allocate space for the string
*/
static Node *named_base(Node *ns, Node *name, NodeType type)
{
    ASSERT(ns, "namespace is null");
    ASSERT(name, "name is null");
    ASSERT_TYPE(ns, SYMBOL | STRING | NAMESPACE, "namespace bad type");
    ASSERT_TYPE(name, SYMBOL | STRING, "name bad type");

    Node *node = NEW(type);

    if(!node)
        return NULL;

    GET_NAMED(node)->ns = ns;
    GET_NAMED(node)->name = name; // allocate place for the string

    return node; // create node does the link
}

/*
    Create a linked symbol, allocate space for the string
*/
Node *symbol(Node *ns, Node *name)
{
    return named_base(ns, name, SYMBOL); // make_string does the link
}

/*
    Create a linked keyword, allocate space for the string
*/
Node *keyword(Node *ns, Node *name)
{
    return named_base(ns, name, KEYWORD); // make_string does the link
}

/*
    test if node is a symbol
*/
Node *symbol_Q_(Node *node)
{
    return (node && node->type & SYMBOL) ? true : false;
}

/*
    test if node is a keyword
*/
Node *keyword_Q_(Node *node)
{
    return (node && node->type & KEYWORD) ? true : false;
}

/*
    Return name of named
*/
Node *named_name(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "node is neither a symbol nor keyword");
    return link_node(GET_NAMED(node)->name); // alloc node
}

/*
    Return ns of name
*/
Node *named_ns(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "node is neither a symbol nor keyword");
    return link_node(GET_NAMED(node)->ns); // alloc node
}

/*
    Evaluation of symbol
*/
Node *symbol_eval(Node *node, Node *env)
{
    // TODO implement evaluation
    return node;
}

/*
    Unalloc named elements : ns and name
*/
Node *named_free(Node *node)
{
    ASSERT_TYPE(node, NAMED,
                "error unallocatig bad type : %s",
                str_type(node->type));

    unlink_node(named_ns(node));
    unlink_node(named_name(node));
    free(node->val.compl);
    free(node);
    return node;
}
