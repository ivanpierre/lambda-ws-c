/****
	All Nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "oop.h"

#ifdef DEBUG_ALLOC
	#define NEW_CONST {CONST, 0l, NULL, NULL}
#else
	#define NEW_CONST {CONST, 0l}
#endif

// global values
static Object nil_val   = NEW_CONST;
static Object true_val  = NEW_CONST;
static Object false_val = NEW_CONST;
Object		*NIL		= &nil_val;
Object		*FALSE		= &false_val;
Object		*TRUE		= &true_val;

static  MethodDesc	object_func_def[] =
	{
		{"identity",	1, &object_identity},
		{"clone",		1, &object_clone},
		{"equals",		2, &object_equals},
		{"finalize",	1, &object_finalize},
		{"getClass",	1, &object_get_class},
		{"hashCode",	1, &object_hash_code},
		{"notify",		1, &object_notify},
		{"notifyAll",	1, &object_notify_all},
		{"toString",	1, &object_to_string},
		{"wait",		1, &object_wait},
		{"wait",		2, &object_wait2},
		{"wait",		3, &object_wait3},
		METHOD_DESC_END
	};

extern void object_static()
{
	CLASS_OBJECT = class("Object");
}

extern void object_functions()
{
	METH_CLONE = key("clone");
	METH_EQUALS = key("equals");
	METH_FINALIZE = key("finalize");
	METH_GET_CLASS = key("getClass");
	METH_HASH_CODE = key("hashCode");
	METH_NOTIFY = key("notify");
	METH_NOTIFY_ALL = key("notifyAll");
	METH_TO_STRING = key("toString");
	METH_WAIT = key("wait");
	CLASS_OBJECT = class_functions_init(CLASS_OBJECT, NULL,
										(void *[]){NULL}, object_func_def);
}

/*
	Init base node content allocated
*/
void *object_init(void *object)
{
	ASSERT(object, ERR_NULL_PTR);
	Object *obj = object;
	obj->occurrences = 1; // will be decremented on valid creation
#ifdef DEBUG_ALLOC
	if (!last_node)
	{
		node->previous_node = obj->next_node = NULL;
		last_node = first_node = obj;
	}
	else
	{
		obj->previous_node = NULL;
		obj->next_node = first_node;
		first_node->previous_node = obj;
		first_node = obj;
	}
#endif
	return obj;

	//*************
	catch:
	return NULL;
}

/*
	Allocate a static node
	Constructor, return linked
	It should be unlink_new() by constructor
*/
void *object_alloc(WS_LONG size)
{
	// TRACE("fait nouveau node %s", str_type(type));
	Object *object = malloc(size);

	ASSERT(object, ERR_ALLOC);
	return object;

	//**************
	catch:
	free(object);
	return NULL;
}

/*
	Push arguments
	Will link all arguments to protect new node from unlinking
	during the function execution
*/
bool push_args(int nb, ...)
{
	va_list args;
	bool res = BOOL_FALSE;

	va_start(args, nb);
	for(int i = 0; i < nb; i++)
	{
		Object *arg = va_arg(args, Object *);
		if(!arg)
			res = BOOL_TRUE;
		else
			link_node(arg);
	}
	return res;
}

/*
	Pop arguments
	This will drop new unlinked nodes
*/
void pop_args(int nb, ...)
{
	va_list args;

	va_start(args, nb);
	for(int i = 0; i < nb; i++)
	{
		Object *arg = va_arg(args, Object *);
		unlink_node(arg);
	}
}

/*
	 Compose functions on an initial value
	 All initial and intermediate values should be allocated linked Nodes*.
	 At every state, the previous state is unlinked.
	 Last value can be anything and should be considered as allocated
	 Function list should finish with a NULL, else.... :D
*/
void *THREAD_NODE(Object *init, ...)
{
	PUSH_ARGS(1, init);
	void *(*func)(Object *arg) = NULL;
	va_list funp;
	Object *res = NULL;

	// Last previous result is init
	ASSIGN(res, init);

	// We will trampoline on function call values. fun(res) -> res,
	// with unlink on previous res
	va_start(funp, init);
	while ((func = va_arg(funp, void *(*)(Object *arg))))
	{
		ASSIGN(res, (*func)(res));
		ASSERT(res, ERR_INIT);
	}

	POP_ARGS(1, init);
	return res;

	//****************
	catch:
	POP_ARGS(2, init, res);
	return NULL;
}

/*
	Test falsey
*/
bool FALSE_Q_(void *node)
{
	PUSH_ARGS(1, node);
	ASSERT(node, ERR_ARG);

	bool res =  node == NIL ||
				node == FALSE;

	POP_ARGS(1, node);
	return res;

	//****************
	catch:
	POP_ARGS(1, node);
	return BOOL_FALSE;
}

/*
	Test truthey
*/
bool TRUE_Q_(void *node)
{
	PUSH_ARGS(1, node);
	ASSERT(node, ERR_ARG);

	bool res =  !FALSE_Q(node);

	POP_ARGS(1, node);
	return res;

	//****************
	catch:
	POP_ARGS(1, node);
	return BOOL_FALSE;
}

/*
	Test falsey
*/
Object *false_Q_(void *node)
{
	return FALSE_Q_(node) ? TRUE : FALSE;
}

/*
	Test truthey
*/
Object *true_Q_(void *node)
{
	return TRUE_Q_(node) ? TRUE : FALSE;
}

/*
 * Get type Object isa
 * TODO implement through interface
 */
bool node_isa_type(void *node, void *isa)
{
	PUSH_ARGS(1, node);
	bool res = node->bin_type & get_type(isa)->bin_type &&
			   node->bin_type <= get_type(isa)->bin_type;
	POP_ARGS(1, node);
	return res;

	//****************
	catch:
	POP_ARGS(1, node);
	return BOOL_FALSE;
}
