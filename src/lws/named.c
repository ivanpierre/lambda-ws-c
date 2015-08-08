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
static Named *named(Node *node)
{
    return (Named *)node->val.compl;
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
    named(node)->name = new_string_allocate(value); // allocate place for the string
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
Node *string_symbol(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "string_symbol : node is not a symbol or keyword");
    return link_node(named(node)->name); // alloc node
}

/*
    Return ns of symbol...
*/
Node *string_symbol_formated(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "string_symbol_formated : node is not a symbol or keyword");
    return link_node(named(node)->ns); // alloc node
}

/*
    Return name of symbol...
*/
Node *get_symbol_name(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "get_symbol_name : node is not a symbol or keyword");
    return link_node(named(node)->name); // alloc node
}

/*
    Return name of symbol...
*/
Node *get_named_ns(Node *node)
{
    ASSERT_TYPE(node, SYMBOL|KEYWORD, "get_symbol_ns : node is not a symbol or keyword");
    return link_node(named(node)->ns); // alloc node
}

