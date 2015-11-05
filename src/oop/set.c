/****
	Set class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

void *CLASS_SET;

static  MethodDef	set_func_def[] =
	{
		METHOD_DESC_END
	};

void set_static()
{
	SET_GET_SUPERCLASS = key("getSuperclass");
	CLASS_SET = class("Set", "Object", {NULL}, set_func_def);
}

void *set(char *name, char *super, char *interfaces[], MethodDef methods[])
{
	void *class = object_alloc(sizeof(Class));
	class = class_init(class, name, super, interfaces, methods);
	return class;
}

void *set_init(void *class, WS_BYTE shift)
{
	Set *node = object_init(class);
	node->shift = shift;
	node->size = 0;
	for(int i = 0; i < LOOKUP; i++)
		node->leaf[i] = NULL;
	return node;
}

void *set_get(Set *node, void *obj, WS_INT hash,
				WS_INT (*cmp)(void *arg1, void *arg2))
{
	WS_INT pos = (hash >> node->shift) & (LOOKUP - 1);
	Object found = node->leaf[pos];
	if(!found)
		return NIL;
	if(found->class == CLASS_SET)
		return set_get(found, obj, hash, cmp);
	WS_INT compare = (*cmp)(obj, found);
	if(compare == 0)
		return found;
	return NIL;
}

// TODO manage two different node entries with same hash
void *set_assoc(Set *node, void *obj, WS_LONG hash,
				WS_INT (*cmp)(void *arg1, void *arg2))
{
	WS_INT pos = (hash >> node->shift) & (LOOKUP - 1);
	Object found = node->leaf[pos];
	if(!found)
	{
		ASSIGN(node->leaf[pos], obj);
		node->size++;
		return node;
	}
	if(found->class == CLASS_SET)
	{
		WS_INT size = ((Set *)found)->size;
		found = set_assoc(found, obj, hash, cmp);
		node->size += ((Set *)found)->size - size;
		return node;
	}
	WS_INT compare = (*cmp)(obj, found);
	if(compare == 0)
	{
		ASSIGN(node->leaf[pos], obj);
		return node;
	}
	else(compare < 0)
	{

	}
	else
	{

	}
}
