/****
	All nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#include <stdint.h>

/*
	Used type definitions
*/
// Integers
typedef int8_t			WS_BYTE;
typedef int16_t			WS_SHORT;
typedef int32_t			WS_INT;
typedef int64_t			WS_LONG;
typedef int8_t			WS_BOOL;

// Decimal
typedef float			WS_FLOAT;
typedef double			WS_DOUBLE;

struct Object; // forward


#define BOOL_FALSE 0
#define BOOL_TRUE (!BOOL_FALSE)

/*
	Define in case of allocation debugging
*/
#define DEBUG_ALLOC

/*
	To display debugging trace of allocation and unallocation
*/
// #define DEBUG_FREE

#ifdef DEBUG_ALLOC
#define STRUCT_OBJECT \
	struct Object	*class; \
	WS_LONG			occurrences; \
	struct Object	*previous_node; \
	struct Object	*next_node
#else
#define STRUCT_OBJECT \
	struct Object	*type; \
	WS_LONG			occurrences
#endif

/*
	Struct of a base node
*/
typedef struct Object
{
	STRUCT_OBJECT;
} Object;

#include "free.h"
#include "error.h"

// global values
extern Object *NIL;
extern Object *TRUE;
extern Object *FALSE;

extern Object *new_node		(TYPES type);
extern Object *false_Q_		(Object *node);
extern Object *true_Q_		(Object *node);

// Non-standard functions
extern void *NODE_STRUCT	(Object *node, TYPES type);
extern bool FALSE_Q_		(Object *node);
extern bool TRUE_Q_			(Object *node);
extern void *THREAD_NODE	(Object *init, ...);
extern bool node_isa_type	(Object *node, TYPES isa);

// DEBUG_ALLOC functions
extern void init_node_list	();
extern void print_node_list	();

#define BOOL(val) (val ? TRUE : FALSE)
#define STRUCT(node) (void *)((char *)node + sizeof(Object))

// ***************************
#define ACCESS_START(struct_type, return_type, input_type) \
	return_type res; \
	ASSERT_NODE(node, input_type); \
	struct_type *str = STRUCT(node)

// ***************************
#define ACCESS_END(otype) \
	unlink_node(node); \
 \
	if (!res) \
		res = NIL; \
	if (res != NIL) \
		ASSERT_TYPE(res, otype); \
	return unlink_new(res); \
 \
	catch: \
	unlink_node(node); \
	return NULL

// ***************************
#define ACCESS_END_TYPED(otype) \
	unlink_node(node); \
	ASSERT_TYPE(res, otype); \
	return res; \
 \
	catch: \
	unlink_node(node); \
	return NULL

// ***************************
#define ACCESS_END_UNTYPED() \
	unlink_node(node); \
	return res; \
 \
	catch: \
	unlink_node(node); \
	return res

// ***************************
#define ACCESS_NODE(ctype, access, itype, otype) \
	ACCESS_START(ctype, Object *, itype); \
	res = link_node(str->access); \
	ACCESS_END(otype)

// ***************************
#define ACCESS_VALUE(ctype, access, itype, def) \
	itype res = def; \
	link_node(node); \
	ctype *coll = STRUCT(node); \
	res = coll->access; \
	unlink_node(node); \
	return res

// ***************************
#define ACCESS_BOOL(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = BOOL(str->access ); \
	ACCESS_END_TYPED(BOOLEAN)

// ***************************
#define ACCESS_BYTE(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = byte(str->access); \
	ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_SHORT(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = short(str->access); \
	ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_INTEGER(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = integer(str->access); \
	ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_LONG(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = long(str->access); \
	ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_FLOAT(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = float(str->access); \
	ACCESS_END_TYPED(DECIMAL)

// ***************************
#define ACCESS_DOUBLE(ctype, access, itype) \
	ACCESS_START(ctype, Object *, itype); \
	res = double(str->access); \
	ACCESS_END_TYPED(DECIMAL)

// ***************************
#define ACCESS_PTR(ctype, access, itype) \
	ACCESS_START(ctype, void *, itype); \
	res = str->access; \
	ACCESS_END_UNTYPED()

// ***************************
#define ACCESS_STR(ctype, access, itype) \
	ACCESS_START(ctype, char *, itype); \
	res = strdup(str->access); \
	ACCESS_END_UNTYPED()

// ***************************
#define ASSIGN(to, from) \
	{ \
		Object *tmp = link_node(from); \
		if(to != tmp) \
		{ \
			unlink_node(to); \
			to = tmp; \
		} \
	}

// ***************************
#define LINK_ARG(to, from) \
	Object *to = link_node(from)

#endif

#include "named.h"
#include "interface.h"
#include "class.h"
#include "method.h"
#include "number.h"
#include "byte.h"
#include "short.h"
#include "integer.h"
#include "long.h"
#include "bigint.h"
#include "ratio.h"
#include "float.h"
#include "double.h"
#include "bigdec.h"
