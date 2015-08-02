/****
	Nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "nodes.h"


/*
	double linked list of nodes
*/
#if defined(DEBUG_ALLOC)
	Node *first_node    = NULL;
	Node *last_node     = NULL;
#endif

// global values
Node *nil_node = NULL;
Node *true_node = NULL;
Node *false_node = NULL;

// Error signal
Node *error_node = NULL;

// Error function
void ERROR( char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	error_node = sprintf_string(fmt, args);
}


/*
	test if linking is applyable
*/
bool unlinkable(Node *node)
{
	return node && node->type & (NIL_NODE | TRUE_NODE | FALSE_NODE);
}

/*
	create a link to node
	Return Linked node or NIL
*/
Node *link_node(Node *node)
{
	if(!unlinkable(node))
		node->occurences++;
	return node;
}

/*
	Unlink node
	return NIL or subsisting node
*/
Node *unlink_node(Node *node)
{
	if(!unlinkable(node))
	{
		if(node->occurences)
			node->occurences--;
		if(!node->occurences)
			free_node(node);
	}
	return NULL;
}

/*
	First initialisation of an allocated node, first link to the data segment
	Return linked node or NIL
*/
static Node *init_node(Node *node, NodeType type)
{
	node->type = type;
	node->occurences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
	if(!last_node)
	{
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	}
	else
	{
		node->previous_node = last_node;
		node->next_node = NULL;
		last_node->next_node = node;
		last_node = node;
	}
#endif
	return link_node(node);
}

/*
	Free all nodes according to type
*/
Node *free_node(Node *node)
{
	ASSERT(node, "free_node : NULL node");

	switch(node->type)
	{
		case NIL_NODE :
    	case TRUE_NODE :
    	case FALSE_NODE :
			return NULL;

    	case KEYWORD :
    	case SYMBOL :
    	case STRING :
    	    free_string(node);
    	    break;

    	case LIST :
    	case ARRAY :
    	case MAP :
    	case SET :
    	    free_collection(node);
    	    break;

    	case ENVIRONMENT :
    	    free_env(node);
    	    break;

    	case FUNCTION :
    	    free_function(node);
    	    break;

    	case LAMBDA :
    	    free_lambda(node);
    	    break;

    	case ATOM :
    	    free_node(node->val.atom);
    	    node->val.atom = NULL;
			break;

    	case READER :
    	    free_reader(node);
			break;

		case INTEGER :
		case DECIMAL :
		default :
			break;
	}

	free(node);
	return NULL;
}

/*
	return string version of nodes according to type
*/
Node *string_node(Node *node)
{
	ASSERT(node, "free_node : NULL node");

	switch(node->type)
	{
		case NIL_NODE :
			return sprintf_string("nil");

    	case TRUE_NODE :
			return sprintf_string("true");

    	case FALSE_NODE :
			return sprintf_string("strue");

    	case KEYWORD :
    	case SYMBOL :
    	case STRING :
    	    return string_string(node);

    	case LIST :
    	case ARRAY :
    	case MAP :
    	case SET :
    	    return string_collection(node);

    	case ENVIRONMENT :
    	    return string_env(node);

    	case FUNCTION :
    	    return string_function(node);

    	case LAMBDA :
    	    return string_lambda(node);

    	case ATOM :
    	    return string_atom(node->val.atom);

    	case READER :
    	    return string_reader(node);

		case INTEGER :
			return string_integer(node);

		case DECIMAL :
			return string_decimal(node);

		default :
			break;
	}

	free(node);
	return NULL;
}

/*
	Create a node
	Constructor, return linked
*/
Node *new_node(NodeType type_of_node)
{
	Node *new = malloc(sizeof(Node));
	ASSERT(new, "create_node : Error : allocation of node\n");

	Node *tmp = new;
	new = init_node(new, type_of_node); // init_node does link
	if(!new)
	{
		free(tmp);
		ABORT("create_node : Error : initialisation of node\n");
	}

	return new;
}

/*
	completely unlink and init node list
*/
bool init_node_list()
{
#ifdef DEBUG_ALLOC
	while(first_node)
	{
		Node *node = first_node;
		first_node = node->next_node;

		// empty allocation
		while(node)
		    node = free_node(node);
	}
	last_node = NULL;
#else
#endif
	return TRUE;
}

