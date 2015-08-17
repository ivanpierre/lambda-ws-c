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
void print_stack_trace();

extern Node *(*free_ptr)(Node *node);
/*
    double linked list of nodes
*/
#ifdef DEBUG_ALLOC
    extern Node *first_node;
    extern Node *last_node;
#endif


#endif

