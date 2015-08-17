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
    struct Node     *mutable;
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
    Free coll
*/
Node *collection_free(Node *node)
{
    ASSERT_TYPE(node, COLLECTION, "free_coll : error unallocatig bad type : %s", str_type(node->type));

    long size = collection_size(node);
    if(size <= 0)
        return NULL;

    for(long i = 0; i < size; i++)
        if(GET_COLLECTION(node)->nodes[i])
            unlink_node(GET_COLLECTION(node)->nodes[i]);

    free(node);
    return NULL;
}

/*
    Size of coll
*/
long collection_size(Node *node)
{
    if(!(node && (node->type & (SEQUABLE | NIL))))
    {
        ERROR("get size of bad type : %s", str_type(node->type));
        return -1;
    }
    if(node->type & NIL)
        return 0;
    return GET_COLLECTION(node)->size;
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
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION, "not a coll %s", str_type(node->type));
    if(node->type & NIL || GET_COLLECTION(node)->size == 0)
        return nil;
    if(node->type & LIST)
        return link_node(GET_COLLECTION(node)->nodes[GET_COLLECTION(node)->size - 1]);
    else
        return link_node(GET_COLLECTION(node)->nodes[0]);
}

/*
    Get last element of coll or nil, nil gives nil
*/
Node *collection_last(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION,
                "not a coll %s", str_type(node->type));
    if(node->type & NIL || GET_COLLECTION(node)->size == 0)
        return nil;
    if(node->type & LIST)
        return link_node(GET_COLLECTION(node)->nodes[0]);
    else
        return link_node(GET_COLLECTION(node)->nodes[GET_COLLECTION(node)->size - 1]);
}

/*
    Get nth element of coll or nil, nil gives nil
*/
Node *collection_nth(Node *node, long index)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION | NIL,
                "not a coll %s", str_type(node->type));
    ASSERT(node->type & NIL || index < GET_COLLECTION(node)->size || index >= 0,
            "Index out of bound");
    if(node->type & NIL || GET_COLLECTION(node)->size == 0)
        return nil;
    if(node->type & LIST)
        return link_node(GET_COLLECTION(node)->nodes[GET_COLLECTION(node)->size - index - 1]);
    else
        return link_node(GET_COLLECTION(node)->nodes[index]);
}

/*
    Allocate nodes
*/
Node *collection_malloc(Node *node, long size)
{
    ASSERT(node, "null pointer");
    if(node->type & NIL)
        return collection(LIST, size);
    ASSERT_TYPE(node, COLLECTION, "bad type %s", str_type(node->type));
    ASSERT(size >= 0, "Allocation cannot be negative %ld", size);
    GET_COLLECTION(node)->nodes = malloc(sizeof(Node *) * size);
    ASSERT(GET_COLLECTION(node)->nodes, "Error alocating collection nodes");
    GET_COLLECTION(node)->max = size;
    return node;
}

/*
    Reallocate nodes
*/
Node *collection_realloc(Node *node, long size)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION,
                "bad type %s",
                str_type(node->type));
    ASSERT(size >= 0, "reallocation cannot be negative %ld", size);
    GET_COLLECTION(node)->nodes = realloc(GET_COLLECTION(node)->nodes, sizeof(Node *) * size);
    ASSERT(GET_COLLECTION(node)->nodes, "realloc_coll : Error alocating collection nodes");
    GET_COLLECTION(node)->max = size;
    return node;
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
    create a new empty collection
*/
Node *collection(NodeType type,  long alloc)
{
    ASSERT(type & COLLECTION, "bad type %s", str_type(type));
    Node *node = NEW(type);
    ASSERT(node, "Error alocating collection node");
    if(collection_malloc(node, alloc))
    {
        GET_COLLECTION(node)->max = GET_COLLECTION(node)->size = 0;
        unlink_node(node);
        return NULL;
    }
    GET_COLLECTION(node)->size = 0;
    return node; // linked by node
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
