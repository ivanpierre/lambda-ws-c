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
#include "writer.h"
#include "free_internal.h"

/*
	Gives back the string content
*/
char *GET_STRING(Node *node)
{
	Node *tmp_node = NULL;
	ASSERT_NODE(node, tmp_node, ISTRING);
	String *str = STRUCT(node);
	char *res = malloc(str->size + 1);
	ASSERT(res, ERR_ALLOC);
	memcpy(res, str->string, str->size);
	res[str->size] = '\0';
	unlink_node(&node);
	unlink_node(&tmp_node);
	return res;

	//***************
	error_assert:
	unlink_node(&node);
	unlink_node(&tmp_node);
	return NULL;
}

/*
	Create a linked string, don't allocate space for the string
*/
static Node *string_base(char *value)
{
	Node *node = new_node(ISTRING);
	String *str = STRUCT(node);

	str->size = strlen(value);
	str->string = value;
	return node; // node did the link
}

/*
	Create a linked string, allocate space for the string
*/
Node *string_unalloc(char *value)
{
	ASSERT(value, ERR_NODE);
	return string_base(value); // new_string_base did the link

	//***************
	error_assert:
	return NULL;
}

/*
	Create a linked string, allocate space for the string
*/
Node *string(char *value)
{
	ASSERT(value, ERR_NODE);
	return string_base(strdup(value)); // make_string does the link

	//***************
	error_assert:
	return NULL;
}

/*
	create a new string node appending another one
*/
Node *string_sprintf(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char *formated = NULL;
	vasprintf(&formated, fmt, args);
	if(!formated)
		return string("cannot format string");

	TRACE("Formatt = %s'", fmt);
	TRACE("Formatted String = %s'", formated);
	return string(formated);
}

/*
	test if node is a string
*/
Node *string_Q_(Node *node)
{
	Node *res = (node && node->type->int_type == ISTRING) ? TRUE : FALSE;
	unlink_node(&node);
	return res;
}

/*
	Unalloc string
*/
Node *string_free(Node **node)
{
	String *str = STRUCT(*node);
	free(str->string);
	free(*node);
	*node = NULL;
	return *node;
}

/*
	Standard string getter for node function to element
*/
char *GET_ELEM_STRING(Node *elem, Node *(*func)(Node *))
{
	return THREAD_NODE(elem, func, &PRINT, &GET_STRING, NULL);
}

