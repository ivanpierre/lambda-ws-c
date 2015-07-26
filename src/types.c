/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/*
	Node of type TYPE
*/
typedef struct {
	NODE;
	long    size;
	boolean (*equals)(node *node1, node *node2);
	int     (*cmp)(node *node1, node *node2);
	node    *(*eval)(node *node);
	void    (*free)(node *node);
	void    (*print)(node *node);
} type;

/*
	Array of types definition
*/
type   *types[TYPES_SIZE];

/*
	create a link to node
*/
node *link_node(node *node) {
	if(!node)
		return NULL;
	node->occurences++;
	return node;
}

/*
	Unlink node
*/
node *unlink_node(node *node) {
	if(!node)
		return NULL;
	node->occurences--;
	if(!node->occurences)
		free(node);
	return NULL;
}

/*
	return type of node
*/
TYPES get_type(node *node)
{
	if(nullp(node))
		return NULL_TYPE;
	return node->type;
}

static type *get_type_details(TYPES type) {
	return types[type];
}

/*
	Create a node
*/
node *create_node(TYPES type_of_node) {
	type *node_type = get_type_details(type_of_node);
	long size = node_type->size;
	node *new = malloc(size);

	new = init_node(new, type_of_node);
	if(nullp(new)) {
		error("create_node : Error : allocation of node");
	}

	return new;
}

/*
	Create a type node
*/
static type *create_type_type(	long    size,
								boolean (*equals)(node *node1, node *node2),
								int     (*cmp)(node *node1, node *node2),
								node    *(*eval)(node *node),
								void    (*free)(node *node),
								void    (*print)(node *node)) {
	type *new_type;
	node *new = malloc(sizeof(type));

	new = init_node(new, TYPE);
	if(nullp(new)) {
		error("create_node : Error : allocation of node");
		return NULL;
	}

	new_type = (type *)new;
	new_type->size = size;
	new_type->equals = equals;
	new_type->cmp = cmp;
	new_type->eval = eval;
	new_type->free = free;
	new_type->print = print;
	return new_type;
}

boolean equals(node *node1, node *node2) {
	if(node1 == node2)
		return TRUE;

	if(nullp(node1) || nullp(node2))
		return FALSE;

	if(node1->type != node2->type)
		return FALSE;

	type *type = get_type_details(node1->type);
	if(!type->equals)
		return FALSE;
	return type->equals(node1, node2);
}

boolean comparablep(node *node1, node *node2) {
	if(nullp(node1) || nullp(node2))
		return FALSE;

	if(node1->type != node2->type)
		return FALSE;

	type *type = get_type_details(node1->type);
	if(!type->equals)
		return FALSE;

	return TRUE;
}

/*
	Type of node
*/
TYPES get_node_type(node *node)
{
	return node->type;
}

/*
	Test type of node
*/
boolean typep(node *node, TYPES type)
{
	return get_node_type(node) == TYPE;
}

/*
    Is node NULL
*/
boolean nullp(node *node)
{
	return !node;
}

node *init_node(node *node, TYPES type) {
	if(nullp(node)) {
		error("init_node : absent node\n");
		return NULL;
	}
	node->type = type;
	node->occurences = 0;
#ifdef DEBUG_ALLOC
#endif
	return link_node(node);
}

/*
	init type TYPE
*/
boolean init_types()
{
	types[TYPE] = create_type_type(sizeof(type), NULL, NULL, NULL, NULL, NULL);
	return TRUE;
}

