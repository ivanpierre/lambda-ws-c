/****
    Keyval header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef KEYVAL_H
#define KEYVAL_H

Node *keyval_key(Node *node);
Node *keyval_value(Node *node);
Node *keyval(Node *key, Node *value);

#endif
