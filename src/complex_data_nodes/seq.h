/****
    Seq : sequence on a collection

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef SEQ_H
#define SEQ_H

/*
    Walker on a collection act as a list
*/
typedef struct
{
    long            index;
    struct Node     *coll;
} Seq;

Node *seq(long index, Node *coll);
long seq_size(Node *node);
long seq_index(Node *node);
Node *seq_coll(Node *node);

#endif
