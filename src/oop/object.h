/****
	All nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef OBJECT_H
#define OBJECT_H


#ifdef DEBUG_ALLOC
#define STRUCT_OBJECT \
	void	*class; \
	WS_LONG	occurrences; \
	void	*previous_node; \
	void	*next_node
#else
#define STRUCT_OBJECT \
	void	*class; \
	WS_LONG	occurrences
#endif

/*
	Struct of a base object
*/
typedef struct Object
{
	STRUCT_OBJECT;
} Object;

#include "gc.h"

// global values
extern Object *NIL;
extern Object *TRUE;
extern Object *FALSE;

extern void *false_Q_			(void *node);
extern void *true_Q_			(void *node);

// DEBUG_ALLOC functions
extern void init_node_list	();
extern void print_node_list	();

#define BOOL(val) (val ? TRUE : FALSE)

extern Class *CLASS_OBJECT;

extern WS_INT METH_CLONE;
extern WS_INT METH_EQUALS;
extern WS_INT METH_FINALIZE;
extern WS_INT METH_GET_CLASS;
extern WS_INT METH_HASH_CODE;
extern WS_INT METH_NOTIFY;
extern WS_INT METH_NOTIFY_ALL;
extern WS_INT METH_TO_STRING;
extern WS_INT METH_WAIT;

// Class constructors
extern void object_static();

extern void object_functions();

extern void *object_init		(void *class);

extern void *object_alloc		(WS_LONG size);

// constructor for keyindexes
extern void *object();

// Methods
void *object_clone(void *obj);
void *object_equals(void *obj1, void *obj2);
void *object_finalize(void *obj);
void *object_get_class(void *obj);
void *object_hash_code(void *obj);
void *object_notify(void *obj);
void *object_notify_all(void *obj);
void *object_to_string(void *obj);
void *object_wait(void *obj);
void *object_wait2(void *obj1, void *obj2);
void *object_wait3(void *obj1, void *obj2, void *obj3);

#endif
