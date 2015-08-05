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
    Create a linked string, don't allocate space for the string
*/
static Node *new_symbol_base(Node *ns, String value, NodeType type)
{
    ASSERT(value, "make_string_value : value is null");
    Node *s = new_node(type);
    if(!s) return s;
    s->val.string = value;
    return s; // create node does the link
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
Node *new_keyword(Node * ns, char *value)
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
String get_symbol_name(Node *s)
{
    ASSERT_TYPE(s, STRING|SYMBOL|KEYWORD, "get_string : node is not a string, symbol or keyword");
    return strdup(s->val.string);
}

/*
    Return allocated string of symbol name according to type
*/
String get_formated_symbol(Node *s)
{
    ASSERT_TYPE(s, STRING|SYMBOL|KEYWORD, "get_string : node is not a string, symbol or keyword");
    String formated = NULL;
    switch(s->type)
    {
        case KEYWORD :
            asprintf(&formated, ":%s", (s->val.string));
            break;
        case SYMBOL :
            asprintf(&formated, "%s", (s->val.string));
            break;
        default :
            break;
    }
    ASSERT(formated, "get_formated_string : cannot format node");
    return formated;
}

