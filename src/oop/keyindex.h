/****
	KeyIndex class

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef KEYINDEX_H
#define KEYINDEX_H

#define STRUCT_KEY_INDEX \
	STRUCT_OBJECT; \
	void			*key; \
	WS_INT			index

typedef struct KeyIndex
{
	STRUCT_KEYINDEX;
} KeyIndex;

extern void *key_def;

extern Class *CLASS_KEY_INDEX;

extern WS_INT METH_GET_SUPERCLASS;

// Class constructors
extern void key_index_static();

extern void key_index_functions();

// constructor for keyindexes
extern void *key_index(char *key, WS_INT index);

// functions
extern WS_INT key(char *keystr);

// Methods
void *key_index_finalize(void *key_index);

void *key_index_to_string(void *key_index);

#endif
