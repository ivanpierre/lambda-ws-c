/****
    Var : variable boxing

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef VAR_H
#define VAR_H

/*
    Var
*/
typedef struct
{
	Node *symbol;  // reference symbol
	Node *value;   // Bounded value
} Var;

Node *var               (Node *symbol, Node *value);
Node *var_symbol        (Node *node);
Node *var_value         (Node *node);
Node *var_bound_Q_      (Node *node);
Node *var_set_value     (Node *node, Node *value);

#endif
