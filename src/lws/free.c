/****
    Free manage memory free

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "free.h"
#include "writer.h"
#include "strings.h"
#include "free_internal.h"

/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
Node *first_node = NULL;
Node *last_node  = NULL;
#endif


// Forward
static Node *FREE(Node *node);

/*
    test if linking is applicable
*/
static bool unlinkable(Node *node)
{
	return !node || node->type->bin_type & get_type(IUNLINKABLE)->bin_type;
}

/*
    create a link to node
    Return Linked node
    Constant elements are not lonked
*/
Node *link_node(Node *node)
{
	/*
	 * First we link value to tmpnode.
	 * If node is part of future unlinked variable, we have to save it :D
	 */
#ifdef DEBUG_FREE
	TRACE("linking %s", node->type->str_type);
#endif
	ASSERT(node, ERR_NODE);
	if (!unlinkable(node))
		node->occurrences++;


#ifdef DEBUG_FREE
	TRACE("linked %s", node->type->str_type);
#endif
	return node;

	error_assert:
	return NULL;
}

/*
    Unlink node
    Return NULL on freeing else return node.
    Constant nodes are not unlinked
*/
Node *unlink_node(Node *node)
{
	ASSERT(node, ERR_VAR);
	if(!node) return NULL;
#ifdef DEBUG_FREE
	TRACE("unlinking %s", node->type->str_type);
#endif
	if (!unlinkable(node))
	{
		if (node->occurrences)
			node->occurrences--;
		if (node->occurrences <= 0)
		{
#ifdef DEBUG_FREE
			TRACE("freeing %s", (*node)->type->str_type);
#endif
#ifdef DEBUG_ALLOC
			if (node->next_node == NULL && node->previous_node == NULL)
			{
				TRACE("unlink last node");
			}
			if (node == first_node && node == last_node)
				first_node = last_node = NULL;
			else if (first_node == node)
			{
				ASSERT(node->next_node, "Error in node memory management");
				first_node = node->next_node;
				first_node->previous_node = NULL;
			}
			else if (last_node == node)
			{
				ASSERT(node->previous_node, "Error in node memory management");
				last_node = node->previous_node;
				last_node->next_node = NULL;
			}
			else
			{
				ASSERT(node->next_node && node->previous_node, "Error in node memory management");
				node->next_node->previous_node = node->previous_node;
				node->previous_node->next_node = node->next_node;
			}
#endif
			FREE(node);
			node = NULL;
		}
	}
	return node;

	error_assert:
	return NULL;
}

/*
    Unlink new node
    Verify we are linked only once and put occurrence to 0
*/
Node *unlink_new(Node *node)
{
	ASSERT(node, ERR_NODE);
#ifdef DEBUG_FREE
	TRACE("unlinking new %s", node->type->str_type);
#endif
	if (!unlinkable(node))
	{
		if (node->occurrences)
			node->occurrences--;
		ASSERT(node->occurrences == 1, ERR_NEW_BIND);
		node->occurrences--;
	}
	return node;

	error_assert:
	return NULL;
}

/*
    Free all nodes according to type
*/
static Node *free_node(Node *node)
{
	ASSERT(node, ERR_VAR);
	if (!node) return NULL;
	switch (node->type->int_type)
	{
		case INIL :
		case ITRUE :
		case IFALSE :
			break;

		case IKEYWORD :
		case ISYMBOL :
			named_free(node);
	        break;

		case ISTRING :
			string_free(node);
	        break;

		case IENV_STACK :
			break;

		case IENVIRONMENT :
			environment_free(node);
	        break;

		case ILIST :
		case IARRAY :
		case IMAP :
		case ISET :
			collection_free(node);
	        break;

		case ISEQ :
			seq_free(node);
	        break;

		case IKEYVAL :
			keyval_free(node);
	        break;

		case IFUNCTION :
		case ILAMBDA :
			function_free(node);
	        break;


		case IVAR :
			// FREE(node->val.compl);
			break;

		case IREADER :
			reader_free(node);
	        break;

		case IWRITER :
			writer_free(node);
	        break;

		case IINTEGER :
		case IDECIMAL :
			number_free(node);
	        break;

		case IFRACTION :
		case IREF:
		case IAGENT:
		case IFUTURE:
		case INODES:
		case ICONS:
		case ILAZY:
		case INAMESPACE:
		case IAPI:
		case ITYPE:
			break;
		default:
			break;
	}
	return NULL;

	error_assert:
	return NULL;
}

/*
    def pointer for free
*/
Node *(*free_ptr)(Node *node) = &free_node;

/*
    FREE unalloc node using pointer
*/
static Node *FREE(Node *node)
{
	return (*free_ptr)(node);
}

/*
    completely unlink and init node list
*/
void init_node_list()
{
#ifdef DEBUG_ALLOC
	while (first_node)
	{
		Node *node = first_node;
		first_node = node->next_node;

		// empty allocation
		while (node)
		{
			Node *old = node;
			node = node->next_node;
			unlink_node(old);
		}
	}
	last_node = NULL;
#endif
}

/*
 * Print current stack state
 */
void print_node_stack()
{
	TRACE("Stack trace");
	TRACE("-----------");
#ifdef DEBUG_ALLOC
	Node *walk = first_node;
	int  i     = 1;
	while (walk)
	{
		TRACE("%d) %s %ld %s", i++, walk->type->str_type, walk->occurrences,
		//      "");
		      print(walk));
		walk = walk->next_node;
	}
#endif
	TRACE("-----------");
	fflush(stderr);
}

