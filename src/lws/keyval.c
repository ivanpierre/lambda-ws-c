/****
   Key value pairs

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include "nodes.h"
#include "keyval.h"

/*
    Key/Values binding
*/
typedef struct
{
    struct Node     *key;
    struct Node     *value;
} KeyVal;

/*
    Access Keyval from Node
*/
#define KEYVAL(node) ((KeyVal *)(node->val.compl))

/*
    Get the key of keyval
*/
Node *keyval_get_key(Node *node)
{
    Node *res = link_node(KEYVAL(node)->key);
    unlink_node(node);
    return res;
}

/*
    Get the value of keyval
*/
Node *keyval_get_value(Node *node)
{
    Node *res = link_node(KEYVAL(node)->value);
    unlink_node(node);
    return res;
}

/*
    Free keyval
*/
Node *keyval_free(Node *node)
{
    ASSERT_TYPE(node, KEYVAL,
                "error unallocatig bad type : %s",
                str_type(node->type));

    free_node(keyval_get_key(node));
    free_node(keyval_get_value(node));
    return NULL;
}

/*
    New keyval
*/
Node *keyval_new(Node *key, Node *value)
{
	Node *node = new_node(KEYVAL); // Create linked node

	if(!node)
	{
		ABORT("cannor create new keyval");
	}

	KEYVAL(node)->key = key; // don't unlink, it's massed tokeyval
	KEYVAL(node)->value = value;

	return node; // Node is already linked
}
