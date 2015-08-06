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

/*
    Access String from Node
*/
static Symbol *named(Node *node)
{
    return (Symbol *)node->val.compl;
}

/*
    Create a linked string, don't allocate space for the string
*/
static Node *new_symbol_base(Node *ns, String value, NodeType type)
{
    ASSERT(value, "make_string_value : value is null");
    Node *node = new_node(type);
    if(!node)
        return NULL;
    named(node)->ns = ns;
    named(node)->ns = ns;
    return node; // create node does the link
}

/*
    Create a linked symbol, allocate space for the string
*/
Node *new_symbol(Node *ns, char *value)
{
    ASSERT(value, "make_symbol : value is null");
    return new_symbol_base(ns, strdup(value), SYMBOL); // make_string does the link
}

/*
    Create a linked keyword, allocate space for the string
*/
Node *new_keyword(Node * ns, String value)
{
    ASSERT(value, "make_keyword : value is null");
    return new_symbol_base(ns, strdup(value), KEYWORD); // make_string does the link
}

/*
    test if node is a symbol
*/
bool symbolp(Node *node)
{
    return node && node->type & SYMBOL;
}

/*
    test if node is a keyword
*/
bool keywordp(Node *node)
{
    return node && node->type & KEYWORD;
}

/*
    Return name of symbol...
*/
String get_symbol_name(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "get_symbol : node is not a symbol or keyword");
    return strdup(named(node));
}

