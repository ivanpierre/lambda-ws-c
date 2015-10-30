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

typedef struct Class
{
	STRUCT_CLASS;
} Class;

extern Class		*CLASS;

extern Class *class(char *name, char *super,
					char *interfaces[], struct MethodDesc *methods[]);

#endif
