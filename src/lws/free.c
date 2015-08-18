/****
    Free manage memory free

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "free.h"
#include "writer.h"
#include "strings.h"

/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
    Node *first_node    = NULL;
    Node *last_node     = NULL;
#endif

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
    fprintf(stderr, "linking %s\n", str_type(node->type));
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
    fprintf(stderr, "unlinking %s\n", str_type(node->type));
    if(!unlinkable(node))
    {
        if(node->occurrences)
            node->occurrences--;
        if(!node->occurrences)
        {
            fprintf(stderr, "freeing %s\n", str_type(node->type));
#ifdef DEBUG_ALLOC
            if(node == first_node &&
                node == last_node)
                first_node = last_node = NULL;
            else if(first_node == node)
            {
                first_node = node->next_node;
                first_node->previous_node = NULL;
            }
            else if(last_node == node)
            {
                last_node = node->previous_node;
                last_node->next_node = NULL;
            }
            else
            {
                node->next_node->previous_node = node->previous_node;
                node->previous_node->next_node = node->next_node;
            }
#endif
            FREE(node);
        }
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

    switch(log_type(node->type))
    {
        case INIL :
        case ITRUE :
        case IFALSE :
            return node;

        case IKEYWORD :
        case ISYMBOL :
            node = named_free(node);
            break;

        case ISTRING :
            node = string_free(node);
            break;

        case IENV_STACK :
            break;

        case IENVIRONMENT :
            node = env_free(node);
            break;

        case ILIST :
        case IARRAY :
        case IMAP :
        case ISET :
            node = collection_free(node);
            break;

    	case ISEQ :
    	    node = seq_free(node);
    	    break;

        case IKEYVAL :
            node = keyval_free(node);
            break;

        case IFUNCTION :
        case ILAMBDA :
            node = function_free(node);
            break;

//      case REF
//      case ATOM
//      case AGENT
//      case FUTURE
//          break;

        case IVAR :
            node = FREE(node->val.compl);
            break;

        case IREADER :
            node = reader_free(node);
            break;

        case IWRITER :
            node = writer_free(node);
            break;

//      case FRACTION :
//          fraction_free(node->val.compl)
//          break;

        case IINTEGER :
        case IDECIMAL :
            node = number_free(node);
            break;

        default :
            break;
    }
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

void print_stack_trace()
{
    fprintf(stderr, "Stack trace\n");
    fprintf(stderr, "-----------\n");
#ifdef DEBUG_ALLOC
    Node *walk = first_node;
    int i = 1;
    while(walk)
    {
        fprintf(stderr, "%d) %s %ld\n", i++, str_type(walk->type), walk->occurrences);
        fflush(stderr);
        walk = walk->next_node;
    }
#endif
    fprintf(stderr, "-----------\n");
    fflush(stderr);
}

