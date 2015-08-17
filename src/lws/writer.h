/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef WRITER_H
#define WRITER_H

extern Node *(*print_ptr)(Node *node, bool readable);

Node *PRINT(Node *node);
Node *PR(Node *node);

Node *print(Node *node);
Node *pr(Node *node);

Node *writer(FILE *file);
FILE *writer_file(Node *node);

extern Node *curr;

#endif

