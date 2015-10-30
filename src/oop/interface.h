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

extern WS_BOOL isa(Object *type, Object *isa);
extern Object *interface(char *name, char *interface[],
						struct MethodDesc *methods[]);

#endif
