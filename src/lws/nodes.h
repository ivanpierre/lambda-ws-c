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
#define DEBUG_FREE

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
	Type        *type;
	long        occurrences;
#ifdef DEBUG_FREE
	char        *printable_version;
#endif
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

#define BOOL(val) val ? TRUE : FALSE

// ***************************
#define ACCESS_START(ctype, rtype, IType) \
Node *tmp_node = NULL; \
rtype res; \
 \
ASSERT_NODE(node, tmp_node, ITYPE); \
 \
ctype *str = STRUCT(tmp_node)

// ***************************
#define ACCESS_END(OType) \
unlink_node(&tmp_node); \
 \
if (!res) \
	res = NIL; \
if (res != NIL) \
	ASSERT_TYPE(res, OType); \
 \
return unlink_new(res); \
 \
error_assert: \
unlink_node(&tmp_node); \
return NULL

// ***************************
#define ACCESS_END_TYPED(OType) \
unlink_node(&tmp_node); \
 \
ASSERT_TYPE(res, OType); \
 \
return res; \
 \
error_assert: \
unlink_node(&tmp_node); \
return NULL

// ***************************
#define ACCESS_END_UNTYPED() \
unlink_node(&tmp_node); \
return res; \
 \
error_assert: \
unlink_node(&tmp_node); \
return res

// ***************************
#define ACCESS_NODE(ctype, access, IType, OType) \
ACCESS_START(ctype, Node *, IType); \
link_node(&res, str->access); \
ACCESS_END(OType)

// ***************************
#define ACCESS_BOOL(ctype, access, IType) \
ACCESS_START(ctype, Node *, IType); \
res = BOOL(str->access ); \
ACCESS_END_TYPED(IBOOLEAN)

// ***************************
#define ACCESS_INTEGER(ctype, access, IType) \
ACCESS_START(ctype, Node *, IType); \
res = integer(str->access); \
ACCESS_END_TYPED(IINTEGER)

// ***************************
#define ACCESS_DECIMAL(ctype, access, IType) \
ACCESS_START(ctype, Node *, IType); \
res = decimal(str->access); \
ACCESS_END_TYPED(IDECIMAL)

// ***************************
#define ACCESS_PTR(ctype, access, itype) \
ACCESS_START(ctype, void *, itype); \
res = str->access; \
ACCESS_END_UNTYPED()

// ***************************
#define ACCESS_STR(ctype, access, IType) \
ACCESS_START(ctype, char *, IType); \
res = strdup(str->access); \
ACCESS_END_UNTYPED()

#define LINK_NODE(to, from) \


#endif
