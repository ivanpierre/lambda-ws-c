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
    Access named data
*/
static Named *GET_NAMED(Node *node)
{
    return  (Named *)(node->val.compl);
}

/*
    Create a linked string, don't allocate space for the string
*/
static Node *named_base(Node *ns, Node *name, enum TYPE type)
{
    ASSERT(ns, "namespace is null");
    ASSERT(name, "name is null");
    ASSERT_TYPE(ns, SYMBOL | STRING | NAMESPACE | NIL, "namespace bad type %s", str_type(ns->type));
    ASSERT_TYPE(name, SYMBOL | STRING, "name bad type %s", str_type(name->type));

    Node *node = NEW(type);

    ASSERT(node, "Cannot create %s", str_type(node->type));

    node->val.compl = malloc(sizeof(Named));

    GET_NAMED(node)->ns = ns;
    switch(name->type)
    {
        case ISYMBOL:
            GET_NAMED(node)->name = link_node(named_name(name)); // allocate place for the string
            break;

        case ISTRING:
            GET_NAMED(node)->name = link_node(name); // allocate place for the string
            break;

        default:
            ABORT("name bad type");
    }

    return node; // create node does the link
}

/*
    Create a linked symbol, allocate space for the string
*/
Node *symbol(Node *ns, Node *name)
{
    return named_base(ns, name, ISYMBOL); // make_string does the link
}

/*
    Create a linked keyword, allocate space for the string
*/
Node *keyword(Node *ns, Node *name)
{
    return named_base(ns, name, IKEYWORD); // make_string does the link
}

/*
    test if node is a symbol
*/
Node *symbol_Q_(Node *node)
{
    return (node && node->type == ISYMBOL) ? true : FALSE;
}

/*
    test if node is a keyword
*/
Node *keyword_Q_(Node *node)
{
    return (node && node->type == IKEYWORD) ? true : FALSE;
}

/*
    Return name of named
*/
Node *named_name(Node *node)
{
    ASSERT_TYPE(node, NAMED, "node is neither a symbol nor keyword");
    return GET_NAMED(node)->name; // alloc node
}

/*
    Return ns of name
*/
Node *named_ns(Node *node)
{
    ASSERT_TYPE(node, NAMED, "node is neither a symbol nor keyword");
    return GET_NAMED(node)->ns; // alloc node
}

/*
    Evaluation of symbol
*/
Node *symbol_eval(Node *node, Node *environment)
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
    return NULL;
}
