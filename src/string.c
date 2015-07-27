/****
	Strings. This is base for all named nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "string.h"

typedef struct {
	NODE;
	char        *value;
} string;

/*
	Create a string
*/
node *make_string(char *value) {
	node *s = create_node(STRING);

	if(nullp(s))
		return NULL;

	if(!value) {
		error("make_string : string is null");
		return NULL;
	}

	((string *)s)->value = strdup(value);

	return link_node(s);
}

/*
	test if node is a string
*/
bool stringp(node *node) {
	return get_type(node) == STRING;
}

/*
	Return value of string
*/
char *get_string(node *s) {
	if(!stringp(s)) {
		error("node is not a string\n");
		return "\"(null)\"";
	}
	return ((string *)s)->value;
}

/*
	Unalloc string
*/
static void free_string(node *node) {
	string *str = (string *)node;
	if(node->value) {
		free(node->value)
		node->value = NULL;
	}
}

/*
	print string
*/
static void print_string(node *node) {
	fprintf(stdout, "\"%s\"", get_string(node));
}


/*
	init type STRING, so the type exists in the types... ;)
*/
bool init_string_type()
{
	types[STRING] = create_type( "string",
						sizeof(string),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						&free_string,   // free
						&print_string);  // print
	if(nullp((node *)types[STRING])) {
		error("init_string_type : error creating string type\n");
		return FALSE;
	}
	return TRUE;
}

