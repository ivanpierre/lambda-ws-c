/****
    Evaluation header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef EVAL_H
#define EVAL_H

Node *(*eval_ptr)(Node *node, Node *environment);
Node *EVAL(Node *node, Node *environment);

#endif
