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
/*
    double linked list of nodes
*/
#if defined(DEBUG_ALLOC)
    Node *first_node    = NULL;
    Node *last_node     = NULL;
#endif

// global values
Node *nil_node = NULL;
Node *true_node = NULL;
Node *false_node = NULL;

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
    fprintf(stderr, "%s", STRING(error_node));
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
    test if linking is applyable
*/
static bool unlinkable(Node *node)
{
    return node && node->type & (NIL_NODE | TRUE_NODE | FALSE_NODE);
}

/*
    create a link to node
    Return Linked node or NIL
*/
Node *link_node(Node *node)
{
    if(!unlinkable(node))
        node->occurrences++;
    return node;
}

/*
    Unlink node
    return NIL or subsisting node
*/
Node *unlink_node(Node *node)
{
    if(!unlinkable(node))
    {
        if(node->occurrences)
            node->occurrences--;
        if(!node->occurrences)
            FREE(node);
    }
    return NULL;
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
       Extern definition of free functions
       These should be used nowhere else that here
*/

Node *keyval_free(Node *node);
Node *string_free(Node *string);
Node *named_free(Node *node);
Node *function_free(Node *node);
Node *collection_free(Node *node);
// Node *fraction_free(Node *node);
// Node *env_free(Node *node);

/*
    Free all nodes according to type
*/
static Node *free_node(Node *node)
{
    ASSERT(node, "free_node : NULL node");

    switch(node->type)
    {
        case NIL_NODE :
        case TRUE_NODE :
        case FALSE_NODE :
            return NULL;

        case KEYWORD :
        case SYMBOL :
            node = named_free(node);
            break;

        case STRING :
            node = string_free(node);
            break;

        case ENV_STACK :
        case ENVIRONMENT :
            break;

        case LIST :
        case ARRAY :
        case MAP :
        case SET :
            node = collection_free(node);
            break;

//    	case SEQ :
//    	    free_coll(node);
//    	    break;

        case KEYVAL :
            node = keyval_free(node);
            break;

        case FUNCTION :
        case LAMBDA :
            node = function_free(node);
            break;

//      case REF
//      case FUTURE
        case VAR :
            node = FREE(node->val.compl);
            break;

//      case READER :
//          free_reader(node);
//          break;

//      case FRACTION :
//            fraction_free(node->val.compl)
//          break;

        case INTEGER :
        case DECIMAL :
        default :
            break;
    }

    unlink_node(node); // we can now free the main node
    return NULL;
}

/*
    def pointer for free
*/
Node *(*free_ptr)(Node *node) = &free_node;

/*
    FREE unalloc node using pointer
*/
static Node *FREE(Node *node)
{
    return (*free_ptr)(node);
}

/*
    Create a node
    Constructor, return linked
*/
Node *new_node(NodeType type_of_node)
{
    Node *new = malloc(sizeof(Node));
    ASSERT(new, "create_node : Error : allocation of node of type %s", str_type(type_of_node));

    Node *tmp = new;
    new = init_node(new, type_of_node); // init_node does link
    if(!new)
    {
        free(tmp);
        ABORT("create_node : Error : initialisation of node of type %s", str_type(type_of_node));
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
            node = free_node(node);
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
String get_string(Node *node, Node *(*func)(Node *))
{
    return thread_node(node, func, &PRINT, &STRING, NULL);
}
