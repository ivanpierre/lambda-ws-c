/****
    Named : Symbol and keyword header

    Lambda Calculus Workshop
    C version
    Ivan Pierre <ivan@kilroysoft.ch> 2015
*/

#ifndef WRITER_H
#define WRITER_H

/*
    Writer
*/
typedef struct
{
    FILE            *file;
} Writer;

extern char *(*print_ptr)(Node *node, bool readable);

// to current printer
Node *PRINT(Node *node);
Node *PR(Node *node);
Node *PRINTLN(Node *node);
Node *PRN(Node *node);

// to string printers
char *print(Node *node);
char *pr(Node *node);

// to node printers
Node *node_print(Node *node);
Node *node_pr(Node *node);

// constructors
Node *writer(FILE *file);
Node *writer_open_file(Node *name);
Node *writer_stdout();
Node *writer_stderr();

// Set and close currect output
// TODO in appropriate variable
Node *writer_curr(Node *writer);
Node *writer_curr_close();

// Get unnoded data
void *WRITER_FILE(Node *filename);

// Clobal currect writer for now
// TODO manage some other way threoug a language variable...
extern Node *curr;

#endif

