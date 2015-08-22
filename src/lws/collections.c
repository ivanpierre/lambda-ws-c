/****
    colls sets and maps

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
    Collection : Array, List, Map and Set
*/
typedef struct
{
    bool            mutable;
    long            size;
    long            max;
    struct Node     **nodes;
} Collection;

/*
    Access Collection from Node
*/
static Collection *GET_COLLECTION(Node *node)
{
    return (Collection *)(node->val.compl);
}

/*
    create a new empty collection
*/
bool collection(Node **node, enum TYPE type,  long alloc)
{
    ASSERT_TYPE((*node), BCOLLECTION, type);

    // Create node base
    ASSERT(NEW(node, type), ERR_INIT, str_type(type));
    ASSERT((*node), ERR_CREATE_NEW, str_type(type));

    // Alloc collection bases
    TRACE("Creating %s", str_type(type));
    Collection *coll = (*node)->val.compl = malloc(sizeof(Collection));
    ASSERT(coll, ERR_ALLOC);

    // init collection node
    coll->nodes = NULL;
    coll->max = 0;
    coll->size = 0;
    coll->mutable = alloc > 0;

    // Alloc collection array
    TRACE("Allocating %s", str_type(type));
    ASSERT(collection_malloc(node, alloc * sizeof(Node *)), ERR_ALLOC);
    return BOOL_TRUE;

error_assert:
    unlink_node(node); // Will unalloc all the stuff
    *node = NULL;
    return BOOL_FALSE;
}

/*
    Allocate nodes
*/
bool collection_malloc(Node **node, long size)
{
    // nil is replaced by a new collection
    if((*node)->type == INIL)
    {
        unlink_node(node);
        return collection(node, ILIST, size);
    }

    // collection with positive or 0 allocation
    ASSERT_TYPE(*node, BCOLLECTION, (*node)->type);
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
    unlink_node(node); // Will unalloc all the stuff
    *node = NULL;
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
        coll->mutable = BOOL_FALSE;
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
long collection_size(Node *node)
{
    ASSERT(node, ERR_NULL_PTR);
    ASSERT_TYPE(node, BSEQUABLE, node->type);
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
Node *collection_first(Node *node)
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
Node *collection_last(Node *node)
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
Node *collection_nth(Node *node, long index)
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
Node *list_eval(Node *node, Node *env)
{
    // TODO implement evaluation
    return node;
}

/*
    Evaluation of other collections
*/
Node *collection_eval(Node *node, Node *env)
{
    // TODO implement evaluation
    return node;
}

/*
Node        *collection_reduce(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *collection_filter(Node *(*fn)(Node *node), Node *coll);
Node        *collection_map(Node *(*fn)(Node *node), Node *coll);
Node        *collection_map2(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *collection_alloc_clone(Node *coll, long size);
Node        *collection_assoc(Node *map, Node *keyval);
Node        *collection_dissoc(Node *map, Node *keyval);
Node        *collection_push(Node *coll, Node *elem);
Node        *collection_pop(Node *coll);
Node        *collection_sort(Node coll);
Node        *keyval_new(Node *key, Node *value);
long        collection_get(Node *coll, Node *search);
long        collection_get_def(Node *coll, Node *search, Node *default);
*/
