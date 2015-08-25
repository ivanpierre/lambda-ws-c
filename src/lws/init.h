/****
    Initialization header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef ENV_H
#define ENV_H

/*
    Environment. There is only uninterned (local) symbol, so we can
    only keep the symbol name
*/
typedef struct
{
	struct Node     *previous; // Environment
	struct Node     *map; // map [String Value]
} Environment;

Node *environment           (Node **var, Node *previous, Node *map);
Node *env_free      (Node **var);

Node *env_previous  (Node **var, Node *node);
Node *env_map       (Node **var, Node *node);

#endif
