/****
	String header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRINGS_H
#define STRINGS_H

typedef struct
{
	WS_LONG		length;
	WS_INT 		hash;
	char 		*string;
} String;

// Strings
Object *string         		(char *value);
Object *string_sprintf 		(char *fmt, ...);
Object *string_Q_      		(Object *node);
Object *string_hash_code	(Object *node);
Object *string_length  		(Object *node);

/*
	Access string from Object
*/
char 	*GET_STRING			(Object *node);
char 	*GET_ELEM_STRING	(Object *elem, Object *(*func)(Object *node));
WS_BOOL	STRING_Q_			(Object *node);
WS_INT	STRING_HASH_CODE	(Object *node);
WS_LONG	STRING_LENGTH		(Object *node);

#endif
