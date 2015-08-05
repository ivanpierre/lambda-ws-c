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
    NIL_NODE        =   1,       // Constant nil value
    TRUE_NODE       =   1 << 2,  // Constant true value
    FALSE_NODE      =   1 << 3,  // Constant false value
    SYMBOL          =   1 << 4,  // Symbol that can be binded in ENVIRONMENT
    KEYWORD         =   1 << 5,  // Constant symbol :key evaluate to itself
    INTEGER         =   1 << 6,  // Integer numeric values
//	FRACTION        =   1 << 7,  // Fractional numeric values
    DECIMAL         =   1 << 8,  // floating numeric values
    STRING          =   1 << 9,  // String
    LIST            =   1 << 10, // reversed array (growing from head)
    ARRAY           =   1 << 11, // ARRAY
    MAP             =   1 << 12, // Mapped array of KEYVAL
    SET             =   1 << 13, // Mapped array of keys
    SEQ             =   1 << 14, // Walker on a collection
    NAMESPACE       =   1 << 15, // Interning place for global symbols
    ENV_STACK       =   1 << 16, // is a list of ENVIRONMENT
    ENVIRONMENT     =   1 << 17, // is a map of nodes, mapped by SYMBOL
    API             =   1 << 18, // is a map of FUNCTION, mapped by args (ARRAY)
    FUNCTION        =   1 << 19, // Function pointer
    LAMBDA          =   1 << 20, // Body of language to evaluate
    VAR             =   1 << 21, // Values of global vars (bind)
//	REF             =   1 << 22, // CSP managed values
//	FUTURE          =   1 << 23, // Asynchronously managed values
//  AGENT           =   1 << 24,  // Agent management through messages
    READER          =   1 << 25, // Reader for a syntax
    KEYVAL          =   1 << 26, // Binding of key / values for MAP
    INVALID         =        27,  // Self explaining... used not to go too far... :D

    NUMBER          =   INTEGER | DECIMAL,

    NAMED           =   SYMBOL | KEYWORD,

    SEQUABLE        =   STRING |        // Walk on string's characters
                        LIST |          // Walk on list's nodes
                        ARRAY |         // Walk on array's nodes
                        MAP |           // Walk on map's keyvals. [key value]
                        SEQ |           // returns itself's ref
                        NAMESPACE |     // Walk on namespace's symbols
                        ENV_STACK |     // Walk on binding's environments
                        ENVIRONMENT |   // Walk on environment's bindings as keyvals [symbol value]
                        API |           // Walk on function's implementations as keyval [args function]
                        LAMBDA,         // Walk on body's Nodes

    INDEXED         =   STRING |        // Get char at position
                        ARRAY,          // Get Node at postion

    MAPPED          =   MAP |
                        SET |
                        NAMESPACE |
                        ENVIRONMENT |
                        API,

    CALLABLE        =   FUNCTION |
                        LAMBDA
} NodeType;  // WIP

/*
    String representation of types
*/
// extern char *str_types[];

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
    struct Node     *map;
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
    Symbol
*/
typedef struct
{
    struct Node     *ns;
    struct Node     *name;
} Symbol;

/*
    Reader
*/
typedef struct
{
    int             (*getc)();
} Reader;

/*
    Writer
*/
typedef struct
{
    int             (*putc)();
} Writer;

/*
    Functions
*/
typedef struct
{
    bool                is_macro;
    bool                is_special;
    struct Node         *closure; // MAP
    struct Node         *args;    // LIST
    union
    {
        struct Node     *(*func) (struct Node *args, ...);
        struct Node     *body;
    } func;
} Function;

/*
    Struct of a base node
*/
typedef struct Node
{
    NodeType        type;
    long            occurrences;
#ifdef DEBUG_ALLOC
    struct Node     *previous_node;
    struct Node     *next_node;
#endif
    union
    {
        Integer     integer;
        Decimal     decimal;
        String      string;
        Symbol      *symbol;
        Collection  *coll;
        KeyValue    *keyval;
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

// Strings
Node        *new_string(char *value);
Node        *new_string_allocate(char *value);
Node        *sprintf_string(char *fmt, ...);
bool        stringp(Node *node);
String      get_string(Node *string);
String      get_formated_string(Node *string);
Node        *free_string(Node *string); // internal
Node        *string_string(Node *string); // internal
Node        *eval_symbol(Node *node, Node *env);

// symbols, keywords
Node        *new_symbol(Node *ns, char *value);
Node        *new_keyword(Node *ns, char *value);
bool        symbolp(Node *node);
bool        keywordp(Node *node);
String      get_symbol_name(Node *s);
String      get_symbol_formatted_name(Node *s);
Node        *free_symbol(Node *string); // internal
Node        *string_symbol(Node *string); // internal

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
Node        *pop(Node *coll);
Node        *sort(Node coll);
long        pos_coll(Node *coll, Node *search);
Node        *reduce_coll(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *filter_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map2_coll(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *new_empty_coll(NodeType type, long alloc);
Node        *eval_coll(Node *node, Node *env);
Node        *eval_list(Node *node, Node *env);
Node        *eval_keyval(Node *node, Node *env);

// Keyval
Node        *free_keyval(Node *node); // internal
Node        *string_keyval(Node *node); // internal

// Env
Node        *free_env(Node *node); // internal
Node        *string_env(Node *node); // internal

// Reader
Node        *free_reader(Node *node); // internal
Node        *string_reader(Node *node); // internal

// Atom
Node        *deref_var(Node *node); // internal

// DEBUG_ALLOC functions
bool        init_node_list();
void        print_node_list();

#endif
