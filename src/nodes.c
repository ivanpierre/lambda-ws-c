/****
	Nodes

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h""
#include "string.h"

#if defined(DEBUG_ALLOC)
	Node *first_node    = NULL;
	Node *last_node     = NULL;
#endif

/*
	test if linking is applyable
*/
Node *unlinkable(Node *n)
{
	return nulp(node) || falsep(node) || truep(node);
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
	Are nodes equals ?
	Return linked result or NIL
*/
Node *equals_node(Node *node1, Node *node2)
{
	if(node1 == node2)
	{
		return link_node(node1);
	}

	if(nullp(node1) || nullp(node2))
		return NIL;

	if(node1->type != node2->type)
		return NIL;

	// t->equal will link or NIL
	return t->equals(node1, node2);
}

/*
	Compare nodes
	return linked integer od NIL
*/
Node *cmp_node(Node *node1, Node *node2)
{
	// exact identity
	if(node1 == node2)
		return make_integer(0);

	// get linked type or NIL
	type *t = comparablep(node1, node2);

	// no detail on type
	if(nullp(t))
	{
        error("cmp_node : system error, not comparable\n");
        return NIL;
    }

    // returned value is linked or NIL
    Node *res = t->cmp(node1, node2);
    t = unlink_node(t);
	return res;
}

/*
	Are nodes comparable ?
*/
Node *comparablep(Node *node1, Node *node2)
{
	if(nullp(node1) || nullp(node2))
		return NIL;

	if(node1->type != node2->type)
		return NIL;

	return t;
}

/*
	unalloc node
*/
Node *free_node(Node *node)
{
	if(nullp(node))
	{
		return NIL;
	}

	if(t->free)
		node = t->free(node);

	unlink_node(t);
	unlink_node(node);

	return NIL;
}

/*
	print node this one is public !!!!
*/
Node *print_node(Node *node)
{
	if(nullp(node))
	{
		return make_string_alloc("nil");
	}

	type *t = (type *)get_type_details(node->type);

	if(!t->print)
	{
		// Strings are strings, no change
		if(get_type(t) == STRING)
			return link_node(node);

		char *formatted;
		asprintf(&formatted, "<%s %ld>", get_node_type_name(node), node);
		return make_string(formatted); // string allocated by asprintf
	}

	// linked by the function
	return t->print(node);
}

/*
    Is node NULL
*/
Node *nullp(Node *node)
{
	return node ? NIL : true_node;
}

/*
	First initialisation of an allocated node, first link to the data segment
	Return linked node or NIL
*/
Node *init_node(Node *node, TYPES type)
{
	if(nullp(node))
	{
		error("init_node : absent node\n");
		return NIL;
	}

	// DEBUG
	fprintf(stdout, "init node : ");
	print_node(node);
	fprintf(stdout, "\n");

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

/*
	Print node list
*/
bool print_node_list()
{
#ifdef DEBUG_ALLOC
	Node *walk = first_node;
	fprintf(stdout, "Node list\n", formatted);
	while(walk)
	{
		char *formatted = print_node(walk);
		if(formatted)
		{
			fprintf(stdout, "%s\n", formatted);
			free(formatted);
		}
		else
		{
			error("print_node_list : cannot format the node");
		}
		walk = walk->next_node;
	}
	fprintf(stdout, "End of node list\n", formatted);
	return TRUE;
#else
	error("print_node_list : not in debug mode, no list to print\n");
	return FALSE;
#endif
}

