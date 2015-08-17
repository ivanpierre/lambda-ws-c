/****
    Nodes

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "nodes.h"
#include "string.h"
#include "free.h"
#include "writer.h"
/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
    Node *first_node    = NULL;
    Node *last_node     = NULL;
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

// Error signal
Node *error_node = NULL;

// Error* function
void ERROR_STAR(const char *file, int line, const char func[], char *fmt, ...)
{
    char buffer[255];
    va_list args;
    va_start(args, fmt);
    sprintf(buffer, "%s(%d) %s() : %s", file, line, func, fmt);
    error_node = string_sprintf(buffer, args);
    fprintf(stderr, "%s", GET_STRING(error_node));
}

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
                                "namespace"
                                "env_stack",
                                "environment",
                                "api",
                                "function",
                                "lambda",
                                "var",
                                "ref",
                                "future",
                                "agent"
                                "reader",
                                "keyval",
                                "<invalid type>"
                            };

/*
   get type name
*/
String str_type(NodeType type)
{
    int i = 0;
    for(;i < INVALID; i++)
        if(1 << i == type)
            break;
    return str_types[i];
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
    Node *new = malloc(sizeof(Node));
    ASSERT(new, "allocation of node of type %s", str_type(type_of_node));

    Node *tmp = new;
    new = init_node(new, type_of_node); // init_node does link
    if(!new)
    {
        free(tmp);
        ABORT("initialisation of node of type %s", str_type(type_of_node));
    }

    return new;
}

/*
    completely unlink and init node list
*/
bool init_node_list()
{
#ifdef DEBUG_ALLOC
    while(first_node)
    {
        Node *node = first_node;
        first_node = node->next_node;

        // empty allocation
        while(node)
            node = unlink_node(node);
    }
    last_node = NULL;
#endif
    return TRUE;
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
