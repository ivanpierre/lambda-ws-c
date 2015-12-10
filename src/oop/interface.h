/**
	Interface Class
	name		String
	interfaces	Set of Interfaces
	methods		Map of methods indexed by hash of keywords
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#define STRUCT_INTERFACE \
	STRUCT_NAMED; \
	struct Set    		*interfaces; \
	struct Set			*statics; \
	struct Set			*methods

typedef struct Interface
{
	STRUCT_INTERFACE;
} Interface;

extern Class *CLASS_INTERFACE;

extern WS_BOOL isa(void *type, void *isa);

extern Object *interface(char *name, void *interfaces[],
						MethodDesc *methods);

extern void *interface_init(void *interface, char *name);

extern void *interface_add_method(void *set, MethodDesc *method);

extern void *interface_function_init(void *interface, MethodDesc *methods);

extern void *interface_interface_init(void *interface, void *interfaces[]);

extern void *interface_function_inherit(void *class, void *super);

/*
	Methods
*/
void *interface_finalize(void *interface);

#endif
