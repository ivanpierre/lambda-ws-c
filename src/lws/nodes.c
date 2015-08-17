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

    strcpy(buffer, "%s(%d) %s() : ");
    strcat(buffer, fmt);
    fprintf(stderr, buffer, file, line, func, fmt, args);
}

/*
    type of nodes
*/
const NodeType NIL             =   1l;       // Constant nil value
const NodeType TRUE            =   1l << 1;  // Constant true value
const NodeType FALSE           =   1l << 2;  // Constant false value
const NodeType SYMBOL          =   1l << 3;  // Symbol that can be binded in ENVIRONMENT
const NodeType KEYWORD         =   1l << 4;  // Constant symbol :key evaluate to itself
const NodeType INTEGER         =   1l << 5;  // Integer numeric values
//const NodeType FRACTION        =   1l << 6;  // Fractional numeric values
const NodeType DECIMAL         =   1l << 7;  // floating numeric values
const NodeType STRING          =   1l << 8;  // String
const NodeType LIST            =   1l << 9; // reversed array (growing from head)
const NodeType ARRAY           =   1l << 10; // ARRAY
const NodeType MAP             =   1l << 11; // Mapped array of KEYVAL
const NodeType SET             =   1l << 12; // Mapped array of keys
const NodeType SEQ             =   1l << 13; // Walker on a sequence
const NodeType CONS            =   1l << 14; // Walker on two SEQUABLES
const NodeType LAZY            =   1l << 15; // Walker on a lazy sequence
const NodeType NAMESPACE       =   1l << 16; // Interning place for global symbols
const NodeType ENV_STACK       =   1l << 17; // is a list of ENVIRONMENT
const NodeType ENVIRONMENT     =   1l << 18; // is a map of nodes; mapped by SYMBOL
const NodeType API             =   1l << 19; // is a map of FUNCTION; mapped by args (ARRAY)
const NodeType FUNCTION        =   1l << 20; // Function pointer
const NodeType LAMBDA          =   1l << 21; // Body of language to evaluate
const NodeType VAR             =   1l << 22; // Values of global vars (bind)
//const NodeType REF             =   1l << 23; // CSP managed values
//const NodeType FUTURE          =   1l << 24; // Asynchronously managed values
//const NodeType AGENT           =   1l << 25; // Agent management through messages
const NodeType READER          =   1l << 26; // Reader implemented in language
const NodeType WRITER          =   1l << 27; // Writer implemented in language
const NodeType KEYVAL          =   1l << 28; // Binding of key / values for MAP
const NodeType INVALID         =        30l; // Self explaining... used not to go too far... :D

const NodeType    NUMBER          =   INTEGER | DECIMAL;
const NodeType    NAMED           =   SYMBOL | KEYWORD;
const NodeType    ITERABLE        =   LIST | ARRAY | SEQ;
const NodeType    MAPPED          =   MAP | SET;
const NodeType    COLLECTION      =   ITERABLE | MAPPED;
const NodeType    SEQUABLE        =   COLLECTION | NIL;
const NodeType    INDEXED         =   STRING | ARRAY;
const NodeType    CALLABLE        =   FUNCTION | LAMBDA;

#ifdef DEBUG_ALLOC
    #define NEW_CONST(type) {type, 0l, NULL, NULL, {0}}
#else
    #define NEW_CONST(type) {type, 0l, {0}}
#endif

// global values
static Node nil_val = NEW_CONST(NIL);
static Node true_val = NEW_CONST(TRUE);
static Node false_val = NEW_CONST(FALSE);
Node *nil = &nil_val;
Node *false = &false_val;
Node *true = &true_val;


/*
    String representation of types
*/
static char            *str_types[] =
                            {
                                "mheu",
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
*/
enum TYPE log_type(NodeType type)
{
    int i = 0;
    for(;i < INVALID; i++)
        if((1l << i) & type)
            break;
    return i + 1;
}

/*
   get type name
*/
String str_type(NodeType type)
{
    int i = 0;
    for(;i < INVALID; i++)
        {
        // fprintf(stderr, "type = %ld, %ld = %d = %s\n", type, (1l << i), i + 1, str_types[i + 1]);
        if((1l << i) & type)
            break;
        }
    return str_types[i + 1];
}

/*
    First initialisation of an allocated node, first link to the data segment
    Return linked node or NIL
*/
static Node *init_node(Node *node, NodeType type)
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
Node *NEW(NodeType type_of_node)
{
	fprintf(stderr, "fait nouveau node %s %ld\n", str_type(type_of_node), type_of_node);
    Node *new = malloc(sizeof(Node));

    ASSERT(new, "allocation of node of type %s", str_type(type_of_node));

    Node *tmp = new;

    new = init_node(new, type_of_node); // init_node does link
    if(!new)
    {
    	fprintf(stderr, "Erreur niouveau Node %s\n", str_type(type_of_node));

        free(tmp);
        ABORT("initialisation of node of type %s", str_type(type_of_node));
    }
	fprintf(stderr, "Node %s créé\n____________\n", str_type(new->type));
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
    return node->type & (NIL | FALSE);
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
    return !FALSE_Q_(node);
}
