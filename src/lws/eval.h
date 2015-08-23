/****
    Evaluation header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef EVAL_H
#define EVAL_H

bool *(*eval_ptr)(Node **var, Node *node, Node *env);
bool EVAL(Node **var, Node *node, Node *env);

#endif
