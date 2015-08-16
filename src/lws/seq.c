/****
    Seq : sequence on a collection

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "seq.h"


/*
    Walker on a collection act as a list
*/
typedef struct
{
    long            index;
    struct Node     *coll;
} Seq;

