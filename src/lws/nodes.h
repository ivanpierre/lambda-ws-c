/****
    Types

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NODES_H
#define NODES_H

#define BOOL_FALSE 0
#define BOOL_TRUE (!BOOL_FALSE)

/*
    Errors and assertions
*/
extern struct Node *error_node;
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...);

#define ERROR(fmt, ...) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
    }

#define ABORT(fmt, ...) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        return NULL; \
    }

#define ASSERT(cond, fmt, ...) \
    if(!(cond)) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        return NULL; \
    }

#define ASSERT_TYPE(node, typ, fmt, ...) \
    if(!(node && (node->type & (typ)))) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        return NULL; \
    }

/*
    type of nodes
*/
typedef enum
{
    NIL             =   1,       // Constant nil value
    TRUE            =   1 << 2,  // Constant true value
    FALSE           =   1 << 3,  // Constant false value
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
//  AGENT           =   1 << 24, // Agent management through messages
    READER          =   1 << 25, // Reader implemented in language
    WRITER          =   1 << 26, // Writer implemented in language
    KEYVAL          =   1 << 27, // Binding of key / values for MAP
    INVALID         =        28, // Self explaining... used not to go too far... :D

    NUMBER          =   INTEGER | DECIMAL,

    NAMED           =   SYMBOL | KEYWORD,

    ITERABLE        =   LIST |
                        ARRAY |
                        SEQ,

    COLLECTION      =   LIST |          // Walk on list's nodes
                        ARRAY |         // Walk on array's nodes
                        MAP |           // Walk on map's keyvals. [key value]
                        SET |           // Walk on
                        SEQ,            // returns itself's ref

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
#define bool    int
#define Integer long
#define Decimal double
#define String  char *
struct  Node; // forward

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
        Integer     integer;        // Integer as long
        Decimal     decimal;        // Floats as double
        void        *compl;         // all node details
    } val;
} Node;

// global values
extern Node *nil;
extern Node *true;
extern Node *false;

/*
    Main functions pointers FREE, EVAL, PRINT
*/
extern Node *(*eval_ptr)(Node *node, Node *env);

// Node *FREE(Node *node); // called by unlink_node
Node *EVAL(Node *node, Node *env);

// public function for types
String      str_type(NodeType type);

// public function for nodes
Node        *link_node(Node *node);
Node        *unlink_node(Node *node);
bool        FALSE_Q_(Node *node);
bool        TRUE_Q_(Node *node);
Node        *NEW(NodeType type);
void        *thread_node(void *init, ...);
String      GET_ELEM_STRING(Node *node, Node *(*func)(Node *));
const Node  *NEW_CONST(NodeType type_of_node);


// Atom
Node        *var_deref(Node *node); // internal

// DEBUG_ALLOC functions
bool        init_node_list();
void        print_node_list();

#endif
