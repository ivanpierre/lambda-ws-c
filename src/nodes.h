/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#include <glib.h>

#define error(message, ...) \
	fprintf(stderr, message, ...)

#define bool int
#define FALSE 0
#define TRUE (!FALSE)

/*
	Errors and assertions
*/
extern struct Node *error_node;
void ERROR(const char *fmt, ...);

#define ABORT(fmt, ...) \
	{ \
		ERROR(fmt, ##_VA_ARGS__); \
		return NULL; \
	}

#define ASSERT(cond, fmt, ...) \
	if(!(cond)) \
	{ \
		ERROR(fmt, ##_VA_ARGS__); \
		return NULL; \
	}

#define ASSERT_TYPE(node, type, fmt, ...) \
	if(!(node && node->type & (type))) \
	{ \
		ERROR(fmt, ##_VA_ARGS__); \
		return NULL; \
	}

/*
	type of nodes
*/
enum
{
	NIL_NODE    =   1,
	TRUE_NODE   =   1 << 2,
	FALSE_NODE  =   1 << 3,
	SYMBOL      =   1 << 4,
	INTEGER     =   1 << 5,
	FLOAT       =   1 << 6,
	STRING      =   1 << 7,
	LIST        =   1 << 8,
	ARRAY       =   1 << 9,
	MAP         =   1 << 10,
	SET         =   1 << 11,
	ENVIRONMENT =   1 << 12,
	FUNCTION    =   1 << 13,
	LAMBDA      =   1 << 14,
	ATOM        =   1 << 15.
	READER      =   1 << 16
} NodeType;

#define DEBUG_ALLOC

/*
	Used type definitions
*/
#define Array   GArray *
#define Map     GHashTable *
#define Integer gint64
#define Decimal gdouble
#define String  char *
struct  Node; // forward

/*
	Environment
*/
typedef struct Env_s
{
	struct Env_s    *previous;
	Map             binds;
} *Env;

/*
	Lambda functions
*/
typedef struct
{
	struct Node *(*eval)(struct Node *args, Env *env);
	bool        is_macro;
	struct Node *args;
	struct Node *body;
	Env         *env;
} *Function;

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
		String      string;
		Array       array;
		Map         map;
		Function    func;
		Env         env;
	} val;
	int             func_arg_cnt;
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

// Integer
Node        *new_integer(Integer value);
Integer     get_integer(Node *node);
bool        integerp(node *node;
Node        *string_integer(Node *node);

// Decimal
Node        *new_decimal(Decimal value);
Decimal     get_decimal(Node *node);
bool        decimalp(node *node);
Node        *string_decimal(Node *node)

// Strings, symbols, keywords
Node        *new_string(char *value);
Node        *new_string_allocate(char *value);
Node        *new_symbol(char *value);
Node        *new_keyword(char *value);
Node        *concat_string(Node *s, Node *add);
bool        stringp(Node *node);
bool        symbolp(Node *node);
bool        keywordp(Node *node);
String      get_string(Node *s);
Node        *free_string(Node *node);

// DEBUG_ALLOC functions
Node        *init_node_list();
Node        *print_node_list();

#endif
