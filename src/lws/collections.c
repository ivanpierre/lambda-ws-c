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
Node *free_coll(Node *node)
{
    ASSERT_TYPE(node, LIST | ARRAY | MAP | SET,
                "free_coll : error unallocatig bad type : %s",
                str_type(node->type));

    long size = size_coll(node);
    if(size <= 0)
        return NULL;

    for(long i = 0; i < size; i++)
    {
        if(coll(node)->nodes[i])
        {
            free_node(coll(node)->nodes[i]);
            coll(node)->nodes[i] = NULL;
        }
    }
    return NULL;
}

/*
    Size of coll
*/
long size_coll(Node *node)
{
    if(!(node && (node->type & SEQUABLE)))
    {
        ERROR("size_coll : get size of bad type : %s", str_type(node->type));
        return -1;
    }
    if(node->type & NIL_NODE)
        return 0;
    if(!coll(node))
    {
        ERROR("size_coll : not allocated coll");
        return -1;
    }
    return coll(node)->size;
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
Node *first_coll(Node *node)
{
    ASSERT(node, "first_coll : null pointer");
    ASSERT_TYPE(node, SEQUABLE,
                "first_coll : not a coll %s", str_type(node->type));
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
Node *last_coll(Node *node)
{
    ASSERT(node, "last_coll : null pointer");
    ASSERT_TYPE(node, SEQUABLE,
                "last_coll : not a coll %s", str_type(node->type));
    if(node->type & NIL_NODE ||
       coll(node)->size == 0)
        return nil_node;
    if(node->type & LIST)
        return link_node(coll(node)->nodes[0]);
    else
        return link_node(coll(node)->nodes[coll(node)->size - 1]);
}

/*
    Get nth element of coll or nil, nil gives nil
*/
Node *nth(Node *node, long index)
{
    ASSERT(node, "nth_coll : null pointer");
    ASSERT_TYPE(node, LIST | ARRAY | MAP | SET | NIL_NODE,
                "nth_coll : not a coll %s", str_type(node->type));
    ASSERT(index < coll(node)->size || index < 0,
            "nth_coll : Index out of bound");
    if(node->type & NIL_NODE || coll(node)->size == 0)
        return nil_node;
    if(node->type & LIST)
        return link_node(coll(node)->nodes[coll(node)->size - index - 1]);
    else
        return link_node(coll(node)->nodes[index]);
}

/*
    Allocate nodes
*/
Node *malloc_coll(Node *node, long size)
{
    ASSERT(node, "malloc_coll : null pointer");
    ASSERT_TYPE(node, LIST | ARRAY | MAP | SET,
                "alloc_coll : bad type %s",
                str_type(node->type));
    ASSERT(size >= 0, "malloc_coll : Allocation cannot be negative %ld", size);
    coll(node)->nodes = malloc(sizeof(Node *) * size);
    ASSERT(coll(node)->nodes, "malloc_coll : Error alocating collection nodes");
    coll(node)->max = size;
    return node;
}

/*
    Reallocate nodes
*/
Node *realloc_coll(Node *node, long size)
{
    ASSERT(node, "realloc_coll : null pointer");
    ASSERT_TYPE(node, LIST | ARRAY | MAP | SET,
                "realloc_coll : bad type %s",
                str_type(node->type));
    ASSERT(size >= 0, "realloc_coll : Allocation cannot be negative %ld", size);
    coll(node)->nodes = realloc(coll, sizeof(Node *) * size);
    ASSERT(coll(node)->nodes, "realloc_coll : Error alocating collection nodes");
    coll(node)->max = size;
    return node;
}

/*
    create a new empty collection
*/
Node *new_empty_coll(NodeType type,  long alloc)
{
    ASSERT(type & (LIST | ARRAY | MAP | SET), "new_empty_coll : bad type %s", str_type(type));
    Node *node2 = new_node(type);
    ASSERT(node2, "new_empty_coll : Error alocating collection node");
    if(malloc_coll(node2, alloc))
    {
        coll(node2)->max = coll(node2)->size = 0;
        unlink_node(node2);
        return NULL;
    }
    coll(node2)->size = 0;
    return node2;
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
