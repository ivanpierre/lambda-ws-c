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
    Create a linked string, don't allocate space for the string
*/
static Node *new_string_base(String value)
{
    ASSERT(value, "make_string_value : value is null");
    Node *s = new_node(STRING);
    if(!s) return s;
    s->val.string = value;
    return s; // create node does the link
}

/*
    Create a linked string, allocate space for the string
*/
Node *new_string(char *value)
{
    ASSERT(value, "make_string : value is null");
    return new_string_base(value); // make_string does the link
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
    return new_string_allocate(formated);
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
String get_string(Node *s)
{
    ASSERT_TYPE(s, STRING|SYMBOL|KEYWORD, "get_string : node is not a string, symbol or keyword");
    return strdup(s->val.string);
}

/*
    Return allocated string of string formatted according to type
*/
String get_formated_string(Node *s)
{
    ASSERT_TYPE(s, STRING|SYMBOL|KEYWORD, "get_string : node is not a string, symbol or keyword");
    String formated = NULL;
    switch(s->type)
    {
        case STRING :
            asprintf(&formated, "\"%s\"", (s->val.string));
            break;
        default :
            break;
    }
    ASSERT(formated, "get_formated_string : cannot format node");
    return formated;
}


/*
    Return allocated string node of string formatted according to type
*/
Node *string_string(Node *node)
{
    ASSERT_TYPE(node, STRING|SYMBOL|KEYWORD, "string_string : node is not a string, symbol or keyword");
    String formated = get_formated_string(node);
    ASSERT(formated, "string_string : cannot format node");
    return new_string(formated); // formated allocated
}

/*
    Unalloc string
*/
Node *free_string(Node *node)
{
    ASSERT_TYPE(node, STRING|SYMBOL|KEYWORD, "free_string : node is not a string");
    if(node->val.string)
    {
        free(node->val.string);
        node->val.string = NULL;
    }
    return node;
}

