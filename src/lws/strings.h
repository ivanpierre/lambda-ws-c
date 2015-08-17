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
Node        *string_Q_(Node *node);

/*
    Access string from Node
*/
String GET_STRING(Node *node);


#endif
