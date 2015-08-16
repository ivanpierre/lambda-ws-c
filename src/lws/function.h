/****
    Function header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef FUNCTION_H
#define FUNCTION_H

Node *function_is_macro(Node *node);
Node *function_set_macro(Node *node, Node *macro); // nil, false, or else
Node *function_is_special(Node *node);
Node *function_set_special(Node *node, Node *macro); // nil, false, or else
Node *function_clojure(Node *node);
Node *function_args(Node *node);
Node *function_body(Node *node);
void *function_func(Node *node);
Node *function_closure(Node *node);
Node *function_apply(Node *node, Node *args, Node *env); // sequable

#endif
