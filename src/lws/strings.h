/****
    String header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef STRINGS_H
#define STRINGS_H

// Strings
bool string            (Node **var, char *value);
bool string_sprintf    (Node **var, char *fmt, ...);
bool string_Q_         (Node **var, Node *node);

/*
    Access string from Node
*/
String GET_STRING       (Node *node);
String GET_ELEM_STRING  (Node *elem, bool (*func)(Node **, Node *));

#endif
