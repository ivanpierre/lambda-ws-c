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

typedef struct Object Object; // forward

#define BOOL_FALSE 0
#define BOOL_TRUE !BOOL_FALSE

/*
	Define in case of allocation debugging
*/
#define DEBUG_ALLOC

/*
	To display debugging trace of allocation and unallocation
*/
// #define DEBUG_FREE

struct Class;
struct Strings;
struct MethodDesc;
struct Method;

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
	Struct of a base node
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

extern void *object_new			(void *class);
extern void *object_alloc		(WS_LONG size);
extern void *false_Q_			(void *node);
extern void *true_Q_			(void *node);

// DEBUG_ALLOC functions
extern void init_node_list	();
extern void print_node_list	();

#define BOOL(val) (val ? TRUE : FALSE)


// ***************************
#define ASSIGN(to, from) \
	{ \
		void *tmp = link_node(from); \
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
