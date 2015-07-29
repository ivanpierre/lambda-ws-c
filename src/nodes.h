/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#define error(message, ...) \
	fprintf(stderr, message, ...)

#define bool int
#define FALSE 0
#define TRUE (!FALSE)

enum
{
	NIL_NODE,   1
	TRUE_NODE,  2
	FALSE_NODE, 4
	SYMBOL,     8
	INTEGER,    16
	FLOAT,      32
	STRING,     64
	LIST,       128
	ARRAY,      256
	MAP,        512
	ENVIRONMENT,1024
	FUNCTION,   2048
	LAMBDA,     4096
	TYPES_SIZE  100000
};

#define TYPES int

#define DEBUG_ALLOC

/*
	Struct of a base node
*/
typedef struct Node
{
	TYPES   type; \
	long    occurences; \
#ifndef DEBUG_ALLOC
	Node    *previous_node; \
	Node    *next_node
#endif
	union
	{
		long        integer;
		float       decimal;
		char        *string;
		char        *symbol;
		GArray      *array;
		GHashTable  *map;

	} val;
} Node;

// global values
extern Node *nil_node;
extern Node *true_node;
extern Node *false_node;



// public functions for types
// public function for nodes
Node        *nullp(Node *node);
Node        *truep(Node *node);
Node        *falsep(Node *node);
Node        *link_node(Node *node);
Node        *unlink_node(Node *node);
Node        *equals_node(Node *node1, Node *node2);
Node        *free_node(Node *node);
Node        *cmp_node(Node *node1, Node *node2);
Node        *print_node(Node *node);
Node        *comparablep(Node *node1, Node *node2);
Node        *init_node(Node *node, TYPES type);
Node        *create_node(TYPES type);
Node        *unlinkable(Node *n);
Node        *falsep(Node *node);

// DEBUG_ALLOC functions
Node        *init_node_list();
Node        *print_node_list();

#endif
