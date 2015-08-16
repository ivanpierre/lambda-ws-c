/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FREE_H
#define FREE_H

Node *link_node(Node *node);
Node *unlink_node(Node *node);

extern Node *(*free_ptr)(Node *node);

#endif


