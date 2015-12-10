/****
	Set class
	This is a minimal set implementation to enable to make the
	oop system work.

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

#define LOOKUP 32

struct Set;

extern Class *CLASS_SET;

#define STRUCT_SET \
	STRUCT_OBJECT; \
	WS_BYTE		size; \
	WS_BYTE		shift; \
	Object		*leaf[LOOKUP]

typedef struct Set
{
	STRUCT_SET;
} Set;

void set_static();

void *set(char *name, char *super, char **interfaces, MethodDesc methods[]);

void *set_init(void *class, WS_BYTE shift);

void *set_get(Set *node, void *obj, WS_INT hash,
				WS_INT (*cmp)(void *arg1, void *arg2));

void *set_assoc(Set *node, void *obj, WS_LONG hash,
				WS_INT (*cmp)(void *arg1, void *arg2));
