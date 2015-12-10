/****
	Init OOP library

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

static  MethodDesc	interface_func_def[] =
	{
		{"getInterfaces",	1, &interface_get_interfaces},
		{"getMethods",		1, &interface_get_methods},
		{"isInterface",		1, &interface_is_interface},
		{"hashCode",		1, &interface_hash_code},
		{"toString",		1, &interface_to_string},
		METHOD_DESC_END
	};

Class *CLASS_INTERFACE = NULL;

bool isa(Object *type, Object *isa)
{
	return true;
}

void interface_static()
{
	CLASS_INTERFACE =interface("Interface");
}

void interface_functon()
{
	METH_GET_INTERFACES = key("getInterfaces");
	CLASS_INTERFACE = class_function_init("Interface", CLASS_NAMED, (void *[]){NULL}, interface_func_def);
}

void *interface(char *name)
{
	void *interface = object_alloc(sizeof(Interface));
	interface = interface_init(name);
	return interface;
}

void *interface_init(void *interface, char *name)
{
	interface = named_init(interface, name));
	return interface;
}

void *interface_function_init(void *interface, MethodDesc *methods))
{
	while(methods->name)
	{
		if(stricmp(method->name, "static ", 7) == 0)
			interface_add_methods(interface->statics, methods++);
		else
			interface_add_methods(interface->methods, methods++);
	}
	return interface;
}

void *interface_interface_init(void *interface, void *interfaces[])
{
	while(interfaces)
	{
		interface = interface_function_inherit(interface, *interfaces);
		interfaces++;
	}
	return interface;
}

void *interface_add_methods(void *set, MethodDesc *method)
{
	char *name = stricmp(method->name, "static ", 7) ?
							method->name :
							&method->name[7];

	WS_INT key = key(name);
	// TODO finish
}

/******************
	Methods
*/
/**
	Release allocated values of class object to be released
	@overrides
*/
void *interface_finalize(void *interface)
{
	// first finalize functions
	interface = set_finalize(((Interface *)interface)->statics);
	interface = set_finalize(((Interface *)interface)->methods);
	interface = set_finalize(((Interface *)interface)->interfaces);
	interface = named_finalize(interface);
	return interface;
}
