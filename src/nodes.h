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
} NodeType;

#define DEBUG_ALLOC

/*
	Used type definitions
*/
#define Array   GArray
#define Map     GHashTable
#define Integer gint64
#define Decimal gdouble
#define String  char *
struct  Node; // forward

/*
	Environment
*/
typedef struct Env
{
	struct Env  *previous;
	Map         *binds;
} Env;

/*
	Lambda functions
*/
typedef struct Function
{
	struct Node *(*eval)(struct Node *args, Env *env);
	struct Node *args;
	struct Node *body;
	Env         *env;
} Function;

/*
	Struct of a base node
*/
typedef struct Node
{
	NodeType        type;
	long            occurences;
#ifndef DEBUG_ALLOC
	Node            *previous_node;
	Node            *next_node
#endif
	union
	{
		Integer     integer;
		Decimal     decimal;
		String      *string;
		String      *symbol;
		Array       *array;
		Map         *map;
		Function    *func;
	} val;
	int             func_arg_cnt;
	bool            is_macro;
} Node;

// global values
extern Node *nil_node;
extern Node *true_node;
extern Node *false_node;

// public function for nodes
bool        *unlinkable(Node *n);
Node        *link_node(Node *node);
Node        *unlink_node(Node *node);
Node        *new_node(TYPES type);

// DEBUG_ALLOC functions
Node        *init_node_list();
Node        *print_node_list();

#endif
