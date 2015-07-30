/****
	Strings. This is base for all named nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015

	Warning this implementation is based on C strings
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"

/*
	Create a linked string, don't allocate space for the string
*/
static Node *new_string_base(String value, NodeType type)
{
	ASSERT(value, "make_string_value : value is null");
	Node *s = create_node(type);
	if(!s) return s;
	s->value.string = value;
	return s; // create node does the link
}

/*
	Create a linked string, allocate space for the string
*/
Node *new_string(char *value)
{
	ASSERT(value, "make_string : value is null");
	return make_string_base(value, STRING); // make_string does the link
}

/*
	Create a linked string, allocate space for the string
*/
Node *new_string_allocate(char *value)
{
	ASSERT(value, "make_string_allocate : value is null");
	return make_string_base(strdup(value), STRING); // make_string does the link
}

/*
	Create a linked symbol, allocate space for the string
*/
Node *new_symbol(char *value)
{
	ASSERT(value, "make_symbol : value is null");
	return make_string_base(strdup(value), SYMBOL); // make_string does the link
}

/*
	Create a linked keyword, allocate space for the string
*/
Node *new_keyword(char *value)
{
	ASSERT(value, "make_keyword : value is null");
	return make_string_base(strdup(value), KEYWORD); // make_string does the link
}

/*
	create a new string node appending another one
*/
Node *concat_string(Node *s, Node *add)
{
	char *formatted = NULL;;
	Node *tmp = string_node(add);
	ASSERT(tmp, "concat_string : cannot format node");
	asprintf(&formatted, "%s%s", ((String *)s)->value, tmp);
	free(tmp);                          // unallocate string verstion of add
	ASSERT(formatted, "concat_string : cannot format node");
	return make_string(formatted);   // formatted has been allocated
}

/*
	test if node is a string
*/
bool stringp(Node *node)
{
	return node && node->type & STRING;
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
	Return linked value of string...
*/
String get_string(Node *s)
{
	ASSERT_TYPE(STRING|SYMBOL|KEYWORD, "get_string : node is not a string");
	return strdup(((String *)s)->value);
}

/*
	Unalloc string
*/
Node *free_string(Node *node)
{
	ASSERT_TYPE(STRING|SYMBOL|KEYWORD, "free_string : node is not a string");
	String *str = (String *)node;
	if(str->value)
	{
		free(str->value);
		str->value = NULL;
	}
	return node;
}

