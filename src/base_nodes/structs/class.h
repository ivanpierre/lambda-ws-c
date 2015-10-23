/****
	INode class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRUCT_H
#define STRUCT_H

#include "interface.h"

#define STRUCT_CLASS \
struct Object *super

typedef struct
{
	STRUCT_INTERFACE;
	STRUCT_CLASS;
} Class;

extern Object *class(char *name, char *super, 
						char *interfaces[], MethodDesc *methods[]);

#endif
