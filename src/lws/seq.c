/****
    Seq : sequence on a collection

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "seq.h"
#include "collection.h"

/*
    Walker on a collection act as a list
*/
typedef struct
{
    long            index;
    struct Node     *coll;
} Seq;

/*
    Access named data
*/
static Seq *GET_SEQ(Node *node)
{
    return  (Seq *)(node->val.compl);
}

/*
    Constructor
*/
Node *seq(long index, Node *coll)
{
    Node *new_coll = NULL;
    // loop across seq if we make a seq from a seq until we find a collection
    while(coll->type & SEQ)
    {
        /*
            We will manage the CONS, BUNDLE, etc. types
        */
        switch(coll->type)
        {
            case SEQ:
                new_coll = seq_coll(coll);
                index += seq_index(coll);
                unlink_node(coll);
                coll = new_coll;
                break;

            default:
                break;
        }
    }

    // (seq ()) => nil
    if(collection_size(coll) - index <= 0)
    {
        unlink_node(coll);
        return nil;
    }

    // create seq
    Node *node = NEW(SEQ);
    ASSERT(node, "Creation of new seq");
    GET_SEQ(node)->index = index;
    GET_SEQ(node)->coll = coll;
    return(node);
}

/*
    length of the sequence
*/
long seq_size(Node *node)
{
    return collection_size(seq_coll(node)) - seq_index(node);
}

/*
    Get index
*/
long seq_index(Node *node)
{
    if(!node)
    {
        ERROR("Seq null");
        unlink_node(node);
        return -1l;
    }
    return GET_SEQ(node)->index;
}

/*
    Get collection
*/
Node *seq_coll(Node *node)
{
    ASSERT(node, "Seq null");

    return link_node(GET_SEQ(node)->coll);
}

/*
    Free sequence
*/
Node *seq_free(Node *node)
{
    unlink_node(seq_coll(node));
    free(GET_SEQ(node));
    free(node->val.compl);
    free(node);
    return NULL;
}
