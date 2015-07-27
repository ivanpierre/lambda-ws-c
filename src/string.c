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
	Create a string, don't allocate space for the string
*/
node *make_string(char *value)
{
	node *s = create_node(STRING);

	if(nullp(s))
		return NULL;

	if(!value)
	{
		error("make_string : string is null");
		unlink_node(s);
		return NULL;
	}

	((string *)s)->value = value;

	return s;
}

/*
	Create a string, allocate space for the string
*/
node *make_string_allocate(char *value)
{
	if(value)
		return make_string(strdup(value));
	else
	{
		error("make_string_allocate : value is null");
		return NULL;
	}
}

/*
	create a new string node appending another one
*/
node *concat_string(node *s, node *add)
{
	char *formatted = NULL;;
	char *tmp = print_node(add);
	node *new = NULL; // default return value if error

	if(!tmp)
	{
		error("concat_string : cannot format node");
		return new;
	}

	asprintf(&formatted, "%s%s", ((string *)s)->value, tmp);
	free(tmp);                          // unallocate string verstion of add
	if(formatted)
		new = make_string(formatted);   // formatted has been allocated

	unlink_node(s);
	unlink_node(add);

	return new;
}

/*
	test if node is a string
*/
bool stringp(node *node)
{
	return get_type(node) == STRING;
}

/*
	Return value of string.... !!! immutable
*/
char *get_string(node *s)
{
	if(!stringp(s))
	{
		error("node is not a string\n");
		return "\"(null)\"";
	}
	return ((string *)s)->value;
}

/*
	Unalloc string
*/
static void free_string(node *node)
{
	string *str = (string *)node;
	if(str->value)
	{
		free(str->value);
		str->value = NULL;
	}
}

/*
	init type STRING, so the type exists in the types... ;)
*/
bool init_string_type()
{
	if(!set_type(STRING, create_type( "string",
						sizeof(string),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						&free_string,   // free
						NULL)))  // print
	{
		error("init_string_type : error creating string type\n");
		return FALSE;
	}
	return TRUE;
}

