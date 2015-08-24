/****
    General reader to create objects

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

/*
    Unalloc reader
*/
Node *reader_free(Node *node)
{
    ASSERT(node, "free_reader : null environment");
    ASSERT_TYPE(node, READER, "free_reader : Bad type %s", str_type(node->type));
    free(node->val.compl);
    free(node);
    return NULL;
}
