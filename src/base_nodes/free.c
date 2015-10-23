/****
    Free manage memory free

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "free.h"
#include "writer.h"

/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
Object *first_node = NULL;
Object *last_node  = NULL;
#endif

/*
    test if linking is applicable
*/
static bool unlinkable(Object *node)
{
	return !node || node->type == CONST;
}

/*
    create a link to node
    Return Linked node
    Constant elements are not lonked
*/
Object *link_node(Object *node)
{
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

	//**************
	catch:
	return NULL;
}

/*
    Unlink node
    Return NULL on freeing else return node.
    Constant nodes are not unlinked
*/
Object *unlink_node(Object *node)
{
	if(!node && !unlinkable(node))
	{
#ifdef DEBUG_FREE
	TRACE("unlinking %s", node->type->str_type);
#endif
		if (node->occurrences)
			node->occurrences--;
		if (node->occurrences <= 0)
		{
#ifdef DEBUG_FREE
			TRACE("freeing %s", node->type->str_type);
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
			// unalloc node
			void (*free_node)(Object *node) = func_free_type(node->type);
			if(free_node)
				(*free_node)(node);
			else
				free(node);
			node = NULL;
		}
	}
	return node;

	//***************
	catch:
	return NULL;
}

/*
    Unlink new node
    Verify we are linked only once and put occurrence to 0
*/
Object *unlink_new(Object *node)
{
#ifdef DEBUG_FREE
	TRACE("unlinking new %s", node->type->str_type);
#endif
	if (!unlinkable(node))
	{
		ASSERT(node->occurrences == 1, ERR_NEW_BIND);
		node->occurrences--;
	}
	return node;

	//**************
	catch:
	return NULL;
}

/*
    completely unlink and init node list
*/
void init_node_list()
{
#ifdef DEBUG_ALLOC
	while (first_node)
	{
		Object *node = first_node;
		first_node = node->next_node;

		// force free
		node->occurrences = 1;
		unlink_node(node);
	}
	last_node = NULL;
#endif
}

/*
	Print current stack state
 */
void print_node_stack()
{
	TRACE("Stack trace");
	TRACE("-----------");
#ifdef DEBUG_ALLOC
	Object *walk = first_node;
	int i = 1;
	while (walk)
	{
		TRACE("%d) %s %ld %s", i++, str_type(walk->type),
								walk->occurrences, print(walk));
		walk = walk->next_node;
	}
#endif
	TRACE("-----------");
	fflush(stderr);
}
