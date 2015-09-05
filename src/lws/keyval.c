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
Node *keyval_free(Node **node)
{
	KeyVal *kv = STRUCT(*node);
	unlink_node(&kv->key);
	unlink_node(&kv->value);
	free(*node);
	*node = NULL;
	return *node;
}

/*
    New keyval
*/
Node *keyval(Node *key, Node *value)
{
	Node *res          = NULL;
	Node *tmp_key      = NULL;
	Node *tmp_value    = NULL;

	ASSERT_NODE(key, tmp_key, INODES);
	ASSERT_NODE(value, tmp_value, INODES);

	res = new_node(IKEYVAL);
	KeyVal *kv = STRUCT(res);
	link_node(&kv->key, tmp_key);
	link_node(&kv->value, tmp_value);

	error_assert:
	unlink_node(&key);
	unlink_node(&value);
	unlink_node(&tmp_key);
	unlink_node(&tmp_value);

	return res; // Node is already linked
}
