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
#define NAMED(nopde) ((Named *)node->val.compl)

/*
    Create a linked string, don't allocate space for the string
*/
static Node *named_base(Node *ns, Node *name, NodeType type)
{
    ASSERT(ns, "namespace is null");
    ASSERT(name, "name is null");

    Node *node = new_node(type);

    if(!node)
        return NULL;

    NAMED(node)->ns = ns;
    NAMED(node)->name = name; // allocate place for the string

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
bool symbol_QM_(Node *node)
{
    return node && node->type & SYMBOL;
}

/*
    test if node is a keyword
*/
bool keyword_QM_(Node *node)
{
    return node && node->type & KEYWORD;
}

/*
    Return name of named
*/
Node *named_get_name(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "node is neither a symbol nor keyword");
    return link_node(NAMED(node)->name); // alloc node
}

/*
    Return ns of name
*/
Node *named_get_ns(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "node is neither a symbol nor keyword");
    return link_node(NAMED(node)->ns); // alloc node
}

/*
    Unalloc named elements : ns and name
*/
Node *named_free(Node *node)
{
    ASSERT_TYPE(node, NAMED,
                "error unallocatig bad type : %s",
                str_type(node->type));

    free_node(named_get_ns(node));
    free_node(named_get_name(node));
    return node;
}
