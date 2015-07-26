/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#if defined(DEBUG_ALLOC)
	node *first_node    = NULL;
	node *last_node     = NULL;
#endif

/*
	Node of type TYPE
*/
typedef struct {
	NODE;
	char    *name;
	long    size;
	bool    (*equals)(node *node1, node *node2);
	int     (*cmp)(node *node1, node *node2);
	node    *(*eval)(node *node);
	void    (*free)(node *node);
	void    (*print)(node *node);
} type;

/*
	Array of types definition
*/
node *types[TYPES_SIZE];

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
		free_node(node);
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

node *get_type_details(TYPES type) {
	if(type >= TYPES_SIZE || type < 0) {
		error("get_type_details : invalid type\n");
		return NULL;
	}
	return types[type];
}

/*
	get the type name from the type value
*/
char *get_type_name(TYPES type_enum) {
	node *type_det = get_type_details(type_enum);

	if(nullp(type_det)) {
		error("get_type_name : invalid type\n");
		return "Bad type";
	}
	return ((type*)type_det)->name;
}

/*
	get the type name from the node
*/
char *get_node_type_name(node *node) {
	return get_type_name(node->type);
}

/*
	Create a node
*/
node *create_node(TYPES type_of_node) {
	type *node_type = (type *)get_type_details(type_of_node);
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
node *create_type(	char    *name,
			long    size,
			bool    (*equals)(node *node1, node *node2),
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
	new_type->name = name;
	new_type->size = size;
	new_type->equals = equals;
	new_type->cmp = cmp;
	new_type->eval = eval;
	new_type->free = free;
	new_type->print = print;
	return new;
}

/*
	Are nodes equals ?
*/
bool equals_node(node *node1, node *node2) {
	if(node1 == node2)
		return TRUE;

	if(nullp(node1) || nullp(node2))
		return FALSE;

	if(node1->type != node2->type)
		return FALSE;

	type *t = (type *)get_type_details(node1->type);
	if(!t->equals)
		return FALSE;
	return t->equals(node1, node2);
}

/*
	Compare nodes
*/
int cmp_node(node *node1, node *node2) {
	if(node1 == node2)
		return 0;

	if(nullp(node1) || nullp(node2)) {
		error("cmp_node : system error comparing with null\n");
		return -1;
	}

	if(node1->type != node2->type) {
        error("cmp_node : system error comparing different types\n");
        return -1;
    }

	type *t = (type *)get_type_details(node1->type);
	if(!t->cmp) {
        error("cmp_node : system error comparing uncomparables\n");
        return -1;
    }
	return (t->cmp(node1, node2));
}

/*
	Are nodes comparable ?
*/
bool comparablep(node *node1, node *node2) {
	if(nullp(node1) || nullp(node2))
		return FALSE;

	if(node1->type != node2->type)
		return FALSE;

	type *t = (type *)get_type_details(node1->type);
	if(!t->equals)
		return FALSE;

	return TRUE;
}

/*
	unalloc node
*/
bool free_node(node *node) {
	if(nullp(node)) {
		error("free_node : unallocation of a null pointer\n");
		return FALSE;
	}

	type *t = (type *)get_type_details(node->type);
	if(t->free)
		t->free(node);
	free(node);
	return TRUE;
}

/*
	print node
*/
void print_node(node *node) {
	if(nullp(node)) {
		fprintf(stdout, "nil");
		return;
	}

	type *t = (type *)get_type_details(node->type);
	if(!t->print){
		fprintf(stdout, "<%s>", get_node_type_name(node));
		return;
	}

	t->print(node);
}

/*
	print node
*/
void print_type(node *node) {
	fprintf(stdout, "<type %s >", ((type *)node)->name);
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
bool typep(node *node, TYPES type)
{
	return get_node_type(node) == TYPE;
}

/*
    Is node NULL
*/
bool nullp(node *node)
{
	return !node;
}

/*
	First initialisation of an allocated node, first link to the data segment
*/
node *init_node(node *node, TYPES type) {
	if(nullp(node)) {
		error("init_node : absent node\n");
		return NULL;
	}

	// DEBUG
	fprintf(stdout, "init node : ");
	print_node(node);
	fprintf(stdout, "\n");

	node->type = type;
	node->occurences = 0;
#ifdef DEBUG_ALLOC
	if(nullp(last_node)) {
		node->previous_node = node->next_node = NULL;
		last_node = first_node = node;
	} else {
		node->previous_node = last_node;
		node->next_node = NULL;
		last_node->next_node = node;
	}
#endif
	return link_node(node);
}

/*
	completely unaloc and init node list
*/
bool init_node_list() {
#ifdef DEBUG_ALLOC
	while(first_node) {
		node *node = first_node;
		first_node = node->next_node;
		free_node(node);
	}
	last_node = NULL;
#else
#endif
	return TRUE;
}

/*
	Print node list
*/
bool print_node_list() {
#ifdef DEBUG_ALLOC
	node *walk = first_node;
	while(walk) {
		print_node(walk);
		walk = walk->next_node;
	}
	return TRUE;
#else
	error("print_node_list : not in debug mode, no list to print\n");
	return FALSE;
#endif
}

/*
	init type TYPE, so the type exists in the types... ;)
*/
bool init_types()
{
	types[TYPE] = create_type( "type",
						sizeof(type),
						NULL,   // equals
						NULL,   // cmp
						NULL,   // eval
						NULL,   // free
						&print_type);  // print
	if(nullp((node *)types[TYPE])) {
		error("init_types : error creating type\n");
		return FALSE;
	}
	return TRUE;
}

