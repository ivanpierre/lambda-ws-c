/****
   Key value pairs

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <string.h>
#include "nodes.h"

/*
    Key/Values binding
*/
typedef struct
{
    struct Node     *key;
    struct Node     *value;
} KeyValue;

/*
    Access Keyval from Node
*/
static KeyValue *keyval(Node *node)
{
    return (KeyValue *)(node->val.compl);
}

/*
    Free keyval
*/
Node *free_keyval(Node *node)
{
    ASSERT_TYPE(node, KEYVAL,
                "free_keyval : error unallocatig bad type : %s",
                str_type(node->type));

    free_node(keyval(node)->key);
    free_node(keyval(node)->value);
    return NULL;
}

