/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef NAMED_H
#define NAMED_H

// symbols, keywords
Node        *symbol(Node *ns, Node *name);
Node        *keyword(Node *ns, Node *name);
bool        symbol_QM_p(Node *node);
bool        keyword_QM_(Node *node);
Node        *named_get_name(Node *node);
Node        *named_get_ns(Node *node);
Node        *symbol_eval(Node *node, Node *env);

#endif
