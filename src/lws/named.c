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
    Create a named object
*/
static Node *named_base(Node *ns, Node *name, TYPE type)
{
    ASSERT(ns, ERR_ARG, "namespace");
    ASSERT(name, ERR_ARG, "name");
    if(ns != NIL)
    {
	    ASSERT_TYPE(ns, INAMESPACE);
    }
	ASSERT_TYPE(name, ISTRING);

    Node *node = new_node(type);

    ASSERT(node, ERR_CREATE_NEW, str_type(type));

	Named *named = STRUCT(node);
    named->ns = ns;
	unlink_node(&ns);
    switch(name->type->int_type)
    {
        case ISYMBOL:
            link_node(&named->name, named_name(name)); // allocate place for the string
            break;

        case ISTRING:
            link_node(&named->name,name); // allocate place for the string
            break;

        default:
            ABORT("name bad type");
    }
	unlink_node(&name);
    return node; // create node does the link

	error_assert:
	unlink_node(&ns);
	unlink_node(&name);
	unlink_node(&node);
	return NULL;
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
    Node *res = (node && node->type->int_type == ISYMBOL) ? TRUE : FALSE;
	unlink_node(&node);
	return res;
}

/*
    test if node is a keyword
*/
Node *keyword_Q_(Node *node)
{
	Node *res = (node && node->type->int_type == IKEYWORD) ? TRUE : FALSE;
	unlink_node(&node);
	return res;
}

/*
    Return name of named
*/
Node *named_name(Node *node)
{
    ACCESS_NODE(Named, name, INAMED, ISTRING);
}

/*
    Return ns of name
*/
Node *named_ns(Node *node)
{
	ACCESS_NODE(Named, ns, INAMED, INAMESPACE);
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
Node *named_free(Node **node)
{
	Named *named = STRUCT(*node);
    unlink_node(&named->ns);
    unlink_node(&named->name);
    free(*node);
	*node = NULL;
    return *node;
}
