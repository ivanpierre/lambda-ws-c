/****
    Free manage memory free

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "free.h"

/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
    Node *first_node    = NULL;
    Node *last_node     = NULL;
#endif

// Forward
static Node *FREE(Node **node);

/*
    test if linking is applyable
*/
static bool unlinkable(Node *node)
{
    return !node ||  bin_type(node->type) & (BUNLINKABLE);
}

/*
    create a link to node
    Return Linked node
    Constant elements are not lonked
*/
Node *link_node(Node **var, Node *node)
{
    TRACE("linking %s", str_type(node->type));
    if(*var) unlink_node(var);

    ASSERT(node, ERR_NULL_PTR);
    if(!unlinkable(node))
        node->occurrences++;
    *var = node;
    return *var;

error_assert:
    *var = NULL;
    return *var;
}

/*
    Unlink node
    return return NULL on freeing else return node.
    Constant nodes are niot unlinked
*/
Node *unlink_node(Node **node)
{
    TRACE("unlinking %s", str_type(node->type));
    if(!unlinkable(node))
    {
        if(node->occurrences)
            node->occurrences--;
        if(!node->occurrences)
        {
            TRACE("freeing %s", str_type(node->type));
#ifdef DEBUG_ALLOC
            if(node == first_node &&
                node == last_node)
                first_node = last_node = NULL;
            else if(first_node == node)
            {
                ASSERT(node->next_node, "Error in node memory management");
                first_node = node->next_node;
                first_node->previous_node = NULL;
            }
            else if(last_node == node)
            {
                ASSERT(node->previous_node, "Error in node memory management");
                last_node = node->previous_node;
                last_node->next_node = NULL;
            }
            else
            {
                ASSERT(node->next_node && node->previous_node, "Error in node memory management");
                node->next_node->previous_node = node->previous_node;
                node->previous_node->next_node = node->next_node;
            }
#endif
            FREE(node);
            node = NULL;
        }
    }
    return node;
}

bool collection_free (Node **var);
bool named_free (Node **var);
bool string_free (Node **var);
bool env_free (Node **var);
bool seq_free (Node **var);
bool keyval_free (Node **var);
bool function_free (Node **var);
bool reader_free (Node **var);
bool writer_free (Node **var);
bool number_free (Node **var);

/*
    Free all nodes according to type
*/
static Node *free_node(Node **node)
{
    ASSERT_VAR(node, bin_type((*node)->type));

    switch((*node)->type)
    {
        case INIL :
        case ITRUE :
        case IFALSE :
            return *node;

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


        case IVAR :
            node = FREE(node->val.compl);
            break;

        case IREADER :
            node = reader_free(node);
            break;

        case IWRITER :
            node = writer_free(node);
            break;

        case IINTEGER :
        case IDECIMAL :
            node = number_free(node);
            break;

        case FRACTION :
        case REF:
        case ATOM:
        case AGENT:
        case FUTURE:
            break;
    }
    return NULL;
}

/*
    def pointer for free
*/
Node *(*free_ptr)(Node **node) = &free_node;

/*
    FREE unalloc node using pointer
*/
static Node *FREE(Node **node)
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

void print_node_stack()
{
    TRACE("Stack trace");
    TRACE("-----------");
#ifdef DEBUG_ALLOC
    Node *walk = first_node;
    int i = 1;
    while(walk)
    {
        TRACE("%d) %s %ld", i++, str_type(walk->type), walk->occurrences);
        fflush(stderr);
        walk = walk->next_node;
    }
#endif
    TRACE("-----------");
    fflush(stderr);
}

