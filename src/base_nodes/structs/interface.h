/**
	Interface Class
	name		String
	interfaces	Set of Interfaces
	methods		Map of methods indexed by hash of keywords
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#define STRUCT_INTERFACE \
char				*name; \
struct Object		*interfaces; \
struct Object		*methods

typedef struct
{
	STRUCT_INTERFACE;
} Interface;

extern bool isa(Object *type, Object *isa);
extern Object *interface(char *name, char *interface[], MethodDesc *methods[]);

#endif
