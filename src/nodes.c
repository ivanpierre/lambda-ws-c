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
	Node *first_node    = NULL;
	Node *last_node     = NULL;
#endif

/*
	test if linking is applyable
*/
Node *unlinkable(Node *n)
{
	return node->type & (NIL_NODE || TRUE_NODE || FALSE_NODE);
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
	)
	return NIL;
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

	if(nullp(new))
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
	if(nullp(last_node))
	{
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	}
	else
	{
		node->previous_node = last_node;
		node->next_node = NULL;
		last_node->next_node = node;
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
