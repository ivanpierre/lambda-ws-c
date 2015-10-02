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
    #define NEW_CONST {NULL, 0l}
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
	node->occurrences = 1; // will be decremented on valid creation
#ifdef DEBUG_ALLOC
	if (!last_node)
	{
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	}
	else
	{
		node->previous_node  = NULL;
		node->next_node      = first_node;
		first_node->previous_node = node;
		first_node = node;
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
	// TRACE("fait nouveau node %s", str_type(type));
	Node *node = NULL;
	node = malloc(sizeof(Node) + size_type(type));
	ASSERT(init_node(node, type), ERR_INIT, str_type(type));
	return node;

	error_assert:
	unlink_node(node);
	return NULL;
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
	Node *res = NULL;

	ASSERT_NODE(init, tmp_init, INODES);

	// Last previous result is init
	ASSIGN(res, tmp_init);

	// We will trampoline on function call values. fun(res) -> res,
	// with unlink on previous res
	va_start(funp, tmp_init);
	while ((func = va_arg(funp, void *(*)(Node *arg))))
	{
		ASSIGN(res, (*func)(res));
		ASSERT(res, ERR_INIT);
	}

	unlink_node(tmp_init);
	return res;

	//****************
	error_assert:
	unlink_node(tmp_init);
	unlink_node(res);
	return NULL;
}

/*
    Test falsey
*/
bool FALSE_Q_(Node *node)
{
	ASSERT_NODE(node, tmp_node, INODES);
	bool res =  node == NIL ||
				node == FALSE;
	unlink_node(tmp_node);
	return res;

	//****************
	error_assert:
	unlink_node(tmp_node);
	return BOOL_FALSE;
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
	ASSERT_NODE(node, tmp_node, INODES);
	bool res = !FALSE_Q_(node);
	unlink_node(tmp_node);
	return res;

	//****************
	error_assert:
	unlink_node(tmp_node);
	return BOOL_FALSE;
}

/*
    Test falsey
*/
Node *false_Q_(Node *node)
{
	ASSERT_NODE(node, INODES);
	Node *res = FALSE_Q_(node) ? TRUE : FALSE;
	unlink_node(node);
	return res;

	//****************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
    Test truthey
*/
Node *true_Q_(Node *node)
{
	ASSERT_NODE(node, INODES);
	Node *res = TRUE_Q_(node) ? TRUE : FALSE;
	unlink_node(node);
	return res;

	//****************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
 * Get type Node isa
 */
bool node_isa_type(Node *node, TYPE isa)
{
	bool res = node->type->bin_type & get_type(isa)->bin_type &&
	           node->type->bin_type <= get_type(isa)->bin_type;
	return res;

	//****************
	error_assert:
	return BOOL_FALSE;
}
