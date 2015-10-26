/****
	INode class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRUCT_H
#define STRUCT_H

#define STRUCT_CLASS \
STRUCT_INTERFACE; \
struct Class *super

typedef struct
{
	STRUCT_CLASS;
} Class;

extern Object *class(char *name, char *super,
						char *interfaces[], MethodDesc *methods[]);

#endif
