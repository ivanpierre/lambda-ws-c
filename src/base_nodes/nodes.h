/****
	All nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#include "type.h"
#include "error.h"

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

/*
	Used type definitions
*/
#define bool            int
struct Node; // forward

/*
	Struct of a base node
*/
typedef struct Node
{
	TYPE        type;
	long        occurrences;
#ifdef DEBUG_ALLOC
	struct Node *previous_node;
	struct Node *next_node;
#endif
} Node;

#include "free.h"

// Get Node internal struct
void *STRUCT(Node *node);

// global values
extern Node *NIL;
extern Node *TRUE;
extern Node *FALSE;

extern Node *new_node       (TYPE type);
extern Node *false_Q_       (Node *node);
extern Node *true_Q_        (Node *node);

// Non-standard functions
extern void *NODE_STRUCT    (Node *node, TYPE type);
extern bool FALSE_Q_        (Node *node);
extern bool TRUE_Q_         (Node *node);
extern void *THREAD_NODE    (Node *init, ...);
extern bool node_isa_type   (Node *node, TYPE isa);

// DEBUG_ALLOC functions
extern void init_node_list  ();
extern void print_node_list ();

#define BOOL(val) (val ? TRUE : FALSE)
#define STRUCT(node) ((void *)((char *)node) + sizeof(Node)))

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
    error_assert: \
    unlink_node(node); \
    return NULL

// ***************************
#define ACCESS_END_TYPED(otype) \
    unlink_node(node); \
    ASSERT_TYPE(res, otype); \
    return res; \
 \
    error_assert: \
    unlink_node(node); \
    return NULL

// ***************************
#define ACCESS_END_UNTYPED() \
    unlink_node(node); \
    return res; \
 \
    error_assert: \
    unlink_node(node); \
    return res

// ***************************
#define ACCESS_NODE(ctype, access, itype, otype) \
    ACCESS_START(ctype, Node *, itype); \
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
    ACCESS_START(ctype, Node *, itype); \
    res = BOOL(str->access ); \
    ACCESS_END_TYPED(BOOLEAN)

// ***************************
#define ACCESS_BYTE(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
    res = byte(str->access); \
    ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_SHORT(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
    res = short(str->access); \
    ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_INTEGER(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
    res = integer(str->access); \
    ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_INTEGER(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
    res = double(str->access); \
    ACCESS_END_TYPED(INTEGER)

// ***************************
#define ACCESS_FLOAT(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
    res = float(str->access); \
    ACCESS_END_TYPED(DECIMAL)

// ***************************
#define ACCESS_DOUBLE(ctype, access, itype) \
    ACCESS_START(ctype, Node *, itype); \
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
	    Node *tmp = link_node(from); \
	    if(to != tmp) \
	    { \
	        unlink_node(to); \
	        to = tmp; \
	    } \
	}

// ***************************
#define LINK_ARG(to, from) \
    Node *to = link_node(from)

#endif
