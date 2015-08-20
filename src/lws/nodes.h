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
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...);



#define ERROR(fmt, ...) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
    }

#define TRACE(fmt, ...) \
    { \
        TRACE_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
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
    if(!(node && (exp_type(node->type) & (typ)))) \
    { \
        ERROR_STAR(__FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__); \
        return NULL; \
    }

/*
    type of nodes
*/
#define NodeType    long        // on 8 bytes, 64 bits
extern const NodeType    NIL;
extern const NodeType    TRUE;
extern const NodeType    FALSE;
extern const NodeType    SYMBOL;
extern const NodeType    KEYWORD;
extern const NodeType    INTEGER;
extern const NodeType	 FRACTION;
extern const NodeType    DECIMAL;
extern const NodeType    STRING;
extern const NodeType    LIST;
extern const NodeType    ARRAY;
extern const NodeType    MAP;
extern const NodeType    SET;
extern const NodeType    SEQ;
extern const NodeType    CONS;
extern const NodeType    LAZY;
extern const NodeType    NAMESPACE;
extern const NodeType    ENV_STACK;
extern const NodeType    ENVIRONMENT;
extern const NodeType    API;
extern const NodeType    FUNCTION;
extern const NodeType    LAMBDA;
extern const NodeType    VAR;
//extern const NodeType	REF;
//extern const NodeType	FUTURE;
//extern const NodeType  AGENT;
extern const NodeType    READER;
extern const NodeType    WRITER;
extern const NodeType    KEYVAL;
extern const NodeType    INVALID;
extern const NodeType    NUMBER;
extern const NodeType    NAMED;
extern const NodeType    ITERABLE;
extern const NodeType    COLLECTION;
extern const NodeType    SEQUABLE;
extern const NodeType    INDEXED;
extern const NodeType    MAPPED;
extern const NodeType    CALLABLE;

/*
    type of nodes
*/
enum TYPE
{
    INIL             =   0,  // Constant nil value
    ITRUE            =   1,  // Constant true value
    IFALSE           =   2,  // Constant false value
    ISYMBOL          =   3,  // Symbol that can be binded in ENVIRONMENT
    IKEYWORD         =   4,  // Constant symbol :key evaluate to itself
    IINTEGER         =   5,  // Integer numeric values
    IFRACTION        =   6,  // Fractional numeric values
    IDECIMAL         =   7,  // floating numeric values
    ISTRING          =   8,  // String
    ILIST            =   9, // reversed array (growing from head)
    IARRAY           =   10, // ARRAY
    IMAP             =   11, // Mapped array of KEYVAL
    ISET             =   12, // Mapped array of keys
    ISEQ             =   13, // Walker on a sequence
    ICONS            =   14, // Walker on two SEQUABLES
    ILAZY            =   15, // Walker on a lazy sequence
    INAMESPACE       =   16, // Interning place for global symbols
    IENV_STACK       =   17, // is a list of ENVIRONMENT
    IENVIRONMENT     =   18, // is a map of nodes, mapped by SYMBOL
    IAPI             =   19, // is a map of FUNCTION, mapped by args (ARRAY)
    IFUNCTION        =   20, // Function pointer
    ILAMBDA          =   21, // Body of language to evaluate
    IVAR             =   22, // Values of global vars (bind)
    IREF             =   23, // CSP managed values
    IFUTURE          =   24, // Asynchronously managed values
    IAGENT           =   25, // Agent management through messages
    IREADER          =   26, // Reader implemented in language
    IWRITER          =   27, // Writer implemented in language
    IKEYVAL          =   28, // Binding of key / values for MAP
    IINVALID         =   29  // Self explaining... used not to go too far... :D
};

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
#define bool        int
#define Integer     long
#define Decimal     double
#define String      char *
struct  Node; // forward

/*
    Struct of a base node
*/
typedef struct Node
{
    enum TYPE       type;
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
String      str_type(enum TYPE type);
// enum TYPE   log_type(NodeType type);
NodeType    exp_type(enum TYPE type);

// public function for nodes
Node        *link_node(Node *node);
Node        *unlink_node(Node *node);
bool        FALSE_Q_(Node *node);
bool        TRUE_Q_(Node *node);
Node        *NEW(enum TYPE type);
void        *thread_node(void *init, ...);
String      GET_ELEM_STRING(Node *node, Node *(*func)(Node *));
const Node  *NEW_CONST(enum TYPE type_of_node);


// Atom
Node        *var_deref(Node *node); // internal

// DEBUG_ALLOC functions
bool        init_node_list();
void        print_node_list();

#endif
