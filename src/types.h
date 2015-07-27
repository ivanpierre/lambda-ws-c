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
	TYPE,
	LIST,
	ARRAY,
	MAP,
	SYMBOL,
	FUNCTION,
	SPECIAL,
	LAMBDA,
	STRING,
	INTEGER,
	TRUE_NODE,
	FALSE_NODE,
	TYPES_SIZE
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
	void    *previous_node; \
	void    *next_node
#endif

/*
	Struct of a base node
*/
typedef struct
{
	NODE;
} node;

// public functions for types
TYPES       get_type(node *node);
bool        typep(node *node, TYPES type);
node        *get_type_details(TYPES type);
node        *get_type_name(TYPES type);
bool        init_types();
bool        set_type(TYPES type, node *type_def);
node        *create_type(	char    *name,
							long    size,
							node    *(*equals)(node *node1, node *node2),
							node    *(*cmp)(node *node1, node *node2),
							node    *(*eval)(node *node),
							node    *(*free)(node *node),
							node    *(*print)(node *node));

// public function for nodes
bool        nullp(node *node);
node        *link_node(node *node);
node        *unlink_node(node *node);
node        *equals_node(node *node1, node *node2);
node        *free_node(node *node);
int         cmp_node(node *node1, node *node2);
node        *print_node(node *node);
bool        comparablep(node *node1, node *node2);
node        *init_node(node *node, TYPES type);
node        *create_node(TYPES type);
bool        falsep(node *node);
bool        truep(node *node);
node        *true_node();
node        *false_node();

// DEBUG_ALLOC functions
bool        init_node_list();
bool        print_node_list();

#endif
