/****
   Key value pairs

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "keyval.h"
#include "free_internal.h"

/*
    Get the key of keyval
*/
Node *keyval_key(Node *node)
{
	ACCESS_NODE(KeyVal, key, IKEYVAL, INODES);
}

/*
    Get the value of keyval
*/
Node *keyval_value(Node *node)
{
	ACCESS_NODE(KeyVal, value, IKEYVAL, INODES);
}

/*
    Evaluation of other keyval
*/
Node *keyval_eval(Node *node, Node *environment)
{
	return node;
}

/*
    Free keyval
*/
Node *keyval_free(Node *node)
{
	KeyVal *kv = STRUCT(node);
	unlink_node(kv->key);
	unlink_node(kv->value);
	free(node);
	return NULL;
}

/*
    New keyval
*/
Node *keyval(Node *key, Node *value)
{
	Node *res          = NULL;

	ASSERT_NODE(key, INODES);
	ASSERT_NODE(value, INODES);

	res = new_node(IKEYVAL);
	KeyVal *kv = STRUCT(res);
	ASSIGN(kv->key, key);
	ASSIGN(kv->value, value);

	error_assert:
	unlink_node(key);
	unlink_node(value);

	return res; // Node is already linked
}
