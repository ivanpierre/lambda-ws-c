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
Node *NIL = &nil_val;
Node *FALSE = &false_val;
Node *TRUE = &true_val;

/*
    First initialisation of an allocated node, first link to the data segment
    Return linked node or NIL
*/
static bool init_node(Node **var, enum TYPE type)
{
    ASSERT(*var, ERR_NULL_PTR);
    (*var)->type = type;
    (*var)->occurrences = 0; // will be incremented on link
#ifdef DEBUG_ALLOC
    if(!last_node)
    {
        (*var)->previous_node = (*var)->next_node = NULL;
        last_node = first_node = *var;
    }
    else
    {
        (*var)->previous_node = last_node;
        (*var)->next_node = NULL;
        last_node->next_node = *var;
        last_node = *var;
    }
#endif
    return link_node(var);

error_assert:
    return BOOL_FALSE;
}

/*
    Create a node
    Constructor, return linked
*/
bool new_node(Node **var, enum TYPE type_of_node)
{
	TRACE("fait nouveau node %s %ld", str_type(type_of_node), type_of_node);

    if(var) unlink_node(*var);

    *var = malloc(sizeof(Node));
    ASSERT(*var, ERR_ALLOC, str_type(type_of_node));

    ASSERT(init_node(var, type_of_node), ERR_INIT);

	TRACE("Node %s créé", str_type((*var)->type));
    return BOOL_TRUE;

error_assert:
    free(*var);
    *var = NULL;
    return BOOL_FALSE;
}

/*
     Compose functions on an initial value
     All initial and intermediate values should be allocated linked Nodes*.
     At every state, the previous state is unlinked.
     Last value can be anything and should be considered as allocated
     Function list should finish with a NULL, else.... :D
*/
void *THREAD_NODE(void **var, Node *init, ...)
{
    bool        (*func)(void **node, Node *arg) = NULL;
    va_list     funp;

    if(var) unlink_node(*var);
    ASSERT(link_node(var, init), ERR_INIT);

    va_start(funp, init);
    while((func = va_arg(funp, void *(*)(void **var, Node *arg))))
        ASSERT((*func)(var, *res), ERR_INIT);

    return BOOL_TRUE;

error_assert:
    unlink_node(var);
    return BOOL_FALSE;
}

/*
    Test falsey
*/
bool FALSE_Q_(Node *node)
{
    return node->type == INIL || node->type == IFALSE;
}

/*
    Test truthey
*/
bool TRUE_Q_(Node *node)
{
    return !FALSE(node);
}

/*
    Test falsey
*/
bool false_Q_(Node **var, Node *node)
{
    Node *arg = NULL;
    link_node(&arg, node);
    if(*var) unlink_node(*var);

    *var = (arg->type == NIL || arg->type == IFALSE) ? TRUE : NIL;
    unlink_node(&arg);
    return BOOL_TRUE;
}

/*
    Test truthey
*/
bool true_Q_(Node *node)
{
    Node *arg = NULL;
    link_node(&arg, node);
    if(*var) unlink_node(*var);

    *var = (arg->type == NIL || arg->type == IFALSE) ? NIL : TRUE;
    unlink_node(&arg);
    return BOOL_TRUE;
}
