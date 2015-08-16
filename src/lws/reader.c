/****
    General reader to create objects

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"

/*
    Reader
*/
typedef struct
{
    int             (*getc)();
} Reader;

/*
    Unalloc reader
*/
Node *reader_free(Node *node)
{
    ASSERT(node, "free_reader : null environment");
    ASSERT_TYPE(node, READER, "free_reader : Bad type %s", str_type(node->type));
//	if(node->val.function->closure)
//		node->val.function->closure = free_node(node->val.function->closure);
    return NULL;
}



