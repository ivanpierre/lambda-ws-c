/****
	Init OOP library

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

static  MethodDef	interface_func_def[] =
	{
		{"getInterfaces",	1, &interface_get_interfaces},
		{"getMethods",		1, &interface_get_methods},
		{"isInterface",		1, &interface_is_interface},
		{"hashCode",		1, &interface_hash_code},
		{"toString",		1, &interface_to_string},
		METHOD_DESC_END
	};

bool isa(Object *type, Object *isa)
{
	return true;
}

void interface_static()
{
	METH_GET_INTERFACES = key("getInterfaces");
	CLASS_INTERFACE = class("Interface", CLASS_NAMED, {NULL}, interface_func_def);
}

void *interface(char *name, char *interface[], MethodDesc *methods)
{
	void *interface = object_alloc(sizeof(Interface));
	interface = class_init(interface, name, super, interfaces, methods);
	return interface;
}

void *interface_init(void *interface, char *name, char *interfaces[],
						MethodDef *methods))
{
	interface = named_init(interface, name));
	while(methods->name)
	{
		if(stricmp(method->name, "static ", 7) == 0)
			interface_add_methods(interface->statics, methods++);
		else
			interface_add_methods(interface->methods, methods++);
	}
	return interface;
}

void *interface_add_methods(void *set, MethodDef *method)
{
	char *name = stricmp(method->name, "static ", 7) ?
							method->name :
							&method->name[7];

	WS_INT key = key(name);
}
