/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPES_H
#define TYPES_H
#include "global.h"

enum {
	NULL_TYPE,
	ERROR,
	TYPE,
	LIST,
	ARRAY,
	MAP,
	SYMBOL,
	FUNCTION,
	SPECIAL,
	LAMBDA,
	STRING,
	INT,
	TYPES_SIZE
};

#define TYPES int

// #define DEBUG_ALLOC

#ifndef DEBUG_ALLOC
#define NODE \
	TYPES   type; \
	long    occurences
#else
#define NODE \
	TYPES   type; \
	long    occurences; \
	node    *previous_node; \
	node    *next_node
#endif

/*
	Struct of a base node
*/
typedef struct {
	NODE;
} node;

// public functions for types
TYPES       get_type(node *node);
bool        typep(node *node, TYPES type);
char        *get_type_name(TYPES type);
int         init_types();

// public function for nopdes
bool     nullp(node *node);
node        *link_node(node *node);
node        *unlink_node(node *node);
bool        equals_node(node *node1, node *node2);
bool        free_node(node *node);
int         cmp_node(node *node1, node *node2);
bool        comparablep(node *node1, node *node2);
node        *init_node(node *node, TYPES type);
node        *create_node(TYPES type);

// DEBUG_ALLOC functions
bool        init_node_list();

#endif
