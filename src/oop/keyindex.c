/****
	KeyIndex class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "oop.h"

void *key_def = NULL;

void *CLASS_KEY_INDEX = NULL;

static  MethodDef	key_index_func_def[] =
	{
		{"toString",		1, &key_index_to_string}, // override
		{"finalize",		1, &key_index_finalize}, // overrides
		METHOD_DESC_END
	};

// WS_INT METH_GET_SUPERCLASS;

// Class constructors
void key_index_static()
{
	CLASS_KEY_INDEX = class("KeyIndex");
}

void key_index_functions()
{
	key_def = set();
	CLASS_KEY_INDEX = class_init(CLASS_KEY_INDEX, CLASS_OBJECT,
									{NULL}, key_index_func_def);
}

// constructor for keyindexes
void *key_index(char *key, WS_INT index)
{
	void *key_index = object_alloc(sizeof(KeyIndex));
	key_index = key_index_init(key_index, key, index);
	return key_index;
}

void *key_index_init(void *key_index, char *key, WS_INT index)
{
	key_index = object_init(key_index);
	key_index->key = strings(key);
	key_index->index = index;
	return key_index;
}

static WS_INT new_key()
{
	static index = 0;
	return index++;
}

// functions
extern WS_INT key(char *keystr)
{
	void *keyi = link_node(key_index(keystr, -1));
	void *feyf = set_get(key_def, key1)
	if(keyi->index == -1)
	{

	}
}

// Methods
void *key_index_finalize(void *key_index)
{
	string_finalize(key_index->key);
	object_finalize(key_index);
}

void *key_index_to_string(void *key_index)
{

}
