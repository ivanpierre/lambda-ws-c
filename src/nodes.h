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
	KEYWORD     =   1 << 5,
	INTEGER     =   1 << 6,
	FLOAT       =   1 << 7,
	STRING      =   1 << 8,
	LIST        =   1 << 9,
	ARRAY       =   1 << 10,
	MAP         =   1 << 11,
	SET         =   1 << 12,
	ENVIRONMENT =   1 << 13,
	FUNCTION    =   1 << 14,
	LAMBDA      =   1 << 15,
	ATOM        =   1 << 16.
	READER      =   1 << 17
} NodeType;

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
} *Env;

/*
	Array
*/
typedef struct
{
	bool            mutable;
	long            size;
	struct Node     *Node;
} *Array;

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
} *Lambda;

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
} *Function;

/*
	Struct of a base node
*/
typedef struct Node
{
	NodeType        type;
	long            occurences;
#ifndef DEBUG_ALLOC
	struct Node     *previous_node;
	struct Node     *next_node
#endif
	union
	{
		Integer     integer;
		Decimal     decimal;
		String      string;
		Array       array;
		Lambda      lambda;
		Function    function;
		Env         env;
		struct Node *atom;
	} val;
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
Node        *free_node(Node *node);

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
String      get_formated_string(Node *s);
Node        *free_string(Node *node);
Node        *string_string(Node *node);


// DEBUG_ALLOC functions
Node        *init_node_list();
Node        *print_node_list();

#endif
