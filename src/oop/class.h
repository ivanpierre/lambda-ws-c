/****
	class class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef CLASS_H
#define CLASS_H

#define STRUCT_CLASS \
	STRUCT_INTERFACE; \
	void			*super; \
	void			*ctors

typedef struct Class
{
	STRUCT_CLASS;
} Class;

extern void *CLASS_CLASS;

extern WS_INT METH_GET_SUPERCLASS;

// Class constructors
extern void class_static();

extern void class_functions();

// constructor for other classes
extern void *class(char *name, char *super,	void *interfaces);

extern void *class_init(void *class, char *name, void *super,
						void *interfaces[]);

extern void *class_functions_init(void *class, MethodDef *methods);


// Methods
void *class_finalize(void *class);

void *class_get_superclass(void *class);

void *class_to_string(void *class);

#endif
