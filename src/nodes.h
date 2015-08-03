/****
	Types

	Lambda Calculus Workshop
	C version
	Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#define bool int
#define FALSE 0
#define TRUE (!FALSE)

/*
	Errors and assertions
*/
extern struct Node *error_node;
void ERROR(char *fmt, ...);

#define ABORT(fmt, ...) \
	{ \
		ERROR(fmt, ##__VA_ARGS__); \
		return NULL; \
	}

#define ASSERT(cond, fmt, ...) \
	if(!(cond)) \
	{ \
		ERROR(fmt, ##__VA_ARGS__); \
		return NULL; \
	}

#define ASSERT_TYPE(node, typ, fmt, ...) \
	if(!(node && (node->type & (typ)))) \
	{ \
		ERROR(fmt, ##__VA_ARGS__); \
		return NULL; \
	}

/*
	type of nodes
*/
typedef enum
{
	NIL_NODE    =   1,
	TRUE_NODE   =   1 << 2,
	FALSE_NODE  =   1 << 3,
	SYMBOL      =   1 << 4,
	KEYWORD     =   1 << 5,
	INTEGER     =   1 << 6,
	DECIMAL     =   1 << 7,
	STRING      =   1 << 8,
	LIST        =   1 << 9,
	ARRAY       =   1 << 10,
	MAP         =   1 << 11,
	SET         =   1 << 12,
	SEQ         =   1 << 13,
	ENVIRONMENT =   1 << 14,
	FUNCTION    =   1 << 15,
	LAMBDA      =   1 << 16,
	ATOM        =   1 << 17,
	READER      =   1 << 18,
	KEYVAL      =   1 << 19,
	INVALID     =   20
} NodeType;

/*
	String representation of types
*/
extern char *str_types[];

/*
	Define in case of allocation debugging
*/
#define DEBUG_ALLOC

/*
	Used type definitions
*/
#define Integer long
#define Decimal double
#define String  char *
struct  Node; // forward

/*
	Environment
*/
typedef struct Env
{
	struct Node     *previous; // Environment
	struct Node     *binds;    // Map
} Env;

/*
	Collection : Array, List, Map and Set
*/
typedef struct
{
	bool            mutable;
	long            size;
	long            max;
	struct Node     **nodes;
} Collection;

typedef struct
{
	long            index;
	struct Node     *coll;
} Seq;

/*
	Key/Values binding
*/
typedef struct
{
	struct Node     *key;
	struct Node     *value;
} KeyValue;

/*
	Reader
*/
typedef struct
{
	FILE            *handle;
} Reader;

/*
	Lambda functions
*/
typedef struct
{
	struct Node *(*eval)(struct Node *args, Env *env);
	bool        is_macro;
	struct Node *args;
	struct Node *body;
	struct Node *closure;
} Lambda;

/*
	Compiled functions
*/
typedef struct
{
	struct Node *(*eval)(struct Node *args, Env *env);
	bool                is_macro;
	int                 nb_args;
	union
	{
        struct Node     *(*f0) ();
        struct Node     *(*f1) (struct Node*);
        struct Node     *(*f2) (struct Node*,struct Node*);
        struct Node     *(*f3) (struct Node*,struct Node*,struct Node*);
        struct Node     *(*f4) (struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f5) (struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f6) (struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f7) (struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*);
        struct Node     *(*f8) (struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*);
        struct Node     *(*f9) (struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*);
        struct Node     *(*f10)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f11)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f12)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f13)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*);
        struct Node     *(*f14)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*);
        struct Node     *(*f15)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*);
        struct Node     *(*f16)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f17)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f18)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*);
        struct Node     *(*f19)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*);
        struct Node     *(*f20)(struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,struct Node*,
                                struct Node*,struct Node*);
	} func;
} Function;

/*
	Struct of a base node
*/
typedef struct Node
{
	NodeType        type;
	long            occurences;
#ifdef DEBUG_ALLOC
	struct Node     *previous_node;
	struct Node     *next_node;
#endif
	union
	{
		Integer     integer;
		Decimal     decimal;
		String      string;
		Collection  *coll;
		KeyValue    *keyval;
		Lambda      *lambda;
		Function    *function;
		Env         *env;
		struct Node *atom;
		Reader      *reader;
	} val;
} Node;

// global values
extern Node *nil_node;
extern Node *true_node;
extern Node *false_node;

// public function for types
String      str_type(NodeType type);

// public function for nodes
Node        *link_node(Node *node);
Node        *unlink_node(Node *node);
Node        *new_node(NodeType type);
Node        *free_node(Node *node);
Node        *string_node(Node *node);

// Integer
Node        *new_integer(Integer value);
Integer     get_integer(Node *node);
bool        integerp(Node *node);
Node        *string_integer(Node *node); // internal

// Decimal
Node        *new_decimal(Decimal value);
Decimal     get_decimal(Node *node);
bool        decimalp(Node *node);
Node        *string_decimal(Node *node); // internal

// Strings, symbols, keywords
Node        *new_string(char *value);
Node        *new_string_allocate(char *value);
Node        *new_symbol(char *value);
Node        *new_keyword(char *value);
Node        *sprintf_string(char *fmt, ...);
bool        stringp(Node *node);
bool        symbolp(Node *node);
bool        keywordp(Node *node);
String      get_string(Node *string);
String      get_formated_string(Node *string);
Node        *free_string(Node *string); // internal
Node        *string_string(Node *string); // internal

// Function
Node        *free_function(Node *func); // internal
Node        *string_function(Node *func); // internal

// Lambda
Node        *free_lambda(Node *node); // internal
Node        *string_lambda(Node *node); // internal

// Collections
Node        *free_coll(Node *coll); // internal
Node        *string_coll(Node *coll); // internal
long        size_coll(Node *coll);
Node        *first_coll(Node *coll);
Node        *last_coll(Node *coll);
Node        *take_coll(Node *coll);
Node        *malloc_clone_coll(Node *coll, long diff);
Node        *malloc_coll(Node *coll, long diff);
Node        *realloc_coll(Node *coll, long diff);
Node        *assoc(Node *map, Node *keyval);
Node        *dissoc(Node *map, Node *keyval);
Node        *nth(Node *coll, long index);
Node        *push(Node *coll, Node *elem);
Node        *sort(Node coll);
long        pos_coll(Node *coll, Node *search);
Node        *reduce_coll(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *map_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map2_coll(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *new_empty_coll(long alloc, NodeType type);

// Keyval
Node        *free_keyval(Node *node); // internal
Node        *string_keyval(Node *node); // internal

// Env
Node        *free_env(Node *node); // internal
Node        *string_env(Node *node); // internal

// Reader
Node        *free_reader(Node *node); // internal
Node        *string_reader(Node *node); // internal

// Reader
Node        *free_atom(Node *node); // internal
Node        *string_atom(Node *node); // internal

// DEBUG_ALLOC functions
bool        init_node_list();
void        print_node_list();

#endif
