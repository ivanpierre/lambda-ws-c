/****
    Nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "nodes.h"
#include "strings.h"
#include "free.h"
#include "writer.h"

#ifdef DEBUG_ALLOC
#define NEW_CONST {NULL, 0l, NULL, NULL}
#else
    #define NEW_CONST {type, 0l}
#endif

// global values
static Node nil_val   = NEW_CONST;
static Node true_val  = NEW_CONST;
static Node false_val = NEW_CONST;
Node        *NIL      = &nil_val;
Node        *FALSE    = &false_val;
Node        *TRUE     = &true_val;

/*
    First initialisation of an allocated node, first link to the data segment
    Return linked node or NIL
*/
static Node *init_node(Node *node, enum TYPE type)
{
	ASSERT(node, ERR_NULL_PTR);
	node->type        = type;
	node->occurrences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
	if (!last_node)
	{
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	}
	else
	{
		node->previous_node  = last_node;
		node->next_node      = NULL;
		last_node->next_node = node;
		last_node = node;
	}
#endif
	return node;

	error_assert:
	return NULL;
}

/*
    Create a node
    Constructor, return linked
*/
bool new_node(TYPE type_of_node)
{
	TRACE("fait nouveau node %s %ld", str_type(type_of_node), type_of_node);

	Node *node = malloc(sizeof(Node) + size_type(type_of_node));
	ASSERT_NODE(node, type_of_node);

	ASSERT(init_node(node, type_of_node), ERR_INIT, str_type(type_of_node);

	TRACE("Node %s créé", str_type(type_of_node));
	return node;

	error_assert:
	unlink_node(&node);
	*var = NULL;
	return BOOL_FALSE;

	error_assert:

}

/*
     Compose functions on an initial value
     All initial and intermediate values should be allocated linked Nodes*.
     At every state, the previous state is unlinked.
     Last value can be anything and should be considered as allocated
     Function list should finish with a NULL, else.... :D
*/
void *THREAD_NODE(void **var, Node *init, ...)
{
	bool        (*func)(void **node, Node *arg) = NULL;
	va_list funp;

	if (var)
		unlink_node(*var);
	ASSERT(link_node(var, init), ERR_INIT);

	va_start(funp, init);
	while ((func = va_arg(funp, void *(*)(void **var, Node *arg))))
		ASSERT((*func)(var, *res), ERR_INIT);

	return BOOL_TRUE;

	error_assert:
	unlink_node(var);
	return BOOL_FALSE;
}

/*
    Test falsey
*/
bool FALSE_Q_(Node *node)
{
	return node->type == INIL || node->type == IFALSE;
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
	return !FALSE(node);
}

/*
    Test falsey
*/
bool false_Q_(Node **var, Node *node)
{
	Node *arg = NULL;
	link_node(&arg, node);
	if (*var)
		unlink_node(*var);

	*var = (arg->type == NIL || arg->type == IFALSE) ? TRUE : NIL;
	unlink_node(&arg);
	return BOOL_TRUE;
}

/*
    Test truthey
*/
bool true_Q_(Node *node)
{
	Node *arg = NULL;
	link_node(&arg, node);
	if (*var)
		unlink_node(*var);

	*var = (arg->type == NIL || arg->type == IFALSE) ? NIL : TRUE;
	unlink_node(&arg);
	return BOOL_TRUE;
}

/*
 * Get type Node isa
 */
bool node_isa_type(Node *node, TYPE isa)
{
	return node_ > type->bin_type & get_type(isa)->bin_type && node->type->bin_type <= get_type(isa)->bin_type;
}

