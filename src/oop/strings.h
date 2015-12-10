/****
	String header

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRINGS_H
#define STRINGS_H

#define STRUCT_STRINGS \
	STRUCT_OBJECT; \
	WS_LONG		length; \
	WS_INT 		hash; \
	char 		*string

typedef struct
{
	STRUCT_STRINGS;
} String;

extern Class *CLASS_STRINGS;

extern void strings_static();
extern void strings_functions();

// Strings
extern Object *string         		(char *value);
extern Object *string_format 		(char *fmt, ...);
extern Object *string_hash_code		(Object *node);
extern Object *string_length  		(Object *node);

/*
	Access string from Object
*/
extern char 	*GET_STRING			(Object *node);
extern char 	*GET_ELEM_STRING	(Object *elem, Object *(*func)(Object *node));
extern WS_BOOL	STRING_Q_			(Object *node);
extern WS_INT	STRING_HASH_CODE	(Object *node);
extern WS_LONG	STRING_LENGTH		(Object *node);

#endif
