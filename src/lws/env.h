/****
    Environment header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef ENV_H
#define ENV_H

Node *env_map(Node *node);
Node *env_previous(Node *node);
Node *env_free(Node *node);
Node *env(Node *previous, Node *map);

#endif
