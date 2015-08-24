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

/*
    Access Keyval from Node
*/
#define KEYVAL(node) ((KeyVal *)(node->val.compl))

/*
    Get the key of keyval
*/
Node *keyval_key(Node *node)
{
	Node *res = link_node(KEYVAL(node)->key);
	unlink_node(node);
	return res;
}

/*
    Get the value of keyval
*/
Node *keyval_value(Node *node)
{
	Node *res = link_node(KEYVAL(node)->value);
	unlink_node(node);
	return res;
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
	ASSERT_TYPE(node, KEYVAL, str_type(node->type));

	unlink_node(keyval_key(node));
	unlink_node(keyval_value(node));
	free(node->val.compl);
	free(node);
	return node;
}

/*
    New keyval
*/
Node *keyval(Node *key, Node *value)
{
	Node *node          = NEW(IKEYVAL); // Create linked node

	ASSERT(node, ERR_CREATE_NEW, IKEYVAL);
	KEYVAL(node)->key   = key; // don't unlink, it's assigned to keyval
	KEYVAL(node)->value = value;

	return node; // Node is already linked
}
