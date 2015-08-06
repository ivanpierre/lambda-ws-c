/****
    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "nodes.h"

Node *string(Node *node);
Node *eval(Node *node, Node *env);

#endif
