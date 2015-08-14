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

/*
    Access Collection from Node
*/
static Collection *coll(Node *node)
{
    return (Collection *)(node->val.compl);
}

/*
    Free coll
*/
Node *collection_free(Node *node)
{
    ASSERT_TYPE(node, LIST | ARRAY | MAP | SET,
                "free_coll : error unallocatig bad type : %s",
                str_type(node->type));

    long size = collection_count(node);
    if(size <= 0)
        return NULL;

    for(long i = 0; i < size; i++)
    {
        if(coll(node)->nodes[i])
        {
            unlink_node(coll(node)->nodes[i]);
            coll(node)->nodes[i] = NULL;
        }
    }
    return NULL;
}

/*
    Size of coll
*/
long collection_count(Node *node)
{
    if(!(node && (node->type & (COLLECTION | NIL_NODE))))
    {
        ERROR("get size of bad type : %s", str_type(node->type));
        return -1;
    }
    if(node->type & NIL_NODE)
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
    ASSERT_TYPE(node, ,
                "not a coll %s", str_type(node->type));
    if(node->type & NIL_NODE ||
       coll(node)->size == 0)
        return nil_node;
    if(node->type & LIST)
        return link_node(coll(node)->nodes[coll(node)->size - 1]);
    else
        return link_node(coll(node)->nodes[0]);
}

/*
    Get last element of coll or nil, nil gives nil
*/
Node *collection_last_coll(Node *node)
{
    ASSERT(node, "null pointer");
    ASSERT_TYPE(node, COLLECTION,
                "not a coll %s", str_type(node->type));
    if(node->type & NIL_NODE || GET_COLLECTION(node)->size == 0)
        return nil_node;
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
    ASSERT_TYPE(node, COLLECTION | NIL_NODE,
                "not a coll %s", str_type(node->type));
    ASSERT(node->type & NIL_NODE || index < GET_COLLECTION(node)->size || index >= 0,
            "Index out of bound");
    if(node->type & NIL_NODE || GET_COLLECTION(node)->size == 0)
        return nil_node;
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
    if(node->type & NIL_NODE)
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
    GET_COLLECTION(node)->nodes = realloc(coll, sizeof(Node *) * size);
    ASSERT(GET_COLLECTION(node)->nodes, "realloc_coll : Error alocating collection nodes");
    GET_COLLECTION(node)->max = size;
    return node;
}

/*
    create a new empty collection
*/
Node *collection(NodeType type,  long alloc)
{
    ASSERT(type & COLLECTION, "bad type %s", str_type(type));
    Node *node = new_node(type);
    ASSERT(node, "Error alocating collection node");
    if(collection_malloc(node, alloc))
    {
        GET_COLLECTION(node)->max = GET_COLLECTION(node)->size = 0;
        unlink_node(node);
        return NULL;
    }
    GET_COLLECTION(node)->size = 0;
    return node; // linked by new_node
}

/*
Node        *reduce_coll(Node *init, Node *(*fn)(Node *arg1, Node *arg2), Node *coll);
Node        *filter_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map_coll(Node *(*fn)(Node *node), Node *coll);
Node        *map2_coll(Node *(*fn)(Node *node1, Node *node2), Node *coll1, Node *coll2);
Node        *alloc_clone_coll(Node *coll, long diff);
Node        *assoc_coll(Node *map, Node *keyval);
Node        *dissoc_coll(Node *map, Node *keyval);
Node        *push(Node *coll, Node *elem);
Node        *pop(Node *coll);
Node        *sort(Node coll);
Node        *new_keyval(Node *key, Node *value);
long        pos_coll(Node *coll, Node *search);
*/
