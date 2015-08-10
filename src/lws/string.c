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
#include "string.h"

/*
    Create a linked string, don't allocate space for the string
*/
static Node *string_base(String value)
{
    ASSERT(value, "value is null");

    Node *node = new_node(STRING);

    if(!node)
        return NULL;

    STRING(node) = value;
    return node; // new_node did the link
}

/*
    Create a linked string, allocate space for the string
*/
Node *string(char *value)
{
    ASSERT(value, "value is null");

    return string_base(value); // new_string_base did the link
}

/*
    Create a linked string, allocate space for the string
*/
Node *string_allocate(char *value)
{
    ASSERT(value, "value is null");

    return string_base(strdup(value)); // make_string does the link
}

/*
    create a new string node appending another one
*/
Node *string_sprintf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    String formated = NULL;
    asprintf(&formated, fmt, args);
    if(!formated)
        return string_allocate("cannot format string");
    return string(formated);
}

/*
    test if node is a string
*/
bool string_QM_(Node *node)
{
    return node && node->type & STRING;
}

/*
    Unalloc string
*/
Node *string_free(Node *node)
{
    ASSERT_TYPE(node, STRING, "node is not a string");

    String str = STRING(node);
    if(str)
    {
        free(str);
        str = NULL;
    }

    return node;
}

