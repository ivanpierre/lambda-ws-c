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
    Init base node content allocated
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
    Allocate a static node
    Constructor, return linked
	It should be unlink_new() by constructor
*/
Node *new_node(TYPE type)
{
	// TRACE("fait nouveau node %s", str_type(type));
	Node *node = NULL;
	node = malloc(sizeof(Node) + size_type(type));

	// Init base node content
	ASSERT(init_node(node, type), ERR_INIT, str_type(type));
	return node;

	//**************
	error_assert:
	unlink_node(node);
	return NULL;
}

/*
    Allocate a dynamic node, i.e. a String 
    Constructor, return linked
	It should be unlink_new() by constructor
*/
Node *new_dynamic_node(TYPE type, size_t size)
{
	// TRACE("fait nouveau node %s", str_type(type));
	Node *node = NULL;
	node = malloc(sizeof(Node) + size);

	// Init base node content
	ASSERT(init_node(node, type), ERR_INIT, str_type(type));
	return node;

	//**************
	error_assert:
	unlink_node(node);
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
	for(i = 0; i < nb; i++)
	{
		Node *arg = va_arg(args, Node *);
		if(arg)
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
	for(i = 0; i < nb; i++)
	{
		Node *arg = va_arg(args, Node *);
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
