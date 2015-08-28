/****
    Function header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FUNCTION_H
#define FUNCTION_H

/*
    Functions
*/
typedef struct
{
    Node                *is_macro;
    Node                *is_special;
    Node                *closure; // as a previous Environment
    Node                *args;    // seq of symbols to create local Environment
    // for function call manage variadic arguments
    // and to coerce types
    union
    {
        Node            *(*func) (Node *args, ...);
        Node            *body;
    } func;
} Function;

Node *function_is_macro(Node *node);
Node *function_set_macro(Node *node, Node *macro); // nil, FALSE, or else
Node *function_is_special(Node *node);
Node *function_set_special(Node *node, Node *macro); // nil, FALSE, or else
Node *function_clojure(Node *node);
Node *function_args(Node *node);
Node *function_body(Node *node);
void *function_func(Node *node);
Node *function_closure(Node *node);
Node *function_apply(Node *node, Node *args, Node *environment); // sequable

#endif
