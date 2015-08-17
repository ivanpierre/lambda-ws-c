/****
    Free manage memory free

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "free.h"

// Forward
static Node *FREE(Node *node);

/*
    test if linking is applyable
*/
static bool unlinkable(Node *node)
{
    return node && node->type & (NIL | TRUE | FALSE);
}

/*
    create a link to node
    Return Linked node
    Constant elements are not lonked
*/
Node *link_node(Node *node)
{
    if(!unlinkable(node))
        node->occurrences++;
    return node;
}

/*
    Unlink node
    return return NULL on freeing else return node.
    Constant nodes are niot unlinked
*/
Node *unlink_node(Node *node)
{
    if(!unlinkable(node))
    {
        if(node->occurrences)
            node->occurrences--;
        if(!node->occurrences)
            return FREE(node);
    }
    return node;
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
Node *var_free(Node *node);
Node *reader_free(Node *node);
Node *writer_free(Node *node);
Node *seq_free(Node *node);
Node *env_free(Node *node);
Node *number_free(Node *node);

/*
    Free all nodes according to type
*/
static Node *free_node(Node *node)
{
    ASSERT(node, "free_node : NULL node");

    switch(node->type)
    {
        case NIL :
        case TRUE :
        case FALSE :
            return node;

        case KEYWORD :
        case SYMBOL :
            node = named_free(node);
            break;

        case STRING :
            node = string_free(node);
            break;

        case ENV_STACK :
            break;

        case ENVIRONMENT :
            node = env_free(node);
            break;

        case LIST :
        case ARRAY :
        case MAP :
        case SET :
            node = collection_free(node);
            break;

    	case SEQ :
    	    node = seq_free(node);
    	    break;

        case KEYVAL :
            node = keyval_free(node);
            break;

        case FUNCTION :
        case LAMBDA :
            node = function_free(node);
            break;

//      case REF
//      case ATOM
//      case AGENT
//      case FUTURE
//          break;

        case VAR :
            node = FREE(node->val.compl);
            break;

        case READER :
            node = reader_free(node);
            break;

        case WRITER :
            node = writer_free(node);
            break;

//      case FRACTION :
//          fraction_free(node->val.compl)
//          break;

        case INTEGER :
        case DECIMAL :
            node = number_free(node);
            break;

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

