/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NAMED_H
#define NAMED_H

/*
    Named : symbols and kerywords
*/
typedef struct
{
    struct Node     *ns;
    struct Node     *name;
} Named;

// symbols, keywords
Node        *symbol(Node *ns, Node *name);
Node        *symbol_Q_(Node *node);
Node        *symbol_eval(Node *node, Node *environment);
Node        *keyword(Node *ns, Node *name);
Node        *keyword_Q_(Node *node);
Node        *named_name(Node *node);
Node        *named_ns(Node *node);

#endif
