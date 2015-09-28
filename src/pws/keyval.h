/****
    Keyval header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef KEYVAL_H
#define KEYVAL_H

/*
    Key/Values binding
*/
typedef struct
{
	struct Node     *key;
	struct Node     *value;
} KeyVal;

// Constructor
Node *keyval        (Node *key, Node *value);

// accessors
Node *keyval_key    (Node *node);
Node *keyval_value  (Node *node);

// Eval helper
Node *keyval_eval   (Node *node, Node *environment);

#endif
