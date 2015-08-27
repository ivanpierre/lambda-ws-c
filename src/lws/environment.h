/****
    Environment header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

/*
    Environment. There is only uninterned (local) symbol, so we can
    only keep the symbol name
*/
typedef struct
{
	struct Node *previous; // Environment
	struct Node *map; // map [Symbol Value]
} Environment;


// Constructor
Node *environment           (Node *previous, Node *map);

// Accessors
Node *environment_previous  (Node *node);
Node *environment_map       (Node *node);

#endif
