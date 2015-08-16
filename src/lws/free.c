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
static Node *keyval_free(Node *node);
static Node *string_free(Node *string);
static Node *named_free(Node *node);
static Node *function_free(Node *node);
static Node *collection_free(Node *node);
static Node *var_free(Node *node);
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
        case NIL :
        case TRUE :
        case FALSE :
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

        case READER :
            reader_free(node);
            break;

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

