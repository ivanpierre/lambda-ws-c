/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef TYPES_H
#define TYPES_H

#define error(message) \
	fprintf(stderr, message)

#define bool int
#define FALSE 0
#define TRUE (!FALSE)
#define NIL NULL
enum
{
	NIL,        1
	TRUE,       2
	FALSE,      4
	TYPE,       8
	SYMBOL,     16
	INTEGER,    32
	FLOAT,      64
	STRING,     128
	LIST,       256
	ARRAY,      512
	MAP,        1024
	ENVIRONMENT,2048
	FUNCTION,   4096
	LAMBDA,     8192
	TYPES_SIZE  100000
};

#define TYPES int

#define DEBUG_ALLOC

#ifndef DEBUG_ALLOC
#define NODE \
	TYPES   type; \
	long    occurences
#else
#define NODE \
	TYPES   type; \
	long    occurences; \
	Node    *previous_node; \
	Node    *next_node
#endif

/*
	Struct of a base node
*/
typedef struct node
{
	NODE;
} node;

// public functions for types
TYPES       get_type(Node *node);
Node        *typep(Node *node, TYPES type);
Node        *get_type_details(TYPES type);
Node        *get_type_name(TYPES type);
Node        *init_types();
Node        *set_type(TYPES type, Node *type_def);
Node        *create_type(	char    *name,
							long    size,
							Node    *(*equals)(Node *node1, Node *node2),
							Node    *(*cmp)(Node *node1, Node *node2),
							Node    *(*eval)(Node *node),
							Node    *(*free)(Node *node),
							Node    *(*print)(Node *node));

// public function for nodes
Node        *nullp(Node *node);
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
Node        *truep(Node *node);
Node        *true_node();
Node        *false_node();

// DEBUG_ALLOC functions
Node        *init_node_list();
Node        *print_node_list();

#endif
