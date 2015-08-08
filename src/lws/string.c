/****
    Strings

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
    Access Collection from Node
*/
static void *string(Node *node)
{
    return node->val.compl;
}

/*
    Create a linked string, don't allocate space for the string
*/
static Node *new_string_base(String value)
{
    ASSERT(value, "make_string_value : value is null");
    Node *node = new_node(STRING);
    if(!node)
        return node;
    node->val.compl = value;
    return node; // new_node does the link
}

/*
    Create a linked string, allocate space for the string
*/
Node *new_string(char *value)
{
    ASSERT(value, "make_string : value is null");
    return new_string_base(value); // new_string_base does the link
}

/*
    Create a linked string, allocate space for the string
*/
Node *new_string_allocate(char *value)
{
    ASSERT(value, "make_string_allocate : value is null");
    return new_string_base(strdup(value)); // make_string does the link
}

/*
    create a new string node appending another one
*/
Node *sprintf_string(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    String formated = NULL;
    asprintf(&formated, fmt, args);
    if(!formated)
        return new_string_allocate("Cannot format string");
    return new_string(formated);
}

/*
    test if node is a string
*/
bool stringp(Node *node)
{
    return node && node->type & STRING;
}

/*
    Return linked value of string...
*/
static String get_string(Node *node)
{
    ASSERT_TYPE(node, STRING, "get_string : node is not a string, symbol or keyword");
    return strdup(string(node));
}

/*
    Return allocated string of string formatted according to type
*/
static String get_formated_string(Node *node)
{
    ASSERT_TYPE(node, STRING, "get_string : node is not a string, symbol or keyword");
    String formated = NULL;
    switch(node->type)
    {
        case STRING :
            asprintf(&formated, "\"%s\"", (string(node)));
            break;
        default :
            break;
    }
    ASSERT(formated, "get_formated_string : cannot format node");
    return formated;
}

/*
    Unalloc string
*/
Node *free_string(Node *node)
{
    ASSERT_TYPE(node, STRING, "free_string : node is not a string");
    if(string(node))
    {
        free(string(node));
        node->val.compl = NULL;
    }
    return node;
}

