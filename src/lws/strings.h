/****
	String header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRINGS_H
#define STRINGS_H

// Strings
Node *string         (char *value);
Node *string_sprintf (char *fmt, ...);
Node *string_Q_      (Node *node);

typedef struct
{
	long size;
	char *string;
} String;

/*
	Access string from Node
*/
char *GET_STRING        (Node *node);
char *GET_ELEM_STRING   (Node *elem, Node *(*func)(Node *));
Node *STRING_Q_         (Node *node);

#endif
