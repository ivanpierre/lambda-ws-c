/****
	Strings. This is base for all named nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

typedef struct
{
	NODE;
	char        *value;
} string;

/*
	Create a linked string, don't allocate space for the string
*/
node *make_string(char *value)
{
	node *s = create_node(STRING);

	if(nullp(s))
		return NIL;

	if(!value)
	{
		error("make_string : string is null");
		unlink_node(s);
		return NIL;
	}

	((string *)s)->value = value;

	return s; // create node does the link
}

/*
	Create a linked string, allocate space for the string
*/
node *make_string_allocate(char *value)
{
	if(value)
		return make_string(strdup(value)); // make_string does the link
	else
	{
		error("make_string_allocate : value is null");
		return NIL;
	}
}

/*
	create a new string node appending another one
*/
node *concat_string(node *s, node *add)
{
	char *formatted = NULL;;
	char *tmp = print_node(add);
	node *new = NIL; // default return value if error

	if(!tmp)
	{
		error("concat_string : cannot format node");
		return NIL; // return NIL
	}

	asprintf(&formatted, "%s%s", ((string *)s)->value, tmp);
	free(tmp);                          // unallocate string verstion of add
	if(formatted)
		new = make_string(formatted);   // formatted has been allocated

	return new;
}

/*
	test if node is a string
	Return the linked string or NIL
*/
node *stringp(node *node)
{
	return (get_type(node) == STRING) ? link_node(node) : NIL;
}

/*
	Return linked value of string...
*/
char *get_string(node *s)
{
	if(!stringp(s))
	{
		error("node is not a string\n");
		return "\"(null)\"";
	}
	return strdup(((string *)s)->value);
}

/*
	Unalloc string
*/
static node *free_string(node *node)
{
	string *str = (string *)node;
	if(!stringp(node))
		return node;
	if(str->value)
	{
		free(str->value);
		str->value = NULL;
	}
	return node;
}

/*
	init type STRING, so the type exists in the types... ;)
*/
bool init_string_type()
{
	node *string =
	set_type(STRING, create_type( "string",
						sizeof(string),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						&free_string,   // free
						NULL))  // print directly managed by print_node
	if(!string)
	{
		error("init_string_type : error creating string type\n");
		return FALSE;
	}
	unlink_node(string);
	return TRUE;
}

