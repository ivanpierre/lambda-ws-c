/****
    String header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRING_H
#define STRING_H

// Strings
Node        *string(char *value);
Node        *string_allocate(char *value);
Node        *string_sprintf(char *fmt, ...);
bool        string_QM_(Node *node);
/*
    Access string from Node
*/
#define STRING(node) ((String)(node ? strdup(node->val.compl) : strdup("(null)")))

#endif
