/****
    Nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "nodes.h"
#include "strings.h"
#include "free.h"
#include "writer.h"

// Error signal
Node *error_node = NULL;

// Error* function
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char buffer[4000];
    va_list args;
    va_start(args, fmt);
    va_start(args, fmt);

    sprintf(buffer, "ERROR !!!! %s(%d) %s() : %s\n", file, line, func, fmt);
    vfprintf(stderr, buffer, args);
    fflush(stderr);
}

// Error* function
void TRACE_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char buffer[4000];
    va_list args;
    va_start(args, fmt);
    va_start(args, fmt);

                        sprintf(buffer, "            %s(%d) %s() : %s\n", file, line, func, fmt);
    // sprintf(buffer, "            %s\n", fmt);
    vfprintf(stdout, buffer, args);
    fflush(stdout);
}

/*
    type of nodes
*/
const NodeType NIL             =   1l << INIL;          // Constant nil value
const NodeType TRUE            =   1l << ITRUE;         // Constant true value
const NodeType FALSE           =   1l << IFALSE;        // Constant false value
const NodeType SYMBOL          =   1l << ISYMBOL;       // Symbol that can be binded in ENVIRONMENT
const NodeType KEYWORD         =   1l << IKEYWORD;      // Constant symbol :key evaluate to itself
const NodeType INTEGER         =   1l << IINTEGER;      // Integer numeric values
const NodeType FRACTION        =   1l << IFRACTION;     // Fractional numeric values
const NodeType DECIMAL         =   1l << IDECIMAL;      // floating numeric values
const NodeType STRING          =   1l << ISTRING;       // String
const NodeType LIST            =   1l << ILIST;         // reversed array (growing from head)
const NodeType ARRAY           =   1l << IARRAY;        // ARRAY
const NodeType MAP             =   1l << IMAP;          // Mapped array of KEYVAL
const NodeType SET             =   1l << ISET;          // Mapped array of keys
const NodeType SEQ             =   1l << ISEQ;          // Walker on a sequence
const NodeType CONS            =   1l << ICONS;         // Walker on two SEQUABLES
const NodeType LAZY            =   1l << ILAZY;         // Walker on a lazy sequence
const NodeType NAMESPACE       =   1l << INAMESPACE;    // Interning place for global symbols
const NodeType ENV_STACK       =   1l << IENV_STACK;    // is a list of ENVIRONMENT
const NodeType ENVIRONMENT     =   1l << IENVIRONMENT;  // is a map of nodes; mapped by SYMBOL
const NodeType API             =   1l << IAPI;          // is a map of FUNCTION; mapped by args (ARRAY)
const NodeType FUNCTION        =   1l << IFUNCTION;     // Function pointer
const NodeType LAMBDA          =   1l << ILAMBDA;       // Body of language to evaluate
const NodeType VAR             =   1l << IVAR;          // Values of global vars (bind)
const NodeType REF             =   1l << IREF;          // CSP managed values
const NodeType FUTURE          =   1l << IFUTURE;       // Asynchronously managed values
const NodeType AGENT           =   1l << IAGENT;        // Agent management through messages
const NodeType READER          =   1l << IREADER;       // Reader implemented in language
const NodeType WRITER          =   1l << IWRITER;       // Writer implemented in language
const NodeType KEYVAL          =   1l << IKEYVAL;       // Binding of key / values for MAP
const NodeType INVALID         =         IINVALID;      // Self explaining... used not to go too far... :D

const NodeType    NUMBER       =   INTEGER | DECIMAL;
const NodeType    NAMED        =   SYMBOL | KEYWORD;
const NodeType    ITERABLE     =   LIST | ARRAY | SEQ;
const NodeType    MAPPED       =   MAP | SET;
const NodeType    COLLECTION   =   ITERABLE | MAPPED;
const NodeType    SEQUABLE     =   COLLECTION | NIL;
const NodeType    INDEXED      =   STRING | ARRAY;
const NodeType    CALLABLE     =   FUNCTION | LAMBDA;

#ifdef DEBUG_ALLOC
    #define NEW_CONST(type) {type, 0l, NULL, NULL, {0}}
#else
    #define NEW_CONST(type) {type, 0l, {0}}
#endif

// global values
static Node nil_val = NEW_CONST(INIL);
static Node true_val = NEW_CONST(ITRUE);
static Node false_val = NEW_CONST(IFALSE);
Node *nil = &nil_val;
Node *false = &false_val;
Node *true = &true_val;


/*
    String representation of types
*/
static char            *str_types[] =
                            {
                                "nil",
                                "true",
                                "false",
                                "symbol",
                                "keyword",
                                "integer",
                                "fraction",
                                "decimal",
                                "string",
                                "list",
                                "array",
                                "map",
                                "set",
                                "sequence",
                                "cons",
                                "lazy",
                                "namespace",
                                "env_stack",
                                "environment",
                                "api",
                                "function",
                                "lambda",
                                "var",
                                "ref",
                                "future",
                                "agent",
                                "reader",
                                "writer",
                                "keyval",
                                "<invalid type1>",
                                "<invalid type2>",
                                "<invalid type3>",
                                "<invalid type4>",
                                "<invalid type5>"
                            };

/*
   get main type order
enum TYPE log_type(NodeType type)
{
    int i = 0;
    for(;i < INVALID; i++)
        if((1l << i) & type)
            break;
    return i;
}
*/

/*
   get main type order
*/
NodeType exp_type(enum TYPE type)
{
    return 1l << type;
}

/*
   get type name
*/
String str_type(enum TYPE type)
{
    return str_types[type];
}

/*
    First initialisation of an allocated node, first link to the data segment
    Return linked node or NIL
*/
static Node *init_node(Node *node, enum TYPE type)
{
    node->type = type;
    node->occurrences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
    if(!last_node)
    {
        node->previous_node = node->next_node = NULL;
        last_node = first_node = node;
    }
    else
    {
        node->previous_node = last_node;
        node->next_node = NULL;
        last_node->next_node = node;
        last_node = node;
    }
#endif
    return link_node(node);
}

/*
    Create a node
    Constructor, return linked
*/
Node *NEW(enum TYPE type_of_node)
{
	TRACE("fait nouveau node %s %ld", str_type(type_of_node), type_of_node);
    Node *new = malloc(sizeof(Node));

    ASSERT(new, "allocation of node of type %s", str_type(type_of_node));

    Node *tmp = new;

    new = init_node(new, type_of_node); // init_node does link
    if(!new)
    {
        free(tmp);
        ABORT("initialisation of node of type %s", str_type(type_of_node));
    }
	TRACE("Node %s créé", str_type(new->type));
    return new;
}

/*
     Compoose functions on an initial value
     All initial and intermediate values should be allocated linked Nodes*.
     At every state, the previous state is unlinked.
     Last value can be anything and should be considered as allocated
     Function list should finish with a NULL, else.... :D
*/
void *thread_node(void *init, ...)
{
    void        *state = link_node(init);
    void        *(*func)(Node *arg) = NULL;
    va_list     funp;

    va_start(funp, init);
    while((func = va_arg(funp, void *(*)(Node *arg))))
    {
        void *new_state = (*func)((Node *)state);
        unlink_node((Node *)state);
        state = new_state;
    }
    return state;
}

/*
    Standard string getter for node function to element
*/
String GET_ELEM_STRING(Node *node, Node *(*func)(Node *))
{
    return thread_node(node, func, &PRINT, &GET_STRING, NULL);
}

/*
    Test falsey
*/
bool FALSE_Q_(Node *node)
{
    return exp_type(node->type) & (NIL | FALSE);
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
    return !FALSE_Q_(node);
}
