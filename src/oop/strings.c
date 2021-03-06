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
#include "oop.h"

extern Class *CLASS_STRINGS;

static  MethodDesc	strings_func_def[] =
	{
		{"toString",		1, &object_identity}, // override
		{"finalize",		1, &string_finalize}, // overrides
		METHOD_DESC_END
	};

void strings_static()
{
	CLASS_STRINGS = class("String");
}

void strings_functions()
{
	CLASS_STRINGS = class_functions_init(CLASS_STRINGS, CLASS_OBJECT,
										(void *[]){NULL}, strings_func_def);

}

/*
	Gives back the string content
*/
char *GET_STRING(Object *node)
{
	String *str = NULL;
	ASSERT_NODE(node, ISTRING)
	str = STRUCT(node);
	char *res = malloc(str->size + 1);
	ASSERT(res, ERR_ALLOC);
	memcpy(res, str->string, str->size);
	res[str->size] = '\0';
	unlink_node(node);
	return res;

	//***************
	error_assert:
	unlink_node(node);
	free(res);
	return NULL;
}

/*
	Create a linked string, don't allocate space for the string
*/
static Object *string_base(char *value)
{
	Object *node = new_node(ISTRING);
	String *str = STRUCT(node);

	str->size = strlen(value);
	str->string = value;
	return node; // node did the link
}

/*
	Create a linked string, allocate space for the string
*/
Object *string(char *value)
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
Object *string_format(char *fmt, ...)
{
	// TODO use STRING_SPRINTF
	void *res = NULL;
	va_list args;
	va_start(args, fmt);
	char *formated = NULL;
	vasprintf(&formated, fmt, args);
	if(!formated)
		return string("null");

	res = string(formated);
	free(formated);
	return res;
}

/*
	create a new string node appending another one
*/
Object *STRING_SPRINTF(char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char *formated = NULL;
	vasprintf(&formated, fmt, args);
	if(!formated)
		return string("cannot format string");

	return string(formated);
}

/*
	test if node is a string
*/
Object *string_Q_(Object *node)
{
    ASSERT_NODE(node, INODES);
	Object *res = (node && node->int_type == ISTRING) ? TRUE : FALSE;
	unlink_node(node);
	return res;

	//***************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
	Unalloc string
*/
Object *string_free(Object *node)
{
	String *str = STRUCT(node);
	free(str->string);
	free(node);
	return NULL;
}

/*
	Standard string getter for node function to element
*/
char *GET_ELEM_STRING(Object *elem, Object *(*func)(Object *))
{
	return THREAD_NODE(elem, func, &PRINT, &GET_STRING, NULL);
}
