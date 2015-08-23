/****
    Collections List, array, set and map

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "collection.h"

/*
    create a new empty collection
*/
bool collection(Node **var, enum TYPE type,  Node *alloc)
{
    ASSERT_VAR(var);

    // Create node base
    TRACE("Creating %s", str_type(type));
    ASSERT(new_node(var, type), ERR_INIT, str_type(type));

    // Alloc collection bases
    Collection *coll = (*var)->val = malloc(sizeof(Collection));
    ASSERT(coll, ERR_ALLOC);

    // init collection node
    coll->nodes = NULL;
    coll->max = 0;
    coll->size = 0;
    coll->mut = alloc > 0;

    // Alloc collection array
    TRACE("Allocating %s", str_type(type));
    ASSERT(collection_malloc(var, *var, alloc * sizeof(Node *)), ERR_ALLOC);
    return BOOL_TRUE;

    error_assert:
    unlink_node(var); // Will unalloc all the stuff
    return BOOL_FALSE;
}

/*
    Allocate nodes
*/
bool collection_malloc(Node **var, long size)
{

    // nil is replaced by a new collection
    if((*var)->type == INIL)
    {
        unlink_node(var);
        return collection(var, ILIST, size);
    }

    // collection with positive or 0 allocation
    ASSERT_TYPE(*var, BCOLLECTION, (*node)->type);
    ASSERT(size >= 0, ERR_NEG_ALLOC, size);

    // set new collection values
    Collection *coll = GET_COLLECTION(*node);

    // free previous nodes
    // TODO unalloc all nodes
    if(coll->nodes)
        free(coll->nodes);
    coll->nodes = malloc(sizeof(Node *) * size);
    ASSERT(coll->nodes, ERR_ALLOC);

    coll->max = size;
    return BOOL_TRUE;

    error_assert:
    unlink_node(var); // Will unalloc all the stuff
    return BOOL_FALSE;
}

/*
    Reallocate nodes
*/
bool collection_realloc(Node **node, long size)
{
    ASSERT(*node, ERR_NULL_PTR);
    ASSERT_TYPE(*node, BCOLLECTION, (*node)->type);
    ASSERT(size >= 0, ERR_NEG_ALLOC, size);

    Collection *coll = GET_COLLECTION(*node);

    coll->nodes = realloc(coll->nodes, sizeof(Node *) * size);
    ASSERT(coll->nodes, ERR_ALLOC);

    coll->max = size;
    if(coll->size >= size)
    {
        coll->mut = BOOL_FALSE;
        coll->size = size;
    }
    return BOOL_TRUE;

    error_assert:
    unlink_node(node); // Will unalloc all the stuff
    *node = NULL;
    return BOOL_FALSE;
}

/*
    Free coll
*/
bool collection_free(Node **node)
{
    ASSERT_TYPE(*node, BCOLLECTION, (*node)->type);

    Collection *coll = GET_COLLECTION(*node);
    long size = coll->size;
    for(long i = 0; i < size; i++)
        if(coll->nodes[i])
            unlink_node(&coll->nodes[i]);

    free(*node);
    *node = NULL;
    return BOOL_TRUE;

    error_assert:
    return BOOL_FALSE;
}

/*
    Size of coll
*/
bool collection_size(Node **var, Node *node)
{
    ASSERT_VAR(var);
    ASSERT_Node(node, BSEQUABLE);
    if(node->type == INIL)
        return 0;
    return GET_COLLECTION(node)->size;

    error_assert:
    return 0; // TODO mhhhh faut voir comment
}

/*
    return total sring size of string representation of inner string
*/
static long list_size(long size, char **strings)
{
    long res = 0;
    for(long i = 0; i < size; i++)
        res += strlen(strings[i]) + 1; // counting space
    return res + 1; // for \0
}

/*
    Get first element of coll or nil, nil gives nil
*/
collection_first(Node **var, Node *node)
{
ASSERT(node, ERR_NULL_PTR);
ASSERT_TYPE(node, BCOLLECTION, node->type);
Collection *col = GET_COLLECTION(node);
if(node->type == INIL || coll->size == 0)
return nil;
if(node->type == ILIST)
return link_node(&coll->nodes[coll->size - 1]);
else
return link_node(&coll->nodes[0]);

error_assert:
return NULL; // TODO mhhhh faut voir comment
}

/*
    Get last element of coll or nil, nil gives nil
*/
Node *collection_last(Node **node, Node *node)
{
    ASSERT(node, ERR_NULL_PTR);
    ASSERT_TYPE(node, BCOLLECTION, str_type(node->type));
    if(node->type == INIL || GET_COLLECTION(node)->size == 0)
        return nil;
    if(node->type == ILIST)
        return link_node(GET_COLLECTION(node)->nodes[0]);
    else
        return link_node(GET_COLLECTION(node)->nodes[GET_COLLECTION(node)->size - 1]);
}

/*
    Get nth element of coll or nil, nil gives nil
*/
Node *collection_nth(Node **node, Node *node, long index)
{
    ASSERT(node, ERR_NULL_PTRT);
    ASSERT_TYPE(node, BSEQUABLE, str_type(node->type));
    ASSERT(node->type == INIL || index < GET_COLLECTION(node)->size || index >= 0, ERR_INDEX, index);
    if(node->type == INIL || GET_COLLECTION(node)->size == 0)
        return nil;
    if(node->type == ILIST)
        return link_node(GET_COLLECTION(node)->nodes[GET_COLLECTION(node)->size - index - 1]);
    else
        return link_node(GET_COLLECTION(node)->nodes[index]);
}

/*
    Evaluation of lists
*/
Node *list_eval(Node **node, Node *node, Node *env)
{
    // TODO implement evaluation
    return node;
}

/*
    Evaluation of other collections
*/
Node *collection_eval(Node **node, Node *node, Node *env)
{
    // TODO implement evaluation
    return node;
}
