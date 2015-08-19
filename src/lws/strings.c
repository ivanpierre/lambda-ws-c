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
#include "strings.h"

/*
    Gives back the string content
*/
String GET_STRING(Node *node)
{
    ASSERT(node, "null value")
    ASSERT_TYPE(node, STRING, "get szring grom non string");
    return (String)(node->val.compl);
}

/*
    Create a linked string, don't allocate space for the string
*/
static Node *string_base(String value)
{
    ASSERT(value, "value is null");

    Node *node = NEW(STRING);

    if(!node)
        return NULL;

    node->val.compl = value;
    return node; // node did the link
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
    vasprintf(&formated, fmt, args);
    if(!formated)
        return string_allocate("cannot format string");

    // TRACE("Formatt = %s'", fmt);
    // TRACE("Formatted String = %s'", formated);
    return string(formated);
}

/*
    test if node is a string
*/
Node *string_Q_(Node *node)
{
    return (node && node->type & STRING) ? true : false;
}

/*
    Unalloc string
*/
Node *string_free(Node *node)
{
    ASSERT_TYPE(node, STRING, "node is not a string");
    if(node->val.compl)
        free(node->val.compl);
    node->val.compl = NULL;
    free(node);
    return NULL;
}

