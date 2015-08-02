/****
	Nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h""


#if defined(DEBUG_ALLOC)
	/*
		double linked list of nodes
	*/
	Node *first_node    = NULL;
	Node *last_node     = NULL;

	// global values
	Node *nil_node = {NIL_NODE, 0, NULL, NULL, {0};
	Node *true_node = {TRUE_NODE, 0, NULL, NULL, {0};
	Node *false_node = {FALSE_NODE, 0, NULL, NULL, {0};
#else
	Node *nil_node = {NIL_NODE, 0, {0};
	Node *true_node = {TRUE_NODE, 0, {0};
	Node *false_node = {FALSE_NODE, 0, {0};
#endif

// Error signal
Node *error_node = NULL;

/*
	test if linking is applyable
*/
bool unlinkable(Node *n)
{
	return node && node->type & (NIL_NODE || TRUE_NODE || FALSE_NODE);
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
		if(node-occurence)
			node->occurences--;
		if(!node->occurences)
			free_node(node);
	}
	return NULL;
}

/*
	Create a node
	Constructor, return linked
*/
Node *create_node(TYPES type_of_node)
{
	type *node_type = (type *)get_type_details(type_of_node); // linked
	long size;
	if(!node_type)
		return NIL;

	size = node_type->size;
	node_type = unlink_node(node_type); // unlink

	Node *new = malloc(size);
	Node *tmp = new;

	if(!new)
	{
		error("create_node : Error : allocation of node\n");
		return NIL;
	}
	new = init_node(new, type_of_node); // init_node does link
	if(nullp(new))
	{
		free(tmp); //
		error("create_node : Error : initialisation of node\n");
	}

	return new;
}

/*
	First initialisation of an allocated node, first link to the data segment
	Return linked node or NIL
*/
static Node *init_node(Node *node, TYPES type)
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
    	    free_array(node->array);
    	    break;

    	case ENVIRONMENT :
    	    free_env(node->env);
    	    break;

    	case FUNCTION :
    	    free_function(node->function);
    	    break;

    	case LAMBDA :
    	    free_lambda(node->lambda);
    	    break;

    	case ATOM :
    	    free_node(node->atom);
			break;

    	case READER :
    	    free_node(node->atom);
			break;

		case INTEGER :
		case DECIMAL :
		default :
	}

	free(node);
	return NULL;
}
