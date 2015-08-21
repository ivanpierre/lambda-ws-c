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
    First initialisation of an allocated node, first link to the data segment
    Return linked node or NIL
*/
static bool init_node(Node **node, enum TYPE type)
{
    ASSERT(*node, ERR_NULL_PTR);
    (*node)->type = type;
    (*node)->occurrences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
    if(!last_node)
    {
        (*node)->previous_node = (*node)->next_node = NULL;
        last_node = first_node = *node;
    }
    else
    {
        (*node)->previous_node = last_node;
        (*node)->next_node = NULL;
        last_node->next_node = *node;
        last_node = *node;
    }
#endif
    return link_node(node);

error_assert:
    return BOOL_FALSE;
}

/*
    Create a node
    Constructor, return linked
*/
bool NEW(Node **node, enum TYPE type_of_node)
{
	TRACE("fait nouveau node %s %ld", str_type(type_of_node), type_of_node);
    *node = malloc(sizeof(Node));
    ASSERT(*new, ERR_ALLOC, str_type(type_of_node));

    ASSERT(init_node(new, type_of_node, ERR_INIT);

	TRACE("Node %s créé", str_type(new->type));
    return BOOL_TRUE;

error_assert:
    *node = NULL;
    return BOOL_FALSE;
}

/*
     Compoose functions on an initial value
     All initial and intermediate values should be allocated linked Nodes*.
     At every state, the previous state is unlinked.
     Last value can be anything and should be considered as allocated
     Function list should finish with a NULL, else.... :D
*/
void *thread_node(void **node, Node *init, ...)
{
    bool        (*func)(void **node, Void *arg) = NULL;
    va_list     funp;

    va_start(funp, init);

    ASSERT(link_node(node, init), ERR_INIT);
    while((func = va_arg(funp, void *(*)(void **node, void *arg))))
        ASSERT((*func)(node, *res), ERR_INIT);

    return BOOL_TRUE;

error_assert:
    *res = NULL;
    return BOOL_FALSE;
}

/*
    Standard string getter for node function to element
*/
bool GET_ELEM_STRING(void **res, Node *elem, Node *(*func)(void **, Node *))
{
    return thread_node(res, elem, func, &PRINT, &GET_STRING, NULL);
}

/*
    Test falsey
*/
bool FALSE(Node *node)
{
    return node->type == NIL || node->type == FALSE);
}

/*
    Test truthey
*/
bool TRUE(Node *node)
{
    return !FALSE(node);
}
