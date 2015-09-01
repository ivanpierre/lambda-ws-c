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
static Node *init_node(Node *node, TYPE type)
{
	ASSERT(node, ERR_NULL_PTR);
	node->type        = get_type(type);
	node->occurrences = 1; // will be incremented on link
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
Node *new_node(TYPE type)
{
	TRACE("fait nouveau node %s %ld", str_type(type), type);

	Node *node = malloc(sizeof(Node) + size_type(type));
	ASSERT(init_node(node, type), ERR_INIT, str_type(type));

	TRACE("Node %s créé", str_type(type));
	return node;

	error_assert:
	unlink_node(&node);
	return node;
}

/*
     Compose functions on an initial value
     All initial and intermediate values should be allocated linked Nodes*.
     At every state, the previous state is unlinked.
     Last value can be anything and should be considered as allocated
     Function list should finish with a NULL, else.... :D
*/
void *THREAD_NODE(Node *init, ...)
{
	void *(*func)(Node *arg) = NULL;
	va_list funp;
	Node *node = NULL;

	link_node(&node, init);
	unlink_node(&init);
	ASSERT(node, ERR_INIT);

	va_start(funp, init);
	while ((func = va_arg(funp, void *(*)(Node *arg))))
	{
		Node *res = (*func)(node);
		link_node(&node, res);
		unlink_node(&res);
		ASSERT(node, ERR_INIT);
	}

	return node;

	error_assert:
	unlink_node(&node);
	unlink_node(&init);
	return node;
}

/*
    Test falsey
*/
bool FALSE_Q_(Node *node)
{
	bool res =  node == NIL ||
				node == FALSE;
	unlink_node(&node);
	return res;
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
	bool res = !FALSE_Q_(node);
	unlink_node(&node);
	return res;
}

/*
    Test falsey
*/
Node *false_Q_(Node *node)
{
	return FALSE_Q_(node) ? TRUE : FALSE;
}

/*
    Test truthey
*/
Node *true_Q_(Node *node)
{
	return TRUE_Q_(node) ? TRUE : FALSE;
}

/*
 * Get type Node isa
 */
bool node_isa_type(Node *node, TYPE isa)
{
	return node->type->bin_type & get_type(isa)->bin_type &&
			node->type->bin_type <= get_type(isa)->bin_type;
}

void *STRUCT(Node *node)
{
	return ((char *)node) + sizeof(Node);
}
